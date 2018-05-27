/*== SOURCE file list of “compare.c” with Structure A ==*/ 
#define S_FUNCTION_LEVEL 2 
#define S_FUNCTION_NAME  compare
#include "simstruc.h"
#include <math.h>

#define U(element) (*uPtrs[element])  /*Pointer to Input Port0*/

static void mdlInitializeSizes(SimStruct *S){
	if (!ssSetNumInputPorts(S, 1)) return;
		ssSetInputPortWidth(S, 0, 2);
		ssSetInputPortDirectFeedThrough(S, 0, 1);
		ssSetInputPortOverWritable(S, 0, 1);
	
	if (!ssSetNumOutputPorts(S, 1)) return;
		ssSetOutputPortWidth(S, 0, 1);
		ssSetNumSampleTimes(S, 1);
		
	ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE); }

static void mdlInitializeSampleTimes(SimStruct *S) {
	ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
	ssSetOffsetTime(S, 0, 0.0); }

static void mdlOutputs(SimStruct *S, int_T tid) {
	real_T *Y = ssGetOutputPortRealSignal(S,0);
	InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
	
	if(U(0) >= U(1)){Y[0] = U(0);}
	else{Y[0] = U(1);}}

static void mdlTerminate(SimStruct *S)
{ } /*Keep this function empty since no memory is allocated*/

#ifdef  MATLAB_MEX_FILE
	/* Is this file being compiled as a MEX-file? */
	#include "simulink.c"    /* MEX-file interface mechanism */
#else
	#include "cg_sfun.h"  /*Code generation registration function*/
#endif