// Module rhfns.h
// header for right hand functions implementation
// for differential-algebraic equation system
// description.
//
// It was built 05.11.2002 by Starojilova T.K.
// Last modification 18.11.2002.

/* Type of functional vectors and tables                    */
typedef double (* pfn_fi)(StepParameters * CurrentValues);

/* Tables Generated by the Right Hand Functions             */

extern pfn_fi rhf_array[]; // Vector of right hand functions

extern pfn_fi rhft_array[];// Vector of right hand functions
                           // partial derivity by time

extern pfn_fi rhJacoby_matrix[][MAX_N];// Jacobies matrix
                                       // generated by right
                                       // hand functions
