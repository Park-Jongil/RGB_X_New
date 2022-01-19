//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "DatabaseFunction.h"
#include "frmCalculator.h"
#include "frmRGB_X_Main.h"
#include "frmSettingMaster.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma resource "*.dfm"
Tfrm_SettingMaster *frm_SettingMaster;
//---------------------------------------------------------------------------
extern  DeviceConfig        stDeviceConfig;
//---------------------------------------------------------------------------
__fastcall Tfrm_SettingMaster::Tfrm_SettingMaster(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingMaster::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingMaster::ImageChange_byID(TWCImageButton *BtnCtrl,int iMode)
{
  Graphics::TBitmap *BlankScr1 = new Graphics::TBitmap();

  ImageList1->GetBitmap(iMode,BlankScr1);
  BtnCtrl->Picture_Normal->Bitmap->Assign(BlankScr1);
  delete BlankScr1;
  BtnCtrl->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingMaster::FormShow(TObject *Sender)
{
  if (stDeviceConfig.isMasterPassword==0x00) {
    ImageChange_byID(WCImageButton1,0x00);
  } else {
    ImageChange_byID(WCImageButton1,0x01);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingMaster::WCImageButton6Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingMaster::WCImageButton5Click(TObject *Sender)
{
  frm_RGB_X_Main->ComPort1->Connected = false;
  frm_RGB_X_Main->ComPort1->ShowSetupDialog();
  frm_RGB_X_Main->ComPort1->Connected = true;
  frm_RGB_X_Main->ComPort1->StoreSettings( stIniFile , "RGB_X_New.ini");
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_SettingMaster::WCImageButton1Click(TObject *Sender)
{
  char      szFileName[1024];

  stDeviceConfig.isMasterPassword = !stDeviceConfig.isMasterPassword;
  ImageChange_byID(WCImageButton1,stDeviceConfig.isMasterPassword);
  try {
    strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
    strcat(szFileName,"Config.ini");
    WritePrivateProfileString("MASTER","isPawword" ,IntToStr(stDeviceConfig.isMasterPassword).c_str(),szFileName);
  } catch(...) {
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingMaster::WCImageButton2Click(TObject *Sender)
{
  char      szFileName[1024];
  if (stDeviceConfig.isMasterPassword == 0x01) {
    frm_Calculator->Top = this->Top + 90;
    frm_Calculator->Left = this->Left + 520;
    frm_Calculator->Label1->Caption = stDeviceConfig.szMasterPassword;
    if (frm_Calculator->ShowModal()==mrOk) {   //
      strcpy(stDeviceConfig.szMasterPassword,frm_Calculator->szValue.c_str());
      strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
      strcat(szFileName,"Config.ini");
      WritePrivateProfileString("MASTER","PASSWORD" ,stDeviceConfig.szMasterPassword,szFileName);
    }
  }
}
//---------------------------------------------------------------------------

