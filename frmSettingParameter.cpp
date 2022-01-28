//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "TypeConversion.h"
#include "frmCalculator.h"
#include "frmRGB_X_Main.h"
#include "frmSettingParameter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvSpin"
#pragma link "WCImageButton"
#pragma resource "*.dfm"
Tfrm_SettingParameter *frm_SettingParameter;
//---------------------------------------------------------------------------
UCL_SET_DATA            stSetData;
OnOff_TimeData          stSetTime;
extern  DeviceConfig    stDeviceConfig;
//---------------------------------------------------------------------------
__fastcall Tfrm_SettingParameter::Tfrm_SettingParameter(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingParameter::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingParameter::FormShow(TObject *Sender)
{
  memcpy((char*)&stSetData,(char*)&stDeviceConfig.CurStatus.RGB_UCL,sizeof(UCL_SET_DATA));
  memcpy((char*)&stSetTime,(char*)&stDeviceConfig.CurStatus.RGB_ON_TIME,sizeof(OnOff_TimeData));
  Label1->Caption = IntToStr(stSetData.RGB_UCL);
  Label2->Caption = IntToStr(stSetData.RGB_SET);
  Label3->Caption = IntToStr(stSetData.RGB_LCL);
  Label4->Caption = IntToStr(stSetData.ORP_UCL);
  Label5->Caption = IntToStr(stSetData.ORP_SET);
  Label6->Caption = IntToStr(stSetData.ORP_LCL);
  Label7->Caption = FormatFloat("0.00",stSetData.HCL_UCL / 100.0);
  Label8->Caption = FormatFloat("0.00",stSetData.HCL_SET / 100.0);
  Label9->Caption = FormatFloat("0.00",stSetData.HCL_LCL / 100.0);
  Label10->Caption = FormatFloat("0.000",stSetData.SG_UCL / 1000.0);
  Label11->Caption = FormatFloat("0.000",stSetData.SG_SET / 1000.0);
  Label12->Caption = FormatFloat("0.000",stSetData.SG_LCL / 1000.0);
  Label13->Caption = FormatFloat("00.0",stSetData.TEMP_UCL / 10.0);
  Label15->Caption = FormatFloat("00.0",stSetData.TEMP_LCL / 10.0);
// Setting_Control 에서의 설정값
  if (stDeviceConfig.CurStatus.ModePump.bit8.RGB_ORP==0x01) {    // RGB:1 , ORP:0
    Label16->Caption = IntToStr(stSetTime.RGB_ON_TIME);
    Label17->Caption = IntToStr(stSetTime.RGB_OFF_TIME);
  } else {
    Label16->Caption = IntToStr(stSetTime.ORP_ON_TIME);
    Label17->Caption = IntToStr(stSetTime.ORP_OFF_TIME);
  }
  Label18->Caption = IntToStr(stSetTime.HCL_ON_TIME);
  Label19->Caption = IntToStr(stSetTime.HCL_OFF_TIME);
  Label20->Caption = IntToStr(stSetTime.SG_ON_TIME);
  Label21->Caption = IntToStr(stSetTime.SG_OFF_TIME);
  Label22->Caption = IntToStr(stSetTime.MAX_ON_TIME);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingParameter::WCImageButton6Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingParameter::WCImageButton1Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 80;
  frm_Calculator->Left = this->Left + 120;;
  frm_Calculator->Label1->Caption = Label1->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label1->Caption = frm_Calculator->szValue;
    stSetData.RGB_UCL = frm_Calculator->szValue.ToIntDef(0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton2Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 125;
  frm_Calculator->Left = this->Left + 120;;
  frm_Calculator->Label1->Caption = Label2->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label2->Caption = frm_Calculator->szValue;
    stSetData.RGB_SET = frm_Calculator->szValue.ToIntDef(0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton3Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 170;
  frm_Calculator->Left = this->Left + 120;;
  frm_Calculator->Label1->Caption = Label3->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label3->Caption = frm_Calculator->szValue;
    stSetData.RGB_LCL = frm_Calculator->szValue.ToIntDef(0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton4Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 80;
  frm_Calculator->Left = this->Left + 320;;
  frm_Calculator->Label1->Caption = Label4->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label4->Caption = frm_Calculator->szValue;
    stSetData.ORP_UCL = frm_Calculator->szValue.ToIntDef(0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton5Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 125;
  frm_Calculator->Left = this->Left + 320;;
  frm_Calculator->Label1->Caption = Label5->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label5->Caption = frm_Calculator->szValue;
    stSetData.ORP_SET = frm_Calculator->szValue.ToIntDef(0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton7Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 170;
  frm_Calculator->Left = this->Left + 320;;
  frm_Calculator->Label1->Caption = Label6->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label6->Caption = frm_Calculator->szValue;
    stSetData.ORP_LCL = frm_Calculator->szValue.ToIntDef(0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton8Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 80;
  frm_Calculator->Left = this->Left + 520;;
  frm_Calculator->Label1->Caption = Label7->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    stSetData.HCL_UCL = frm_Calculator->szValue.ToDouble() * 100.0;
    Label7->Caption = FormatFloat("0.00",stSetData.HCL_UCL / 100.0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton9Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 125;
  frm_Calculator->Left = this->Left + 520;;
  frm_Calculator->Label1->Caption = Label8->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    stSetData.HCL_SET = frm_Calculator->szValue.ToDouble() * 100.0;
    Label8->Caption = FormatFloat("0.00",stSetData.HCL_SET / 100.0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton10Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 170;
  frm_Calculator->Left = this->Left + 520;;
  frm_Calculator->Label1->Caption = Label9->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    stSetData.HCL_LCL = frm_Calculator->szValue.ToDouble() * 100.0;
    Label9->Caption = FormatFloat("0.00",stSetData.HCL_LCL / 100.0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton11Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 80;
  frm_Calculator->Left = this->Left + 720;;
  frm_Calculator->Label1->Caption = Label10->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
//    Label10->Caption = frm_Calculator->szValue;
    stSetData.SG_UCL = frm_Calculator->szValue.ToDouble() * 1000.0;
    Label10->Caption = FormatFloat("0.000",stSetData.SG_UCL / 1000.0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton12Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 125;
  frm_Calculator->Left = this->Left + 720;;
  frm_Calculator->Label1->Caption = Label11->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
//    Label11->Caption = frm_Calculator->szValue;
    stSetData.SG_SET = frm_Calculator->szValue.ToDouble() * 1000.0;
    Label11->Caption = FormatFloat("0.000",stSetData.SG_SET / 1000.0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton13Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 170;
  frm_Calculator->Left = this->Left + 720;;
  frm_Calculator->Label1->Caption = Label12->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
//    Label12->Caption = frm_Calculator->szValue;
    stSetData.SG_LCL = frm_Calculator->szValue.ToDouble() * 1000.0;
    Label12->Caption = FormatFloat("0.000",stSetData.SG_LCL / 1000.0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton14Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 80;
  frm_Calculator->Left = this->Left + 540;;
  frm_Calculator->Label1->Caption = Label13->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
//    Label13->Caption = frm_Calculator->szValue;
    stSetData.TEMP_UCL = frm_Calculator->szValue.ToDouble() * 10.0;
    Label13->Caption = FormatFloat("00.0",stSetData.TEMP_UCL / 10.0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_SettingParameter::WCImageButton16Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 170;
  frm_Calculator->Left = this->Left + 540;;
  frm_Calculator->Label1->Caption = Label15->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
//    Label15->Caption = frm_Calculator->szValue;
    stSetData.TEMP_LCL = frm_Calculator->szValue.ToDouble() * 10.0;
    Label15->Caption = FormatFloat("00.0",stSetData.TEMP_LCL / 10.0);
    TypeConversion(&stSetData);
    frm_RGB_X_Main->Make_SendMessage(CMD_UCL_SET_LCL,sizeof(UCL_SET_DATA),(char*)&stSetData);
    TypeConversion(&stSetData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton17Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 226;
  frm_Calculator->Left = this->Left + 120;;
  frm_Calculator->Label1->Caption = Label16->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label16->Caption = frm_Calculator->szValue;
    if (stDeviceConfig.CurStatus.ModePump.bit8.RGB_ORP==0x01) {    // RGB
      stSetTime.RGB_ON_TIME = frm_Calculator->szValue.ToIntDef(0);
    } else {
      stSetTime.ORP_ON_TIME = frm_Calculator->szValue.ToIntDef(0);
    }
   frm_RGB_X_Main->Make_SendMessage(CMD_ONOFF_TIME ,sizeof(OnOff_TimeData),(char*)&stSetTime);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton18Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 270;
  frm_Calculator->Left = this->Left + 120;;
  frm_Calculator->Label1->Caption = Label17->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label17->Caption = frm_Calculator->szValue;
    if (stDeviceConfig.CurStatus.ModePump.bit8.RGB_ORP==0x01) {    // RGB
      stSetTime.RGB_OFF_TIME = frm_Calculator->szValue.ToIntDef(0);
    } else {
      stSetTime.ORP_OFF_TIME = frm_Calculator->szValue.ToIntDef(0);
    }
   frm_RGB_X_Main->Make_SendMessage(CMD_ONOFF_TIME ,sizeof(OnOff_TimeData),(char*)&stSetTime);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton19Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 226;
  frm_Calculator->Left = this->Left + 320;;
  frm_Calculator->Label1->Caption = Label18->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label18->Caption = frm_Calculator->szValue;
    stSetTime.HCL_ON_TIME = frm_Calculator->szValue.ToIntDef(0);
    frm_RGB_X_Main->Make_SendMessage(CMD_ONOFF_TIME ,sizeof(OnOff_TimeData),(char*)&stSetTime);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton20Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 270;
  frm_Calculator->Left = this->Left + 320;;
  frm_Calculator->Label1->Caption = Label19->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label19->Caption = frm_Calculator->szValue;
    stSetTime.HCL_OFF_TIME = frm_Calculator->szValue.ToIntDef(0);
    frm_RGB_X_Main->Make_SendMessage(CMD_ONOFF_TIME ,sizeof(OnOff_TimeData),(char*)&stSetTime);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton21Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 226;
  frm_Calculator->Left = this->Left + 520;;
  frm_Calculator->Label1->Caption = Label20->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label20->Caption = frm_Calculator->szValue;
    stSetTime.SG_ON_TIME = frm_Calculator->szValue.ToIntDef(0);
    frm_RGB_X_Main->Make_SendMessage(CMD_ONOFF_TIME ,sizeof(OnOff_TimeData),(char*)&stSetTime);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton22Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 270;
  frm_Calculator->Left = this->Left + 520;;
  frm_Calculator->Label1->Caption = Label21->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label21->Caption = frm_Calculator->szValue;
    stSetTime.SG_OFF_TIME = frm_Calculator->szValue.ToIntDef(0);
    frm_RGB_X_Main->Make_SendMessage(CMD_ONOFF_TIME ,sizeof(OnOff_TimeData),(char*)&stSetTime);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingParameter::WCImageButton23Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 290;
  frm_Calculator->Left = this->Left + 580;;
  frm_Calculator->Label1->Caption = Label22->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label22->Caption = frm_Calculator->szValue;
    stSetTime.MAX_ON_TIME = frm_Calculator->szValue.ToIntDef(0);
    frm_RGB_X_Main->Make_SendMessage(CMD_ONOFF_TIME ,sizeof(OnOff_TimeData),(char*)&stSetTime);
  }
}
//---------------------------------------------------------------------------

