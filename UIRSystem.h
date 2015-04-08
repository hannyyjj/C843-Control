/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2008. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  P_SYSTEM                        1       /* callback function: pFunctions */
#define  P_SYSTEM_CMD_DEINIT             2       /* callback function: SystemFunctions */

#define  P_SYSTEM_CMD_LOAD_HWCONFIG_INI  3       /* callback function: SystemFunctions */
#define  P_SYSTEM_CMD_LOAD_INI           4       /* callback function: SystemFunctions */
#define  P_SYSTEM_DECORATION_5           5
#define  P_SYSTEM_LED_PI_IS_INIT         6
#define  P_SYSTEM_LED_NI_IS_INIT         7
#define  P_SYSTEM_LED_ACT_IS_INIT        8
#define  P_SYSTEM_LED_AMP_IS_INIT        9
#define  P_SYSTEM_DECORATION_12          10
#define  P_SYSTEM_LBL_ERROR_CODE         11
#define  P_SYSTEM_LBL_ERROR_CODE_2       12
#define  P_SYSTEM_STR_SENSOR_INI_FILE    13
#define  P_SYSTEM_STR_HW_INI_FILE        14


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK pFunctions(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SystemFunctions(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
