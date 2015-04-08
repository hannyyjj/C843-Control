// Hardware
#include "C843_GCS_DLL.h"
#include "C843cmd.h"
/*
#include <easyio.h>
#include <dataacq.h>
#include <analysis.h>      */

// CVI
#include <utility.h>
#include <ansi_c.h>
//#include "inifile.h"
#include <userint.h>

// System

#include "PiCard.h"
#include "NiCard.h"

/*
#include "Data.h"
#include "BasicFnct.h"
#include "InternGlobals.h"
*/

// Interfaces

#include "UIRBasicFnct.h"
#include "UIRSystem.h"

// Error Codes
#define ERR_NO_ERROR    0

// Struct
struct PiDcMotCtrlCardStruct srctPiCard;

// Global Variables
double mChargeSensorPos1 = 0.0, mChargeSensorNeg1 = 0.0;
double mChargeSensorPos2 = 0.0, mChargeSensorNeg2 = 0.0;
char mAxesNo1[10], mAxesNo2[10];

double mLastMovePosAxe1 = 0.0, mLastMovePosAxe2 = 0.0;

BOOL  Is_ref_OK = 1,
      Ref_result = 1,
      Is_ref = 1,
      Is_move = 1;

int PiCardFnct (int iMode)
{
    BOOL bStatus = ERR_NO_ERROR;

  int test,
      iCmd,
      iVal;

  int *piCmd = &iCmd,
      *piVal = &iVal;

  double dVal;
  double *pdVal = &dVal;

  srctPiCard.dHome = 0.0000;
  
  switch (iMode)
  {
    case PI_CONNECT:
      srctPiCard.iId = C843_Connect (srctPiCard.iCardNo);

      if (srctPiCard.iId < 0)
      {
        PiCardFnct (PI_GET_ERROR);
        DebugPrintf ("Error Code <%d> in PiCardFnct [case CONNECT]\n", srctPiCard.iErrorCode);

        return RET_PI_CARD_CONNECT_ERR;
      }

      DebugPrintf("---> [PI_CONNECT]  srctPiCard.iCardNo = %d  srctPiCard.iId = %d\n", srctPiCard.iCardNo, srctPiCard.iId);
      
      break;
      
////---------------------------------------------------------------------------------------------------------------------
      
    case PI_INIT:
        
      C843_CST (srctPiCard.iId, "1", srctPiCard.sEngineName);
      if (C843_CST (srctPiCard.iId, "", srctPiCard.sEngineName) == FALSE)
      {
        test = C843_GetError(srctPiCard.iId);
        DebugPrintf("Fehler CST\nError: %d", test);
      }
        
      C843_INI (srctPiCard.iId, "1");
      if (C843_INI (srctPiCard.iId, "") == FALSE)
      {
        test = C843_GetError(srctPiCard.iId);
        DebugPrintf("Fehler INI\nError: %d", test);
      }
        
      
// Max. Beschleunigung einstellen      
      iCmd = ACC;
      dVal = srctPiCard.dAcceleration;
      C843_SPA (srctPiCard.iId, "1", piCmd, pdVal, NULL);
      
// Max. Verzögerung einstellen
      iCmd = DEC;
      dVal = srctPiCard.dDeceleration;
      C843_SPA (srctPiCard.iId, "1", piCmd, pdVal, NULL);                         

// Max. Geschwindigkeit einstellen
      iCmd = VEL;
      dVal = srctPiCard.dMaxVelocity;
      C843_SPA (srctPiCard.iId, "1", piCmd, pdVal, NULL);
      
// Geschwindigkeit einstellen 
      dVal = srctPiCard.dVelocity;
      C843_VEL (srctPiCard.iId, "1", pdVal);                                      

      
// Referenzieren      
      iVal = 0;

      C843_RON(srctPiCard.iId, "", piVal);
      if (C843_RON(srctPiCard.iId, "", piVal) == FALSE)
      {
        DebugPrintf("Fehler RON\n");
        exit(0);
      }
      else
        DebugPrintf("RON OK\n");
      
      C843_REF(srctPiCard.iId, "1");
      while (Is_ref_OK == 1)
        C843_IsReferencing(srctPiCard.iId, "1", &Is_ref_OK);
      
      C843_IsReferenceOK(srctPiCard.iId, "", &Is_ref);
      
      if (C843_GetRefResult(srctPiCard.iId, "", &Ref_result) == FALSE)
        exit(0);
      else
        DebugPrintf("Ref OK\n");

      C843_POS(srctPiCard.iId, "1", &srctPiCard.dHome);
      C843_qPOS(srctPiCard.iId, "1", &srctPiCard.dParam1);
        DebugPrintf("qPOS(): %f\n", srctPiCard.dParam1);
      
      srctPiCard.iCardIsInit = 2;
      
    break;
    
// -------------------------------------------------------------------------------------------------------------------
    
    case PI_GET_ERROR:
      if (srctPiCard.iCardIsInit == 2)
        srctPiCard.iErrorCode = C843_GetError (srctPiCard.iId);

    break;
    
// --------------------------------------------------------------------------------------------------------------------
    
    case PI_MOVE_UP:
      if (srctPiCard.iCardIsInit == 2)
      {
          dVal = srctPiCard.dParam1;
          DebugPrintf("Move Up: %f\n", dVal);
          C843_MVR (srctPiCard.iId, "1", pdVal);
      }
      
    break;
          
    case PI_MOVE_DOWN:
      if (srctPiCard.iCardIsInit == 2)
      {
        dVal = srctPiCard.dParam1;
        DebugPrintf("Move Down: %f\n", dVal);
        C843_MVR (srctPiCard.iId, "1", pdVal);
      } 

      break;
      
// ---------------------------------------------------------------------------------------------------------------------
      
    case PI_HOME:
        if (srctPiCard.iCardIsInit == 2)
        {
            dVal = srctPiCard.dHome;
            C843_MOV(srctPiCard.iId, "1", pdVal);
            
        //    srctPiCard.dLastPosition = srctPiCard.dHome;
        //    PiCardFnct (PI_WAIT_FOR_STOP);
        }
        
    break;
        
// ----------------------------------------------------------------------------------------------------------------------
        
    case PI_MOVE_REL:
        if (srctPiCard.iCardIsInit == 2)
        {
            dVal = srctPiCard.dParam1;
            
            C843_MVR (srctPiCard.iId, "1", pdVal);
            
       //     srctPiCard.dLastPosition = srctPiCard.dParam1;
        }
        
    break;
    
    case PI_MOVE_ABS:
        if (srctPiCard.iCardIsInit == 2)
        {
            
            dVal = srctPiCard.dParam1;
            DebugPrintf("Move ABS: %f\n", dVal);
            C843_MOV(srctPiCard.iId, "1", pdVal);
            
            srctPiCard.dLastPosition = srctPiCard.dParam1;
            PiCardFnct(PI_SAVE_LAST_POS);
            
        }
        
    break;
    
// ---------------------------------------------------------------------------------------------------------------
    
    case PI_GET_POS:
        if (srctPiCard.iCardIsInit == 2)
        {
            if (!bStatus) bStatus = !C843_qPOS (srctPiCard.iId, "1", &srctPiCard.dPosition);
            
            if (bStatus)
            {
                PiCardFnct (PI_GET_ERROR);
                DebugPrintf ("Error Code <%d> in PiCardFnct [case GET_POS]\n", srctPiCard.iErrorCode);
                
                return RET_PI_CARD_GET_POS_ERR;
            }
        }
        
    break;
    
// --------------------------------------------------------------------------------------------------------------
    
    case PI_MOVING:
        if (srctPiCard.iCardIsInit == 2)
        {
            if (!bStatus) bStatus = !C843_IsMoving(srctPiCard.iId, "", &srctPiCard.bIsMoving);
            
            if (bStatus)
            {
                PiCardFnct (PI_GET_ERROR);
                DebugPrintf ("Error Code <%d> in PiCardFnct [case MOVING]\n", srctPiCard.iErrorCode);
                
                return RET_PI_CARD_MOVING_ERR;
            }
        }
        
    break;
    
// ---------------------------------------------------------------------------------------------------------------
    
        
  }
  
    return 0;
    
}

int SetPiCardScrtItem (int iItem, int iMode, ...)
{
  va_list vaList;
  
  va_start (vaList, iMode);
  
  switch (iMode)
  {
    
    case 1:    // Double

      switch (iItem)
      {
        case PI_PARAM_1:            srctPiCard.dParam1           = va_arg (vaList, double);     break;
        case PI_PARAM_2:            srctPiCard.dParam2           = va_arg (vaList, double);     break;
        case PI_PARAM_3:            srctPiCard.dParam3           = va_arg (vaList, double);     break;
        case PI_ACCELERATION:       srctPiCard.dAcceleration     = va_arg (vaList, double);     break;
        case PI_DECELERATION:       srctPiCard.dDeceleration     = va_arg (vaList, double);     break;

        case PI_VELOCITY:
          srctPiCard.dVelocity = va_arg (vaList, double);
          DebugPrintf("SetPiCardScrtItem dVelocity=%e\n",srctPiCard.dVelocity); 
          break;

        case PI_NEW_POS:            srctPiCard.dNewPosition      = va_arg (vaList, double);     break;
        case PI_POS:                srctPiCard.dPosition         = va_arg (vaList, double);     break;
        case PI_LAST_POS:           srctPiCard.dLastPosition     = va_arg (vaList, double);     break;
        case PI_MAX_AMP_CAPA:       srctPiCard.dMaxAmpCapa       = va_arg (vaList, double);     break;
        case PI_MAX_AMP_VOLT:       srctPiCard.dMaxAmpVolt       = va_arg (vaList, double);     break;
        case PI_MULT_DISTANCE:      srctPiCard.dMultDistance     = va_arg (vaList, double);     break;
        case PI_CHARGE_SENSOR_POS:  srctPiCard.dChargeSensorPos  = va_arg (vaList, double);     break;
        case PI_CHARGE_SENSOR_NEG:  srctPiCard.dChargeSensorNeg  = va_arg (vaList, double);     break;
        default:                    return 1;
      } 

      break;
  }
  
    
    return 0;
    
}

// ------------------------------------------------------------------------------------------------
int GetPiCardScrtItem (int iItem, int iMode, void *vResult)
{
  switch (iMode)
  {
    case 1:

      switch (iItem)
      {
        case PI_PARAM_1:            *((double *) vResult) = srctPiCard.dParam1;               break;
        case PI_PARAM_2:            *((double *) vResult) = srctPiCard.dParam2;               break;
        case PI_PARAM_3:            *((double *) vResult) = srctPiCard.dParam3;               break;
        case PI_ACCELERATION:       *((double *) vResult) = srctPiCard.dAcceleration;         break;
        case PI_DECELERATION:       *((double *) vResult) = srctPiCard.dDeceleration;         break;
        case PI_VELOCITY:           *((double *) vResult) = srctPiCard.dVelocity;             break;
        case PI_NEW_POS:            *((double *) vResult) = srctPiCard.dNewPosition;          break;
        case PI_POS:                *((double *) vResult) = srctPiCard.dPosition;             break;
        case PI_LAST_POS:           *((double *) vResult) = srctPiCard.dLastPosition;         break;
        case PI_MAX_AMP_CAPA:       *((double *) vResult) = srctPiCard.dMaxAmpCapa;           break;
        case PI_MAX_AMP_VOLT:       *((double *) vResult) = srctPiCard.dMaxAmpVolt;           break;
        case PI_MULT_DISTANCE:      *((double *) vResult) = srctPiCard.dMultDistance;         break;
        case PI_CHARGE_SENSOR_POS:  *((double *) vResult) = srctPiCard.dChargeSensorPos;      break;
        case PI_CHARGE_SENSOR_NEG:  *((double *) vResult) = srctPiCard.dChargeSensorNeg;      break;
        default:                    *((double *) vResult) = 0.0;                              return 1;
      } 

      break;

    default:
      return 1;
  } // End "switch (iMode)"



  return 0;
} // End "int GetPiCardScrtItem (int iItem, void *vResult, int iMode)"

