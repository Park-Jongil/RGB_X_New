#include <vcl.h>
#include <Comctrls.hpp>
#include <scktcomp.hpp>

#ifndef User_DataStruct_Define
#define User_DataStruct_Define
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#define   CMD_SENSOR_DATA         0x00
#define   CMD_STATUS_DATA         0x01
#define   CMD_RGB_WLED_BR         0x02
#define   CMD_SENSOR_SHIFT        0x03
#define   CMD_ONOFF_TIME          0x04
#define   CMD_UCL_SET_LCL         0x05
#define   CMD_MODE_N_PUMP         0x06
//---------------------------------------------------------------------------
#define   ERROR_CHECKSUM          0x01
#define   ERROR_FRAME_ETX         0x02
#define   ERROR_NO_COMMAND        0x03
//---------------------------------------------------------------------------
#define   GRAPH_MAX_BUFFER        570
//---------------------------------------------------------------------------
typedef struct  _RequestPacket {
  unsigned char   Header;         //
  unsigned char   SiteID;         //
  unsigned char   DeviceID;       //
  unsigned char   Command;        //
  unsigned char   DataSize;       //
  unsigned char   Data[256];      //   , Reserved(0x00),Tail(ETX:0x03),CheckSum
} RequestPacket;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
union U_Control {
  struct {
    unsigned char  OXI_PUMP      : 1;    // Bit00 (LSB) ON:1 , OFF:0
    unsigned char  HCL_PUMP      : 1;    // Bit01
    unsigned char  H2O_PUMP      : 1;    // Bit02
    unsigned char  AUTO_MANUAL   : 1;    // Bit03 , AUTO:1 , MANUAL:0
    unsigned char  PC_SENSORBOX  : 1;    // Bit04 , PC:1 , SENSOR_BOX:0
    unsigned char  ONOFF_HBC     : 1;    // Bit05 , ON/OFF:1 , HBC:0
    unsigned char  RGB_ORP       : 1;    // Bit06 , RGB:1 , ORP:0
    char  Reserved      : 1;    // Bit07 (MSB)
  } bit8;
  unsigned char Value;
};
union U_Alarm1 {
  struct {
    unsigned char  RGB_UCL_Alarm : 1;    // Bit00 (LSB)
    unsigned char  RGB_LCL_Alarm : 1;    // Bit01
    unsigned char  ORP_UCL_Alarm : 1;    // Bit02
    unsigned char  ORP_LCL_Alarm : 1;    // Bit03
    unsigned char  HCL_UCL_Alarm : 1;    // Bit04
    unsigned char  HCL_LCL_Alarm : 1;    // Bit05
    unsigned char  SG_UCL_Alarm  : 1;    // Bit06
    unsigned char  SG_LCL_Alarm  : 1;    // Bit07 (MSB)
  } bit8;
  unsigned char Value;
} ;
union U_Alarm2 {
  struct {
    unsigned char  TEMP_UCL_Alarm   : 1;    // Bit00 (LSB)
    unsigned char  TEMP_LCL_Alarm   : 1;    // Bit01
    unsigned char  CIRCURATING_PUMP : 1;    // Bit02
    unsigned char  FLOW_Alarm       : 1;    // Bit03
    unsigned char  Reserved1        : 1;    // Bit04
    unsigned char  Reserved2        : 1;    // Bit05
    unsigned char  Reserved3        : 1;    // Bit06
    unsigned char  Reserved4        : 1;    // Bit07 (MSB)
  } bit8;
  unsigned char Value;
} ;

//---------------------------------------------------------------------------
typedef struct  _SensorData {
  short int       FQ_R;
  short int       FQ_G;
  short int       FQ_B;
  short int       ORP;
  short int       HCL;
  short int       SG;
  short int       LQ_TEMP;
  U_Control       ModePump;
  U_Alarm1        Alarm1;
  U_Alarm2        Alarm2;
} SensorData;

//---------------------------------------------------------------------------
typedef struct  _StatusData {
  U_Control       ModePump;
  U_Alarm1        Alarm1;
  U_Alarm2        Alarm2;
  unsigned char   FQ_RGB_WLED;
  short int       R_SHIFT;
  short int       G_SHIFT;
  short int       B_SHIFT;
  short int       ORP_SHIFT;
  short int       HCL_SHIFT;
  short int       SG_SHIFT;
  short int       TEMP_SHIFT;
  unsigned char   RGB_ON_TIME;
  unsigned char   RGB_OFF_TIME;
  unsigned char   ORP_ON_TIME;
  unsigned char   ORP_OFF_TIME;
  unsigned char   HCL_ON_TIME;
  unsigned char   HCL_OFF_TIME;
  unsigned char   SG_ON_TIME;
  unsigned char   SG_OFF_TIME;
  unsigned char   MAX_ON_TIME;
  short int       RGB_UCL;
  short int       RGB_SET;
  short int       RGB_LCL;
  short int       ORP_UCL;
  short int       ORP_SET;
  short int       ORP_LCL;
  short int       HCL_UCL;
  short int       HCL_SET;
  short int       HCL_LCL;
  short int       SG_UCL;
  short int       SG_SET;
  short int       SG_LCL;
  short int       TEMP_UCL;
  short int       TEMP_LCL;
} StatusData;

//---------------------------------------------------------------------------
typedef struct  _RGB_WLED_Brightness {
  unsigned char   FQ_RGB_WLED;
  unsigned char   VT_RGB_WLED;
} RGB_WLED_Brightness;

//---------------------------------------------------------------------------
typedef struct  _Sensor_ShiftData {
  short int       R_SHIFT;
  short int       G_SHIFT;
  short int       B_SHIFT;
  short int       ORP_SHIFT;
  short int       HCL_SHIFT;
  short int       SG_SHIFT;
  short int       TEMP_SHIFT;
} Sensor_ShiftData;

//---------------------------------------------------------------------------
typedef struct  _OnOff_TimeData {
  unsigned char   RGB_ON_TIME;
  unsigned char   RGB_OFF_TIME;
  unsigned char   ORP_ON_TIME;
  unsigned char   ORP_OFF_TIME;
  unsigned char   HCL_ON_TIME;
  unsigned char   HCL_OFF_TIME;
  unsigned char   SG_ON_TIME;
  unsigned char   SG_OFF_TIME;
  unsigned char   MAX_ON_TIME;
} OnOff_TimeData;

//---------------------------------------------------------------------------
typedef struct  _UCL_SET_DATA {
  short int       RGB_UCL;
  short int       RGB_SET;
  short int       RGB_LCL;
  short int       ORP_UCL;
  short int       ORP_SET;
  short int       ORP_LCL;
  short int       HCL_UCL;
  short int       HCL_SET;
  short int       HCL_LCL;
  short int       SG_UCL;
  short int       SG_SET;
  short int       SG_LCL;
  short int       TEMP_UCL;
  short int       TEMP_LCL;
} UCL_SET_DATA;


//---------------------------------------------------------------------------
typedef struct  _DeviceConfig {
  SensorData    PrevSensor;
  SensorData    CurSensor;
  StatusData    CurStatus;
  SensorData    SaveSensor;
// 화면에 그래프를 출력하기 위하여 생성된 버퍼  
  short int     Graph_RGB[GRAPH_MAX_BUFFER];
  short int     Graph_ORP[GRAPH_MAX_BUFFER];
  short int     Graph_HCL[GRAPH_MAX_BUFFER];
  short int     Graph_SG[GRAPH_MAX_BUFFER];
  short int     Graph_TEMP[GRAPH_MAX_BUFFER];
// 그래프의 Y Axis 변수
  short int     RGB_Top , RGB_Bottom;
  short int     ORP_Top , ORP_Bottom;
  short int     HCL_Top , HCL_Bottom;
  short int     SG_Top , SG_Bottom;
  short int     TEMP_Top , TEMP_Bottom;
//  GraphUsage 에서 사용량을 관리할 변수들
  double        HCL_Capa;
  double        HCL_Daily;
  double        HCL_Total;
  double        OXI_Capa;
  double        OXI_Daily;
  double        OXI_Total;
  double        H2O_Capa;
  double        H2O_Daily;
  double        H2O_Total;
// Setting_Control 에서의 설정값
  int           Control_SubHCL1;      // g/l 여부
  int           Control_SubHCL2;      // %  여부
// Setting_SensorChange 에서의 설정값
  char          szChangeDate_RGB[32];
  char          szChangeDate_ORP[32];
  char          szChangeDate_HCL[32];
  char          szChangeDate_SG[32];
  char          szChangeCheckDate[32];
  int           ORP_Count;            // 센서교체일
// Setting_Master 에서의 설정값
  int           isMasterPassword;
  char          szMasterPassword[128];

} DeviceConfig;

//---------------------------------------------------------------------------
// 통계를 위한 데이터(데이터를 일분단위로 저장하기 위하여 카운터와 합계를 저장한 다음, DB에 저장할때 카운터로 나눈다.)
//---------------------------------------------------------------------------
typedef struct _DeviceStatistics {
  int           iStatCount;
  double        avg_RGB;
  double        avg_ORP;
  double        avg_HCL;
  double        avg_SG;
  double        avg_TEMP;
  short int     OXI_Pump;
  short int     HCL_Pump;
  short int     H2O_Pump;
  short int     AutoMode;
  short int     CircurPump;
} DeviceStatistics;

//---------------------------------------------------------------------------
// Graph Usae 에 사용할 월벌 사용량을 누적하기 위한 구조체
//---------------------------------------------------------------------------
typedef struct _GraphUsage {
  char        szCheckDate[32];
  short int   iDays;
  short int   OXI_Pump;
  short int   HCL_Pump;
  short int   H2O_Pump;
} GraphUsage;


//---------------------------------------------------------------------------
// DataBase Structure
//---------------------------------------------------------------------------
typedef struct  _QueryData {
  char    szCheckDate[32];
  int     EventCode;
  char    szDescript[128];
} QueryData;

//---------------------------------------------------------------------------
#endif
