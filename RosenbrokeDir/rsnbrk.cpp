// Module rsnbrk.c
// implementation of the one step of Rosenbroke
// method, error evaluation and time step
// adjustments.
//
// It was built 05.11.2002 by Starojilova T.K.
// Last modification 19.11.2002.

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "main.h"
#include "rhfns.h"
#include "matrix.h"
#include "rsnbrk.h"

int REC_NUM = 0;// Number of recursive call of
                // the function RosenbrokeStep

double KSI  = 1;// Ratio of updated step tau
                // to previous step tau

/* alpha coefficiens of Rosenbroke method */
/* (see documentations)                   */
static double alpha2[2] = { 0.386,
                            0.386};
static double alpha3[3] = { 0.1460747075254355,
                            6.39252924745645291e-2,
                            0.21};
static double alpha4[4] = {-0.33081150366772792,
                            0.711151025168282737,
                            0.24966047849944518,
                            0.3438};
static double alpha5[5] = {-2.3081419476726651,
                            0.907511048562394942,
                            2.15520871692307812,
                            0.24542218218719202983,
                            1.0};
static double alpha6[6] = { 2.4286337654669860,
                           -0.3827487337647842714,
                           -1.8557203309295777,
                            0.55983529922737593097,
                            0.25,
                            1.0};

static MethodCoeffs Alpha[5] = {{1, alpha2},
                                {2, alpha3},
                                {3, alpha4},
                                {4, alpha5},
                                {5, alpha6}};


/* gamma coefficients of Rosenbroke method */
/* (see documentations)                    */

static double gamma2[2] = {-0.3543,
                           -0.1043};
static double gamma3[3] = {-0.165402505268193,
                           1.289749473180703e-2,
                           0.09749498946361403};
static double gamma4[4] = { 1.526849173006465,
                           -0.5336562887504555,
                           -1.279392884256009,
                           -0.0361999999999995};
static double gamma5[6] = { 4.736775713139651,
                           -1.290259782327179,
                           -4.010929004785266,
                            0.3144131170401839,
                            4.30673899e-8};
static double gamma6[6] = {-2.080189494180933,
                            0.595762355676682271,
                            1.701617798267259,
                            0.088514519835879833,
                           -0.3786761399271284,
                            0.1770290396717597};

static MethodCoeffs Gamma[5] = {{1, gamma2},
                                {2, gamma3},
                                {3, gamma4},
                                {4, gamma5},
                                {5, gamma6}};


/* The function FirstCalcJacobyMatrix calculates method     */
/* matrix A, Jacobies matrix B, vector r and the first      */
/* vector z for time step of Rosenbroke method at the first */
/* trace.                                                   */
void FirstCalcJacobyMatrix (StepParameters * CurrentValues);

/* The function CalcJacobyMatrix calculates method matrix A,*/
/* Jacobies matrix B, vector r and the first vector z  for  */
/* time step of Rosenbroke method at the repeated trace     */
/* with time step ksi times smaller previous one.           */
void CalcJacobyMatrix (StepParameters * CurrentValues,
                       double           ksi);

/* The function CalcCi calculates vector C at the current   */
/* stage of Rosenbroke method and puts its elements into    */
/* the storage pointed by Ci.                               */
void CalcCi (double         * ki,
             double         * Ci,
             StepParameters * CurrentValues);

/* The function UpdateY_and_t recalculates solution Y and   */
/* current time CurrentValues->t at the current stage of    */
/* Rosenbroke method.                                       */
void UpdateY_and_t (StepParameters * CurrentValues,
                    double         * y,
                    MethodCoeffs   * Alpha,
                    double           time);

/* The function UpdateZ recalculates vector z for the next  */
/* stage of Rosenbroke method.                              */
void UpdateZ (StepParameters * CurrentValues,
              double         * y,
              MethodCoeffs   * Gamma);

/* The function CalcError calculates error of Rosenbroke    */
/* method and returns its relative value. The absolute      */
/* error are stored in abs_eps.                             */
double CalcError (double * vector,
                  double * exact_vector,
                  int      Vector_size,
                  double * abs_eps);

/* The function UpdateTau recalculates time step for        */
/* Rosenbroke method using absolute error value -- abs_eps  */
/* and puts new time step in CurrentValues->tau.            */
/* UpdateTau returns ration of new time step to previous    */
/* one.                                                     */
double UpdateTau (StepParameters * CurrentValues,
                  double           abs_eps);

/* The function RosenbrokeStep implements one step          */
/* computations using Rosenbroke method. Solution values at */
/* previous time step are given by y.                       */
/*                                                          */
/* Features:                                                */
/*    At the end of RosenbrokeStep vectors CurrentValues->y */
/*    and y contain updated solution at the time sroed in   */
/*    CurrentValues->t.                                     */
double RosenbrokeStep (StepParameters * CurrentValues,
                       double         * y){

      int      N    = CurrentValues->N;
      int      i;
      double   time = CurrentValues->t;
      double   tau  = CurrentValues->tau;
      double * y1   = vector_ini (CurrentValues->N);
      double * k    = CurrentValues->k;
      double * C    = CurrentValues->C;
      double * k1, * k2, * k3, * k4, * k5;
      double   eps, abs_eps;

      if (y1 == NULL)
         return 10;
      CopyVectors (CurrentValues->y, y, N);

      if (REC_NUM == 0)
         FirstCalcJacobyMatrix (CurrentValues);
	  else
         CalcJacobyMatrix (CurrentValues, KSI);

      Solve_LinSys (CurrentValues->A, CurrentValues->z, k, CurrentValues->N);
      for (i = 0; i < 5; i++){
          CalcCi (k, C, CurrentValues);
          UpdateY_and_t (CurrentValues, y, Alpha + i, time);
          UpdateZ (CurrentValues, y, Gamma + i);
          k += N;
          C += N;
          Solve_LinSys (CurrentValues->A, CurrentValues->z, k,
                        CurrentValues->N);
      }
      k1               = k - 5 * N;
      k2               = k - 4 * N;
      k3               = k - 3 * N;
      k4               = k - 2 * N;
      k5               = k - N;

      for (i = 0; i < N; i++)
          y1[i] = y[i] + 0.34844427128605321482 * *k1++ + 
                  0.21301362191189803772 * *k2++ -
                  0.15410253266231898945 * *k3++ +
                  0.47132077939149609711 * *k4++ -
                  0.12867613992712836020 * *k5++ + 0.25 * *k++;

      eps = CalcError (CurrentValues->y, y1, N, &abs_eps);
	  REC_NUM++;
	  KSI = UpdateTau (CurrentValues, abs_eps);

      if (KSI < 1.0 ){
         free (y1);
         CurrentValues->t = time;
         eps = RosenbrokeStep (CurrentValues, y);
      }
      else{
         CurrentValues->t = time + tau;
         CopyVectors (CurrentValues->y, y1, N);
         CopyVectors (y, y1, N);
         free (y1);
         REC_NUM = 0;
         KSI     = 1.0;
      }
      return eps;
}

void FirstCalcJacobyMatrix (StepParameters * CurrentValues){
      int    i, j;
      double *a;
      double *b;
      pfn_fi *J;
      double scale_A = -0.25 * CurrentValues->tau;
      double scale_r = CurrentValues->tau * CurrentValues->tau;
      double r_i;
      double b_ij;

      for (i = 0; i < CurrentValues->N; i++){
          a = CurrentValues->A[i];
          b = CurrentValues->B[i];
          J = rhJacoby_matrix[i];

          CurrentValues->r[i] = r_i = scale_r * (*rhft_array[i])(CurrentValues);

          CurrentValues->z[i] = CurrentValues->z[i] =
          CurrentValues->tau * (*rhf_array[i])(CurrentValues)
          + 0.25 * r_i;
          for (j = 0; j < CurrentValues->N; j++){
              *b++ = b_ij = (*J++)(CurrentValues);
              *a++ = scale_A * b_ij;
          }
      }
      for (i = 0; i < CurrentValues->M; i++)
          CurrentValues->A[i][i]++;
}

void CalcJacobyMatrix (StepParameters * CurrentValues,
                       double           ksi){
      int    i, j;
      double *a;
      double *b;
      double scale_A = -0.25 * CurrentValues->tau;
      double scale_r = ksi * ksi;
      double r_i;

      for (i = 0; i < CurrentValues->N; i++){
          a   = CurrentValues->A[i];
          b   = CurrentValues->B[i];
          r_i = (CurrentValues->r[i] *= scale_r);
          CurrentValues->z[i] = ksi * CurrentValues->z1[i];
          for (j = 0; j < CurrentValues->N; j++)
              *a++ = scale_A * *b++;
	  }
      for (i = 0; i < CurrentValues->M; i++)
          CurrentValues->A[i][i]++;
}

void CalcCi (double         * ki,
             double         * Ci,
             StepParameters * CurrentValues){
      int i;
      double *zi = CurrentValues->z;

      for (i = 0; i < CurrentValues->M; i++)
          *Ci++ = 4 * (*ki++ - *zi++);
      for (; i < CurrentValues->N; i++)
          *Ci++ = -4 * *zi++;
}

void UpdateY_and_t (StepParameters * CurrentValues,
                    double         * y,
                    MethodCoeffs   * Alpha,
                    double           time){
      int i, j;
      double * k = CurrentValues->k;
      double * ki;
      double y_new;

      CurrentValues->t = time + CurrentValues->tau * Alpha->Values[Alpha->Number];
      for (j = 0; j < CurrentValues->N; j++){
          y_new = *y++ + Alpha->Values[0] * *k;
          ki    = k + CurrentValues->N;
          for (i = 1; i < Alpha->Number; i++){
              y_new += Alpha->Values[i] * *ki;
              ki += CurrentValues->N;
          }
          k++;
          CurrentValues->y[j] = y_new;
      }
}

void UpdateZ (StepParameters * CurrentValues,
              double         * y,
              MethodCoeffs   * Gamma){
      int i, j;
      double * C = CurrentValues->C;
      double * Ci;
      double z_new;

      for (j = 0; j < CurrentValues->N; j++){
          z_new = Gamma->Values[Gamma->Number] * CurrentValues->r[j] + CurrentValues->tau *
                  (*rhf_array[j])(CurrentValues) + Gamma->Values[0] * *C;
          Ci = C + CurrentValues->N;
          for (i = 1; i < Gamma->Number; i++){
              z_new += Gamma->Values[i] * *Ci;
              Ci    += CurrentValues->N;
          }
          C++;
          CurrentValues->z[j] = z_new;
      }
}

double CalcError (double * vector,
                  double * exact_vector,
                  int      Vector_size,
                  double * abs_eps){
      int    i;
      double dy_norm = 0;
      double y_norm  = 0;
      double dy_i;
      double y_i;

      for (i = 0; i < Vector_size; i++){
          y_i      = *exact_vector;
          dy_i     = *exact_vector++ - *vector++;
          dy_norm += dy_i * dy_i;
          y_norm  += y_i * y_i;
      }
      y_norm  = sqrt (y_norm);
//      if (_isnan (dy_norm) || _isnan (y_norm) || !_finite (dy_norm)
//          || !_finite (y_norm)){
//         *abs_eps = HUGE_VAL;
//         return 10;
//      }
      dy_norm = sqrt (dy_norm);
      *abs_eps = dy_norm;
      if (y_norm > 1.0)
         return dy_norm / y_norm;
      return dy_norm;
}

double UpdateTau (StepParameters * CurrentValues,
                  double           abs_eps){
      double tau;
      double ratio = abs_eps / tolerance;

      if (ratio == 0)
         tau = CurrentValues->tau * 2.0;
      else
      if (abs_eps >= HUGE_VAL)
         tau = tau_min;
      else{
         tau = CurrentValues->tau / sqrt (sqrt (ratio));
         if (error > 0)
            tau *= pow (error / tolerance, 0.08);
      }
      if (tau > tau_max)
         tau = tau_max;
      if (tau < tau_min)
         tau = tau_min;
      if (tau == CurrentValues->tau)
         return 1.0;
      ratio = tau / CurrentValues->tau;
      CurrentValues->tau = tau;
      return ratio;
}
