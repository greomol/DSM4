// Module matrix.c
// vector and matrix operations implementation and
// differential-algebraic equation system solving.
// It contains linear algebraic system solver 
// based on the modified Gauss method.
//
// It was built 05.11.2002 by Starojilova T.K.
// Last modification 19.11.2002.

#include <stdlib.h>
#include <math.h>
#include "error.h"
#include "matrix.h"

/* The function FindMaxVectorComponent finds and returns    */
/* the value of the maximum absolute element of vector with */
/* length elements. FindMaxVectorComponent stores in *index */
/* the first component number where this value has occurred.*/
double FindMaxVectorComponent (double * vector,
                               int      length,
                               int    * index);

/* The function ScaleEquation devides linear equation with  */
/* length coeffitients stored in a and right hand value     */
/* stored in f by max_element.                              */
double ScaleEquation (double * a,
                      double * f,
                      double   max_element,
                      int      length);

/* The function EliminateVariable eliminates from the l-th  */
/* equation of linear algebraic system variable of number   */
/* index with the help of the i-th equation. System size is */
/* length by length. In success EliminateVariable returns   */
/* elimminator for the l-th right hand using right hand of  */
/* the i-th equation f_i.                                   */
double EliminateVariable (double * a_l,
                          double * a_i,
                          double   f_i,
                          int      length,
                          int      index);

/* The function CalcSolutionComponent implements one step   */
/* of the reverse trace for modified Gauss method.          */
/* CalcSolutionComponent returns the one component of       */
/* solution using the i-th equation for calculations.       */
double CalcSolutionComponent (double * a_i,
                              double * x,
                              int    * indices,
                              int      length);

/* The function matrix_ini allocates and initializes matrix */
/* of size Matrix_size by Matrix_size that consists of      */
/* double delements and is filled by zeros.                 */
/* matrix_ini returns pointer to pointers to matrix rows in */
/* success, NULL otherwise.                                 */
double ** matrix_ini (int Matrix_size){

      double ** Matrix = (double **) malloc (sizeof(double *) * Matrix_size);
      int       i;

      if (Matrix == NULL){
         SendErrorMsg (errlog_name, "Not enough memory to allocate matrix", ERROR);
         return NULL;
      }

      for (i = 0; i < Matrix_size; i++){
          Matrix[i] = (double *) calloc (Matrix_size, sizeof(double));
          if (Matrix[i] == NULL){
             SendErrorMsg (errlog_name, "Not enough memory to allocate matrix", ERROR);
             return NULL;
          }
      }
    
      return Matrix;
}

/* The function vector_ini allocates and initializes vector */
/* of size Matrix_size that consists of double elements and */
/* is filled by zeros.                                      */
/* vector_ini returns pointer to vector elements in         */
/* success, NULL otherwise.                                 */
double * vector_ini (int Vector_size){

      double *Vector = (double *) calloc (Vector_size, sizeof(double));

      if (Vector == NULL){
         SendErrorMsg (errlog_name, "Not enough memory to allocate (double) vector", ERROR);
         return NULL;
      }
      return Vector;
}

/* The function matrix_free frees memory allocated for      */
/* matrix which has the size Matrix_size by Matrix_size and */
/* is pointed by Matrix.                                    */
/*                                                          */
/* Features:                                                */
/*   If Matrix has NULL value then matrix_free does not     */
/*   free memory.                                           */
void matrix_free (double ** Matrix, int Matrix_size){
      int i;

      if (Matrix == NULL)
         return;

      for (i = 0; i < Matrix_size; i++){
          if (Matrix[i] == NULL)
             continue;
      free (Matrix[i]);
      }

      free (Matrix);
}

/* The function CopyVectors copies the first Vector_size    */
/* elements of vector origin into the corresponding         */
/* elements of the vector copy.                             */
/*                                                          */
/* Features:                                                */
/*   if origin or copy have less then Vector_size elements  */
/*   then the result of CopyVectors work is undefined.      */
void CopyVectors (double * copy,
                  double * origin,
                  int      Vector_size){
      int i;

      for (i = 0; i < Vector_size; i++)
          *copy++ = *origin++;
}

/* The function Solve_LinSys solves linear algebraic system */
/* of Matrix_size equations defining as: A*x = z;           */
/* Modified Gauss method is used in Solve_LinSys.           */
/* Solve_LinSys returns 1 in success, 0 otherwise.          */
int Solve_LinSys (double ** A,
                  double *  z,
                  double *  x,
                  int       Matrix_size){

      int    *  indices = (int *) calloc (Matrix_size, sizeof(int));
      double ** A1      = matrix_ini (Matrix_size);
      double *  f       = vector_ini (Matrix_size);
      double *  a_i;
      int       i, j;
      double    max_element;
      double    f_i;

      if (A1 == NULL)
         return 0;
      if (f == NULL)
         return 0;
      if (indices == NULL){
         SendErrorMsg (errlog_name, "Not enough memory to allocate (int) vectors", ERROR);
      return 0;
      }

      CopyVectors (f, z, Matrix_size);
      for (i = 0; i < Matrix_size; i++)
          CopyVectors (A1[i], A[i], Matrix_size);

      for (i = 0; i < Matrix_size; i++){
          a_i = A1[i];
          max_element = FindMaxVectorComponent (a_i, Matrix_size, indices);
          f_i = ScaleEquation (a_i, f + i, max_element, Matrix_size);
          for (j = i + 1; j < Matrix_size; j++)
              f[j] -= EliminateVariable (A1[j], a_i, f_i, Matrix_size, *indices);
          indices++;
      }

      for (i = Matrix_size - 1; i >=0; i--){
          indices--;
          x[*indices] = CalcSolutionComponent (A1[i], x, indices + 1, Matrix_size - i) + f[i];
      }
      matrix_free (A1, Matrix_size);
      free (indices);
      free (f);
      return 1;
}

double FindMaxVectorComponent (double * vector,
                               int      length,
                               int    * index){
      int j;
      int k = 0;
      double max_element = fabs (*vector++);
      double abs_element;

      for (j = 1; j < length; j++){
          abs_element = fabs (*vector++);
          if (max_element < abs_element){
             max_element = abs_element;
             k           = j;
          }
      }
      *index = k;
      k -= j;
      if (max_element < 1e-16)
         SendErrorMsg (errlog_name, "Singular string has been found. NaN values may occur",
                       WARNING);

      return *(vector + k);
}

double ScaleEquation (double * a,
                      double * f,
                      double   max_element,
                      int      length){
      int j;

      for (j = 0; j < length; j++)
          *a++ /= max_element;
          *f   /= max_element;
      return *f;
}

double EliminateVariable (double * a_l,
                          double * a_i,
                          double   f_i,
                          int      length,
                          int      index){
      int    j;
      double eliminator  = a_l[index];

      for (j = 0; j < length; j++)
          *a_l++ -= eliminator * *a_i++;
      return f_i * eliminator;
}

double CalcSolutionComponent (double * a_i,
                              double * x,
                              int    * indices,
                              int      length){
      double answer = 0;
      int    i, j;

      for (j = 1; j < length; j++){
          i = *indices++;
          answer -= x[i] * a_i[i];
      }
      return answer;
}
