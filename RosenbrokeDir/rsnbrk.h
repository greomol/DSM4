// Module rsnbrk.h
// header for implementation of the one step
// of Rosenbroke method, error evaluation 
// and time step adjustments. 
//
// It was built 05.11.2002 by Starojilova T.K.
// Last modification 19.11.2002.

#define MAX_REC_NUM 5 /* Maximum number of recursive call   */
                      /* of the function RosenbrokeStep     */

typedef struct CoefficientsInnards{
      int      Number;// Number of Rosenbroke coefficients
                      // of the fixed type

	double * Values;// Pointer to Rosenbroke coefficients
	                // of the fixed type 
} MethodCoeffs;

/* The function RosenbrokeStep implements one step          */
/* computations using Rosenbroke method. Solution values at */
/* previous time step are given by y.                       */
/*                                                          */
/* Features:                                                */
/*    At the end of RosenbrokeStep vectors CurrentValues->y */
/*    and y contain updated solution at the time sroed in   */
/*    CurrentValues->t.                                     */
double RosenbrokeStep (StepParameters * CurrentValues,
                       double         * y);

