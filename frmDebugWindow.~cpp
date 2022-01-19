//---------------------------------------------------------------------------

#include <vcl.h>
#include <dos.h>
#include <stdio.h>
#pragma hdrstop

#include "frmDebugWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_DebugWindow *frm_DebugWindow;
//---------------------------------------------------------------------------
__fastcall Tfrm_DebugWindow::Tfrm_DebugWindow(TComponent* Owner)
        : TForm(Owner)
{
  iAppendStatus = 1;
}
//---------------------------------------------------------------------------
void Tfrm_DebugWindow::Display_DebugMessage(int iMode,unsigned char *szCommand, int iSize)
{
    //TODO: Add your source code here
  int     i , j , iCount , iValue , iChkColor;
  struct  time t;
  struct  date d;
  char    szBuffer[4096] , szTemp[32];
  TColor  CharColor;
  Richedit::CHARFORMAT2 cf;           

  if (iAppendStatus==0x00) return;
  getdate(&d);
  gettime(&t);
  switch(iMode) {
    case 0x00 : strcpy(szTemp,"[Recv]");
                CharColor = clBlue;
                break;
    case 0x01 : strcpy(szTemp,"[Send]");
                CharColor = clRed;
                break;
    default   : strcpy(szTemp,"[    ]");
                CharColor = clBlack;
                break;
  }
  memset( szBuffer , 0x00 , sizeof(szBuffer) );
  sprintf(szBuffer , "%s %4d-%02d-%02d %2d:%02d:%02d.%03d [%4d]",szTemp,
    d.da_year,d.da_mon,d.da_day,t.ti_hour,t.ti_min,t.ti_sec,t.ti_hund,iSize);

  iChkColor = RichEdit1->Lines->Add( szBuffer );
  RichEdit1->SelStart = SendMessage(RichEdit1->Handle, EM_LINEINDEX, iChkColor, 0);
  RichEdit1->SelLength = strlen(szBuffer);
  RichEdit1->SelAttributes->Color = CharColor;

  for(i=0;i<iSize;i+=0x20) {
    memset( szBuffer , 0x00 , sizeof(szBuffer) );
    sprintf( szBuffer , "[%04X] : " , i );  // Offset Display
    for(j=0;j<0x20;j++) {
      if (i+j<iSize) sprintf( szTemp , "%02X " , szCommand[i+j] );
       else sprintf( szTemp , "   " );
      strcat( szBuffer , szTemp );
    }
    for(j=0;j<0x20;j++) {
      if (i+j<iSize) {
        if (0x20<=szCommand[i+j] && szCommand[i+j]<=0x80) sprintf( szTemp , "%c" , szCommand[i+j] );
         else sprintf( szTemp , "." );
      } else sprintf( szTemp , " " );
      strcat( szBuffer , szTemp );
    }
    iChkColor = RichEdit1->Lines->Add( szBuffer );
    RichEdit1->SelStart = SendMessage(RichEdit1->Handle, EM_LINEINDEX, iChkColor, 0);
    RichEdit1->SelLength = strlen(szBuffer);
    RichEdit1->SelAttributes->Color = clBlack;
  }
  if (RichEdit1->Lines->Count > 2000) {         // 만일 2000 줄이 넘는다면..
    RichEdit1->SetFocus();
    RichEdit1->SelStart = 0;
    iValue = 0;
    for(i=0;i<1000;i++) iValue += RichEdit1->Lines->Strings[i].Length();
    iValue += 1000 * 2; // add CR/LF for all skipped lines
    RichEdit1->SelLength = iValue;
    RichEdit1->ClearSelection();
  }
  iValue = RichEdit1->Lines->Count;
  RichEdit1->SelLength = 0;
  RichEdit1->SelStart  = RichEdit1->Perform(EM_LINEINDEX, iValue , 0);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_DebugWindow::BitBtn1Click(TObject *Sender)
{
  RichEdit1->Lines->Clear();        
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_DebugWindow::BitBtn2Click(TObject *Sender)
{
  iAppendStatus = !iAppendStatus;
  BitBtn2->Caption = iAppendStatus==0x01 ? "Pause" : "Start" ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_DebugWindow::BitBtn3Click(TObject *Sender)
{
  if (SaveDialog1->Execute()) {
    RichEdit1->Lines->SaveToFile(SaveDialog1->FileName);
  }
}
//---------------------------------------------------------------------------

