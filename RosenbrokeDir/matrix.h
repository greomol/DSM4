// Module matrix.h
// header for vector and matrix operations and
// differential-algebraic equation system solving.
//
// It was built 05.11.2002 by Starojilova T.K.
// Last modification 19.11.2002.


/* The function matrix_ini allocates and initializes matrix */
/* of size Matrix_size by Matrix_size that consists of      */
/* double delements and is filled by zeros.                 */
/* matrix_ini returns pointer to pointers to matrix rows in */
/* success, NULL otherwise.                                 */
double ** matrix_ini (int Matrix_size);

/* The function vector_ini allocates and initializes vector */
/* of size Matrix_size that consists of double delements    */
/* and is filled by zeros.                                  */
/* vector_ini returns pointer to vector elements in         */
/* success, NULL otherwise.                                 */
double *  vector_ini (int Vector_size);

/* The function matrix_free frees memory allocated for      */
/* matrix which has the size Matrix_size by Matrix_size and */
/* is pointed by Matrix.                                    */
/*                                                          */
/* Features:                                                */
/*   If Matrix has NULL value then matrix_free does not     */
/*   free memory.                                           */ 
void matrix_free (double ** Matrix, int Matrix_size);

/* The function CopyVectors copies the first Vector_size    */
/* elements of vector origin into the corresponding         */
/* elements of the vector copy.                             */
/*                                                          */
/* Features:                                                */
/*   if origin or copy have less then Vector_size elements  */
/*   then the result of CopyVectors work is undefined.      */
void CopyVectors (double * copy,
                  double * origin,
                  int Vector_size);

/* The function Solve_LinSys solves linear algebraic system */
/* of Matrix_size equations defining as: A*x = z;           */
/* Modified Gauss method is used in Solve_LinSys.           */
/* Solve_LinSys returns 1 in success, 0 otherwise.          */ 
int Solve_LinSys (double ** A,
                  double *  z,
                  double *  x,
                  int       Matrix_size);
