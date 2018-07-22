// Module rhfns.c
// right hand functions implementation for
// differential-algebraic equation system
// description.
//
// It was built 05.11.2002 by Starojilova T.K.
// Last modification 18.11.2002.

#include <math.h>
#include "main.h"
#include "rhfns.h"

/* Right Hand Functions                 */
/* of the Differential-Algebraic System */

double f0 (StepParameters * CurrentValues){
      return 9.5e4*P1*(P10-CurrentValues->y[0]-CurrentValues->y[2]-CurrentValues->y[3])*(P11-CurrentValues->y[0]-CurrentValues->y[1]-2*CurrentValues->y[3])-3e3*P2*CurrentValues->y[0]*(P11-CurrentValues->y[0]-CurrentValues->y[1]-2*CurrentValues->y[3])-P1*CurrentValues->y[0]-P7*CurrentValues->y[0]*(P9-CurrentValues->y[1]-CurrentValues->y[2])*(P9-CurrentValues->y[1]-CurrentValues->y[2])+P2*CurrentValues->y[3]+P8*CurrentValues->y[3]*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f1 (StepParameters * CurrentValues){
      return P4*(P9-CurrentValues->y[1]-CurrentValues->y[2])*(P11-CurrentValues->y[0]-CurrentValues->y[1]-2*CurrentValues->y[3])-P6*CurrentValues->y[1]+P7*CurrentValues->y[0]*(P9-CurrentValues->y[1]-CurrentValues->y[2])*(P9-CurrentValues->y[1]-CurrentValues->y[2])+P8*CurrentValues->y[3]*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f2 (StepParameters * CurrentValues){
      return P3*(P9-CurrentValues->y[1]-CurrentValues->y[2])*(P10-CurrentValues->y[0]-CurrentValues->y[2]-CurrentValues->y[3])-P5*CurrentValues->y[2]+P7*CurrentValues->y[0]*(P9-CurrentValues->y[1]-CurrentValues->y[2])*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f3 (StepParameters * CurrentValues){
      return 3e3*P2*CurrentValues->y[0]*(P11-CurrentValues->y[0]-CurrentValues->y[1]-2*CurrentValues->y[3])-P2*CurrentValues->y[3]-P8*CurrentValues->y[3]*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f4 (StepParameters * CurrentValues){
      return 0;
}

double f5 (StepParameters * CurrentValues){
      return 0;
}

double f6 (StepParameters * CurrentValues){
      return 0;
}

double f7 (StepParameters * CurrentValues){
      return 0;
}

double f8 (StepParameters * CurrentValues){
      return 0;
}

double f9 (StepParameters * CurrentValues){
      return 0;
}

double f10 (StepParameters * CurrentValues){
      return 0;
}

double f11 (StepParameters * CurrentValues){
      return 0;
}

double f12 (StepParameters * CurrentValues){
      return 0;
}

double f13 (StepParameters * CurrentValues){
      return 0;
}

double f14 (StepParameters * CurrentValues){
      return 0;
}

double f15 (StepParameters * CurrentValues){
      return 0;
}

double f16 (StepParameters * CurrentValues){
      return 0;
}

double f17 (StepParameters * CurrentValues){
      return 0;
}

double f18 (StepParameters * CurrentValues){
      return 0;
}

double f19 (StepParameters * CurrentValues){
      return 0;
}


/* Time Derivative of Right Hand Functions of */
/* the Differential-Algebraic System          */

double ft0 (StepParameters * CurrentValues){
      return 0;
}

double ft1 (StepParameters * CurrentValues){
      return 0;
}

double ft2 (StepParameters * CurrentValues){
      return 0;
}

double ft3 (StepParameters * CurrentValues){
      return 0;
}

double ft4 (StepParameters * CurrentValues){
      return 0;
}

double ft5 (StepParameters * CurrentValues){
      return 0;
}

double ft6 (StepParameters * CurrentValues){
      return 0;
}

double ft7 (StepParameters * CurrentValues){
      return 0;
}

double ft8 (StepParameters * CurrentValues){
      return 0;
}

double ft9 (StepParameters * CurrentValues){
      return 0;
}

double ft10 (StepParameters * CurrentValues){
      return 0;
}

double ft11 (StepParameters * CurrentValues){
      return 0;
}

double ft12 (StepParameters * CurrentValues){
      return 0;
}

double ft13 (StepParameters * CurrentValues){
      return 0;
}

double ft14 (StepParameters * CurrentValues){
      return 0;
}

double ft15 (StepParameters * CurrentValues){
      return 0;
}

double ft16 (StepParameters * CurrentValues){
      return 0;
}

double ft17 (StepParameters * CurrentValues){
      return 0;
}

double ft18 (StepParameters * CurrentValues){
      return 0;
}

double ft19 (StepParameters * CurrentValues){
      return 0;
}


/* Component Derivative of Right Hand Functions */
/* of the Differential-Algebraic System         */

double f0_0 (StepParameters * CurrentValues){
      return -9.5e4*P1*(P11+P10-2*CurrentValues->y[0]-CurrentValues->y[1]-CurrentValues->y[2]-3*CurrentValues->y[3])-3e3*P2*(P11-2*CurrentValues->y[0]-CurrentValues->y[1]-2*CurrentValues->y[3])-P1-P7*(P9-CurrentValues->y[1]-CurrentValues->y[2])*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f0_1 (StepParameters * CurrentValues){
      return -9.5e4*P1*(P10-CurrentValues->y[0]-CurrentValues->y[2]-CurrentValues->y[3])+3e3*P2*CurrentValues->y[0]+P7*CurrentValues->y[0]*2*(P9-CurrentValues->y[1]-CurrentValues->y[2])-P8*CurrentValues->y[3];
}

double f0_2 (StepParameters * CurrentValues){
      return -9.5e4*P1*(P11-CurrentValues->y[0]-CurrentValues->y[1]-2*CurrentValues->y[3])+P7*CurrentValues->y[0]*2*(P9-CurrentValues->y[1]-CurrentValues->y[2])-P8*CurrentValues->y[3];
}

double f0_3 (StepParameters * CurrentValues){
      return -9.5e4*P1*(2*P10+P11-3*CurrentValues->y[0]-CurrentValues->y[1]-2*CurrentValues->y[2]-4*CurrentValues->y[3])+2*3e3*P2*CurrentValues->y[0]+P2+P8*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f0_4 (StepParameters * CurrentValues){
      return 0;
}

double f0_5 (StepParameters * CurrentValues){
      return 0;
}

double f0_6 (StepParameters * CurrentValues){
      return 0;
}

double f0_7 (StepParameters * CurrentValues){
      return 0;
}

double f0_8 (StepParameters * CurrentValues){
      return 0;
}

double f0_9 (StepParameters * CurrentValues){
      return 0;
}

double f0_10 (StepParameters * CurrentValues){
      return 0;
}

double f0_11 (StepParameters * CurrentValues){
      return 0;
}

double f0_12 (StepParameters * CurrentValues){
      return 0;
}

double f0_13 (StepParameters * CurrentValues){
      return 0;
}

double f0_14 (StepParameters * CurrentValues){
      return 0;
}

double f0_15 (StepParameters * CurrentValues){
      return 0;
}

double f0_16 (StepParameters * CurrentValues){
      return 0;
}

double f0_17 (StepParameters * CurrentValues){
      return 0;
}

double f0_18 (StepParameters * CurrentValues){
      return 0;
}

double f0_19 (StepParameters * CurrentValues){
      return 0;
}

double f1_0 (StepParameters * CurrentValues){
      return -P4*(P9-CurrentValues->y[1]-CurrentValues->y[2])+P7*(P9-CurrentValues->y[1]-CurrentValues->y[2])*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f1_1 (StepParameters * CurrentValues){
      return -P4*(P9+P11-CurrentValues->y[0]-2*CurrentValues->y[1]-CurrentValues->y[2]-2*CurrentValues->y[3])-P6-P7*CurrentValues->y[0]*2*(P9-CurrentValues->y[1]-CurrentValues->y[2])-P8*CurrentValues->y[3];
}

double f1_2 (StepParameters * CurrentValues){
      return -P4*(P11-CurrentValues->y[0]-CurrentValues->y[1]-2*CurrentValues->y[3])-P7*CurrentValues->y[0]*2*(P9-CurrentValues->y[1]-CurrentValues->y[2])-P8*CurrentValues->y[3];
}

double f1_3 (StepParameters * CurrentValues){
      return -2*P4*(P9-CurrentValues->y[1]-CurrentValues->y[2])+P8*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f1_4 (StepParameters * CurrentValues){
      return 0;
}

double f1_5 (StepParameters * CurrentValues){
      return 0;
}

double f1_6 (StepParameters * CurrentValues){
      return 0;
}

double f1_7 (StepParameters * CurrentValues){
      return 0;
}

double f1_8 (StepParameters * CurrentValues){
      return 0;
}

double f1_9 (StepParameters * CurrentValues){
      return 0;
}

double f1_10 (StepParameters * CurrentValues){
      return 0;
}

double f1_11 (StepParameters * CurrentValues){
      return 0;
}

double f1_12 (StepParameters * CurrentValues){
      return 0;
}

double f1_13 (StepParameters * CurrentValues){
      return 0;
}

double f1_14 (StepParameters * CurrentValues){
      return 0;
}

double f1_15 (StepParameters * CurrentValues){
      return 0;
}

double f1_16 (StepParameters * CurrentValues){
      return 0;
}

double f1_17 (StepParameters * CurrentValues){
      return 0;
}

double f1_18 (StepParameters * CurrentValues){
      return 0;
}

double f1_19 (StepParameters * CurrentValues){
      return 0;
}

double f2_0 (StepParameters * CurrentValues){
      return -P3*(P9-CurrentValues->y[1]-CurrentValues->y[2])+P7*(P9-CurrentValues->y[1]-CurrentValues->y[2])*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f2_1 (StepParameters * CurrentValues){
      return -P3*(P10-CurrentValues->y[0]-CurrentValues->y[2]-CurrentValues->y[3])-2*P7*CurrentValues->y[0]*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f2_2 (StepParameters * CurrentValues){
      return -P3*(P9-CurrentValues->y[1]-CurrentValues->y[2])-P3*(P10-CurrentValues->y[0]-CurrentValues->y[2]-CurrentValues->y[3])-P5-2*P7*CurrentValues->y[0]*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f2_3 (StepParameters * CurrentValues){
      return -P3*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f2_4 (StepParameters * CurrentValues){
      return 0;
}

double f2_5 (StepParameters * CurrentValues){
      return 0;
}

double f2_6 (StepParameters * CurrentValues){
      return 0;
}

double f2_7 (StepParameters * CurrentValues){
      return 0;
}

double f2_8 (StepParameters * CurrentValues){
      return 0;
}

double f2_9 (StepParameters * CurrentValues){
      return 0;
}

double f2_10 (StepParameters * CurrentValues){
      return 0;
}

double f2_11 (StepParameters * CurrentValues){
      return 0;
}

double f2_12 (StepParameters * CurrentValues){
      return 0;
}

double f2_13 (StepParameters * CurrentValues){
      return 0;
}

double f2_14 (StepParameters * CurrentValues){
      return 0;
}

double f2_15 (StepParameters * CurrentValues){
      return 0;
}

double f2_16 (StepParameters * CurrentValues){
      return 0;
}

double f2_17 (StepParameters * CurrentValues){
      return 0;
}

double f2_18 (StepParameters * CurrentValues){
      return 0;
}

double f2_19 (StepParameters * CurrentValues){
      return 0;
}

double f3_0 (StepParameters * CurrentValues){
      return 3e3*P2*(P11-2*CurrentValues->y[0]-CurrentValues->y[1]-2*CurrentValues->y[3]);
}

double f3_1 (StepParameters * CurrentValues){
      return -3e3*P2*CurrentValues->y[0]+P8*CurrentValues->y[3];
}

double f3_2 (StepParameters * CurrentValues){
      return P8*CurrentValues->y[3];
}

double f3_3 (StepParameters * CurrentValues){
      return -2*3e3*P2*CurrentValues->y[0]-P2-P8*(P9-CurrentValues->y[1]-CurrentValues->y[2]);
}

double f3_4 (StepParameters * CurrentValues){
      return 0;
}

double f3_5 (StepParameters * CurrentValues){
      return 0;
}

double f3_6 (StepParameters * CurrentValues){
      return 0;
}

double f3_7 (StepParameters * CurrentValues){
      return 0;
}

double f3_8 (StepParameters * CurrentValues){
      return 0;
}

double f3_9 (StepParameters * CurrentValues){
      return 0;
}

double f3_10 (StepParameters * CurrentValues){
      return 0;
}

double f3_11 (StepParameters * CurrentValues){
      return 0;
}

double f3_12 (StepParameters * CurrentValues){
      return 0;
}

double f3_13 (StepParameters * CurrentValues){
      return 0;
}

double f3_14 (StepParameters * CurrentValues){
      return 0;
}

double f3_15 (StepParameters * CurrentValues){
      return 0;
}

double f3_16 (StepParameters * CurrentValues){
      return 0;
}

double f3_17 (StepParameters * CurrentValues){
      return 0;
}

double f3_18 (StepParameters * CurrentValues){
      return 0;
}

double f3_19 (StepParameters * CurrentValues){
      return 0;
}
double f4_0 (StepParameters * CurrentValues){
      return 0;
}

double f4_1 (StepParameters * CurrentValues){
      return 0;
}

double f4_2 (StepParameters * CurrentValues){
      return 0;
}

double f4_3 (StepParameters * CurrentValues){
      return 0;
}

double f4_4 (StepParameters * CurrentValues){
      return 0;
}

double f4_5 (StepParameters * CurrentValues){
      return 0;
}

double f4_6 (StepParameters * CurrentValues){
      return 0;
}

double f4_7 (StepParameters * CurrentValues){
      return 0;
}

double f4_8 (StepParameters * CurrentValues){
      return 0;
}

double f4_9 (StepParameters * CurrentValues){
      return 0;
}

double f4_10 (StepParameters * CurrentValues){
      return 0;
}

double f4_11 (StepParameters * CurrentValues){
      return 0;
}

double f4_12 (StepParameters * CurrentValues){
      return 0;
}

double f4_13 (StepParameters * CurrentValues){
      return 0;
}

double f4_14 (StepParameters * CurrentValues){
      return 0;
}

double f4_15 (StepParameters * CurrentValues){
      return 0;
}

double f4_16 (StepParameters * CurrentValues){
      return 0;
}

double f4_17 (StepParameters * CurrentValues){
      return 0;
}

double f4_18 (StepParameters * CurrentValues){
      return 0;
}

double f4_19 (StepParameters * CurrentValues){
      return 0;
}
double f5_0 (StepParameters * CurrentValues){
      return 0;
}

double f5_1 (StepParameters * CurrentValues){
      return 0;
}

double f5_2 (StepParameters * CurrentValues){
      return 0;
}

double f5_3 (StepParameters * CurrentValues){
      return 0;
}

double f5_4 (StepParameters * CurrentValues){
      return 0;
}

double f5_5 (StepParameters * CurrentValues){
      return 0;
}

double f5_6 (StepParameters * CurrentValues){
      return 0;
}

double f5_7 (StepParameters * CurrentValues){
      return 0;
}

double f5_8 (StepParameters * CurrentValues){
      return 0;
}

double f5_9 (StepParameters * CurrentValues){
      return 0;
}

double f5_10 (StepParameters * CurrentValues){
      return 0;
}

double f5_11 (StepParameters * CurrentValues){
      return 0;
}

double f5_12 (StepParameters * CurrentValues){
      return 0;
}

double f5_13 (StepParameters * CurrentValues){
      return 0;
}

double f5_14 (StepParameters * CurrentValues){
      return 0;
}

double f5_15 (StepParameters * CurrentValues){
      return 0;
}

double f5_16 (StepParameters * CurrentValues){
      return 0;
}

double f5_17 (StepParameters * CurrentValues){
      return 0;
}

double f5_18 (StepParameters * CurrentValues){
      return 0;
}

double f5_19 (StepParameters * CurrentValues){
      return 0;
}

double f6_0 (StepParameters * CurrentValues){
      return 0;
}

double f6_1 (StepParameters * CurrentValues){
      return 0;
}

double f6_2 (StepParameters * CurrentValues){
      return 0;
}

double f6_3 (StepParameters * CurrentValues){
      return 0;
}

double f6_4 (StepParameters * CurrentValues){
      return 0;
}

double f6_5 (StepParameters * CurrentValues){
      return 0;
}

double f6_6 (StepParameters * CurrentValues){
      return 0;
}

double f6_7 (StepParameters * CurrentValues){
      return 0;
}

double f6_8 (StepParameters * CurrentValues){
      return 0;
}

double f6_9 (StepParameters * CurrentValues){
      return 0;
}

double f6_10 (StepParameters * CurrentValues){
      return 0;
}

double f6_11 (StepParameters * CurrentValues){
      return 0;
}

double f6_12 (StepParameters * CurrentValues){
      return 0;
}

double f6_13 (StepParameters * CurrentValues){
      return 0;
}

double f6_14 (StepParameters * CurrentValues){
      return 0;
}

double f6_15 (StepParameters * CurrentValues){
      return 0;
}

double f6_16 (StepParameters * CurrentValues){
      return 0;
}

double f6_17 (StepParameters * CurrentValues){
      return 0;
}

double f6_18 (StepParameters * CurrentValues){
      return 0;
}

double f6_19 (StepParameters * CurrentValues){
      return 0;
}

double f7_0 (StepParameters * CurrentValues){
      return 0;
}

double f7_1 (StepParameters * CurrentValues){
      return 0;
}

double f7_2 (StepParameters * CurrentValues){
      return 0;
}

double f7_3 (StepParameters * CurrentValues){
      return 0;
}

double f7_4 (StepParameters * CurrentValues){
      return 0;
}

double f7_5 (StepParameters * CurrentValues){
      return 0;
}

double f7_6 (StepParameters * CurrentValues){
      return 0;
}

double f7_7 (StepParameters * CurrentValues){
      return 0;
}

double f7_8 (StepParameters * CurrentValues){
      return 0;
}

double f7_9 (StepParameters * CurrentValues){
      return 0;
}

double f7_10 (StepParameters * CurrentValues){
      return 0;
}

double f7_11 (StepParameters * CurrentValues){
      return 0;
}

double f7_12 (StepParameters * CurrentValues){
      return 0;
}

double f7_13 (StepParameters * CurrentValues){
      return 0;
}

double f7_14 (StepParameters * CurrentValues){
      return 0;
}

double f7_15 (StepParameters * CurrentValues){
      return 0;
}

double f7_16 (StepParameters * CurrentValues){
      return 0;
}

double f7_17 (StepParameters * CurrentValues){
      return 0;
}

double f7_18 (StepParameters * CurrentValues){
      return 0;
}

double f7_19 (StepParameters * CurrentValues){
      return 0;
}

double f8_0 (StepParameters * CurrentValues){
      return 0;
}

double f8_1 (StepParameters * CurrentValues){
      return 0;
}

double f8_2 (StepParameters * CurrentValues){
      return 0;
}

double f8_3 (StepParameters * CurrentValues){
      return 0;
}

double f8_4 (StepParameters * CurrentValues){
      return 0;
}

double f8_5 (StepParameters * CurrentValues){
      return 0;
}

double f8_6 (StepParameters * CurrentValues){
      return 0;
}

double f8_7 (StepParameters * CurrentValues){
      return 0;
}

double f8_8 (StepParameters * CurrentValues){
      return 0;
}

double f8_9 (StepParameters * CurrentValues){
      return 0;
}

double f8_10 (StepParameters * CurrentValues){
      return 0;
}

double f8_11 (StepParameters * CurrentValues){
      return 0;
}

double f8_12 (StepParameters * CurrentValues){
      return 0;
}

double f8_13 (StepParameters * CurrentValues){
      return 0;
}

double f8_14 (StepParameters * CurrentValues){
      return 0;
}

double f8_15 (StepParameters * CurrentValues){
      return 0;
}

double f8_16 (StepParameters * CurrentValues){
      return 0;
}

double f8_17 (StepParameters * CurrentValues){
      return 0;
}

double f8_18 (StepParameters * CurrentValues){
      return 0;
}

double f8_19 (StepParameters * CurrentValues){
      return 0;
}

double f9_0 (StepParameters * CurrentValues){
      return 0;
}

double f9_1 (StepParameters * CurrentValues){
      return 0;
}

double f9_2 (StepParameters * CurrentValues){
      return 0;
}

double f9_3 (StepParameters * CurrentValues){
      return 0;
}

double f9_4 (StepParameters * CurrentValues){
      return 0;
}

double f9_5 (StepParameters * CurrentValues){
      return 0;
}

double f9_6 (StepParameters * CurrentValues){
      return 0;
}

double f9_7 (StepParameters * CurrentValues){
      return 0;
}

double f9_8 (StepParameters * CurrentValues){
      return 0;
}

double f9_9 (StepParameters * CurrentValues){
      return 0;
}

double f9_10 (StepParameters * CurrentValues){
      return 0;
}

double f9_11 (StepParameters * CurrentValues){
      return 0;
}

double f9_12 (StepParameters * CurrentValues){
      return 0;
}

double f9_13 (StepParameters * CurrentValues){
      return 0;
}

double f9_14 (StepParameters * CurrentValues){
      return 0;
}

double f9_15 (StepParameters * CurrentValues){
      return 0;
}

double f9_16 (StepParameters * CurrentValues){
      return 0;
}

double f9_17 (StepParameters * CurrentValues){
      return 0;
}

double f9_18 (StepParameters * CurrentValues){
      return 0;
}

double f9_19 (StepParameters * CurrentValues){
      return 0;
}

double f10_0 (StepParameters * CurrentValues){
      return 0;
}

double f10_1 (StepParameters * CurrentValues){
      return 0;
}

double f10_2 (StepParameters * CurrentValues){
      return 0;
}

double f10_3 (StepParameters * CurrentValues){
      return 0;
}

double f10_4 (StepParameters * CurrentValues){
      return 0;
}

double f10_5 (StepParameters * CurrentValues){
      return 0;
}

double f10_6 (StepParameters * CurrentValues){
      return 0;
}

double f10_7 (StepParameters * CurrentValues){
      return 0;
}

double f10_8 (StepParameters * CurrentValues){
      return 0;
}

double f10_9 (StepParameters * CurrentValues){
      return 0;
}

double f10_10 (StepParameters * CurrentValues){
      return 0;
}

double f10_11 (StepParameters * CurrentValues){
      return 0;
}

double f10_12 (StepParameters * CurrentValues){
      return 0;
}

double f10_13 (StepParameters * CurrentValues){
      return 0;
}

double f10_14 (StepParameters * CurrentValues){
      return 0;
}

double f10_15 (StepParameters * CurrentValues){
      return 0;
}

double f10_16 (StepParameters * CurrentValues){
      return 0;
}

double f10_17 (StepParameters * CurrentValues){
      return 0;
}

double f10_18 (StepParameters * CurrentValues){
      return 0;
}

double f10_19 (StepParameters * CurrentValues){
      return 0;
}

double f11_0 (StepParameters * CurrentValues){
      return 0;
}

double f11_1 (StepParameters * CurrentValues){
      return 0;
}

double f11_2 (StepParameters * CurrentValues){
      return 0;
}

double f11_3 (StepParameters * CurrentValues){
      return 0;
}

double f11_4 (StepParameters * CurrentValues){
      return 0;
}

double f11_5 (StepParameters * CurrentValues){
      return 0;
}

double f11_6 (StepParameters * CurrentValues){
      return 0;
}

double f11_7 (StepParameters * CurrentValues){
      return 0;
}

double f11_8 (StepParameters * CurrentValues){
      return 0;
}

double f11_9 (StepParameters * CurrentValues){
      return 0;
}

double f11_10 (StepParameters * CurrentValues){
      return 0;
}

double f11_11 (StepParameters * CurrentValues){
      return 0;
}

double f11_12 (StepParameters * CurrentValues){
      return 0;
}

double f11_13 (StepParameters * CurrentValues){
      return 0;
}

double f11_14 (StepParameters * CurrentValues){
      return 0;
}

double f11_15 (StepParameters * CurrentValues){
      return 0;
}

double f11_16 (StepParameters * CurrentValues){
      return 0;
}

double f11_17 (StepParameters * CurrentValues){
      return 0;
}

double f11_18 (StepParameters * CurrentValues){
      return 0;
}

double f11_19 (StepParameters * CurrentValues){
      return 0;
}

double f12_0 (StepParameters * CurrentValues){
      return 0;
}

double f12_1 (StepParameters * CurrentValues){
      return 0;
}

double f12_2 (StepParameters * CurrentValues){
      return 0;
}

double f12_3 (StepParameters * CurrentValues){
      return 0;
}

double f12_4 (StepParameters * CurrentValues){
      return 0;
}

double f12_5 (StepParameters * CurrentValues){
      return 0;
}

double f12_6 (StepParameters * CurrentValues){
      return 0;
}

double f12_7 (StepParameters * CurrentValues){
      return 0;
}

double f12_8 (StepParameters * CurrentValues){
      return 0;
}

double f12_9 (StepParameters * CurrentValues){
      return 0;
}

double f12_10 (StepParameters * CurrentValues){
      return 0;
}

double f12_11 (StepParameters * CurrentValues){
      return 0;
}

double f12_12 (StepParameters * CurrentValues){
      return 0;
}

double f12_13 (StepParameters * CurrentValues){
      return 0;
}

double f12_14 (StepParameters * CurrentValues){
      return 0;
}

double f12_15 (StepParameters * CurrentValues){
      return 0;
}

double f12_16 (StepParameters * CurrentValues){
      return 0;
}

double f12_17 (StepParameters * CurrentValues){
      return 0;
}

double f12_18 (StepParameters * CurrentValues){
      return 0;
}

double f12_19 (StepParameters * CurrentValues){
      return 0;
}

double f13_0 (StepParameters * CurrentValues){
      return 0;
}

double f13_1 (StepParameters * CurrentValues){
      return 0;
}

double f13_2 (StepParameters * CurrentValues){
      return 0;
}

double f13_3 (StepParameters * CurrentValues){
      return 0;
}

double f13_4 (StepParameters * CurrentValues){
      return 0;
}

double f13_5 (StepParameters * CurrentValues){
      return 0;
}

double f13_6 (StepParameters * CurrentValues){
      return 0;
}

double f13_7 (StepParameters * CurrentValues){
      return 0;
}

double f13_8 (StepParameters * CurrentValues){
      return 0;
}

double f13_9 (StepParameters * CurrentValues){
      return 0;
}

double f13_10 (StepParameters * CurrentValues){
      return 0;
}

double f13_11 (StepParameters * CurrentValues){
      return 0;
}

double f13_12 (StepParameters * CurrentValues){
      return 0;
}

double f13_13 (StepParameters * CurrentValues){
      return 0;
}

double f13_14 (StepParameters * CurrentValues){
      return 0;
}

double f13_15 (StepParameters * CurrentValues){
      return 0;
}

double f13_16 (StepParameters * CurrentValues){
      return 0;
}

double f13_17 (StepParameters * CurrentValues){
      return 0;
}

double f13_18 (StepParameters * CurrentValues){
      return 0;
}

double f13_19 (StepParameters * CurrentValues){
      return 0;
}

double f14_0 (StepParameters * CurrentValues){
      return 0;
}

double f14_1 (StepParameters * CurrentValues){
      return 0;
}

double f14_2 (StepParameters * CurrentValues){
      return 0;
}

double f14_3 (StepParameters * CurrentValues){
      return 0;
}

double f14_4 (StepParameters * CurrentValues){
      return 0;
}

double f14_5 (StepParameters * CurrentValues){
      return 0;
}

double f14_6 (StepParameters * CurrentValues){
      return 0;
}

double f14_7 (StepParameters * CurrentValues){
      return 0;
}

double f14_8 (StepParameters * CurrentValues){
      return 0;
}

double f14_9 (StepParameters * CurrentValues){
      return 0;
}

double f14_10 (StepParameters * CurrentValues){
      return 0;
}

double f14_11 (StepParameters * CurrentValues){
      return 0;
}

double f14_12 (StepParameters * CurrentValues){
      return 0;
}

double f14_13 (StepParameters * CurrentValues){
      return 0;
}

double f14_14 (StepParameters * CurrentValues){
      return 0;
}

double f14_15 (StepParameters * CurrentValues){
      return 0;
}

double f14_16 (StepParameters * CurrentValues){
      return 0;
}

double f14_17 (StepParameters * CurrentValues){
      return 0;
}

double f14_18 (StepParameters * CurrentValues){
      return 0;
}

double f14_19 (StepParameters * CurrentValues){
      return 0;
}

double f15_0 (StepParameters * CurrentValues){
      return 0;
}

double f15_1 (StepParameters * CurrentValues){
      return 0;
}

double f15_2 (StepParameters * CurrentValues){
      return 0;
}

double f15_3 (StepParameters * CurrentValues){
      return 0;
}

double f15_4 (StepParameters * CurrentValues){
      return 0;
}

double f15_5 (StepParameters * CurrentValues){
      return 0;
}

double f15_6 (StepParameters * CurrentValues){
      return 0;
}

double f15_7 (StepParameters * CurrentValues){
      return 0;
}

double f15_8 (StepParameters * CurrentValues){
      return 0;
}

double f15_9 (StepParameters * CurrentValues){
      return 0;
}

double f15_10 (StepParameters * CurrentValues){
      return 0;
}

double f15_11 (StepParameters * CurrentValues){
      return 0;
}

double f15_12 (StepParameters * CurrentValues){
      return 0;
}

double f15_13 (StepParameters * CurrentValues){
      return 0;
}

double f15_14 (StepParameters * CurrentValues){
      return 0;
}

double f15_15 (StepParameters * CurrentValues){
      return 0;
}

double f15_16 (StepParameters * CurrentValues){
      return 0;
}

double f15_17 (StepParameters * CurrentValues){
      return 0;
}

double f15_18 (StepParameters * CurrentValues){
      return 0;
}

double f15_19 (StepParameters * CurrentValues){
      return 0;
}

double f16_0 (StepParameters * CurrentValues){
      return 0;
}

double f16_1 (StepParameters * CurrentValues){
      return 0;
}

double f16_2 (StepParameters * CurrentValues){
      return 0;
}

double f16_3 (StepParameters * CurrentValues){
      return 0;
}

double f16_4 (StepParameters * CurrentValues){
      return 0;
}

double f16_5 (StepParameters * CurrentValues){
      return 0;
}

double f16_6 (StepParameters * CurrentValues){
      return 0;
}

double f16_7 (StepParameters * CurrentValues){
      return 0;
}

double f16_8 (StepParameters * CurrentValues){
      return 0;
}

double f16_9 (StepParameters * CurrentValues){
      return 0;
}

double f16_10 (StepParameters * CurrentValues){
      return 0;
}

double f16_11 (StepParameters * CurrentValues){
      return 0;
}

double f16_12 (StepParameters * CurrentValues){
      return 0;
}

double f16_13 (StepParameters * CurrentValues){
      return 0;
}

double f16_14 (StepParameters * CurrentValues){
      return 0;
}

double f16_15 (StepParameters * CurrentValues){
      return 0;
}

double f16_16 (StepParameters * CurrentValues){
      return 0;
}

double f16_17 (StepParameters * CurrentValues){
      return 0;
}

double f16_18 (StepParameters * CurrentValues){
      return 0;
}

double f16_19 (StepParameters * CurrentValues){
      return 0;
}

double f17_0 (StepParameters * CurrentValues){
      return 0;
}

double f17_1 (StepParameters * CurrentValues){
      return 0;
}

double f17_2 (StepParameters * CurrentValues){
      return 0;
}

double f17_3 (StepParameters * CurrentValues){
      return 0;
}

double f17_4 (StepParameters * CurrentValues){
      return 0;
}

double f17_5 (StepParameters * CurrentValues){
      return 0;
}

double f17_6 (StepParameters * CurrentValues){
      return 0;
}

double f17_7 (StepParameters * CurrentValues){
      return 0;
}

double f17_8 (StepParameters * CurrentValues){
      return 0;
}

double f17_9 (StepParameters * CurrentValues){
      return 0;
}

double f17_10 (StepParameters * CurrentValues){
      return 0;
}

double f17_11 (StepParameters * CurrentValues){
      return 0;
}

double f17_12 (StepParameters * CurrentValues){
      return 0;
}

double f17_13 (StepParameters * CurrentValues){
      return 0;
}

double f17_14 (StepParameters * CurrentValues){
      return 0;
}

double f17_15 (StepParameters * CurrentValues){
      return 0;
}

double f17_16 (StepParameters * CurrentValues){
      return 0;
}

double f17_17 (StepParameters * CurrentValues){
      return 0;
}

double f17_18 (StepParameters * CurrentValues){
      return 0;
}

double f17_19 (StepParameters * CurrentValues){
      return 0;
}

double f18_0 (StepParameters * CurrentValues){
      return 0;
}

double f18_1 (StepParameters * CurrentValues){
      return 0;
}

double f18_2 (StepParameters * CurrentValues){
      return 0;
}

double f18_3 (StepParameters * CurrentValues){
      return 0;
}

double f18_4 (StepParameters * CurrentValues){
      return 0;
}

double f18_5 (StepParameters * CurrentValues){
      return 0;
}

double f18_6 (StepParameters * CurrentValues){
      return 0;
}

double f18_7 (StepParameters * CurrentValues){
      return 0;
}

double f18_8 (StepParameters * CurrentValues){
      return 0;
}

double f18_9 (StepParameters * CurrentValues){
      return 0;
}

double f18_10 (StepParameters * CurrentValues){
      return 0;
}

double f18_11 (StepParameters * CurrentValues){
      return 0;
}

double f18_12 (StepParameters * CurrentValues){
      return 0;
}

double f18_13 (StepParameters * CurrentValues){
      return 0;
}

double f18_14 (StepParameters * CurrentValues){
      return 0;
}

double f18_15 (StepParameters * CurrentValues){
      return 0;
}

double f18_16 (StepParameters * CurrentValues){
      return 0;
}

double f18_17 (StepParameters * CurrentValues){
      return 0;
}

double f18_18 (StepParameters * CurrentValues){
      return 0;
}

double f18_19 (StepParameters * CurrentValues){
      return 0;
}

double f19_0 (StepParameters * CurrentValues){
      return 0;
}

double f19_1 (StepParameters * CurrentValues){
      return 0;
}

double f19_2 (StepParameters * CurrentValues){
      return 0;
}

double f19_3 (StepParameters * CurrentValues){
      return 0;
}

double f19_4 (StepParameters * CurrentValues){
      return 0;
}

double f19_5 (StepParameters * CurrentValues){
      return 0;
}

double f19_6 (StepParameters * CurrentValues){
      return 0;
}

double f19_7 (StepParameters * CurrentValues){
      return 0;
}

double f19_8 (StepParameters * CurrentValues){
      return 0;
}

double f19_9 (StepParameters * CurrentValues){
      return 0;
}

double f19_10 (StepParameters * CurrentValues){
      return 0;
}

double f19_11 (StepParameters * CurrentValues){
      return 0;
}

double f19_12 (StepParameters * CurrentValues){
      return 0;
}

double f19_13 (StepParameters * CurrentValues){
      return 0;
}

double f19_14 (StepParameters * CurrentValues){
      return 0;
}

double f19_15 (StepParameters * CurrentValues){
      return 0;
}

double f19_16 (StepParameters * CurrentValues){
      return 0;
}

double f19_17 (StepParameters * CurrentValues){
      return 0;
}

double f19_18 (StepParameters * CurrentValues){
      return 0;
}

double f19_19 (StepParameters * CurrentValues){
      return 0;
}


/* Tables Generated by the Right Hand Functions */

pfn_fi rhf_array[MAX_N]={f0,  f1,  f2,  f3,  f4,  f5,  f6,  f7,  f8,  f9, 
                         f10, f11, f12, f13, f14, f15, f16, f17, f18, f19};

pfn_fi rhft_array[MAX_N]={ft0,  ft1,  ft2,  ft3,  ft4,  ft5,  ft6,  ft7,  ft8,  ft9, 
                          ft10, ft11, ft12, ft13, ft14, ft15, ft16, ft17, ft18, ft19};

pfn_fi rhJacoby_matrix[][MAX_N]={
{f0_0,   f0_1,   f0_2,   f0_3,   f0_4,   f0_5,   f0_6,   f0_7,   f0_8,   f0_9, 
 f0_10,  f0_11,  f0_12,  f0_13,  f0_14,  f0_15,  f0_16,  f0_17,  f0_18,  f0_19},
{f1_0,   f1_1,   f1_2,   f1_3,   f1_4,   f1_5,   f1_6,   f1_7,   f1_8,   f1_9, 
 f1_10,  f1_11,  f1_12,  f1_13,  f1_14,  f1_15,  f1_16,  f1_17,  f1_18,  f1_19},
{f2_0,   f2_1,   f2_2,   f2_3,   f2_4,   f2_5,   f2_6,   f2_7,   f2_8,   f2_9, 
 f2_10,  f2_11,  f2_12,  f2_13,  f2_14,  f2_15,  f2_16,  f2_17,  f2_18,  f2_19},
{f3_0,   f3_1,   f3_2,   f3_3,   f3_4,   f3_5,   f3_6,   f3_7,   f3_8,   f3_9, 
 f3_10,  f3_11,  f3_12,  f3_13,  f3_14,  f3_15,  f3_16,  f3_17,  f3_18,  f3_19},
{f4_0,   f4_1,   f4_2,   f4_3,   f4_4,   f4_5,   f4_6,   f4_7,   f4_8,   f4_9, 
 f4_10,  f4_11,  f4_12,  f4_13,  f4_14,  f4_15,  f4_16,  f4_17,  f4_18,  f4_19},
{f5_0,   f5_1,   f5_2,   f5_3,   f5_4,   f5_5,   f5_6,   f5_7,   f5_8,   f5_9, 
 f5_10,  f5_11,  f5_12,  f5_13,  f5_14,  f5_15,  f5_16,  f5_17,  f5_18,  f5_19},
{f6_0,   f6_1,   f6_2,   f6_3,   f6_4,   f6_5,   f6_6,   f6_7,   f6_8,   f6_9, 
 f6_10,  f6_11,  f6_12,  f6_13,  f6_14,  f6_15,  f6_16,  f6_17,  f6_18,  f6_19},
{f7_0,   f7_1,   f7_2,   f7_3,   f7_4,   f7_5,   f7_6,   f7_7,   f7_8,   f7_9, 
 f7_10,  f7_11,  f7_12,  f7_13,  f7_14,  f7_15,  f7_16,  f7_17,  f7_18,  f7_19},
{f8_0,   f8_1,   f8_2,   f8_3,   f8_4,   f8_5,   f8_6,   f8_7,   f8_8,   f8_9, 
 f8_10,  f8_11,  f8_12,  f8_13,  f8_14,  f8_15,  f8_16,  f8_17,  f8_18,  f8_19},
{f9_0,   f9_1,   f9_2,   f9_3,   f9_4,   f9_5,   f9_6,   f9_7,   f9_8,   f9_9, 
 f9_10,  f9_11,  f9_12,  f9_13,  f9_14,  f9_15,  f9_16,  f9_17,  f9_18,  f9_19},
{f10_0,  f10_1,  f10_2,  f10_3,  f10_4,  f10_5,  f10_6,  f10_7,  f10_8,  f10_9, 
 f10_10, f10_11, f10_12, f10_13, f10_14, f10_15, f10_16, f10_17, f10_18, f10_19},
{f11_0,  f11_1,  f11_2,  f11_3,  f11_4,  f11_5,  f11_6,  f11_7,  f11_8,  f11_9, 
 f11_10, f11_11, f11_12, f11_13, f11_14, f11_15, f11_16, f11_17, f11_18, f11_19},
{f12_0,  f12_1,  f12_2,  f12_3,  f12_4,  f12_5,  f12_6,  f12_7,  f12_8,  f12_9, 
 f12_10, f12_11, f12_12, f12_13, f12_14, f12_15, f12_16, f12_17, f12_18, f12_19},
{f13_0,  f13_1,  f13_2,  f13_3,  f13_4,  f13_5,  f13_6,  f13_7,  f13_8,  f13_9, 
 f13_10, f13_11, f13_12, f13_13, f13_14, f13_15, f13_16, f13_17, f13_18, f13_19},
{f14_0,  f14_1,  f14_2,  f14_3,  f14_4,  f14_5,  f14_6,  f14_7,  f14_8,  f14_9, 
 f14_10, f14_11, f14_12, f14_13, f14_14, f14_15, f14_16, f14_17, f14_18, f14_19},
{f15_0,  f15_1,  f15_2,  f15_3,  f15_4,  f15_5,  f15_6,  f15_7,  f15_8,  f15_9, 
 f15_10, f15_11, f15_12, f15_13, f15_14, f15_15, f15_16, f15_17, f15_18, f15_19},
{f16_0,  f16_1,  f16_2,  f16_3,  f16_4,  f16_5,  f16_6,  f16_7,  f16_8,  f16_9, 
 f16_10, f16_11, f16_12, f16_13, f16_14, f16_15, f16_16, f16_17, f16_18, f16_19},
{f17_0,  f17_1,  f17_2,  f17_3,  f17_4,  f17_5,  f17_6,  f17_7,  f17_8,  f17_9, 
 f17_10, f17_11, f17_12, f17_13, f17_14, f17_15, f17_16, f17_17, f17_18, f17_19},
{f18_0,  f18_1,  f18_2,  f18_3,  f18_4,  f18_5,  f18_6,  f18_7,  f18_8,  f18_9, 
 f18_10, f18_11, f18_12, f18_13, f18_14, f18_15, f18_16, f18_17, f18_18, f18_19},
{f19_0, f19_1,  f19_2,  f19_3,  f19_4,  f19_5,  f19_6,  f19_7,  f19_8,  f19_9, 
 f19_10, f19_11, f19_12, f19_13, f19_14, f19_15, f19_16, f19_17, f19_18, f19_19}};
