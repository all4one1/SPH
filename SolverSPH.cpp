#include "SolverSPH.h"
#include <vector>
#include <random>
#include <iostream> 
#include "Wkernel.h"
#define Pi acos(-1.0)
#define Rij(i,j) sqrt(pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2))

using std::cout;
using std::endl;

SolverSPH::SolverSPH()
{
	iter = 0;
	total_time = 0;
}
void SolverSPH::initial_state()
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<> distrib(0, 1);

	std::vector<double> X, Y;
	int iter = 0;
	for (double xx = EPS; xx <= Lx * 0.4; xx += H) {
		for (double yy = EPS; yy <= Ly * 0.8; yy += H) {
			if (iter >= Nmax) break;

			float jitter = 0;
			jitter = distrib(generator);
			
			X.push_back(xx + jitter);
			Y.push_back(yy + jitter);
			
			iter++;
			
		}
	}
	N = X.size();

	
	memory_allocation(N);
	for (int i = 0; i < N; i++)
	{
		x[i] = X[i];
		y[i] = Y[i];
	}
}
void SolverSPH::memory_allocation(int n)
{
	//memory allocation
	auto alloc = [&n](double** f)
	{
		//*f = (double*)malloc(sizeof(double) * N);
		*f = new double[n];
		for (int l = 0; l < n; l++)
			(*f)[l] = 0.0;
	};

	alloc(&x);
	alloc(&y);
	alloc(&vx);
	alloc(&vy);
	alloc(&fx);
	alloc(&fy);
	alloc(&fx2);
	alloc(&fy2);
	alloc(&p);
	alloc(&rho);
	alloc(&fxT);
	alloc(&fyT);
}


void SolverSPH::computeDensityPressure()
{
	for (int i = 0; i < N; i++) {
		p[i] = 0.0;
		rho[i] = 0.0;
		for (int j = 0; j < N; j++) 
		{ 
			double dx = x[j] - x[i];
			double dy = y[j] - y[i];
			double r = sqrt(dx * dx + dy * dy);
			if (r < H)
			{
				rho[i] += M * wP6D2(r);
			}
		}
		p[i] = K_gas * (rho[i] - rho0);
		//p[i] = K_gas/10 *rho0* (pow(rho[i]/rho0, 7.0) - 1.0);
	}

}
void SolverSPH::computePressureViscosityForces()
{
	double coef;
	double FxP, FyP, FxV, FyV, FxG, FyG;
	double nx, ny, curv, nn;

	//F - force
	//P - pressure
	//V - viscosity
	//G - gravity
	//n means normal vector (или хз че)

	for (int i = 0; i < N; i++) 
	{
		
		FxP = FyP = FxV = FyV = FxG = FyG  = 0.0;
		nx = ny = curv = nn = 0;

		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			double dx = x[j] - x[i];
			double dy = y[j] - y[i];
			double r = sqrt(dx * dx + dy * dy);


			if (r < H)
			{
				//Pressure force
				coef = -M * (p[i] + p[j]) / (2.0 * rho[j]) * wSpikyD2Grad(r);
				FxP += coef * (dx / r);
				FyP += coef * (dy / r);

				//Viscous force
				coef = eta * M / rho[j] * wViscD2Lapl(r);
				FxV += coef * (vx[j] - vx[i]);
				FyV += coef * (vy[j] - vy[i]);

			}

		}

		FxG = 0.0;
		FyG = G * rho[i];
		fx[i] = FxP + FxV;
		fy[i] = FyP + FyV + FyG;
	}
}
void SolverSPH::computeTensionForce()
{
	double coef;
	double nx, ny, curv, nn;
	double fxW, fyW, W;


	for (int i = 0; i < N; i++)
	{

		nx = ny = curv = nn = 0;

		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			double dx = x[j] - x[i];
			double dy = y[j] - y[i];
			double r = sqrt(dx * dx + dy * dy);

			if (r < H)
			{
				//Surface tension, Part 1/3
				coef = M / rho[j];
				curv += coef * wP6D2Lapl(r);

				coef = M / rho[j] * wP6D2Grad(r);
				nx += coef * (dx / r);
				ny += coef * (dy / r);
			}

		}

		//Surface tension, Part 2/3
		nn = sqrt(nx * nx + ny * ny);
		if (nn > sigma_l) {
			coef = -sigma * curv / nn;
			fxT[i] = coef * nx;
			fyT[i] = coef * ny;
		}
	}


	//Surface tension, Part 3/3
	for (int i = 0; i < N; i++)
	{
		//fx[i] += fxT[i]; 	fy[i] += fyT[i]; continue;
		fxW = fyW = W = 0.0;

		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			double dx = x[j] - x[i];
			double dy = y[j] - y[i];
			double r = sqrt(dx * dx + dy * dy);
			if (r > H) {
				coef = wP6D2(r);
				W += coef;
				fxW += coef * fxT[j];
				fyW += coef * fyT[j];
			}

		}
		fxW = fxW / W;
		fyW = fyW / W;
		fx[i] += fxW;
		fy[i] += fyW;
	}

}

void SolverSPH::integrate(int type)
{
	for (int i = 0; i < N; i++) {
		// forward Euler integration
		if (type == 0) {
			vx[i] += dt * fx[i] / rho[i];
			vy[i] += dt * fy[i] / rho[i];
			x[i] += dt * vx[i];
			y[i] += dt * vy[i];
		}
		//Verlet 
		if (type == 1) {
			vx[i] += dt * 0.5 * (fx[i] + fx2[i]) / rho[i];
			vy[i] += dt * 0.5 * (fy[i] + fy2[i]) / rho[i];
			x[i] += vx[i] * dt + fx2[i] * dt * dt;
			y[i] += vy[i] * dt + fy2[i] * dt * dt;
		}

		// enforce boundary conditions
		if (x[i] - EPS < 0.0)
		{
			vx[i] *= BOUND_DAMPING;
			x[i] = EPS;
		}
		if (x[i] + EPS > Lx)
		{
			vx[i] *= BOUND_DAMPING;
			x[i] = Lx - EPS;
		}
		if (y[i] - EPS < 0.0)
		{
			vy[i] *= BOUND_DAMPING;
			y[i] = EPS;
		}
		if (y[i] + EPS > Ly)
		{
			vy[i] *= BOUND_DAMPING;
			y[i] = Ly - EPS;
		}
	}
}

void SolverSPH::solve() 
{

	computeDensityPressure();
	computePressureViscosityForces();
	//computeTensionForce();
	integrate(1);

	//swap arrays
	double *temp; 	
	temp = fx; 	fx = fx2; 	fx2 = temp; 
	temp = fy; 	fy = fy2; 	fy2 = temp;

	iter++;
	total_time += dt;
}