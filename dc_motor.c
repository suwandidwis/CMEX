#define S_FUNCTION_LEVEL 2                                                       
#define S_FUNCTION_NAME dc_motor                                             
#include "simstruc.h"                                                                           
#include <math.h>                                                                                

#define U(element) (*uPtrs0[element])		

static void mdlInitializeSizes(SimStruct *S)
{                                   
  ssSetNumContStates(S, 10);                                                               

  if (!ssSetNumInputPorts(S, 1)) return;                                            
  ssSetInputPortWidth(S, 0, 1);                                                          
  ssSetInputPortDirectFeedThrough(S, 0, 1);                                   
  ssSetInputPortOverWritable(S, 0, 1);                                            

  if (!ssSetNumOutputPorts(S, 1)) return;                                        
  ssSetOutputPortWidth(S, 0, 1);                                                         

  ssSetNumSampleTimes(S, 1);                                                            
                                                                                                              
  ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE); 
}    
                                                                                                              
static void mdlInitializeSampleTimes(SimStruct *S) 
{                   
  ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);         

  ssSetOffsetTime(S, 0, 0.0); 
}                                                              
                                                                                                             
#define MDL_INITIALIZE_CONDITIONS                                  
static void mdlInitializeConditions(SimStruct *S) 
{                                                                                                                  
  real_T 	*X0 = ssGetContStates(S);                                       
  int_T 	nStates = ssGetNumContStates(S);                         
  int_T 	i;                                                                                  
                                                                                                            
  /* initialize the states to 0.0 */                                                            
  for (i=0; i < nStates; i++) 
	{
	X0[i] = 0.0;
	}
}                                       
                                                                                                              
static void mdlOutputs(SimStruct *S, int_T tid) 
{                          
  real_T            *Y = ssGetOutputPortRealSignal(S,0);                  
  real_T            *X = ssGetContStates(S);                                         
  InputRealPtrsType uPtrs0 = ssGetInputPortRealSignalPtrs(S,0);  

  real_T tetadot;
  
  tetadot = X[0];
  Y[0]= tetadot;
}                                                                                           

#define MDL_DERIVATIVES                                                          
static void mdlDerivatives(SimStruct *S) 
{                                      
  real_T  *dX = ssGetdX(S);                                                               
  real_T  *X = ssGetContStates(S);                                                    
  InputRealPtrsType uPtrs0 = ssGetInputPortRealSignalPtrs(S,0);  
  
  /* variables */
  real_T tetadot, i, v;
  real_T J, b, K, R, L;
  real_T tetadot2, idot;
  
  /* motor parameters */
  J = 0.01;
  b = 0.1;
  K = 0.01;
  R = 1;
  L = 0.5;
  
  /* input */
  v = U(0);
  
  /* update state data */
  tetadot = X[0];
  i = X[1];
  
  /* dc motor model */
  tetadot2 = -(b/J)*tetadot + (K/J)*i;
  idot = -(K/L)*tetadot - (R/L)*i + (1/L)*v;

  /* update state data */
  dX[0] = tetadot2;
  dX[1] = idot;
  
}

   
static void mdlTerminate(SimStruct *S)                                         
{}
                                                                                                            
#ifdef  MATLAB_MEX_FILE                                                        
                           
#include "simulink.c"  
#else                                                                                                   
#include "cg_sfun.h"
#endif      
                                                                                           