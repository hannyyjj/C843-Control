/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2006. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  P_CTRL_PAD                      1       /* callback function: pFunctions */
#define  P_CTRL_PAD_CMD_RESET_LAST_POS   2       /* callback function: CtrlPadFunctions */
#define  P_CTRL_PAD_CMD_HOME             3       /* callback function: CtrlPadFunctions */
#define  P_CTRL_PAD_CMD_LEFT             4       /* callback function: CtrlPadFunctions */
#define  P_CTRL_PAD_DECORATION           5
#define  P_CTRL_PAD_DECORATION_13        6
#define  P_CTRL_PAD_LBL_POSITION_2       7
#define  P_CTRL_PAD_LBL_POSITION_3       8
#define  P_CTRL_PAD_LBL_TURN_RIGHT_3     9
#define  P_CTRL_PAD_LBL_TURN_RIGHT_2     10
#define  P_CTRL_PAD_LBL_TURN_LEFT_3      11
#define  P_CTRL_PAD_CMD_RIGHT            12      /* callback function: CtrlPadFunctions */
#define  P_CTRL_PAD_LBL_TURN_LEFT_2      13
#define  P_CTRL_PAD_CMD_MOVE             14      /* callback function: CtrlPadFunctions */
#define  P_CTRL_PAD_LBL_STEP_DOWN_3      15
#define  P_CTRL_PAD_CMD_DOWN             16      /* callback function: CtrlPadFunctions */
#define  P_CTRL_PAD_LBL_STEP_DOWN_2      17
#define  P_CTRL_PAD_CMD_STOP             18      /* callback function: CtrlPadFunctions */
#define  P_CTRL_PAD_LBL_STEP_UP_3        19
#define  P_CTRL_PAD_CMD_UP               20      /* callback function: CtrlPadFunctions */
#define  P_CTRL_PAD_LBL_STEP_UP_2        21
#define  P_CTRL_PAD_LED_ACTIVE           22
#define  P_CTRL_PAD_NUM_TURN_RIGHT       23      /* callback function: BasicFunctions */
#define  P_CTRL_PAD_NUM_TURN_LEFT        24      /* callback function: BasicFunctions */
#define  P_CTRL_PAD_NUM_POSITION         25      /* callback function: BasicFunctions */
#define  P_CTRL_PAD_NUM_STEP_DOWN        26      /* callback function: BasicFunctions */
#define  P_CTRL_PAD_NUM_STEP_UP          27      /* callback function: BasicFunctions */
#define  P_CTRL_PAD_TGL_MODE             28      /* callback function: CtrlPadFunctions */
#define  P_CTRL_PAD_DECORATION_12        29
#define  P_CTRL_PAD_LBL_ERROR_CODE       30
#define  P_CTRL_PAD_LBL_CURRENT_POS_4    31
#define  P_CTRL_PAD_LBL_LAST_POS         32
#define  P_CTRL_PAD_LBL_ERROR_CODE_2     33
#define  P_CTRL_PAD_LBL_CURRENT_POS_5    34
#define  P_CTRL_PAD_LBL_CURRENT_POS_6    35
#define  P_CTRL_PAD_LBL_LAST_POS_3       36
#define  P_CTRL_PAD_LBL_LAST_POS_2       37


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK BasicFunctions(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CtrlPadFunctions(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK pFunctions(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
