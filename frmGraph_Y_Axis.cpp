//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "frmCalculator.h"
#include "frmGraph_Y_Axis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma link "AdvSpin"
#pragma resource "*.dfm"
Tfrm_Graph_Y_Axis *frm_Graph_Y_Axis;
//---------------------------------------------------------------------------
extern  DeviceConfig    stDeviceConfig;
//---------------------------------------------------------------------------
__fastcall Tfrm_Graph_Y_Axis::Tfrm_Graph_Y_Axis(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Graph_Y_Axis::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Graph_Y_Axis::FormShow(TObject *Sender)
{
  char        szFileName[1024],szBuffer[1024];

  Label1->Caption = szDataName;
  strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
  strcat(szFileName,"Config.ini");
// Config File Load
  try {
    if (iDataCode==0x00) {
      Label2->Caption = IntToStr(GetPrivateProfileInt("GRAPH_Y","RGB_Top",1000,szFileName));
      Label3->Caption = IntToStr(GetPrivateProfileInt("GRAPH_Y","RGB_Bottom",20,szFileName));
    } else if (iDataCode==0x01) {
      Label2->Caption = IntToStr(GetPrivateProfileInt("GRAPH_Y","ORP_Top",600,szFileName));
      Label3->Caption = IntToStr(GetPrivateProfileInt("GRAPH_Y","ORP_Bottom",450,szFileName));
    } else if (iDataCode==0x02) {
      GetPrivateProfileString("GRAPH_Y","HCL_Top" ,"1.20",szBuffer,1024,szFileName);
      Label2->Caption = FormatFloat("0.00",atof(szBuffer));
      GetPrivateProfileString("GRAPH_Y","HCL_Bottom" ,"0.40",szBuffer,1024,szFileName);
      Label3->Caption = FormatFloat("0.00",atof(szBuffer));
    } else if (iDataCode==0x03) {
      GetPrivateProfileString("GRAPH_Y","SG_Top" ,"1.400",szBuffer,1024,szFileName);
      Label2->Caption = FormatFloat("0.000",atof(szBuffer));
      GetPrivateProfileString("GRAPH_Y","SG_Bottom" ,"1.280",szBuffer,1024,szFileName);
      Label3->Caption = FormatFloat("0.000",atof(szBuffer));;
    } else if (iDataCode==0x04) {
      GetPrivateProfileString("GRAPH_Y","TEMP_Top" ,"55.0",szBuffer,1024,szFileName);
      Label2->Caption = FormatFloat("00.0",atof(szBuffer));;
      GetPrivateProfileString("GRAPH_Y","TEMP_Bottom" ,"45.0",szBuffer,1024,szFileName);
      Label3->Caption = FormatFloat("00.0",atof(szBuffer));;
    }
  } catch(...) {
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Graph_Y_Axis::WCImageButton6Click(TObject *Sender)
{
  char      szFileName[1024];

  strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
  strcat(szFileName,"Config.ini");
  if (iDataCode==0x00) {
    WritePrivateProfileString("GRAPH_Y","RGB_Top",Label2->Caption.c_str(),szFileName);
    WritePrivateProfileString("GRAPH_Y","RGB_Bottom",Label3->Caption.c_str(),szFileName);
  } else if (iDataCode==0x01) {
    WritePrivateProfileString("GRAPH_Y","ORP_Top",Label2->Caption.c_str(),szFileName);
    WritePrivateProfileString("GRAPH_Y","ORP_Bottom",Label3->Caption.c_str(),szFileName);
  } else if (iDataCode==0x02) {
    WritePrivateProfileString("GRAPH_Y","HCL_Top",Label2->Caption.c_str(),szFileName);
    WritePrivateProfileString("GRAPH_Y","HCL_Bottom",Label3->Caption.c_str(),szFileName);
  } else if (iDataCode==0x03) {
    WritePrivateProfileString("GRAPH_Y","SG_Top",Label2->Caption.c_str(),szFileName);
    WritePrivateProfileString("GRAPH_Y","SG_Bottom",Label3->Caption.c_str(),szFileName);
  } else if (iDataCode==0x04) {
    WritePrivateProfileString("GRAPH_Y","TEMP_Top",Label2->Caption.c_str(),szFileName);
    WritePrivateProfileString("GRAPH_Y","TEMP_Bottom",Label3->Caption.c_str(),szFileName);
  }
  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Graph_Y_Axis::WCImageButton4Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 40;
  frm_Calculator->Left = this->Left + this->Width + 10;;
  frm_Calculator->Label1->Caption = Label2->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label2->Caption = frm_Calculator->szValue;
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_Graph_Y_Axis::WCImageButton5Click(TObject *Sender)
{
  frm_Calculator->Top = this->Top + 40;
  frm_Calculator->Left = this->Left + this->Width + 10;;
  frm_Calculator->Label1->Caption = Label3->Caption;
  if (frm_Calculator->ShowModal()==mrOk) {   //
    Label3->Caption = frm_Calculator->szValue;
  }
}
//---------------------------------------------------------------------------
