// Module main.h
// header for 4(5) order Rosenbroke method for
// differential-algebraic equation system solving.
#include <string>
#include <stdio.h>
using namespace std;

#define MAX_N 20 /* Maximum number of equations of all type */
                 /* in the system should be solved          */
 
extern string input_filename;
extern string output_filename;

typedef struct Matrix_and_Vectors{
	double ** A;  // Rosenbroke matrix at fixed time step;
	double ** B;  // Jacobies matrix at fixed time step;
	double *  r;  // Rosenbroke vector r at fixed time step;
	double *  k;  // Rosenbroke vectors k at fixed stage;
	double *  C;  // Rosenbroke vectors C at fixed stage;

	double *  y;  // Rosenbroke solution approximation
	              // at fixed stage;

	double *  z;  // Rosenbroke vector z at fixed stage;
	double *  z1;  // Rosenbroke vector z at the first stage;
	double    t;  // Rosenbroke time at fixed stage;
	double    tau;// Rosenbroke time step at fixed stage;
	int       N;  // Number of overall system equations;
	int       M;  // Number of differential equations;
} StepParameters;

extern double error;    // relative error at fixed time step

extern double tolerance;// absolute tolerance for 
                        // time step adjustment

extern double tau_min;  // minimum time step
extern double tau_max;  // maximum time step
extern double save_time;// time step for result savings


/* Kinetic parameters of right hand functions */
extern double P1,  P2,  P3,  P4,  P5;
extern double P6,  P7,  P8,  P9,  P10;
extern double P11, P12, P13, P14, P15;
extern double P16, P17, P18, P19, P20;


/* The function MainLoop calculates solution of          */
/* differential-algebraic equation system from t till    */
/* final_t with initial time step of tau and initial     */
/* data vector y of N components. Computed data are      */
/* saved in file with path output_filename once every    */
/* save_time. The path output_filename is defined in     */
/* main.h. Variable save_time is global, written by      */
/* the function ReadData.                                */
/*                                                       */
/* Features:                                             */
/*   N is the number of overall equations in              */
/*   differential-algebraic equation system should be    */
/*   solved. M is the number of DIFFERENTIAL equations   */
/*   in the system concerned. (Hence M should be smaller */
/*   than N. The maximum value of N is restricted by     */
/*   MAX_N defined in main.h                             */
void MainLoop (double * y,
			   int      N,
			   int      M,
			   double   tau,
			   double   t,
			   double   final_t);
