//---------------------------------------------------------------------------
#include <stdio.h>
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
  int   iResult,iYear;
  char  szCheckDate[64],szTemp[128];

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

