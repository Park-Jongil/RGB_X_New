//---------------------------------------------------------------------------
#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <vector.h>
#include <vcl.h>
#pragma hdrstop

#include "sqlite3.h"
#include "UserDefine.h"
#include "DatabaseFunction.h"
#include "frmRGB_X_Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
int     iRecordCount = 0;
sqlite3 *pDataBase = NULL;
std::vector<QueryData> vResultData;
//---------------------------------------------------------------------------
DeviceStatistics  stSensorData[1440];   // 통계데이터를 위한 변수
GraphUsage        stGraphUsage[31];
//---------------------------------------------------------------------------
int  __fastcall DataBase_LocalDB_Initialize()
{
  int     iRet;
  struct  date d;
  char    szBuffer[1024];

// File DataBase Creation
  getdate(&d);
  iRet = sqlite3_open("RGB_X.db",&pDataBase);
  if (iRet != 0) {
    sprintf(szBuffer,"[DB Error] %s",sqlite3_errmsg(pDataBase));
    return(0x00);
  }
  DataBase_Check_CreateTable_EventLog();
  DataBase_Check_CreateTable_SensorData(d.da_year);
  DataBase_Check_CreateTable_GraphUsage();
  return(0x01);
}

//---------------------------------------------------------------------------
void __fastcall DataBase_LocalDB_Finitialize()
{
  int   nResult;
// File DataBase Termination
  nResult = sqlite3_close(pDataBase);
  if(nResult != 0) {
  } else {
    pDataBase = NULL;
  }
}

//---------------------------------------------------------------------------
void __fastcall DataBase_Check_CreateTable_EventLog()
{
  int nResult;
  char *szQuery = "CREATE TABLE tbl_EventLog ("
                  " seq           INTEGER PRIMARY KEY AUTOINCREMENT,"
                  " checkdate     varchar(32),"
                  " event_type    int ,"
                  " event_code    varchar(32),"
                  " descript	    varchar(64)"
                  " ) ;\n"
                  "CREATE INDEX tbl_EventLog_checkdate_IDX ON tbl_EventLog (checkdate,event_type);";
  if (pDataBase==NULL) return;
  nResult = sqlite3_exec(pDataBase,szQuery,NULL,0,0);
}

//---------------------------------------------------------------------------
void __fastcall DataBase_Check_CreateTable_SensorData(int iYear)
{
  int   nResult;
  char  szBuffer[1024] , szMakeQuery[2048];
  char *szQuery = " seq           INTEGER PRIMARY KEY AUTOINCREMENT,"
                  " checkdate     varchar(32),"
                  " TimeIndex     int ,"
                  " RGB           float ,"
                  " ORP           float ,"
                  " HCL           float ,"
                  " SG            float ,"
                  " TEMP          float ,"
                  " OXI_Pump      int ,"
                  " HCL_Pump      int ,"
                  " H2O_Pump      int ,"
                  " AutoMode      int ,"
                  " CircurPump    int "
                  " ) ;\n";

  sprintf(szBuffer,"CREATE TABLE tbl_SensorData%04d(",iYear);
  strcpy(szMakeQuery , szBuffer );
  strcat(szMakeQuery , szQuery );
  sprintf(szBuffer,"CREATE INDEX tbl_SensorData%04d_checkdate_IDX ON tbl_SensorData%04d (checkdate);",iYear,iYear);
  strcat(szMakeQuery , szBuffer );

  if (pDataBase==NULL) return;
  nResult = sqlite3_exec(pDataBase,szMakeQuery,NULL,0,0);
}

//---------------------------------------------------------------------------
void __fastcall DataBase_Check_CreateTable_GraphUsage()
{
  int   nResult;
  char  szBuffer[1024] , szMakeQuery[2048];
  char *szQuery = "CREATE TABLE tbl_GraphUsage ("
                  " seq           INTEGER PRIMARY KEY AUTOINCREMENT,"
                  " checkdate     varchar(32),"
                  " HCL_Daily     float ,"
                  " OXI_Daily     float ,"
                  " H2O_Daily     float "
                  " ) ;\n";
                  "CREATE INDEX tbl_GraphUsage_checkdate_IDX ON tbl_GraphUsage (checkdate);";
  if (pDataBase==NULL) return;
  nResult = sqlite3_exec(pDataBase,szQuery,NULL,0,0);
}


//---------------------------------------------------------------------------
int __fastcall DataBase_EventLog_Insert(char *szCheckTime,int iEventID)
{
  int           nResult,i;
  char          szQuery[1024];
  char          *szEventCode[16] = { "","RGB 상한알람","RGB 하한알람","ORP 상한알람","ORP 하한알람","HCL 상한알람","HCL 하한알람","S.G 상한알람","S.G 하한알람",
                                     "TEMP 상한알람","TEMP 하한알람","통신끊김확인필요","순환펌프가동정지","ORP 센서교체필요"};
  sqlite3_stmt  *pStmt;

  if (pDataBase==NULL) return(0);
  sprintf(szQuery,"INSERT INTO tbl_EventLog (checkdate,event_type,descript) VALUES('%s','%d','%s');",szCheckTime,iEventID,szEventCode[iEventID]);
  try {
    nResult = sqlite3_prepare(pDataBase,szQuery,strlen(szQuery),&pStmt,NULL);
    if (nResult == 0) {
      sqlite3_reset(pStmt);
      nResult = sqlite3_step(pStmt);
      if (nResult != SQLITE_DONE) {   // Error
      }
      sqlite3_finalize(pStmt);
    }
  } catch(...) {
  }
  return(nResult);
}

//---------------------------------------------------------------------------
int  __fastcall DataBase_EventLog_Search_byDateTime(char *StartTime,char *FinalTime)
{
  int           nResult,iSeq;
  char          szBuffer[1024];
  sqlite3_stmt  *pStmt;
  char          szQuery[1024];
  QueryData     stData;

  if (pDataBase==NULL) return(0);
  strcpy(szQuery,"select checkdate,event_type,descript from tbl_EventLog where ? <= CheckDate and CheckDate <= ?");
  nResult = sqlite3_prepare(pDataBase,szQuery,strlen(szQuery),&pStmt,NULL);
  if (nResult == 0) {
    iSeq = 0;
    sqlite3_reset(pStmt);
    sqlite3_bind_text(pStmt,1,StartTime,strlen(StartTime),SQLITE_STATIC);
    sqlite3_bind_text(pStmt,2,FinalTime,strlen(FinalTime),SQLITE_STATIC);
    vResultData.clear();
    while(true) {
      nResult = sqlite3_step(pStmt);
      if(nResult != SQLITE_ROW) break;
      strcpy(stData.szCheckDate,(char*)sqlite3_column_text(pStmt,0));
      stData.EventCode = sqlite3_column_int(pStmt,1);
      strcpy(stData.szDescript,(char*)sqlite3_column_text(pStmt,2));
      vResultData.push_back(stData);
      iSeq = iSeq + 1;
    }
    sqlite3_finalize(pStmt);
  }
  iRecordCount = iSeq;
  return(iSeq);
}

//---------------------------------------------------------------------------
int __fastcall DataBase_SensorData_Insert(int iYear,char *szCheckTime,int iTimeIndex,DeviceStatistics *pChkPnt)
{
  int           nResult,i;
  char          szQuery[1024];
  sqlite3_stmt  *pStmt;

  if (pDataBase==NULL) return(0);
  if (pChkPnt->iStatCount == 0x00) return(0);
  pChkPnt->avg_RGB = pChkPnt->avg_RGB / pChkPnt->iStatCount;
  pChkPnt->avg_ORP = pChkPnt->avg_ORP / pChkPnt->iStatCount;
  pChkPnt->avg_HCL = pChkPnt->avg_HCL / pChkPnt->iStatCount;
  pChkPnt->avg_SG  = pChkPnt->avg_SG  / pChkPnt->iStatCount;
  pChkPnt->avg_TEMP = pChkPnt->avg_TEMP / pChkPnt->iStatCount;
  pChkPnt->OXI_Pump = pChkPnt->OXI_Pump * frm_RGB_X_Main->Timer_SensorData->Interval / 1000.0;
  pChkPnt->HCL_Pump = pChkPnt->HCL_Pump * frm_RGB_X_Main->Timer_SensorData->Interval / 1000.0;
  pChkPnt->H2O_Pump = pChkPnt->H2O_Pump * frm_RGB_X_Main->Timer_SensorData->Interval / 1000.0;
  pChkPnt->CircurPump = pChkPnt->CircurPump * frm_RGB_X_Main->Timer_SensorData->Interval / 1000.0;
  sprintf(szQuery,"INSERT INTO tbl_SensorData%04d (checkdate,TimeIndex,RGB,ORP,HCL,SG,TEMP,OXI_Pump,HCL_Pump,H2O_Pump,AutoMode,CircurPump) VALUES('%s','%d','%f','%f','%f','%f','%f','%d','%d','%d','%d','%d');",iYear,szCheckTime,iTimeIndex
                ,pChkPnt->avg_RGB,pChkPnt->avg_ORP,pChkPnt->avg_HCL,pChkPnt->avg_SG,pChkPnt->avg_TEMP,pChkPnt->OXI_Pump,pChkPnt->HCL_Pump,pChkPnt->H2O_Pump,pChkPnt->AutoMode,pChkPnt->CircurPump);
  try {
    nResult = sqlite3_prepare(pDataBase,szQuery,strlen(szQuery),&pStmt,NULL);
    if (nResult == 0) {
      sqlite3_reset(pStmt);
      nResult = sqlite3_step(pStmt);
      if (nResult != SQLITE_DONE) {   // Error
      }
      sqlite3_finalize(pStmt);
    }
  } catch(...) {
  }
  return(nResult);
}

//---------------------------------------------------------------------------
int  __fastcall DataBase_SensorData_Search_byDateTime(int iYear,char *CheckDate)
{
  int           nResult,iSeq,iTimeIndex;
  char          szQuery[1024];
  char          szBuffer[1024],StartTime[64],FinalTime[64];
  sqlite3_stmt  *pStmt;

  if (pDataBase==NULL) return(0);
  memset((char*)&stSensorData,0x00,sizeof(stSensorData)); // 전체영역 초기화
  sprintf(szQuery,"select checkdate,TimeIndex,RGB,ORP,HCL,SG,TEMP,OXI_Pump,HCL_Pump,H2O_Pump,AutoMode,CircurPump from tbl_SensorData%04d where checkdate = ? ",iYear);
  nResult = sqlite3_prepare(pDataBase,szQuery,strlen(szQuery),&pStmt,NULL);
  if (nResult == 0) {
    iSeq = 0;
    sqlite3_reset(pStmt);
    sqlite3_bind_text(pStmt,1,CheckDate,strlen(CheckDate),SQLITE_STATIC);
    vResultData.clear();
    while(true) {
      nResult = sqlite3_step(pStmt);
      if(nResult != SQLITE_ROW) break;
      iTimeIndex = sqlite3_column_int(pStmt,1);
      stSensorData[iTimeIndex].avg_RGB = sqlite3_column_double(pStmt,2);
      stSensorData[iTimeIndex].avg_ORP = sqlite3_column_double(pStmt,3);
      stSensorData[iTimeIndex].avg_HCL = sqlite3_column_double(pStmt,4);
      stSensorData[iTimeIndex].avg_SG  = sqlite3_column_double(pStmt,5);
      stSensorData[iTimeIndex].avg_TEMP = sqlite3_column_double(pStmt,6);
      stSensorData[iTimeIndex].OXI_Pump = sqlite3_column_int(pStmt,7);
      stSensorData[iTimeIndex].HCL_Pump = sqlite3_column_int(pStmt,8);
      stSensorData[iTimeIndex].H2O_Pump = sqlite3_column_int(pStmt,9);
      stSensorData[iTimeIndex].AutoMode = sqlite3_column_int(pStmt,10);
      stSensorData[iTimeIndex].CircurPump = sqlite3_column_int(pStmt,11);
      iSeq = iSeq + 1;
    }
    sqlite3_finalize(pStmt);
  }
  return(iSeq);
}

//---------------------------------------------------------------------------
// CheckDate는 YYYY-MM 까지만 전달되면. 쿼리에서 01~31일까지를 누적합산하여 처리한다.
// select checkdate,sum(OXI_Pump),sum(HCL_Pump),sum(H2O_Pump) from tbl_SensorData2021 where '2021-12-01' <= checkdate and checkdate <= '2021-12-31' group by checkdate;
//---------------------------------------------------------------------------
int  __fastcall DataBase_SensorData_Usage_byDateTime(int iYear,char *CheckDate)
{
  int           nResult,iSeq,iTimeIndex;
  char          szQuery[1024];
  char          szBuffer[1024],StartTime[64],FinalTime[64];
  sqlite3_stmt  *pStmt;

  if (pDataBase==NULL) return(0);
  memset((char*)&stGraphUsage,0x00,sizeof(stGraphUsage)); // 전체영역 초기화
  sprintf(szQuery,"select checkdate,sum(OXI_Pump),sum(HCL_Pump),sum(H2O_Pump) from tbl_SensorData%04d where ? <= checkdate and checkdate <= ? group by checkdate;",iYear);
  nResult = sqlite3_prepare(pDataBase,szQuery,strlen(szQuery),&pStmt,NULL);
  if (nResult == 0) {
    iSeq = 0;
    sqlite3_reset(pStmt);
    sprintf(StartTime,"%s-01",CheckDate);
    sprintf(FinalTime,"%s-31",CheckDate);
    sqlite3_bind_text(pStmt,1,StartTime,strlen(StartTime),SQLITE_STATIC);
    sqlite3_bind_text(pStmt,2,FinalTime,strlen(FinalTime),SQLITE_STATIC);
    vResultData.clear();
    while(true) {
      nResult = sqlite3_step(pStmt);
      if(nResult != SQLITE_ROW) break;
      strcpy(stGraphUsage[iSeq].szCheckDate,(char*)sqlite3_column_text(pStmt,0));
      stGraphUsage[iSeq].iDays = atoi((char*)&stGraphUsage[iSeq].szCheckDate[8]);
      stGraphUsage[iSeq].OXI_Pump = sqlite3_column_int(pStmt,1);
      stGraphUsage[iSeq].HCL_Pump = sqlite3_column_int(pStmt,2);
      stGraphUsage[iSeq].H2O_Pump = sqlite3_column_int(pStmt,3);
      iSeq = iSeq + 1;
    }
    sqlite3_finalize(pStmt);
  }
  return(iSeq);
}

//---------------------------------------------------------------------------
int __fastcall DataBase_GraphUsage_Insert(char *szCheckTime,double HCL,double OXI,double H2O)
{
  int           nResult,i;
  char          szQuery[1024];
  sqlite3_stmt  *pStmt;

  if (pDataBase==NULL) return(0);
  sprintf(szQuery,"INSERT INTO tbl_GraphUsage(checkdate,HCL_Daily,OXI_Daily,H2O_Daily) VALUES('%s','%f','%f','%f');",szCheckTime,HCL,OXI,H2O);
  try {
    nResult = sqlite3_prepare(pDataBase,szQuery,strlen(szQuery),&pStmt,NULL);
    if (nResult == 0) {
      sqlite3_reset(pStmt);
      nResult = sqlite3_step(pStmt);
      if (nResult != SQLITE_DONE) {   // Error
      }
      sqlite3_finalize(pStmt);
    }
  } catch(...) {
  }
  return(nResult);
}

//---------------------------------------------------------------------------
// CheckDate는 YYYY-MM 까지만 전달되면. 쿼리에서 01~31일까지를 누적합산하여 처리한다.
// select checkdate,sum(OXI_Pump),sum(HCL_Pump),sum(H2O_Pump) from tbl_SensorData2021 where '2021-12-01' <= checkdate and checkdate <= '2021-12-31' group by checkdate;
//---------------------------------------------------------------------------
int  __fastcall DataBase_GraphUsage_Search_byDateTime(char *CheckDate)
{
  int           nResult,iSeq,iTimeIndex;
  char          szQuery[1024];
  char          szBuffer[1024],StartTime[64],FinalTime[64];
  sqlite3_stmt  *pStmt;

  if (pDataBase==NULL) return(0);
  memset((char*)&stGraphUsage,0x00,sizeof(stGraphUsage)); // 전체영역 초기화
  sprintf(szQuery,"select checkdate,HCL_Daily,OXI_Daily,H2O_Daily from tbl_GraphUsage where ? <= checkdate and checkdate <= ? group by checkdate;");
  nResult = sqlite3_prepare(pDataBase,szQuery,strlen(szQuery),&pStmt,NULL);
  if (nResult == 0) {
    iSeq = 0;
    sqlite3_reset(pStmt);
    sprintf(StartTime,"%s-01",CheckDate);
    sprintf(FinalTime,"%s-31",CheckDate);
    sqlite3_bind_text(pStmt,1,StartTime,strlen(StartTime),SQLITE_STATIC);
    sqlite3_bind_text(pStmt,2,FinalTime,strlen(FinalTime),SQLITE_STATIC);
    vResultData.clear();
    while(true) {
      nResult = sqlite3_step(pStmt);
      if(nResult != SQLITE_ROW) break;
      strcpy(stGraphUsage[iSeq].szCheckDate,(char*)sqlite3_column_text(pStmt,0));
      stGraphUsage[iSeq].iDays = atoi((char*)&stGraphUsage[iSeq].szCheckDate[8]);
      stGraphUsage[iSeq].HCL_Pump = sqlite3_column_int(pStmt,1);
      stGraphUsage[iSeq].OXI_Pump = sqlite3_column_int(pStmt,2);
      stGraphUsage[iSeq].H2O_Pump = sqlite3_column_int(pStmt,3);
      iSeq = iSeq + 1;
    }
    sqlite3_finalize(pStmt);
  }
  return(iSeq);
}


