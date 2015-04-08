// -------- System

#include <utility.h>
#include <userint.h>
#include <formatio.h>
#include <ansi_c.h>

// -------- Interfaces

#include "UIRBasicFnct.h"
#include "UIRSystem.h"
#include "UIRControlPad.h"

// ------- System -------

#include "PiCard.h"
#include "NiCard.h"

#define XBASIC_FNCT_VERSION             "0.1"
#define XBASIC_FNCT_LAST_MODIFICATION   "08.04.2015"

#define MIN_VAL                         0
#define MAX_VAL                         1

#define MAX_NO_OF_PLOTS                 5

#define RAW_DATA                        0
#define DATA                            1

#define NO_OF_COLOR_SETS                5

#define LAST_ITEM                       -1

#define NO_OF_PB_RESULTS                26
#define NO_OF_TK_RESULTS_2              32
#define NO_OF_TK_RESULTS_3              4

#define DESC_LBL_LEFT                   0
#define DESC_LBL_RIGHT                  1
#define DATA_RES                        0
#define RES_LBL                         1
#define DESC_LBL                        1
#define BU_LBL                          2
#define RU_LBL                          3
#define BU_OP                           4
#define RU_OP                           5

BOOL bDisplayLastFive = OFF,
     bDataMode        = RAW_DATA;

char   sDirName             [MAX_PATHNAME_LEN+1],
       sDirSelect           [MAX_PATHNAME_LEN+1],
       sPushButtonFile      [MAX_PATHNAME_LEN+1],
       sTurningKnobFile     [MAX_PATHNAME_LEN+1],
       sPushButtonFileIni   [MAX_PATHNAME_LEN+1],
       sTurningKnobFileIni  [MAX_PATHNAME_LEN+1],
       sFileName            [MAX_FILENAME_LEN+1],
       sDmcName             [MAX_FILENAME_LEN+1],
       sSearchName          [MAX_FILENAME_LEN+1],
       sHWConfigFile        [MAX_PATHNAME_LEN+1],
       sHWConfigFileIni     [MAX_PATHNAME_LEN+1],
       sDirNamePB           [MAX_PATHNAME_LEN+1],
       sDirNameTK           [MAX_PATHNAME_LEN+1];
char   sInitAtStart         [10];
char   sPbLoopAtStart       [10];

double  *pdDataBuffer    [MAX_NO_OF_PLOTS][NO_OF_DIRECTIONS]; 
unsigned long ulEndPos   [MAX_NO_OF_PLOTS];

int    iColPairs [NO_OF_COLOR_SETS][NO_OF_DIRECTIONS] = {0xFF8040, 0x008000,
                                                         0x0000FF, 0xFF0000,
                                                         0x808000, 0x8080FF,
                                                         0x00FF80, 0xFF80FF,
                                                         0x00FFFF, 0x800000};

int    iYeColSlide [NO_OF_COLOR_SETS]  = {0xFF8040,
                                          0x0000FF,
                                          0x808000,
                                          0x00FF80,
                                          0x00FFFF
                                          };

int    iGnColSlide [NO_OF_COLOR_SETS]  = {0x008000,
                                          0xFF0000,
                                          0x8080FF,
                                          0xFF80FF,
                                          0x800000
                                          };

#define COLOR_GREEN                   0x00FF40
#define COLOR_GRAY                    0xE0DFE3

#define DREH_MODE_ANSCHLAG            1
#define DREH_MODE_360_GRAD            2

#define TK_RESULTS_1                  32
#define TK_RESULTS_2                  4
#define DATA_SKIP                     -1
int SetStepResults (int AktDrehSt);

#define CTRL_HIDE                     0
#define CTRL_VISIBLE                  1
void SetAddResControl (int Mode);

void Calculate (void);
void CheckError (void);
void GetFileList (void);
void GetCurveSet (int iCurveSet);
void ClearCurveSet(BOOL bInit);
void ClearCurve(int iCurveSet,BOOL bInit);
void GetDefaultSettings(void);
void SetDefaultSettings(void);
void SetPlotResults (int iCnt, double dVal);
void ClearPlotResults (void);
void SetFileInfo (char *FileName, char *FilePath);

int  DisplayData (int iDisplayMode);
int  ResultStatus;
int  mTKLeftOnly;
int  iFunctionModeChange = 0;
int  mPBGeraet = 1;
int  mTurningKnob = 0;
int  mAktivSensor;
int  mDrehMode = DREH_MODE_360_GRAD;

// Structs
struct PiDcMotCtrlCardStruct srctPiCard;

// UIR
static int pBasicFn, pSystem, pControlPad;   

// pConfig, pControlPad, pSystem, pMonitor, pResult;


int iFnctMode, iDispMode, iLastFive, iSwitchSens, iDrehMode, iCtrlVal;

int main (int argc, char *argv[])
{
    if (InitCVIRTE (0, argv, 0) == 0)
        return -1;  /* out of memory */      
    if ((pBasicFn = LoadPanel (0, "UIRBasicFnct.uir", P_BASIC_FN)) < 0)
        return -1;
    if ((pSystem = LoadPanel (0, "UIRSystem.uir", P_SYSTEM)) < 0)
        return -1;
    if ((pControlPad = LoadPanel (0, "UIRControlPad.uir", P_CTRL_PAD)) < 0)
        return -1;
    
    GetCtrlVal (pBasicFn, P_BASIC_FN_SWH_FNCT_MODE,         &iFnctMode);
    GetCtrlVal (pBasicFn, P_BASIC_FN_SWH_DISPLAY_MODE,      &iDispMode);
    GetCtrlVal (pBasicFn, P_BASIC_FN_SWH_DISPLAY_LAST_FIVE, &iLastFive);
    GetCtrlVal (pBasicFn, P_BASIC_FN_SWITCH_SENSOR,         &iSwitchSens);
    GetCtrlVal (pBasicFn, P_BASIC_FN_SWITCH_DREH_MODE,      &iDrehMode);
    
    SetCtrlAttribute (pSystem, P_SYSTEM_CMD_DEINIT,             ATTR_DIMMED, 1);
    
    DisplayPanel (pBasicFn);
    RunUserInterface ();
    DiscardPanel (pBasicFn);
    
    return 0;
}
    
int CVICALLBACK BasicFunctions (int panel, int control, int event,
                                void *callbackData, int eventData1, int eventData2)
{
    double dState;
    
    char sTmp [4096];
    
    switch (event)
    {
        case EVENT_COMMIT:
            switch(control)
            {
                case P_BASIC_FN_RNG_SHOW_UI:
                    
                    GetCtrlVal (pBasicFn, P_BASIC_FN_RNG_SHOW_UI, &iCtrlVal);
                    
                    switch(iCtrlVal)
                    {
                        case 0:
                            DisplayPanel (pSystem);
                        break;
                        
                        case 1:
                            DisplayPanel (pControlPad);
                            SetCtrlAttribute (pBasicFn, P_BASIC_FN_TIM_DATA, ATTR_ENABLED, 1);
                        break;
                    }
            }

        break;
        
        case EVENT_TIMER_TICK:
            switch (control)
            {
                case P_BASIC_FN_TIM_DATA:
                
               //     DebugPrintf ("---> [P_BASIC_FN_TIM_DATA]\n");
                
                    PiCardFnct (PI_GET_POS);
                    GetPiCardScrtItem (PI_POS, 1, &dState);
                    sprintf (sTmp, "%f", dState);
                
                    SetCtrlVal (pControlPad, P_CTRL_PAD_LBL_CURRENT_POS_4, sTmp);
                
                    GetPiCardScrtItem (PI_LAST_POS, 1, &dState);
                    sprintf (sTmp, "%f", dState);
                
                    SetCtrlVal (pControlPad, P_CTRL_PAD_LBL_LAST_POS, sTmp);
                
                 break;
            }
    }
    return 0;
}

int CVICALLBACK LoopFunctions (int panel, int control, int event,
                               void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_TIMER_TICK:

        break;
    }
    return 0;
}

int CVICALLBACK pFunctions (int panel, int event, void *callbackData,
                            int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_KEYPRESS:
        if(eventData1 == VAL_END_VKEY)            // Escape == Panel schliessen
        {
            if(panel != pBasicFn)
                HidePanel(panel);
        }
        break;
        
        case EVENT_CLOSE:
            if (panel == pSystem)
                HidePanel(pSystem);
            if (panel == pBasicFn)
            {
                PiCardFnct (PI_HOME);
                QuitUserInterface(0);
            }
            if (panel == pControlPad)
                HidePanel(pControlPad);
        break;
    }
    return 0;
}

int CVICALLBACK SystemFunctions (int panel, int control, int event,
                                 void *callbackData, int eventData1, int eventData2)
{
    char msg[512], maxpathlen[5200];
    int cnt = 0, ioerr = 0;
    int line, hwfile = -1, senini = -1;
    
    switch (event)
    {
        case EVENT_LEFT_CLICK:
            switch(control)
            {
                case P_SYSTEM_CMD_LOAD_HWCONFIG_INI:
                                                                    // Load HWConfig.ini File + Init
                    if (FileSelectPopup ("c:\\Users\\uid500qz\\Desktop\\123\\Haptik\\Ini", "*.ini", ".ini", "Load", VAL_OK_BUTTON, 0, 0, 1, 0, maxpathlen) == (1 || 2))
                    {
                        hwfile = OpenFile(maxpathlen, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
                        while(1)
                        {
                            ioerr = ReadLine(hwfile, msg, -1);               // Read every Line
                            if (ioerr == -2)
                                break;
                            if (ioerr == -1)
                                line = __LINE__;
                            
                            cnt++;                                           // Line Counter

                            switch(cnt)                                       // Werte in Struct übergeben
                            {
                                case 3:
                                    srctPiCard.iCardNo = atoi(msg);
                                break;
                                case 5:
                                    srctPiCard.dDelayOffset = atof(msg);
                                break;
                            }
                            
                        }
                        
                        SetFilePtr(hwfile, 0, 0);
                        DebugPrintf("iCardNo: %d\n", srctPiCard.iCardNo);
                        SetCtrlVal(pSystem, P_SYSTEM_STR_HW_INI_FILE, maxpathlen);
                        SetCtrlAttribute (pSystem, P_SYSTEM_CMD_LOAD_INI,             ATTR_DIMMED, 0);
                        SetCtrlAttribute (pSystem, P_SYSTEM_STR_SENSOR_INI_FILE,      ATTR_DIMMED, 0);
                    }
                    
                break;
                
                case P_SYSTEM_CMD_LOAD_INI:
                    
                    if (FileSelectPopup ("c:\\Users\\uid500qz\\Desktop\\123\\Haptik\\Ini", "*.ini", ".ini", "Load", VAL_OK_BUTTON, 0, 0, 1, 0, maxpathlen) == (1 || 2))
                    {
                        senini = OpenFile(maxpathlen, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
                        while(1)
                        {
                            ioerr = ReadLine(senini, msg, -1);               // Read every Line
                            if (ioerr == -2)
                                break;
                            if (ioerr == -1)
                            {
                                line = __LINE__;
                            }
                            cnt++;
                            
                            switch(cnt)
                            {
                                case 5:
                                    srctPiCard.dMaxAmpVolt = atof(msg);
                                break;
                                
                                case 9:
                                    srctPiCard.dMaxAmpCapa = atof(msg);
                                break;
                                
                                case 15:
                                    srctPiCard.dChargeSensorPos = atof(msg);
                                break;
                                
                                case 17:
                                    srctPiCard.dChargeSensorNeg = atof(msg);
                                break;
                                
                                case 38:
                                    for (int j = 0; j <= 10; j++)
                                    {
                                        srctPiCard.sEngineName[j] = msg[j];
                                    }           
                                break;        
                                
                                case 40:
                                    srctPiCard.dMultDistance = atof(msg);
                                break;
                                
                                case 42:
                                    srctPiCard.dAcceleration = atof(msg);
                                break;
                                
                                case 43:
                                    srctPiCard.dDeceleration = atof(msg);
                                break;
                                
                                case 46:
                                    srctPiCard.dVelocity = atof(msg);
                                break;
                                
                                case 48:
                                    srctPiCard.dMaxVelocity = atof(msg);
                                break;
                                
                                case 50:
                                    srctPiCard.dMaxMove = atof(msg);
                                break;
                                
                                case 52:
                                    srctPiCard.dMaxSpin = atof(msg);
                                break;
                                
                                case 44:
                                    srctPiCard.iOverSampling = atoi(msg);
                                break;
                            }
                            
                        }
                        
                        SetFilePtr(senini, 0, 0);
                        
                    }
                    
                    SetCtrlVal (pSystem, P_SYSTEM_STR_SENSOR_INI_FILE, maxpathlen);
                    SetCtrlAttribute (pSystem, P_SYSTEM_CMD_DEINIT,             ATTR_DIMMED, 0);
                    SetCtrlAttribute (pSystem, P_SYSTEM_CMD_LOAD_INI,           ATTR_DIMMED, 1);
                    SetCtrlAttribute (pSystem, P_SYSTEM_CMD_LOAD_HWCONFIG_INI,  ATTR_DIMMED, 1);
                    
                    DebugPrintf ("srctPiCard.iId: %d.\n", srctPiCard.iId); 
                    DebugPrintf ("sEngineName: %s\n", srctPiCard.sEngineName);
                    
                    PiCardFnct (PI_CONNECT);
                    PiCardFnct (PI_INIT);
                    
                    SetCtrlVal (pSystem, P_SYSTEM_LED_PI_IS_INIT, 1);
                    SetCtrlVal (pControlPad, P_CTRL_PAD_LED_ACTIVE, 1);
                    
                    PiCardFnct (PI_HOME);
                        
                break;
                
                case P_SYSTEM_CMD_DEINIT:
                    
                    memset(&srctPiCard, 0, sizeof(srctPiCard));
                    
                    SetCtrlVal (pSystem, P_SYSTEM_STR_HW_INI_FILE, "");
                    SetCtrlVal (pSystem, P_SYSTEM_STR_SENSOR_INI_FILE, "");
                    SetCtrlAttribute (pSystem, P_SYSTEM_CMD_DEINIT,             ATTR_DIMMED, 1);
                    SetCtrlAttribute (pSystem, P_SYSTEM_CMD_LOAD_INI,           ATTR_DIMMED, 0);
                    SetCtrlAttribute (pSystem, P_SYSTEM_CMD_LOAD_HWCONFIG_INI,  ATTR_DIMMED, 0);
                    
                break;
                
            }

        break;
    }
    
    return 0;
}

int CVICALLBACK CtrlPadFunctions (int panel, int control, int event,
        void *callbackData, int eventData1, int eventData2)
{
  
    double dCtrlVal;

    int    iCtrlVal;
    
    
    switch (event)
    {
        case EVENT_VAL_CHANGED:
          switch (control)
        { 
            case P_CTRL_PAD_TGL_MODE:
                GetCtrlVal (pControlPad, P_CTRL_PAD_TGL_MODE, &iCtrlVal);
          
                if (iCtrlVal)       // ABS
                {
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_CMD_UP,          ATTR_DIMMED, 1);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_CMD_DOWN,        ATTR_DIMMED, 1);

                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_CMD_MOVE,        ATTR_DIMMED, 0);

                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_NUM_POSITION,    ATTR_DIMMED, 0);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_LBL_POSITION_2,  ATTR_DIMMED, 0);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_LBL_POSITION_3,  ATTR_DIMMED, 0);

                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_NUM_STEP_UP,     ATTR_DIMMED, 1);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_LBL_STEP_UP_2,   ATTR_DIMMED, 1);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_LBL_STEP_UP_3,   ATTR_DIMMED, 1);

                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_NUM_STEP_DOWN,   ATTR_DIMMED, 1);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_LBL_STEP_DOWN_2, ATTR_DIMMED, 1);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_LBL_STEP_DOWN_3, ATTR_DIMMED, 1);
                }
                else              // REL
                {
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_CMD_UP,          ATTR_DIMMED, 0);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_CMD_DOWN,        ATTR_DIMMED, 0);

                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_CMD_MOVE,        ATTR_DIMMED, 1);
                
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_NUM_POSITION,    ATTR_DIMMED, 1);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_LBL_POSITION_2,  ATTR_DIMMED, 1);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_LBL_POSITION_3,  ATTR_DIMMED, 1);

                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_NUM_STEP_UP,     ATTR_DIMMED, 0);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_LBL_STEP_UP_2,   ATTR_DIMMED, 0);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_LBL_STEP_UP_3,   ATTR_DIMMED, 0);

                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_NUM_STEP_DOWN,   ATTR_DIMMED, 0);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_LBL_STEP_DOWN_2, ATTR_DIMMED, 0);
                    SetCtrlAttribute (pControlPad, P_CTRL_PAD_LBL_STEP_DOWN_3, ATTR_DIMMED, 0);
                } // End "if (iState)"

            break;
        } // End "switch (control)"

      break;
          
          
    case EVENT_LEFT_CLICK:
      switch (control)
        {
            case P_CTRL_PAD_CMD_UP:
                GetCtrlVal (pControlPad, P_CTRL_PAD_NUM_STEP_UP, &dCtrlVal);
                    DebugPrintf("1. dCtrlVal: %f\n", dCtrlVal);
                dCtrlVal *= -1;
                    DebugPrintf("2. dCtrlVal: %f\n", dCtrlVal);
                SetPiCardScrtItem (PI_PARAM_1, 1, dCtrlVal); 

                PiCardFnct (PI_MOVE_UP);

            break;
            
            case P_CTRL_PAD_CMD_DOWN:
                GetCtrlVal (pControlPad, P_CTRL_PAD_NUM_STEP_DOWN, &dCtrlVal);
                DebugPrintf("1. dCtrlVal: %f\n", dCtrlVal);
                SetPiCardScrtItem (PI_PARAM_1, 1, dCtrlVal);
                    
                PiCardFnct (PI_MOVE_DOWN);

            break;
            
            case P_CTRL_PAD_CMD_MOVE:
                GetCtrlVal(pControlPad, P_CTRL_PAD_NUM_POSITION, &dCtrlVal);
                DebugPrintf("1. dCtrlVal: %f\n", dCtrlVal);
                SetPiCardScrtItem (PI_PARAM_1, 1, dCtrlVal);
                
                PiCardFnct(PI_MOVE_ABS);
            
            break;
            
            case P_CTRL_PAD_CMD_HOME:
                PiCardFnct (PI_HOME);
                
            break;
            
        }
      break;
    }
    return 0;
}

