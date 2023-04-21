#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <iomanip> 
#include <string> 
#include <fstream> 
#include <cmath>
#include <omp.h>
#ifdef _WIN32
#include "windows.h"
#endif
using namespace std;

#define pause cout << "Pause at line " << __LINE__ << endl; system("pause"); 
#define VarLog(var) cout << #var << " " << var << endl;

void mainGL(int argc, char** argv);


int width, height;
double Lx, Ly;
double Xleft, Xright, Ybottom, Ytop;
double* glPosX, * glPosY;
double H;
int N;

#include "SolverSPH.h"
SolverSPH* SPH;
#include "tools.h"
LogSystem Log;

int main(int argc, char **argv) 
{

	Log.init(argc, argv);
	omp_set_num_threads(2); // 2 cores
	Log << "Number of working cores: " << omp_get_max_threads() << endl;

	SPH = new SolverSPH;

	//parameters
	SPH->rho0 = 1000.0;
	SPH->K_gas = 3.0;
	SPH->H = H = 16;
	SPH->H2 = pow(H, 2);
	SPH->H3 = pow(H, 3);
	SPH->H4 = pow(H, 4);
	SPH->H5 = pow(H, 5);
	SPH->H6 = pow(H, 6);
	SPH->H7 = pow(H, 7);
	SPH->H8 = pow(H, 8);
	SPH->H9 = pow(H, 9);
	SPH->M = 25;
	SPH->G = -9.81 * 1.0;
	SPH->eta = 85.5;
	SPH->sigma = -10;
	SPH->sigma_l = 0.0001;
	SPH->EPS = H; // boundary epsilon
	SPH->BOUND_DAMPING = -0.5;
	SPH->Nmax = 500;

#define L 1.5
	SPH->Lx = Lx = 800 * L;
	SPH->Ly = Ly = 600 * L;
	SPH->dt = 0.008;

	SPH->initial_state();

	//size of the window in pixels
	width = 800;	
	height = 600;

	Xleft = 0;  	
	Xright = Lx;
	Ybottom = 0;	
	Ytop = Ly;

	glPosX = SPH->x;
	glPosY = SPH->y;
	N = SPH->N;


	// тут начинается вся движуха 
#pragma omp parallel
	{


		// Core 0 is doing computing
		if (omp_get_thread_num() == 0)
		{ 
			while (true) 
			{
				SPH->solve();

				if (SPH->iter % 1000 == 0 || SPH->iter == 1)
				{
					//cout << "something to print" << endl;
				}
			} // end of main loop
		}

		// Core 1 is doing OpenGL drawing
		if (omp_get_thread_num() == 1)
		{ 
			mainGL(argc, argv);
		}

	} //end of parallel block
	return 0;
}

