//---------------------------------------------------------------------------
#include <stdio.h>
#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "TypeConversion.h"
#include "frmSettingParameter.h"
#include "frmSettingCompensation.h"
#include "frmSettingControl.h"
#include "frmSettingSensorChange.h"
#include "frmSettingMaster.h"
#include "frmSettingPopup.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_SettingPopup *frm_SettingPopup;
//---------------------------------------------------------------------------
__fastcall Tfrm_SettingPopup::Tfrm_SettingPopup(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingPopup::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingPopup::FormShow(TObject *Sender)
{
  this->AlphaBlend = true;
  this->AlphaBlendValue = 200;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingPopup::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  int   iMenu1_Px[] = {125,190,130,  0,125,0};    // USAGE
  int   iMenu1_Py[] = {  0,110,214,214,  0,0};
  int   iMenu2_Px[] = {125,375,310,190,125,0};    // Data Analysis
  int   iMenu2_Py[] = {  0,  0,110,110,  0,0};
  int   iMenu3_Px[] = {375,500,370,310,375,0};    // Excel
  int   iMenu3_Py[] = {  0,215,215,110,  0,0};
  int   iMenu4_Px[] = {190,310,375,125,190,0};    // Home
  int   iMenu4_Py[] = {320,320,430,430,320,0};
  int   iMenu5_Px[] = {  0,130,190,125,  0,0};    // Sensor Change
  int   iMenu5_Py[] = {215,215,320,430,215,0};
  int   iMenu6_Px[] = {370,500,370,310,370,0};    // Master
  int   iMenu6_Py[] = {215,215,430,320,215,0};
  int   iRet;
  char  szBuffer[1024];

  sprintf(szBuffer,"X=%d , Y=%d",X,Y);
//  Label1->Caption = szBuffer;
  iRet = PointInPolygon(X,Y,iMenu1_Px,iMenu1_Py,4);
  if (iRet==true) frm_SettingParameter->ShowModal();
  iRet = PointInPolygon(X,Y,iMenu2_Px,iMenu2_Py,4);
  if (iRet==true) frm_SettingCompensation->ShowModal();
  iRet = PointInPolygon(X,Y,iMenu3_Px,iMenu3_Py,4);
  if (iRet==true) frm_SettingControl->ShowModal();
  iRet = PointInPolygon(X,Y,iMenu4_Px,iMenu4_Py,4);
  if (iRet==true) Close();
  iRet = PointInPolygon(X,Y,iMenu5_Px,iMenu5_Py,4);
  if (iRet==true) frm_SettingSensorChange->ShowModal();
  iRet = PointInPolygon(X,Y,iMenu6_Px,iMenu6_Py,4);
  if (iRet==true) frm_SettingMaster->ShowModal();
}
//---------------------------------------------------------------------------
