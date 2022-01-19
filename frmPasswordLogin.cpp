//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "frmCalculator.h"
#include "frmPasswordLogin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma resource "*.dfm"
Tfrm_PasswordLogin *frm_PasswordLogin;
//---------------------------------------------------------------------------
extern  DeviceConfig        stDeviceConfig;
//---------------------------------------------------------------------------
__fastcall Tfrm_PasswordLogin::Tfrm_PasswordLogin(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_PasswordLogin::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_PasswordLogin::FormShow(TObject *Sender)
{
  memset(szPassword,0x00,sizeof(szPassword));
  iMode = 0;
  szValue = "0";
  Label1->Caption = szValue;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_PasswordLogin::WCImageButton1Click(TObject *Sender)
{
  strcpy(szPassword,szValue.c_str());
  if (strcmp(szPassword,stDeviceConfig.szMasterPassword)==0x00) {
    ModalResult = mrOk;
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_PasswordLogin::WCImageButton18Click(TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_PasswordLogin::WCImageButton16Click(TObject *Sender)
{
  strcpy(szPassword,szValue.c_str());
  if (strcmp(szPassword,stDeviceConfig.szMasterPassword)==0x00) {
    ModalResult = mrOk;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_PasswordLogin::WCImageButton10Click(TObject *Sender)
{
  int   iTag;

  iTag = static_cast<TWCImageButton*>(Sender)->Tag;
  szValue = szValue + IntToStr(iTag);
  if (iMode==0) Label1->Caption = StrToInt(szValue);
   else Label1->Caption = atof(szValue.c_str());
  szValue = Label1->Caption;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_PasswordLogin::WCImageButton11Click(TObject *Sender)
{
  iMode = 1;
  szValue = szValue + ".";
  Label1->Caption = szValue;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_PasswordLogin::WCImageButton17Click(TObject *Sender)
{
  iMode = 0;
  szValue = "0";
  Label1->Caption = szValue;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_PasswordLogin::WCImageButton15Click(TObject *Sender)
{
  char  szBuffer[128];

  strcpy(szBuffer,szValue.c_str());
  szBuffer[szValue.Length()-1] = 0x00;
  szValue = szBuffer;
  Label1->Caption = szValue;
}
//---------------------------------------------------------------------------

