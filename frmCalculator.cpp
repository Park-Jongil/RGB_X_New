//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmCalculator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma resource "*.dfm"
Tfrm_Calculator *frm_Calculator;
//---------------------------------------------------------------------------
__fastcall Tfrm_Calculator::Tfrm_Calculator(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Calculator::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Calculator::WCImageButton16Click(TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Calculator::WCImageButton17Click(TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Calculator::FormShow(TObject *Sender)
{
  iMode = 0;
  szValue = "";
  Label2->Caption = szValue;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_Calculator::WCImageButton9Click(TObject *Sender)
{
  int   iTag;

  iTag = static_cast<TWCImageButton*>(Sender)->Tag;
  szValue = szValue + IntToStr(iTag);
  Label2->Caption = szValue;
//  if (iMode==0) Label2->Caption = StrToInt(szValue);
//   else Label2->Caption = atof(szValue.c_str());
//  szValue = Label2->Caption;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_Calculator::WCImageButton10Click(TObject *Sender)
{
  iMode = 1;
  szValue = szValue + ".";
  Label2->Caption = szValue;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_Calculator::WCImageButton11Click(TObject *Sender)
{
  iMode = 0;
  szValue = "";
  Label2->Caption = szValue;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Calculator::WCImageButton15Click(TObject *Sender)
{
  char  szBuffer[128];

  strcpy(szBuffer,szValue.c_str());
  szBuffer[szValue.Length()-1] = 0x00;
  szValue = szBuffer;
  Label2->Caption = szValue;
}
//---------------------------------------------------------------------------

