//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "DatabaseFunction.h"
#include "frmCalculator.h"
#include "frmGraphUsage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma link "AdvSpin"
#pragma resource "*.dfm"
Tfrm_GraphUsage *frm_GraphUsage;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
extern  DeviceConfig      stDeviceConfig;
extern  GraphUsage        stGraphUsage[31];
//---------------------------------------------------------------------------
__fastcall Tfrm_GraphUsage::Tfrm_GraphUsage(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphUsage::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphUsage::FormCreate(TObject *Sender)
{
  DateTimePicker1->Date = Now();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphUsage::FormShow(TObject *Sender)
{
  char  szBuffer[1024];

  try {
    Label20->Caption = FormatFloat("0.00",stDeviceConfig.HCL_Capa);
    Label10->Caption = FormatFloat("0.00",stDeviceConfig.HCL_Daily);
    Label11->Caption = FormatFloat("0.00",stDeviceConfig.HCL_Total);
    Label12->Caption = FormatFloat("0.00",stDeviceConfig.OXI_Capa);
    Label13->Caption = FormatFloat("0.00",stDeviceConfig.OXI_Daily);
    Label14->Caption = FormatFloat("0.00",stDeviceConfig.OXI_Total);
    Label15->Caption = FormatFloat("0.00",stDeviceConfig.H2O_Capa);
    Label16->Caption = FormatFloat("0.00",stDeviceConfig.H2O_Daily);
    Label17->Caption = FormatFloat("0.00",stDeviceConfig.H2O_Total);
  } catch(...) {
  }
  DateTimePicker1Change(NULL);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphUsage::WCImageButton6Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphUsage::DateTimePicker1Change(TObject *Sender)
{
  int   iResult;
  int   iOXI,iHCL,iH2O;
  char  szCheckDate[64];

  strcpy(szCheckDate,DateTimePicker1->Date.FormatString("yyyy-mm").c_str());
  iResult = DataBase_GraphUsage_Search_byDateTime(szCheckDate);
  Chart1->Series[0]->Clear();
  Chart1->Series[1]->Clear();
  Chart1->Series[2]->Clear();
  iOXI = iHCL = iH2O = 0;
  for(int i=0;i<iResult;i++) {
    iHCL = iHCL + stGraphUsage[i].HCL_Pump;
    iOXI = iOXI + stGraphUsage[i].OXI_Pump;
    iH2O = iH2O + stGraphUsage[i].H2O_Pump;
    Chart1->Series[0]->AddY( stGraphUsage[i].OXI_Pump , stGraphUsage[i].iDays );
    Chart1->Series[1]->AddY( stGraphUsage[i].HCL_Pump , stGraphUsage[i].iDays );
    Chart1->Series[2]->AddY( stGraphUsage[i].H2O_Pump , stGraphUsage[i].iDays );
  }
  Label18->Caption = IntToStr(iOXI);
  Label19->Caption = IntToStr(iHCL);
  Label21->Caption = IntToStr(iH2O);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_GraphUsage::WCImageButton17Click(TObject *Sender)
{
  char      szFileName[1024];

  frm_Calculator->Top = this->Top + 80;
  frm_Calculator->Left = this->Left + 120;;
  frm_Calculator->Label1->Caption = Label20->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label20->Caption = frm_Calculator->szValue;
    stDeviceConfig.HCL_Capa = StrToFloat(Label20->Caption);
    strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
    strcat(szFileName,"Config.ini");
    WritePrivateProfileString("GRAPG_USAGE","HCL_Capa" ,FloatToStr(stDeviceConfig.HCL_Capa).c_str(),szFileName);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_GraphUsage::WCImageButton1Click(TObject *Sender)
{
  char      szFileName[1024];

  frm_Calculator->Top = this->Top + 80;
  frm_Calculator->Left = this->Left + 370;;
  frm_Calculator->Label1->Caption = Label12->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label12->Caption = frm_Calculator->szValue;
    stDeviceConfig.OXI_Capa = StrToFloat(Label12->Caption);
    strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
    strcat(szFileName,"Config.ini");
    WritePrivateProfileString("GRAPG_USAGE","OXI_Capa" ,FloatToStr(stDeviceConfig.OXI_Capa).c_str(),szFileName);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_GraphUsage::WCImageButton2Click(TObject *Sender)
{
  char      szFileName[1024];

  frm_Calculator->Top = this->Top + 80;
  frm_Calculator->Left = this->Left + 620;;
  frm_Calculator->Label1->Caption = Label15->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label15->Caption = frm_Calculator->szValue;
    stDeviceConfig.H2O_Capa = StrToFloat(Label15->Caption);
    strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
    strcat(szFileName,"Config.ini");
    WritePrivateProfileString("GRAPG_USAGE","H2O_Capa" ,FloatToStr(stDeviceConfig.H2O_Capa).c_str(),szFileName);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_GraphUsage::WCImageButton3Click(TObject *Sender)
{
  stDeviceConfig.HCL_Daily = 0;
  stDeviceConfig.HCL_Total = 0;
  FormShow(NULL);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_GraphUsage::WCImageButton4Click(TObject *Sender)
{
  stDeviceConfig.OXI_Daily = 0;
  stDeviceConfig.OXI_Total = 0;
  FormShow(NULL);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_GraphUsage::WCImageButton5Click(TObject *Sender)
{
  stDeviceConfig.H2O_Daily = 0;
  stDeviceConfig.H2O_Total = 0;
  FormShow(NULL);
}
//---------------------------------------------------------------------------

