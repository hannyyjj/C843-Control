/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2015. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  P_BASIC_FN                       1       /* callback function: pFunctions */
#define  P_BASIC_FN_CMD_SIGNAL_SCOPE_RAW  2       /* control type: command, callback function: BasicFunctions */
#define  P_BASIC_FN_CMD_SIGNAL_SCOPE      3       /* control type: command, callback function: BasicFunctions */
#define  P_BASIC_FN_CMD_SHOW_UI           4       /* control type: command, callback function: BasicFunctions */
#define  P_BASIC_FN_CMD_VACUUM_SPIN       5       /* control type: command, callback function: BasicFunctions */
#define  P_BASIC_FN_CMD_READ_TURNING_KNOB 6       /* control type: command, callback function: BasicFunctions */
#define  P_BASIC_FN_CMD_PB_LOOP_BUTTON    7       /* control type: command, callback function: BasicFunctions */
#define  P_BASIC_FN_CMD_HOME_BUTTON       8       /* control type: command, callback function: BasicFunctions */
#define  P_BASIC_FN_CMD_READ_PUSH_BUTTON  9       /* control type: command, callback function: BasicFunctions */
#define  P_BASIC_FN_CMD_SET_DIR           10      /* control type: command, callback function: BasicFunctions */
#define  P_BASIC_FN_CMD_SAVE              11      /* control type: command, callback function: BasicFunctions */
#define  P_BASIC_FN_CMD_FIND_PUSH_BUTTON  12      /* control type: command, callback function: BasicFunctions */
#define  P_BASIC_FN_DECORATION_16         13      /* control type: deco, callback function: (none) */
#define  P_BASIC_FN_DECORATION_14         14      /* control type: deco, callback function: (none) */
#define  P_BASIC_FN_TXT_FUNCTIONS         15      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_TXT_PREVIEW_CURVE     16      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_DECORATION_19         17      /* control type: deco, callback function: (none) */
#define  P_BASIC_FN_TXT_DATA              18      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_TIM_DATA              19      /* control type: timer, callback function: BasicFunctions */
#define  P_BASIC_FN_TIM_IS_INIT           20      /* control type: timer, callback function: BasicFunctions */
#define  P_BASIC_FN_DECORATION_20         21      /* control type: deco, callback function: (none) */
#define  P_BASIC_FN_DECORATION_17         22      /* control type: deco, callback function: (none) */
#define  P_BASIC_FN_LBL_MAX_FORCE_5       23      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_MAX_FORCE_4       24      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_MAX_FORCE_3       25      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_MAX_FORCE_6       26      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_MAX_FORCE_2       27      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_MAX_FORCE         28      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_FILE              29      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_DIR_2             30      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_DIR               31      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_CS_5              32      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_CS_4              33      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_CS_3              34      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_CS_2              35      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_LBL_CS_1              36      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_GRA_CURVE             37      /* control type: graph, callback function: (none) */
#define  P_BASIC_FN_NUM_MAX_FORCE_3       38      /* control type: numeric, callback function: (none) */
#define  P_BASIC_FN_DECORATION_15         39      /* control type: deco, callback function: (none) */
#define  P_BASIC_FN_NUM_MAX_FORCE_1       40      /* control type: numeric, callback function: (none) */
#define  P_BASIC_FN_NUM_MAX_FORCE_2       41      /* control type: numeric, callback function: (none) */
#define  P_BASIC_FN_SWH_FNCT_MODE         42      /* control type: binary, callback function: BasicFunctions */
#define  P_BASIC_FN_SWH_DISPLAY_LAST_FIVE 43      /* control type: binary, callback function: BasicFunctions */
#define  P_BASIC_FN_SWH_DISPLAY_MODE      44      /* control type: binary, callback function: BasicFunctions */
#define  P_BASIC_FN_RNG_CURVE_SET_NO      45      /* control type: ring, callback function: (none) */
#define  P_BASIC_FN_RNG_FILE_NAME         46      /* control type: ring, callback function: BasicFunctions */
#define  P_BASIC_FN_RNG_VAR_NO            47      /* control type: ring, callback function: BasicFunctions */
#define  P_BASIC_FN_RNG_KEY_NO            48      /* control type: ring, callback function: BasicFunctions */
#define  P_BASIC_FN_RNG_SHOW_UI           49      /* control type: ring, callback function: BasicFunctions */
#define  P_BASIC_FN_STR_SEARCH_FILE       50      /* control type: string, callback function: BasicFunctions */
#define  P_BASIC_FN_STR_DIR_NAME          51      /* control type: string, callback function: (none) */
#define  P_BASIC_FN_LED_CURVE_SET_5_2     52      /* control type: LED, callback function: (none) */
#define  P_BASIC_FN_LED_CURVE_SET_5_1     53      /* control type: LED, callback function: (none) */
#define  P_BASIC_FN_LED_CURVE_SET_4_2     54      /* control type: LED, callback function: (none) */
#define  P_BASIC_FN_LED_CURVE_SET_4_1     55      /* control type: LED, callback function: (none) */
#define  P_BASIC_FN_LED_CURVE_SET_3_2     56      /* control type: LED, callback function: (none) */
#define  P_BASIC_FN_LED_CURVE_SET_3_1     57      /* control type: LED, callback function: (none) */
#define  P_BASIC_FN_LED_CURVE_SET_2_2     58      /* control type: LED, callback function: (none) */
#define  P_BASIC_FN_LED_CURVE_SET_2_1     59      /* control type: LED, callback function: (none) */
#define  P_BASIC_FN_LED_CURVE_SET_1_2     60      /* control type: LED, callback function: (none) */
#define  P_BASIC_FN_LED_CURVE_SET_1_1     61      /* control type: LED, callback function: (none) */
#define  P_BASIC_FN_TEXTMSG_3             62      /* control type: textMsg, callback function: BasicFunctions */
#define  P_BASIC_FN_TEXTMSG_2             63      /* control type: textMsg, callback function: BasicFunctions */
#define  P_BASIC_FN_TEXTMSG_4             64      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_TEXTMSG               65      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_CMD_PRINT             66      /* control type: command, callback function: BasicFunctions */
#define  P_BASIC_FN_TK_LEFT_ONLY          67      /* control type: radioButton, callback function: BasicFunctions */
#define  P_BASIC_FN_CANVAS_F4             68      /* control type: canvas, callback function: (none) */
#define  P_BASIC_FN_CANVAS_F1             69      /* control type: canvas, callback function: (none) */
#define  P_BASIC_FN_CANVAS_F2             70      /* control type: canvas, callback function: (none) */
#define  P_BASIC_FN_CANVAS_F3             71      /* control type: canvas, callback function: (none) */
#define  P_BASIC_FN_DECORATION            72      /* control type: deco, callback function: (none) */
#define  P_BASIC_FN_TEXTMSG_SNP1          73      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_TEXTMSG_SNP2          74      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_TEXTMSG_S2_S1         75      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_TEXTMSG_S3_S4         76      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_TEXTMSG_R_SNP1        77      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_TEXTMSG_R_SNP2        78      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_TEXTMSG_R_S2_S1       79      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_TEXTMSG_R_S3_S4       80      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_STR_MOTOR_POS         81      /* control type: string, callback function: (none) */
#define  P_BASIC_FN_TIM_PB_RETRY          82      /* control type: timer, callback function: LoopFunctions */
#define  P_BASIC_FN_TIM_MOTOR_POS         83      /* control type: timer, callback function: BasicFunctions */
#define  P_BASIC_FN_SWITCH_DREH_MODE      84      /* control type: binary, callback function: BasicFunctions */
#define  P_BASIC_FN_SWITCH_SENSOR         85      /* control type: binary, callback function: BasicFunctions */
#define  P_BASIC_FN_TEXTMSG_5             86      /* control type: textMsg, callback function: (none) */
#define  P_BASIC_FN_DECORATION_2          87      /* control type: deco, callback function: (none) */

#define  PANEL                            2


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK BasicFunctions(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LoopFunctions(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK pFunctions(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
