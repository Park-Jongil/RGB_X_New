//---------------------------------------------------------------------------

#ifndef DatabaseFunctionH
#define DatabaseFunctionH
//---------------------------------------------------------------------------
int  __fastcall DataBase_LocalDB_Initialize();
void __fastcall DataBase_LocalDB_Finitialize();
void __fastcall DataBase_Check_CreateTable_EventLog();
void __fastcall DataBase_Check_CreateTable_SensorData(int iYear);
void __fastcall DataBase_Check_CreateTable_GraphUsage();
int  __fastcall DataBase_EventLog_Insert(char *szCheckTime,int iEventID);
int  __fastcall DataBase_EventLog_Search_byDateTime(char *StartTime,char *FinalTime);
int  __fastcall DataBase_SensorData_Insert(int iYear,char *szCheckTime,int iTimeIndex,DeviceStatistics *pChkPnt);
int  __fastcall DataBase_SensorData_Search_byDateTime(int iYear,char *CheckDate);
int  __fastcall DataBase_SensorData_Usage_byDateTime(int iYear,char *CheckDate);
int  __fastcall DataBase_GraphUsage_Insert(char *szCheckTime,double HCL,double OXI,double H2O);
int  __fastcall DataBase_GraphUsage_Search_byDateTime(char *CheckDate);

//---------------------------------------------------------------------------
#endif
