// Module main.c
// 4(5) order Rosenbroke method for
// differential-algebraic equation system solving.
// It contains main loop implementation for 
// computations and result savings.
//
// It was built 05.11.2002 by Starojilova T.K.
// Last modification 18.11.2002.

#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
#include <math.h>
#include <time.h>
#include "main.h"
#include "error.h"
#include "config.h"
#include "matrix.h"
#include "rsnbrk.h"

string output_filename = "./solution.dat";/* File name for   */
                                              /* solution saving */
string input_filename = "./INI.DAT";

double error;// realitve error at fixed time step

double tolerance;// absolute tolerance for 
                 // time step adjustment

double tau_min;  // minimum time step
double tau_max;  // maximum time step
double save_time;// time step for result savings

/* Cinetic parameters of right hand functions */
double P1,  P2,  P3,  P4,  P5;
double P6,  P7,  P8,  P9,  P10;
double P11, P12, P13, P14, P15;
double P16, P17, P18, P19, P20;

int ReadData (const char    * path,
	  int     * N, 
	  int     * M, 
	  double  * t, 
	  double  * tau,
	  double  * final_t,
	  double ** y)
{
	CConfig c;
	if (!c.load(path)) {
		SendErrorMsg (errlog_name, "Can't open input file", ERROR);
		return 0;
	}
	char   y_name[6];
	int    i, N_size;

	SendErrorMsg (errlog_name, "Start Rosenbroke", INIT);
	errlog_name = c.get("errorlog");
	output_filename = c.get("output");

	N_size    = c.getInt("N");
	*N        = N_size;
	*M        = c.getInt("M");
	tolerance = c.getDouble("Tolerance");

	*y = vector_ini (N_size);
	if (y == NULL){
		return 0;
	}

	for (i = 0; i < N_size; i++){
		sprintf (y_name, "y%d", i);
		*(*y + i) = c.getDouble(y_name);
	}

	*t        = c.getDouble("initial_t");
	*tau      = c.getDouble("tau");
	*final_t  = c.getDouble("final_t");
	tau_min   = c.getDouble("tau_min");
	tau_max   = c.getDouble("tau_max");
	save_time = c.getDouble("save_time");

	P1  = c.getDouble("P1");
	P2  = c.getDouble("P2");
	P3  = c.getDouble("P3");
	P4  = c.getDouble("P4");
	P5  = c.getDouble("P5");
	P6  = c.getDouble("P6");
	P7  = c.getDouble("P7");
	P8  = c.getDouble("P8");
	P9  = c.getDouble("P9");
	P10  = c.getDouble("P10");
	P11  = c.getDouble("P11");
	return 1;
}

void SaveData (string const &path,
	const double * data,
	int      data_size,
	double   t,
	double   error)
{
   int    i;
   FILE * output = fopen (path.c_str(), "a+");

   if (output == NULL){
	   printf ("Can't open file %s\n", path.c_str());
	   return;
   }
   fprintf (output, "%g ", t);
   for (i = 0; i < data_size; i++)
	   fprintf (output, "%g ", *data++);
   fprintf (output, "%g\n", error);
   fclose (output);
}

int main (int argc, char **argv){
      int N ;
      int M;
      double t;
      double tau;
      double final_t;
      clock_t start = clock();
      double *y = NULL;
	  const char *input = argc > 1 ? argv[1] : input_filename.c_str();

      if (!ReadData (input, &N, &M, &t,
                    &tau, &final_t, &y))
         return 1;

      SendErrorMsg (errlog_name, "Start Rosenbroke", INIT);
      if (N < 1 || N > MAX_N){
         SendErrorMsg (errlog_name,
                      "Inappropriate size of full system",
                      ERROR);
         return 1;
      }
      if (M < 0 || M > N){
         SendErrorMsg (errlog_name,
                      "Inappropriate number of differential equations",
                      ERROR);
         return 1;
      }

      MainLoop (y, N, M, tau, t, final_t);
      clock_t end = clock();
      printf("Total %lld ticks\n", (long long)(end - start));
      SendErrorMsg  (errlog_name, "Finish Rosenbroke", FINAL);
      free (y);
    return 0;
}

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
/*   N is the number of overall equations in             */
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
               double   final_t){
      StepParameters CurrentValues;
      double current_save_time = 0;

      char ooo[512];
      sprintf(ooo, "%g %g %g %g %g %g %g %g %g %g %g", P1, P2, P3, P4,
       P5, P6, P7, P8, P9, P10, P11); 
      SendErrorMsg (output_filename, ooo, INIT);

      CurrentValues.A = matrix_ini (N);
      CurrentValues.B = matrix_ini (N);
      CurrentValues.r = vector_ini (N);
      CurrentValues.k = vector_ini (6 * N);
      CurrentValues.C = vector_ini (5 * N);
      CurrentValues.y = vector_ini (N);
	  CurrentValues.z1 = vector_ini (N);
      CurrentValues.z = vector_ini (N);

      if (CurrentValues.A == NULL || CurrentValues.z == NULL || 
         CurrentValues.r == NULL || CurrentValues.k == NULL ||
         CurrentValues.C == NULL || CurrentValues.y == NULL || 
         CurrentValues.B == NULL || CurrentValues.z1 == NULL 
		 || t > final_t)
         return;

      CurrentValues.t   = t;
      CurrentValues.tau = tau;
      CurrentValues.N   = N;
      CurrentValues.M   = M;

      error             = 0;
	  current_save_time = 0;

      while (CurrentValues.t <= final_t && error < 0.1){
            if (CurrentValues.t >= current_save_time){
               current_save_time += save_time;
               SaveData (output_filename, y, CurrentValues.N, CurrentValues.t, error);
            }
            error = RosenbrokeStep (&CurrentValues, y);
	    for (int i = 0; i < N; i++) {
		if (y[i] < 0 || y[i] > 10) {
			error = 100000;
		}
	    }
      }
/*
	  _snprintf(str_o,1000,"Current.N %d\n",CurrentValues.N);
	  SendErrorMsg  (errlog_name, str_o, ERROR);*/
      SaveData (output_filename, y, CurrentValues.N, CurrentValues.t, error);
      free (CurrentValues.z);
	  free (CurrentValues.z1);
      free (CurrentValues.y);
      free (CurrentValues.C);
      free (CurrentValues.k);
      free (CurrentValues.r);
      matrix_free (CurrentValues.B, N);
      matrix_free (CurrentValues.A, N);
}
