#ifndef _BOOL
#define _BOOL
typedef int                     BOOL;
#endif

#define PI_CARD_VERSION                   "1.00"
#define PI_CARD_LAST_MODIFICATION         "23. October 2006"

// PiCardFnct Modes
#define PI_CONNECT                        100
#define PI_DISCONNECT                     101
#define PI_HOME                           102
#define PI_INIT                           103
#define PI_MOVE_UP                        104
#define PI_MOVE_DOWN                      105
#define PI_GET_POS                        106
#define PI_TURN_RIGHT                     107
#define PI_TURN_LEFT                      108
#define PI_STOP                           109
#define PI_CLEAN_UP                       110
#define PI_GET_ERROR                      111
#define PI_MOVING                         112
#define PI_MOVE_ABS                       113
#define PI_CONFIG_SSR                     114
#define PI_SET_POS                        115
#define PI_SWITCH_SERVO_ON                116
#define PI_SWITCH_SERVO_OFF               117
#define PI_GET_SERVO_CTRL                 118
#define PI_CLEAR_STATUS                   119
#define PI_WAIT_FOR_STOP                  120
#define PI_SAVE_LAST_POS                  121
#define PI_LOAD_LAST_POS                  122
#define PI_MOVE_REL                       123
#define PI_RECONFIG_VEL                   124
#define PI_SET_BREAK_ZACHSE               125
#define PI_RESET_BREAK_ZACHSE             126
#define PI_TURN_LEFT_FAST                 127
#define PI_INI_SENSOR_1                   128
#define PI_INI_SENSOR_2                   129
#define PI_MOVE_REL_1_2                   130
#define PI_SET_AXES_1                     131
#define PI_SET_AXES_2                     132
#define PI_HOME_TK_AXE_2                  133
#define PI_SAVE_LAST_POS_TK_2             134
#define PI_LOAD_LAST_POS_TK_2             135
#define PI_POS_MOTOR_NULL                 136

// PiSrctFnct Sub Modes
#define PI_PARAM_1                        150
#define PI_PARAM_2                        151
#define PI_PARAM_3                        152
#define PI_ACCELERATION                   153
#define PI_DECELERATION                   154
#define PI_VELOCITY                       155
#define PI_LAST_POS                       156
#define PI_MAX_AMP_CAPA                   157
#define PI_MAX_AMP_VOLT                   158
#define PI_CARD_IS_INIT                   159
#define PI_AMPLIFIER_IS_INIT              160
#define PI_ACTUATOR_IS_INIT               161
#define PI_ERROR_CODE                     162
#define PI_IS_MOVING                      163
#define PI_NEW_POS                        164
#define PI_SERVO_CTRL                     165
#define PI_FNCT_MODE                      166
#define PI_ENGINE_NAME                    167
#define PI_POS                            168
#define PI_MULT_DISTANCE                  169
#define PI_CHARGE_SENSOR_POS              170
#define PI_CHARGE_SENSOR_NEG              171

// PI-Card Error Codes
#define RET_PI_CARD_CONNECT_ERR           -60
#define RET_PI_CARD_INIT_ERR              -61
#define RET_PI_CARD_HOME_ERR              -62
#define RET_PI_CARD_DISCONNECT_ERR        -63
#define RET_PI_CARD_MOVE_X_ERR            -64
#define RET_PI_CARD_MOVE_ABS_ERR          -65
#define RET_PI_CARD_GET_POS_ERR           -66
#define RET_PI_CARD_WRONG_PARAM_ERR       -67
#define RET_PI_CARD_ILLEGAL_MODE_ERR      -68
#define RET_PI_CARD_GET_ERROR_ERR         -69
#define RET_PI_CARD_STOP_ERR              -70
#define RET_PI_CARD_MOVING_ERR            -71
#define RET_PI_CARD_CONFIG_SSR_ERR        -72
#define RET_PI_CARD_SET_POS_ERR           -73
#define RET_PI_CARD_GET_SERVO_CTRL_ERR    -74
#define RET_PI_CARD_SWITCH_SERVO_ON_ERR   -75
#define RET_PI_CARD_SWITCH_SERVO_OFF_ERR  -76
#define RET_PI_CARD_CLEAR_STATUS_ERR      -77
#define RET_PI_CARD_WAIT_FOR_STOP_ERR     -78
#define RET_PI_CARD_TURN_X_ERR            -79
#define RET_PI_CARD_INI_INIT_ERR          -80
#define RET_PI_CARD_LOAD_INI_ERR          -81
#define RET_PI_CARD_GET_ITEM_ERR          -82
#define RET_PI_CARD_SAVE_INI_ERR          -83
#define RET_PI_CARD_PUT_ITEM_ERR          -84
#define RET_PI_CARD_MOVE_REL_ERR          -85
#define RET_PI_CARD_SET_BREAK_ERR         -86
#define RET_PI_CARD_RESET_BREAK_ERR       -87

// Diverse Parameter
#define MIN                               0
#define MAX                               1

#define PUSH_BUTTON                       0
#define TURNING_KNOB                      1

#define DEFAULT_DELAY                     0.010

// Parameter ID for SPA-Commando
#define VEL                               10
#define ACC                               11
#define DEC                               12

#define WARP_VELOCITY                     450.0  




// Structs
struct PiDcMotCtrlCardStruct
{
  int    iId,
         iCardNo,
         iCardIsInit,
         iActuatorIsInit,
         iAmplifierIsInit,
         iErrorCode,
         iOverSampling;

  double dAcceleration,
         dDeceleration,
         dVelocity,
         dMaxVelocity,
         dDelayOffset,
         dPosition,
         dLastPosition,
         dNewPosition,
         dParam1,
         dParam2,
         dParam3,
         dChargeSensorPos,
         dChargeSensorNeg,
         dMaxAmpCapa,
         dMaxAmpVolt,
         dMultDistance,
         dMaxMove,
         dMaxSpin,
         dHome;             

  char   sCardName   [100],
         sEngineName [100],
         sPathName   [260];

  BOOL   bIsReferencing,
         bIsMoving,
         bServoCtrl,
         bFnctMode,
         bBreakZAchse;
};


// Prototypes
int PiCardFnct        (int iMode);
int GetPiCardScrtItem (int iItem, int iMode, void *vResult);
int SetPiCardScrtItem (int iItem, int iMode, ...);
