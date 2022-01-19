//---------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "DatabaseFunction.h"
#include "frmCalculator.h"
#include "frmSettingSensorChange.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma resource "*.dfm"
Tfrm_SettingSensorChange *frm_SettingSensorChange;
//---------------------------------------------------------------------------
extern  DeviceConfig      stDeviceConfig;
//---------------------------------------------------------------------------
__fastcall Tfrm_SettingSensorChange::Tfrm_SettingSensorChange(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingSensorChange::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingSensorChange::FormShow(TObject *Sender)
{
  short int iYear,iMonth,iDay;

  try {
    if (strlen(stDeviceConfig.szChangeDate_RGB) > 8) {
      iYear = atoi(stDeviceConfig.szChangeDate_RGB);
      iMonth = atoi(&stDeviceConfig.szChangeDate_RGB[5]);
      iDay = atoi(&stDeviceConfig.szChangeDate_RGB[8]);
      DateTimePicker1->Date = EncodeDate(iYear,iMonth,iDay);
    } else {
      DateTimePicker1->Date = Now();
    }
    if (strlen(stDeviceConfig.szChangeDate_ORP) > 8) {
      iYear = atoi(stDeviceConfig.szChangeDate_ORP);
      iMonth = atoi(&stDeviceConfig.szChangeDate_ORP[5]);
      iDay = atoi(&stDeviceConfig.szChangeDate_ORP[8]);
      DateTimePicker2->Date = EncodeDate(iYear,iMonth,iDay);
    } else {
      DateTimePicker2->Date = Now();
    }
    if (strlen(stDeviceConfig.szChangeDate_HCL) > 8) {
      iYear = atoi(stDeviceConfig.szChangeDate_HCL);
      iMonth = atoi(&stDeviceConfig.szChangeDate_HCL[5]);
      iDay = atoi(&stDeviceConfig.szChangeDate_HCL[8]);
      DateTimePicker3->Date = EncodeDate(iYear,iMonth,iDay);
    } else {
      DateTimePicker3->Date = Now();
    }
    if (strlen(stDeviceConfig.szChangeDate_SG) > 8) {
      iYear = atoi(stDeviceConfig.szChangeDate_SG);
      iMonth = atoi(&stDeviceConfig.szChangeDate_SG[5]);
      iDay = atoi(&stDeviceConfig.szChangeDate_SG[8]);
      DateTimePicker4->Date = EncodeDate(iYear,iMonth,iDay);
    } else {
      DateTimePicker4->Date = Now();
    }
  } catch(...) {
  }
  Label20->Caption = IntToStr(stDeviceConfig.ORP_Count);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingSensorChange::WCImageButton6Click(
      TObject *Sender)
{
  char      szFileName[1024];
  try {
    strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
    strcat(szFileName,"Config.ini");
    WritePrivateProfileString("SENSOR_CHANGE","CHANGEDATE_RGB" ,DateTimePicker1->Date.FormatString("yyyy-mm-dd").c_str(),szFileName);
    WritePrivateProfileString("SENSOR_CHANGE","CHANGEDATE_ORP" ,DateTimePicker2->Date.FormatString("yyyy-mm-dd").c_str(),szFileName);
    WritePrivateProfileString("SENSOR_CHANGE","CHANGEDATE_HCL" ,DateTimePicker3->Date.FormatString("yyyy-mm-dd").c_str(),szFileName);
    WritePrivateProfileString("SENSOR_CHANGE","CHANGEDATE_SG"  ,DateTimePicker4->Date.FormatString("yyyy-mm-dd").c_str(),szFileName);
    WritePrivateProfileString("SENSOR_CHANGE","ORP_Count" ,Label20->Caption.c_str(),szFileName);
  } catch(...) {
  }
  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingSensorChange::WCImageButton1Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 100;
  frm_Calculator->Left = this->Left + 450;;
  frm_Calculator->Label1->Caption = Label20->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label20->Caption = frm_Calculator->szValue;
    stDeviceConfig.ORP_Count = StrToFloat(Label20->Caption);
  }
}
//---------------------------------------------------------------------------


