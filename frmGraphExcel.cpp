//---------------------------------------------------------------------------
#include <stdio.h>
#include <vector.h>
#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "DatabaseFunction.h"
#include "frmGraphExcel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
#pragma resource "*.dfm"
Tfrm_GraphExcel *frm_GraphExcel;
//---------------------------------------------------------------------------
extern  DeviceStatistics    stSensorData[1440];   // 통계데이터를 위한 변수
extern  std::vector<QueryData> vResultData;
//---------------------------------------------------------------------------
__fastcall Tfrm_GraphExcel::Tfrm_GraphExcel(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphExcel::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphExcel::FormCreate(TObject *Sender)
{
  DateTimePicker1->Date = Now();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphExcel::FormShow(TObject *Sender)
{
  DateTimePicker1Change(NULL);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphExcel::WCImageButton6Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphExcel::DateTimePicker1Change(TObject *Sender)
{
  int   iResult,iYear,iHour,iMin;
  char  szCheckDate[64],szTemp[128],szBuffer[1024];
  char  szStartDate[64],szFinalDate[64];

  strcpy(szCheckDate,DateTimePicker1->Date.FormatString("yyyy-mm-dd").c_str());
  iYear = StrToInt(DateTimePicker1->Date.FormatString("yyyy"));
  iResult = DataBase_SensorData_Search_byDateTime(iYear,szCheckDate);
  if (iResult != 0x00) {
    AdvStringGrid1->RowCount = 1441;
    for(int i=0;i<1440;i++) {
      sprintf(szTemp,"%02d:%02d",i/60,i%60);
      AdvStringGrid1->Cells[0][i+1] = szTemp;
      AdvStringGrid1->Cells[1][i+1] = int(stSensorData[i].avg_RGB);
      AdvStringGrid1->Cells[2][i+1] = int(stSensorData[i].avg_ORP);
      sprintf(szTemp,"%5.2f",stSensorData[i].avg_HCL);
      AdvStringGrid1->Cells[3][i+1] = szTemp;
      sprintf(szTemp,"%5.3f",stSensorData[i].avg_SG);
      AdvStringGrid1->Cells[4][i+1] = szTemp;
      sprintf(szTemp,"%5.1f",stSensorData[i].avg_TEMP);
      AdvStringGrid1->Cells[5][i+1] = szTemp;
      AdvStringGrid1->Cells[6][i+1] = stSensorData[i].HCL_Pump;
      AdvStringGrid1->Cells[7][i+1] = stSensorData[i].OXI_Pump;
      AdvStringGrid1->Cells[8][i+1] = stSensorData[i].H2O_Pump;
    }
  } else {
    AdvStringGrid1->RowCount = 2;
    for(int i=0;i<9;i++) AdvStringGrid1->Cells[i][1] = "";
  }
// Event를 확인하기 위한 부분
  strcpy(szStartDate,DateTimePicker1->Date.FormatString("yyyy-mm-dd").c_str());
  strcpy(szFinalDate,DateTimePicker1->Date.FormatString("yyyy-mm-dd").c_str());
  strcat(szStartDate," 00:00:00");
  strcat(szFinalDate," 23:59:59");
  iResult = DataBase_EventLog_Search_byDateTime(szStartDate,szFinalDate);
  if (iResult != 0x00) {
    memset(szBuffer,0x00,sizeof(szBuffer));
    for(std::vector<QueryData>::size_type i = 0; i < vResultData.size(); i++) {
      strcpy(szCheckDate,vResultData[i].szCheckDate);
      iHour = (szCheckDate[11]-'0') * 10 + (szCheckDate[12]-'0');
      iMin  = (szCheckDate[14]-'0') * 10 + (szCheckDate[15]-'0');
      strcpy(szBuffer,AdvStringGrid1->Cells[9][iHour*60+iMin+1].c_str());
      if (strlen(szBuffer) > 0) {
        strcat(szBuffer," , ");
        strcat(szBuffer,vResultData[i].szDescript);
        AdvStringGrid1->Cells[9][iHour*60+iMin+1] = szBuffer;
      } else {
        AdvStringGrid1->Cells[9][iHour*60+iMin+1] = vResultData[i].szDescript;
      }

//      AdvStringGrid1->Cells[0][iCount+1] = vResultData[i].szCheckDate;
//      AdvStringGrid1->Cells[1][iCount+1] = IntToStr(vResultData[i].EventCode);
//      AdvStringGrid1->Cells[2][iCount+1] = vResultData[i].szDescript;
    }
  }


}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphExcel::AdvStringGrid1GetAlignment(
      TObject *Sender, int ARow, int ACol, TAlignment &HAlign,
      TVAlignment &VAlign)
{
  VAlign = taCenter;
  HAlign = taCenter;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphExcel::WCImageButton1Click(TObject *Sender)
{
  SaveDialog1->InitialDir = ExtractFilePath(Application->ExeName);
  if (SaveDialog1->Execute()) {
    AdvStringGrid1->SaveToXLS(SaveDialog1->FileName);
  }
}
//---------------------------------------------------------------------------

