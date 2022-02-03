//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "TypeConversion.h"
#include "frmCalculator.h"
#include "frmRGB_X_Main.h"
#include "frmSettingRange.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvEdBtn"
#pragma link "AdvEdit"
#pragma link "AdvEdit"
#pragma link "AdvSpin"
#pragma link "WCImageButton"
#pragma resource "*.dfm"
Tfrm_SettingRange *frm_SettingRange;
//---------------------------------------------------------------------------
extern  DeviceConfig    stDeviceConfig;
//---------------------------------------------------------------------------
__fastcall Tfrm_SettingRange::Tfrm_SettingRange(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingRange::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingRange::FormShow(TObject *Sender)
{
  Label1->Caption = szDataName;
  memcpy((char*)&stSetData,(char*)&stDeviceConfig.CurStatus.RGB_UCL,sizeof(UCL_SET_DATA));
  WCImageButton2->Enabled = true;
  if (iDataCode==0x01) {
    Label2->Caption = IntToStr(stSetData.RGB_UCL);
    Label3->Caption = IntToStr(stSetData.RGB_SET);
    Label4->Caption = IntToStr(stSetData.RGB_LCL);
    Label5->Caption = IntToStr(stDeviceConfig.RGB_Top);
    Label6->Caption = IntToStr(stDeviceConfig.RGB_Bottom);
  } else if (iDataCode==0x02) {
    Label2->Caption = IntToStr(stSetData.ORP_UCL);
    Label3->Caption = IntToStr(stSetData.ORP_SET);
    Label4->Caption = IntToStr(stSetData.ORP_LCL);
    Label5->Caption = IntToStr(stDeviceConfig.ORP_Top);
    Label6->Caption = IntToStr(stDeviceConfig.ORP_Bottom);
  } else if (iDataCode==0x03) {
    Label2->Caption = FormatFloat("0.00",stSetData.HCL_UCL / 100.0);
    Label3->Caption = FormatFloat("0.00",stSetData.HCL_SET / 100.0);
    Label4->Caption = FormatFloat("0.00",stSetData.HCL_LCL / 100.0);
    Label5->Caption = FormatFloat("0.00",stDeviceConfig.HCL_Top / 100.0);
    Label6->Caption = FormatFloat("0.00",stDeviceConfig.HCL_Bottom / 100.0);
  } else if (iDataCode==0x04) {
    Label2->Caption = FormatFloat("0.000",stSetData.SG_UCL / 1000.0);
    Label3->Caption = FormatFloat("0.000",stSetData.SG_SET / 1000.0);
    Label4->Caption = FormatFloat("0.000",stSetData.SG_LCL / 1000.0);
    Label5->Caption = FormatFloat("0.000",stDeviceConfig.SG_Top / 1000.0);
    Label6->Caption = FormatFloat("0.000",stDeviceConfig.SG_Bottom / 1000.0);
  } else if (iDataCode==0x05) {
    WCImageButton2->Enabled = false;
    Label2->Caption = FormatFloat("00.0",stSetData.TEMP_UCL / 10.0);
    Label3->Caption = 0;
    Label4->Caption = FormatFloat("00.0",stSetData.TEMP_LCL / 10.0);
    Label5->Caption = FormatFloat("00.0",stDeviceConfig.TEMP_Top / 10.0);
    Label6->Caption = FormatFloat("00.0",stDeviceConfig.TEMP_Bottom / 10.0);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingRange::WCImageButton6Click(TObject *Sender)
{
  char      szFileName[1024];
  char  szSendData[32] = { 0x00, };

  strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
  strcat(szFileName,"Config.ini");
  if (iDataCode==0x01) {
    stSetData.RGB_UCL = StrToInt(Label2->Caption);
    stSetData.RGB_SET = StrToInt(Label3->Caption);
    stSetData.RGB_LCL = StrToInt(Label4->Caption);
    stDeviceConfig.RGB_Top = StrToInt(Label5->Caption);
    stDeviceConfig.RGB_Bottom = StrToInt(Label6->Caption);
    WritePrivateProfileString("RGB_X","RGB_Top",IntToStr(stDeviceConfig.RGB_Top).c_str(),szFileName);
    WritePrivateProfileString("RGB_X","RGB_Bottom",IntToStr(stDeviceConfig.RGB_Bottom).c_str(),szFileName);
  } else if (iDataCode==0x02) {
    stSetData.ORP_UCL = StrToInt(Label2->Caption);
    stSetData.ORP_SET = StrToInt(Label3->Caption);
    stSetData.ORP_LCL = StrToInt(Label4->Caption);
    stDeviceConfig.ORP_Top = StrToInt(Label5->Caption);
    stDeviceConfig.ORP_Bottom = StrToInt(Label6->Caption);
    WritePrivateProfileString("RGB_X","ORP_Top",IntToStr(stDeviceConfig.ORP_Top).c_str(),szFileName);
    WritePrivateProfileString("RGB_X","ORP_Bottom",IntToStr(stDeviceConfig.ORP_Bottom).c_str(),szFileName);
  } else if (iDataCode==0x03) {
    stSetData.HCL_UCL = StrToFloat(Label2->Caption) * 100;
    stSetData.HCL_SET = StrToFloat(Label3->Caption) * 100;
    stSetData.HCL_LCL = StrToFloat(Label4->Caption) * 100;
    stDeviceConfig.HCL_Top = StrToFloat(Label5->Caption) * 100;
    stDeviceConfig.HCL_Bottom = StrToFloat(Label6->Caption) * 100;
    WritePrivateProfileString("RGB_X","HCL_Top",IntToStr(stDeviceConfig.HCL_Top).c_str(),szFileName);
    WritePrivateProfileString("RGB_X","HCL_Bottom",IntToStr(stDeviceConfig.HCL_Bottom).c_str(),szFileName);
  } else if (iDataCode==0x04) {
    stSetData.SG_UCL = StrToFloat(Label2->Caption) * 1000;
    stSetData.SG_SET = StrToFloat(Label3->Caption) * 1000;
    stSetData.SG_LCL = StrToFloat(Label4->Caption) * 1000;
    stDeviceConfig.SG_Top = StrToFloat(Label5->Caption) * 1000;
    stDeviceConfig.SG_Bottom = StrToFloat(Label6->Caption) * 1000;
    WritePrivateProfileString("RGB_X","SG_Top",IntToStr(stDeviceConfig.SG_Top).c_str(),szFileName);
    WritePrivateProfileString("RGB_X","SG_Bottom",IntToStr(stDeviceConfig.SG_Bottom).c_str(),szFileName);
  } else if (iDataCode==0x05) {
    stSetData.TEMP_UCL = StrToFloat(Label2->Caption) * 10;
    stSetData.TEMP_LCL = StrToFloat(Label4->Caption) * 10;
    stDeviceConfig.TEMP_Top = StrToFloat(Label5->Caption) * 10;
    stDeviceConfig.TEMP_Bottom = StrToFloat(Label6->Caption) * 10;
    WritePrivateProfileString("RGB_X","TEMP_Top",IntToStr(stDeviceConfig.TEMP_Top).c_str(),szFileName);
    WritePrivateProfileString("RGB_X","TEMP_Bottom",IntToStr(stDeviceConfig.TEMP_Bottom).c_str(),szFileName);
  }
  TypeConversion(&stSetData);
  frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);     // Request Device Status
  TypeConversion(&stSetData);
  Sleep(100);
//  frm_RGB_X_Main->Make_SendMessage(CMD_STATUS_DATA,0x01,szSendData);     // Request Device Status
  Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingRange::WCImageButton1Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 40;
  frm_Calculator->Left = this->Left + this->Width + 10;;
  frm_Calculator->Label1->Caption = Label2->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label2->Caption = frm_Calculator->szValue;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingRange::WCImageButton2Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 40;
  frm_Calculator->Left = this->Left + this->Width + 10;;
  frm_Calculator->Label1->Caption = Label3->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label3->Caption = frm_Calculator->szValue;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingRange::WCImageButton3Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 40;
  frm_Calculator->Left = this->Left + this->Width + 10;;
  frm_Calculator->Label1->Caption = Label4->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label4->Caption = frm_Calculator->szValue;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingRange::WCImageButton4Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 40;
  frm_Calculator->Left = this->Left + this->Width + 10;;
  frm_Calculator->Label1->Caption = Label5->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label5->Caption = frm_Calculator->szValue;
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingRange::WCImageButton5Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 40;
  frm_Calculator->Left = this->Left + this->Width + 10;;
  frm_Calculator->Label1->Caption = Label6->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label6->Caption = frm_Calculator->szValue;
  }
}
//---------------------------------------------------------------------------

