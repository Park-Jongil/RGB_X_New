//---------------------------------------------------------------------------
#include <stdio.h>
#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "frmDataAnalysis.h"
#include "frmGraphUsage.h"
#include "frmGraphExcel.h"
#include "TypeConversion.h"
#include "frmGraphPopup.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_GraphPopup *frm_GraphPopup;
//---------------------------------------------------------------------------
__fastcall Tfrm_GraphPopup::Tfrm_GraphPopup(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphPopup::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphPopup::FormShow(TObject *Sender)
{
  this->AlphaBlend = true;
  this->AlphaBlendValue = 200;
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphPopup::Image1DblClick(TObject *Sender)
{
  Close();  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_GraphPopup::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  int   iMenu1_Px[] = {125,190,130,  0,125,0};    // PARAMATER
  int   iMenu1_Py[] = {  0,110,214,214,  0,0};
  int   iMenu2_Px[] = {125,375,310,190,125,0};    // COMPENSATION
  int   iMenu2_Py[] = {  0,  0,110,110,  0,0};
  int   iMenu3_Px[] = {375,500,370,310,375,0};    // CONTROL
  int   iMenu3_Py[] = {  0,215,215,110,  0,0};
  int   iMenu4_Px[] = {190,310,375,125,190,0};    // Home
  int   iMenu4_Py[] = {320,320,430,430,320,0};
  int   iRet;
  char  szBuffer[1024];

  sprintf(szBuffer,"X=%d , Y=%d",X,Y);
//  Label1->Caption = szBuffer;
  iRet = PointInPolygon(X,Y,iMenu1_Px,iMenu1_Py,4);
  if (iRet==true) frm_GraphUsage->ShowModal();
  iRet = PointInPolygon(X,Y,iMenu2_Px,iMenu2_Py,4);
  if (iRet==true) frm_DataAnalysis->ShowModal();
  iRet = PointInPolygon(X,Y,iMenu3_Px,iMenu3_Py,4);
  if (iRet==true) frm_GraphExcel->ShowModal();
  iRet = PointInPolygon(X,Y,iMenu4_Px,iMenu4_Py,4);
  if (iRet==true) Close();
}
//---------------------------------------------------------------------------

