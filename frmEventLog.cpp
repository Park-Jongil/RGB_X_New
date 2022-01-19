//---------------------------------------------------------------------------
#include <vcl.h>
#include <dos.h>
#include <stdio.h>
#include <vector.h>
#pragma hdrstop

#include "UserDefine.h"
#include "frmEventLog.h"
#include "DatabaseFunction.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
#pragma resource "*.dfm"
Tfrm_EventLog *frm_EventLog;
extern  std::vector<QueryData> vResultData;
//---------------------------------------------------------------------------
__fastcall Tfrm_EventLog::Tfrm_EventLog(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_EventLog::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_EventLog::FormCreate(TObject *Sender)
{
  DateTimePicker1->Date = Now();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_EventLog::WCImageButton6Click(TObject *Sender)
{
  Close();  
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_EventLog::DateTimePicker1Change(TObject *Sender)
{
  int   iResult,iCount=0;
  char  szStartDate[64],szFinalDate[64],szTemp[128];

  strcpy(szStartDate,DateTimePicker1->Date.FormatString("yyyy-mm-dd").c_str());
  strcpy(szFinalDate,DateTimePicker1->Date.FormatString("yyyy-mm-dd").c_str());
  strcat(szStartDate," 00:00:00");
  strcat(szFinalDate," 23:59:59");
  iResult = DataBase_EventLog_Search_byDateTime(szStartDate,szFinalDate);
  AdvStringGrid1->RowCount = 2;
  for(int j=0;j<3;j++) AdvStringGrid1->Cells[j][1] = "";
  if (iResult != 0x00) {
    for(std::vector<QueryData>::size_type i = 0; i < vResultData.size(); i++) {
      AdvStringGrid1->Cells[0][iCount+1] = vResultData[i].szCheckDate;
      AdvStringGrid1->Cells[1][iCount+1] = IntToStr(vResultData[i].EventCode);
      AdvStringGrid1->Cells[2][iCount+1] = vResultData[i].szDescript;
      iCount = iCount + 1;
    }
    AdvStringGrid1->RowCount = iCount < 0x01 ? 0x02 : iCount + 1;
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_EventLog::WCImageButton1Click(TObject *Sender)
{
  if (iCurRow > 0x01) AdvStringGrid1->Row = AdvStringGrid1->Row - 1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_EventLog::WCImageButton2Click(TObject *Sender)
{
  if (iCurRow < (AdvStringGrid1->RowCount-1)) AdvStringGrid1->Row = AdvStringGrid1->Row + 1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_EventLog::AdvStringGrid1RowChanging(TObject *Sender,
      int OldRow, int NewRow, bool &Allow)
{
  iCurRow = NewRow;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_EventLog::FormShow(TObject *Sender)
{
  DateTimePicker1Change(NULL);  
}
//---------------------------------------------------------------------------

