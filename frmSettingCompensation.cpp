//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "TypeConversion.h"
#include "frmCalculator.h"
#include "frmRGB_X_Main.h"
#include "frmSettingCompensation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma resource "*.dfm"
Tfrm_SettingCompensation *frm_SettingCompensation;
//---------------------------------------------------------------------------
Sensor_ShiftData        stShiftData;
RGB_WLED_Brightness     stRGB_WLED;
extern  DeviceConfig    stDeviceConfig;
//---------------------------------------------------------------------------
__fastcall Tfrm_SettingCompensation::Tfrm_SettingCompensation(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingCompensation::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingCompensation::WCImageButton6Click(
      TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingCompensation::FormShow(TObject *Sender)
{
  memcpy((char*)&stShiftData,(char*)&stDeviceConfig.CurStatus.R_SHIFT,sizeof(stShiftData));
  stRGB_WLED.FQ_RGB_WLED = stDeviceConfig.CurStatus.FQ_RGB_WLED;
  Label1->Caption = IntToStr(stShiftData.R_SHIFT);
  Label2->Caption = IntToStr(stShiftData.G_SHIFT);
  Label3->Caption = IntToStr(stShiftData.B_SHIFT);
  Label4->Caption = IntToStr(stShiftData.ORP_SHIFT);
  Label5->Caption = FormatFloat("0.00",stShiftData.HCL_SHIFT/100.0);
  Label6->Caption = FormatFloat("0.000",stShiftData.SG_SHIFT/1000.0);
  Label7->Caption = FormatFloat("0.0",stShiftData.TEMP_SHIFT/10.0);
  Label8->Caption = IntToStr(stRGB_WLED.FQ_RGB_WLED);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingCompensation::WCImageButton1Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 50;
  frm_Calculator->Left = this->Left + 120;;
  frm_Calculator->Label1->Caption = IntToStr(stDeviceConfig.CurSensor.FQ_R);    //Label1->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label1->Caption = IntToStr(StrToInt(frm_Calculator->szValue)-stDeviceConfig.CurSensor.FQ_R+stShiftData.R_SHIFT);
    stShiftData.R_SHIFT = Label1->Caption.ToIntDef(0);
    TypeConversion(&stShiftData);
    frm_RGB_X_Main->Make_SendMessage(CMD_SENSOR_SHIFT,sizeof(Sensor_ShiftData),(char*)&stShiftData);
    TypeConversion(&stShiftData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingCompensation::WCImageButton2Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 110;
  frm_Calculator->Left = this->Left + 120;;
  frm_Calculator->Label1->Caption = IntToStr(stDeviceConfig.CurSensor.FQ_G);
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label2->Caption = IntToStr(StrToInt(frm_Calculator->szValue)-stDeviceConfig.CurSensor.FQ_G+stShiftData.G_SHIFT);
    stShiftData.G_SHIFT = Label2->Caption.ToIntDef(0);
    TypeConversion(&stShiftData);
    frm_RGB_X_Main->Make_SendMessage(CMD_SENSOR_SHIFT,sizeof(Sensor_ShiftData),(char*)&stShiftData);
    TypeConversion(&stShiftData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingCompensation::WCImageButton3Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 170;
  frm_Calculator->Left = this->Left + 120;;
  frm_Calculator->Label1->Caption = IntToStr(stDeviceConfig.CurSensor.FQ_B);
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label3->Caption = IntToStr(StrToInt(frm_Calculator->szValue)-stDeviceConfig.CurSensor.FQ_B+stShiftData.B_SHIFT);
    stShiftData.B_SHIFT = Label3->Caption.ToIntDef(0);
    TypeConversion(&stShiftData);
    frm_RGB_X_Main->Make_SendMessage(CMD_SENSOR_SHIFT,sizeof(Sensor_ShiftData),(char*)&stShiftData);
    TypeConversion(&stShiftData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingCompensation::WCImageButton4Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 50;
  frm_Calculator->Left = this->Left + 350;;
  frm_Calculator->Label1->Caption = IntToStr(stDeviceConfig.CurSensor.ORP);
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label4->Caption = IntToStr(StrToInt(frm_Calculator->szValue)-stDeviceConfig.CurSensor.ORP+stShiftData.ORP_SHIFT);
    stShiftData.ORP_SHIFT = Label4->Caption.ToIntDef(0);
    TypeConversion(&stShiftData);
    frm_RGB_X_Main->Make_SendMessage(CMD_SENSOR_SHIFT,sizeof(Sensor_ShiftData),(char*)&stShiftData);
    TypeConversion(&stShiftData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingCompensation::WCImageButton5Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 110;
  frm_Calculator->Left = this->Left + 350;;
  frm_Calculator->Label1->Caption = FormatFloat("0.00",stDeviceConfig.CurSensor.HCL/100.0);
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label5->Caption = FormatFloat("0.00",StrToFloat(frm_Calculator->szValue)-stDeviceConfig.CurSensor.HCL/100.0+stShiftData.HCL_SHIFT/100.0);
    stShiftData.HCL_SHIFT = (Label5->Caption.ToDouble() * 100);
    TypeConversion(&stShiftData);
    frm_RGB_X_Main->Make_SendMessage(CMD_SENSOR_SHIFT,sizeof(Sensor_ShiftData),(char*)&stShiftData);
    TypeConversion(&stShiftData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingCompensation::WCImageButton7Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 170;
  frm_Calculator->Left = this->Left + 350;;
  frm_Calculator->Label1->Caption = FormatFloat("0.000",stDeviceConfig.CurSensor.SG/1000.0);
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label6->Caption = FormatFloat("0.000",StrToFloat(frm_Calculator->szValue)-stDeviceConfig.CurSensor.SG/1000.0+stShiftData.SG_SHIFT/1000.0);
    stShiftData.SG_SHIFT = (Label6->Caption.ToDouble() * 1000);
    TypeConversion(&stShiftData);
    frm_RGB_X_Main->Make_SendMessage(CMD_SENSOR_SHIFT,sizeof(Sensor_ShiftData),(char*)&stShiftData);
    TypeConversion(&stShiftData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingCompensation::WCImageButton8Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 230;
  frm_Calculator->Left = this->Left + 350;;
  frm_Calculator->Label1->Caption = FormatFloat("0.0",stDeviceConfig.CurSensor.LQ_TEMP/10.0);
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label7->Caption = FormatFloat("0.0",StrToFloat(frm_Calculator->szValue)-stDeviceConfig.CurSensor.LQ_TEMP/10.0+stShiftData.TEMP_SHIFT/10.0);
    stShiftData.TEMP_SHIFT = (Label7->Caption.ToDouble() * 10);
    TypeConversion(&stShiftData);
    frm_RGB_X_Main->Make_SendMessage(CMD_SENSOR_SHIFT,sizeof(Sensor_ShiftData),(char*)&stShiftData);
    TypeConversion(&stShiftData);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingCompensation::WCImageButton9Click(
      TObject *Sender)
{
  frm_Calculator->Top = this->Top + 240;
  frm_Calculator->Left = this->Left + 120;;
  frm_Calculator->Label1->Caption = Label8->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label8->Caption = frm_Calculator->szValue;
    stRGB_WLED.FQ_RGB_WLED = frm_Calculator->szValue.ToIntDef(0);
    frm_RGB_X_Main->Make_SendMessage(CMD_RGB_WLED_BR ,sizeof(RGB_WLED_Brightness),(char*)&stRGB_WLED);
  }
}
//---------------------------------------------------------------------------

