//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "DatabaseFunction.h"
#include "frmSettingControl.h"
#include "frmRGB_X_Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma resource "*.dfm"
Tfrm_SettingControl *frm_SettingControl;
//---------------------------------------------------------------------------
extern  DeviceConfig        stDeviceConfig;
//---------------------------------------------------------------------------
__fastcall Tfrm_SettingControl::Tfrm_SettingControl(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingControl::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingControl::ImageChange_byID(TWCImageButton *BtnCtrl,int iMode)
{
  Graphics::TBitmap *BlankScr1 = new Graphics::TBitmap();

  ImageList1->GetBitmap(iMode,BlankScr1);
  BtnCtrl->Picture_Normal->Bitmap->Assign(BlankScr1);
  delete BlankScr1;
  BtnCtrl->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingControl::WCImageButton6Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingControl::FormShow(TObject *Sender)
{
  if (stDeviceConfig.CurStatus.ModePump.bit8.ONOFF_HBC==0x00) {   // 0:HBC , 1:On/OFF
    ImageChange_byID(WCImageButton1,0x00);
    ImageChange_byID(WCImageButton2,0x03);
  } else {
    ImageChange_byID(WCImageButton1,0x01);
    ImageChange_byID(WCImageButton2,0x02);
  }
  if (stDeviceConfig.CurStatus.ModePump.bit8.RGB_ORP==0x01) {     // 0:ORP , 1:RGB
    ImageChange_byID(WCImageButton3,0x05);
    ImageChange_byID(WCImageButton4,0x06);
  } else {
    ImageChange_byID(WCImageButton3,0x04);
    ImageChange_byID(WCImageButton4,0x07);
  }
  if (stDeviceConfig.Control_SubHCL1==0x01) {
    ImageChange_byID(WCImageButton5,0x09);
  } else {
    ImageChange_byID(WCImageButton5,0x08);
  }
  if (stDeviceConfig.Control_SubHCL2==0x01) {
    ImageChange_byID(WCImageButton7,0x0B);
  } else {
    ImageChange_byID(WCImageButton7,0x0A);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingControl::WCImageButton1Click(TObject *Sender)
{
  U_Control       ModePump;
  char  szSendData[32] = { 0x00, };

  if (stDeviceConfig.CurStatus.ModePump.bit8.ONOFF_HBC==0x00) {   // 0:HBC , 1:On/OFF
    ModePump.Value = stDeviceConfig.CurSensor.ModePump.Value;
    ModePump.bit8.ONOFF_HBC = 0x01;
    szSendData[0] = ModePump.Value;
    frm_RGB_X_Main->Make_SendMessage(CMD_MODE_N_PUMP,0x01,szSendData);     // Request Device Status
    stDeviceConfig.CurStatus.ModePump.bit8.ONOFF_HBC = 0x01;
    FormShow(NULL);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingControl::WCImageButton2Click(TObject *Sender)
{
  U_Control       ModePump;
  char  szSendData[32] = { 0x00, };

  if (stDeviceConfig.CurStatus.ModePump.bit8.ONOFF_HBC==0x01) {   // 0:HBC , 1:On/OFF
    ModePump.Value = stDeviceConfig.CurSensor.ModePump.Value;
    ModePump.bit8.ONOFF_HBC = 0x00;
    szSendData[0] = ModePump.Value;
    frm_RGB_X_Main->Make_SendMessage(CMD_MODE_N_PUMP,0x01,szSendData);     // Request Device Status
    stDeviceConfig.CurStatus.ModePump.bit8.ONOFF_HBC = 0x00;
    FormShow(NULL);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingControl::WCImageButton3Click(TObject *Sender)
{
  U_Control       ModePump;
  char  szSendData[32] = { 0x00, };

  if (stDeviceConfig.CurStatus.ModePump.bit8.RGB_ORP==0x00) {     // 0:ORP , 1:RGB
    ModePump.Value = stDeviceConfig.CurSensor.ModePump.Value;
    ModePump.bit8.RGB_ORP = 0x01;
    szSendData[0] = ModePump.Value;
    frm_RGB_X_Main->Make_SendMessage(CMD_MODE_N_PUMP,0x01,szSendData);     // Request Device Status
    stDeviceConfig.CurStatus.ModePump.bit8.RGB_ORP = 0x01;
    FormShow(NULL);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingControl::WCImageButton4Click(TObject *Sender)
{
  U_Control       ModePump;
  char  szSendData[32] = { 0x00, };

  if (stDeviceConfig.CurStatus.ModePump.bit8.RGB_ORP==0x01) {     // 0:ORP , 1:RGB
    ModePump.Value = stDeviceConfig.CurSensor.ModePump.Value;
    ModePump.bit8.RGB_ORP = 0x00;
    szSendData[0] = ModePump.Value;
    frm_RGB_X_Main->Make_SendMessage(CMD_MODE_N_PUMP,0x01,szSendData);     // Request Device Status
    stDeviceConfig.CurStatus.ModePump.bit8.RGB_ORP = 0x00;
    FormShow(NULL);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingControl::WCImageButton5Click(TObject *Sender)
{
  char      szFileName[1024];

  if (stDeviceConfig.Control_SubHCL2 == 0x00) {
    stDeviceConfig.Control_SubHCL1 = !stDeviceConfig.Control_SubHCL1;
    if (stDeviceConfig.Control_SubHCL1==0x01) {
      ImageChange_byID(WCImageButton5,0x09);
    } else {
      ImageChange_byID(WCImageButton5,0x08);
    }
    try {
      strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
      strcat(szFileName,"Config.ini");
      WritePrivateProfileString("CONTROL","SubHCL1" ,IntToStr(stDeviceConfig.Control_SubHCL1).c_str(),szFileName);
    } catch(...) {
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingControl::WCImageButton7Click(TObject *Sender)
{
  char      szFileName[1024];

  if (stDeviceConfig.Control_SubHCL1 == 0x00) {
    stDeviceConfig.Control_SubHCL2 = !stDeviceConfig.Control_SubHCL2;
    if (stDeviceConfig.Control_SubHCL2==0x01) {
      ImageChange_byID(WCImageButton7,0x0B);
    } else {
      ImageChange_byID(WCImageButton7,0x0A);
    }
    try {
      strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
      strcat(szFileName,"Config.ini");
      WritePrivateProfileString("CONTROL","SubHCL2" ,IntToStr(stDeviceConfig.Control_SubHCL2).c_str(),szFileName);
    } catch(...) {
    }
  }
}
//---------------------------------------------------------------------------

