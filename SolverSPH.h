#pragma once
#include <cmath>
struct SolverSPH
{
	int iter;
	double total_time;
	double H, H2, H3, H4, H5, H6, H7, H8, H9;
	double rho0, K_gas, M, G, eta, sigma, sigma_l;
	double EPS, BOUND_DAMPING;
	double Lx, Ly, dt;
	int N, Nmax;

	double* x, * y, * vx, * vy, * fx, * fy, * fx2, * fy2, * p, * rho;
	double* fxT, * fyT;
	double* mark;
	double* cR, * cG, * cB;

	SolverSPH();

	void initial_state();
	void memory_allocation(int);

	void computeDensityPressure();
	void computePressureViscosityForces();
	void computeTensionForce();

	void integrate(int);

	void solve();
};

