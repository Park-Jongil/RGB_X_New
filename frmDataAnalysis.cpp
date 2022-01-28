//---------------------------------------------------------------------------
#include <stdio.h>
#include <dos.h>
#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "DatabaseFunction.h"
#include "frmGraph_Y_Axis.h"
#include "frmRGB_X_Main.h"
#include "frmDataAnalysis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma resource "*.dfm"
Tfrm_DataAnalysis *frm_DataAnalysis;
//---------------------------------------------------------------------------
extern  DeviceConfig        stDeviceConfig;
//---------------------------------------------------------------------------
extern  DeviceStatistics    stSensorData[1440];   // 통계데이터를 위한 변수
//---------------------------------------------------------------------------
TShape  *DrawClip = new TShape(frm_DataAnalysis);    // 박스를 그릴때 표
//---------------------------------------------------------------------------
__fastcall Tfrm_DataAnalysis::Tfrm_DataAnalysis(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::FormCreate(TObject *Sender)
{
  pBufImage = new TImage(this);
  pBufImage->Width  = PaintBox1->Width;
  pBufImage->Height = PaintBox1->Height;
  pBufImage->Canvas->Brush->Color = clBlack;
  pBufImage->Canvas->FillRect(Rect(0,0,PaintBox1->Width,PaintBox1->Height));
  pBarImage = new TImage(this);
  pBarImage->Width  = PaintBox2->Width;
  pBarImage->Height = PaintBox2->Height;
  pBarImage->Canvas->Brush->Color = clBlack;
  pBarImage->Canvas->FillRect(Rect(0,0,PaintBox2->Width,PaintBox2->Height));
  DateTimePicker1->Date = Now();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::FormShow(TObject *Sender)
{
// 클립 초기화
  DrawClip->Visible         = false;
  DrawClip->Parent          = this;
// 점선 효과
  DrawClip->Pen->Style      = psDot;
  DrawClip->Pen->Color      = clYellow;
  DrawClip->Brush->Style    = bsClear;
  isZoomMode = 0;
  DateTimePicker1Change(NULL);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::WCImageButton6Click(TObject *Sender)
{
  Close();  
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::WaveDisplay_BasicSetting(TImage *pBufImg,int iSeq,double UCL,double LCL,double SET,double Top,double Bottom)
{
  int     iHeight,iWidth,i,iPx,iPy,iPosition,iSetPos,iMoveMark,iPrePx;
  int     iPos_UCL,iPos_SET,iPos_LCL;
  double  iCurData;
  char    szBuf[1024];

  iWidth  = PaintBox1->Width;
  iHeight = PaintBox1->Height;
  pBufImg->Canvas->Brush->Color = clBlack;
  pBufImg->Canvas->FillRect(Rect(0,0,iWidth,iHeight));
  try {
    iPos_UCL = iHeight - (((UCL-Bottom) * iHeight) / (double)(Top-Bottom));
    iPos_LCL = (iHeight-1) - (((LCL-Bottom) * iHeight) / (double)(Top-Bottom));
    iPos_SET = iHeight - (((SET-Bottom) * iHeight) / (double)(Top-Bottom));
    pBufImg->Canvas->Pen->Color = clGray;
    pBufImg->Canvas->Pen->Style =  psDot;
    for(i=0;i<10;i++) {
//      iPosition = iPos_LCL + (iPos_UCL-iPos_LCL) * i / 9.0;
      iPosition = 0 + (iHeight-1) * i / 9.0;
      pBufImg->Canvas->MoveTo(0,iPosition);
      pBufImg->Canvas->LineTo(iWidth-1,iPosition);
      if (iSeq==0x00 || iSeq==0x01) sprintf(szBuf,"%4d",(int)(Bottom+((10-i)*(Top-Bottom)/10.0)));
      if (iSeq==0x02) sprintf(szBuf,"%5.2f",(Bottom+((10-i)*(Top-Bottom)/10.0)));
      if (iSeq==0x03) sprintf(szBuf,"%5.3f",(Bottom+((10-i)*(Top-Bottom)/10.0)));
      if (iSeq==0x04) sprintf(szBuf,"%5.1f",(Bottom+((10-i)*(Top-Bottom)/10.0)));
      pBufImg->Canvas->TextOutA(iWidth-30,iPosition-14,szBuf);
    }
  } catch(...) {
  }
  try {
    pBufImg->Canvas->Pen->Color = clGray;
    pBufImg->Canvas->Pen->Style = psDot;
    for(i=0;i<24;i++) {
      iPosition = iWidth * (i / 24.0);
      pBufImg->Canvas->MoveTo(iPosition,0);
      pBufImg->Canvas->LineTo(iPosition,iHeight);
      sprintf(szBuf,"%02d",i);
      pBufImg->Canvas->TextOutA(iPosition+1,1,szBuf);
    }
  } catch(...) {
  }

// RGB Graph Set Basis on Set Position
  pBufImg->Canvas->Pen->Style = psSolid;
  if (iSeq==0x00) pBufImg->Canvas->Pen->Color = clLime;
  if (iSeq==0x01) pBufImg->Canvas->Pen->Color = clLime;
  if (iSeq==0x02) pBufImg->Canvas->Pen->Color = clRed;
  if (iSeq==0x03) pBufImg->Canvas->Pen->Color = clAqua;
  if (iSeq==0x04) pBufImg->Canvas->Pen->Color = clRed;
  iPrePx = 0;
  iMoveMark = 0;
  for(i=0;i<1440;i++) {
    if (iSeq==0x00) iCurData = stSensorData[i].avg_RGB;
    if (iSeq==0x01) iCurData = stSensorData[i].avg_ORP;
    if (iSeq==0x02) iCurData = stSensorData[i].avg_HCL;
    if (iSeq==0x03) iCurData = stSensorData[i].avg_SG;
    if (iSeq==0x04) iCurData = stSensorData[i].avg_TEMP;
    if (iCurData != 0) {
      iPx = (double)(i * iWidth) / 1440.0;
      iPy = iHeight - (((iCurData-Bottom) * iHeight) / (double)(Top-Bottom));
      if (iMoveMark==0x00) {
        pBufImg->Canvas->MoveTo(iPx,iPy);
        iMoveMark = 0x01;
      } else {
//        if (iPrePx != iPx) {
          pBufImg->Canvas->LineTo(iPx,iPy);
//        }
        iPrePx = iPx;
      }
    } else {
      iMoveMark = 0;
    }
  }
// UCL Line Draw
  pBufImg->Canvas->Font->Color = clYellow;
  try {
    pBufImg->Canvas->Pen->Color = clRed;
    pBufImg->Canvas->Pen->Style = psSolid;
    pBufImg->Canvas->MoveTo(0,iPos_UCL);
    pBufImg->Canvas->LineTo(iWidth-1,iPos_UCL);
    if (iSeq==0x00 || iSeq==0x01) sprintf(szBuf,"UCL=%4d",(int)UCL);
    if (iSeq==0x02) sprintf(szBuf,"UCL=%5.2f",UCL);
    if (iSeq==0x03) sprintf(szBuf,"UCL=%5.3f",UCL);
    if (iSeq==0x04) sprintf(szBuf,"UCL=%5.1f",UCL);
    pBufImg->Canvas->TextOutA(5,iPos_UCL+1,szBuf);
  } catch(...) {
  }
// LCL Line Draw
  try {
    pBufImg->Canvas->Pen->Color = clGreen;
    pBufImg->Canvas->Pen->Style = psSolid;
    pBufImg->Canvas->MoveTo(0,iPos_LCL);
    pBufImg->Canvas->LineTo(iWidth-1,iPos_LCL);
    if (iSeq==0x00 || iSeq==0x01) sprintf(szBuf,"LCL=%4d",(int)LCL);
    if (iSeq==0x02) sprintf(szBuf,"LCL=%5.2f",LCL);
    if (iSeq==0x03) sprintf(szBuf,"LCL=%5.3f",LCL);
    if (iSeq==0x04) sprintf(szBuf,"LCL=%5.1f",LCL);
    pBufImg->Canvas->TextOutA(5,iPos_LCL-14,szBuf);
  } catch(...) {
  }
// SET Line Draw
  if (iSeq!=0x04) {
    try {
      pBufImg->Canvas->Pen->Color = clYellow;
      pBufImg->Canvas->Pen->Style = psSolid;
      pBufImg->Canvas->MoveTo(0,iPos_SET);
      pBufImg->Canvas->LineTo(iWidth-1,iPos_SET);
      if (iSeq==0x00 || iSeq==0x01) sprintf(szBuf,"SET=%4d",(int)SET);
      if (iSeq==0x02) sprintf(szBuf,"SET=%5.2f",SET);
      if (iSeq==0x03) sprintf(szBuf,"SET=%5.3f",SET);
      if (iSeq!=0x04) pBufImg->Canvas->TextOutA(5,iPos_SET+1,szBuf);
    } catch(...) {
    }
  }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::BarChart_BasicSetting(TImage *pBufImg,int iDataType)
{
  int     iHeight,iWidth,iPx,iPy,i,iCurData;
  char    szBuf[1024];

  iWidth  = PaintBox2->Width;
  iHeight = PaintBox2->Height;
  pBarImage->Canvas->Brush->Color = clBlack;
  pBarImage->Canvas->FillRect(Rect(0,0,iWidth,iHeight));
  pBarImage->Canvas->Pen->Style = psSolid;
  if (iDataType==0x01) pBarImage->Canvas->Pen->Color = clGreen;
  if (iDataType==0x02) pBarImage->Canvas->Pen->Color = clRed;
  if (iDataType==0x03) pBarImage->Canvas->Pen->Color = clBlue;
  if (iDataType==0x04) pBarImage->Canvas->Pen->Color = clRed;
  if (iDataType==0x05) pBarImage->Canvas->Pen->Color = clRed;
  for(i=0;i<1440;i++) {
    if (iDataType==0x01) iCurData = stSensorData[i].OXI_Pump;
    if (iDataType==0x02) iCurData = stSensorData[i].HCL_Pump;
    if (iDataType==0x03) iCurData = stSensorData[i].H2O_Pump;
    if (iDataType==0x04) iCurData = stSensorData[i].AutoMode;
    if (iDataType==0x05) iCurData = stSensorData[i].CircurPump;
    if (iCurData != 0) {
      iPx = (i * iWidth) / 1440.0;
      if (0x01<=iDataType && iDataType<=0x03) {
        if (iCurData==0x00) iPy = iHeight;
         else if ( 1 <= iCurData && iCurData <= 20) iPy = iHeight/2;
         else if (21 <= iCurData && iCurData <= 60) iPy = 0;
      } else if (iDataType==0x04) {
        iPy = (iCurData==0x00) ? iHeight : 0;
      } else if (iDataType==0x05) {
/*        if (iCurData==0x00) iPy = 0;
         else if ( 1 <= iCurData && iCurData <= 20) iPy = iHeight/2;
         else if (21 <= iCurData && iCurData <= 60) iPy = iHeight;
*/
        iPy = (1-(iCurData/60.0)) * iHeight;
      }
      pBarImage->Canvas->MoveTo(iPx,iHeight);
      pBarImage->Canvas->LineTo(iPx,iPy);
    }
  }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::PaintBox1Paint(TObject *Sender)
{
  int     iDataType;
  char    szFileName[1024],szBuffer[1024];
  double  Graph_Top,Graph_Bottom;

  iDataType = ComboBox1->ItemIndex;
  strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
  strcat(szFileName,"Config.ini");
  try {
    if (iDataType==0x00) {
      GetPrivateProfileString("GRAPH_Y","RGB_Top" ,"1000",szBuffer,1024,szFileName);
      Graph_Top    = atof(szBuffer);
      GetPrivateProfileString("GRAPH_Y","RGB_Bottom" ,"0",szBuffer,1024,szFileName);
      Graph_Bottom = atof(szBuffer);
    } else if (iDataType==0x01) {
      GetPrivateProfileString("GRAPH_Y","ORP_Top" ,"600",szBuffer,1024,szFileName);
      Graph_Top    = atof(szBuffer);
      GetPrivateProfileString("GRAPH_Y","ORP_Bottom" ,"450",szBuffer,1024,szFileName);
      Graph_Bottom = atof(szBuffer);
    } else if (iDataType==0x02) {
      GetPrivateProfileString("GRAPH_Y","HCL_Top" ,"1.2",szBuffer,1024,szFileName);
      Graph_Top    = atof(szBuffer);
      GetPrivateProfileString("GRAPH_Y","HCL_Bottom" ,"0.4",szBuffer,1024,szFileName);
      Graph_Bottom = atof(szBuffer);
    } else if (iDataType==0x03) {
      GetPrivateProfileString("GRAPH_Y","SG_Top" ,"1.4",szBuffer,1024,szFileName);
      Graph_Top    = atof(szBuffer);
      GetPrivateProfileString("GRAPH_Y","SG_Bottom" ,"1.28",szBuffer,1024,szFileName);
      Graph_Bottom = atof(szBuffer);
    } else if (iDataType==0x04) {
      GetPrivateProfileString("GRAPH_Y","TEMP_Top" ,"55.0",szBuffer,1024,szFileName);
      Graph_Top    = atof(szBuffer);
      GetPrivateProfileString("GRAPH_Y","TEMP_Bottom" ,"45.0",szBuffer,1024,szFileName);
      Graph_Bottom = atof(szBuffer);
    }
  } catch(...) {
  }

  if (iDataType==0x00) {
    WaveDisplay_BasicSetting(pBufImage,iDataType,stDeviceConfig.CurStatus.RGB_UCL,stDeviceConfig.CurStatus.RGB_LCL,stDeviceConfig.CurStatus.RGB_SET,Graph_Top,Graph_Bottom);
  } else if (iDataType==0x01) {
    WaveDisplay_BasicSetting(pBufImage,iDataType,stDeviceConfig.CurStatus.ORP_UCL,stDeviceConfig.CurStatus.ORP_LCL,stDeviceConfig.CurStatus.ORP_SET,Graph_Top,Graph_Bottom);
  } else if (iDataType==0x02) {
    WaveDisplay_BasicSetting(pBufImage,iDataType,stDeviceConfig.CurStatus.HCL_UCL/100.0,stDeviceConfig.CurStatus.HCL_LCL/100.0,stDeviceConfig.CurStatus.HCL_SET/100.0,Graph_Top,Graph_Bottom);
  } else if (iDataType==0x03) {
    WaveDisplay_BasicSetting(pBufImage,iDataType,stDeviceConfig.CurStatus.SG_UCL/1000.0,stDeviceConfig.CurStatus.SG_LCL/1000.0,stDeviceConfig.CurStatus.SG_SET/1000.0,Graph_Top,Graph_Bottom);
  } else if (iDataType==0x04) {
    WaveDisplay_BasicSetting(pBufImage,iDataType,stDeviceConfig.CurStatus.TEMP_UCL/10.0,stDeviceConfig.CurStatus.TEMP_LCL/10.0,stDeviceConfig.CurStatus.TEMP_LCL/10.0,Graph_Top,Graph_Bottom);
  }
  if (isZoomMode==0x00) {
    BitBlt(PaintBox1->Canvas->Handle,0,0,PaintBox1->Width,PaintBox1->Height,pBufImage->Canvas->Handle,0,0,SRCCOPY);
  } else {
    StretchBlt(PaintBox1->Canvas->Handle,0,0,PaintBox1->Width,PaintBox1->Height,pBufImage->Canvas->Handle,iSx,iSy,(iEx-iSx),(iEy-iSy),SRCCOPY);
  }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::PaintBox2Paint(TObject *Sender)
{
  BarChart_BasicSetting(pBarImage,0x01);
  BitBlt(PaintBox2->Canvas->Handle,0,0,PaintBox2->Width,PaintBox2->Height,pBarImage->Canvas->Handle,0,0,SRCCOPY);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::PaintBox3Paint(TObject *Sender)
{
  BarChart_BasicSetting(pBarImage,0x02);
  BitBlt(PaintBox3->Canvas->Handle,0,0,PaintBox3->Width,PaintBox3->Height,pBarImage->Canvas->Handle,0,0,SRCCOPY);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::PaintBox4Paint(TObject *Sender)
{
  BarChart_BasicSetting(pBarImage,0x03);
  BitBlt(PaintBox4->Canvas->Handle,0,0,PaintBox4->Width,PaintBox4->Height,pBarImage->Canvas->Handle,0,0,SRCCOPY);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::PaintBox5Paint(TObject *Sender)
{
  BarChart_BasicSetting(pBarImage,0x04);
  BitBlt(PaintBox5->Canvas->Handle,0,0,PaintBox5->Width,PaintBox5->Height,pBarImage->Canvas->Handle,0,0,SRCCOPY);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::PaintBox6Paint(TObject *Sender)
{
  BarChart_BasicSetting(pBarImage,0x05);
  BitBlt(PaintBox6->Canvas->Handle,0,0,PaintBox6->Width,PaintBox6->Height,pBarImage->Canvas->Handle,0,0,SRCCOPY);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::DateTimePicker1Change(TObject *Sender)
{
  int   iResult,iYear;
  char  szCheckDate[64],szTemp[128];

  strcpy(szCheckDate,DateTimePicker1->Date.FormatString("yyyy-mm-dd").c_str());
  iYear = StrToInt(DateTimePicker1->Date.FormatString("yyyy"));
  iResult = DataBase_SensorData_Search_byDateTime(iYear,szCheckDate);
  PaintBox1Paint(NULL);
  PaintBox2Paint(NULL);
  PaintBox3Paint(NULL);
  PaintBox4Paint(NULL);
  PaintBox5Paint(NULL);
  PaintBox6Paint(NULL);
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::ComboBox1Change(TObject *Sender)
{
  PaintBox1Paint(NULL);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::WCImageButton1Click(TObject *Sender)
{
  frm_Graph_Y_Axis->iDataCode = ComboBox1->ItemIndex;
  strcpy(frm_Graph_Y_Axis->szDataName,ComboBox1->Text.c_str());
  frm_Graph_Y_Axis->ShowModal();
  PaintBox1Paint(NULL);
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_DataAnalysis::PaintBox1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (isZoomMode==0x00) {
    iSx = X;
    iSy = Y;
    DrawClip->Left    = X + PaintBox1->Left;
    DrawClip->Top     = Y + PaintBox1->Top;
    DrawClip->Width   = 0;
    DrawClip->Height  = 0;
    DrawClip->Visible = true;
  } else {
    isZoomMode = 0x00;
  }
  PaintBox1Paint(NULL);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_DataAnalysis::PaintBox1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if(DrawClip->Visible) {
    DrawClip->Visible = false;
    iEx = X;
    iEy = Y;
    isZoomMode = 0x01;
  } else {
    iSx = iSy = 0;
    iEx = iEy = 0;
    isZoomMode = 0x00;
  }
  PaintBox1Paint(NULL);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_DataAnalysis::PaintBox1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  if(DrawClip->Visible) {
    DrawClip->Width  = X - (DrawClip->Left - PaintBox1->Left);
    DrawClip->Height = Y - (DrawClip->Top - PaintBox1->Top);
  }
}
//---------------------------------------------------------------------------

