//---------------------------------------------------------------------------
#include <stdio.h>
#include <dos.h>
#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "TypeConversion.h"
#include "DatabaseFunction.h"
#include "frmEventLog.h"
#include "frmDebugWindow.h"
#include "frmChangeMode_Confirm.h"
#include "frmSettingRange.h"
#include "frmAlarmWindow.h"
#include "frmGraphMenu.h"
#include "frmSettingMenu.h"
#include "frmCompanyTitle.h"
#include "frmPasswordLogin.h"
#include "frmGraphPopup.h"
#include "frmSettingPopup.h"
#include "frmRGB_X_Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma link "VrAnimate"
#pragma link "VrControls"
#pragma link "VrDesign"
#pragma link "VrSystem"
#pragma link "CPort"
#pragma resource "*.dfm"
Tfrm_RGB_X_Main *frm_RGB_X_Main;
//---------------------------------------------------------------------------
DeviceConfig        stDeviceConfig;
DeviceStatistics    stDeviceStat;
//---------------------------------------------------------------------------
__fastcall Tfrm_RGB_X_Main::Tfrm_RGB_X_Main(TComponent* Owner)
  : TForm(Owner)
{
  memset((char*)&stDeviceStat,0x00,sizeof(DeviceStatistics));
  for(int i=0;i<GRAPH_MAX_BUFFER;i++) {
    stDeviceConfig.Graph_RGB[i] = 0;
    stDeviceConfig.Graph_ORP[i] = 0;
    stDeviceConfig.Graph_HCL[i] = 0;
    stDeviceConfig.Graph_SG[i] = 0;
    stDeviceConfig.Graph_TEMP[i] = 0;
  }
  strcpy(stDeviceConfig.szChangeCheckDate,"");
  iAutoMode = 0x01;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::WCImageButton1Click(TObject *Sender)
{
  Close();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::DeviceClient_Config_Load()
{
  char        szFileName[1024],szServerAddr[1024],szBuffer[1024];
  TDateTime   CheckDate;
  int         iServerPort,iServerUsed;
  short int   iYear,iMonth,iDay;

  strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
  strcat(szFileName,"Config.ini");
// Config File Load
  try {
    GetPrivateProfileString("RGB_X","ServerAddr","127.0.0.1",szServerAddr,1024,szFileName);
    iServerPort = GetPrivateProfileInt("RGB_X","ServerPort",9797,szFileName);
    iServerUsed = GetPrivateProfileInt("RGB_X","ServerUsed",0,szFileName);
  } catch(...) {
  }
  try {
    stDeviceConfig.RGB_Top = GetPrivateProfileInt("RGB_X","RGB_Top",1000,szFileName);
    stDeviceConfig.RGB_Bottom = GetPrivateProfileInt("RGB_X","RGB_Bottom",20,szFileName);
    stDeviceConfig.ORP_Top = GetPrivateProfileInt("RGB_X","ORP_Top",600,szFileName);
    stDeviceConfig.ORP_Bottom = GetPrivateProfileInt("RGB_X","ORP_Bottom",450,szFileName);
    stDeviceConfig.HCL_Top = GetPrivateProfileInt("RGB_X","HCL_Top",120,szFileName);
    stDeviceConfig.HCL_Bottom = GetPrivateProfileInt("RGB_X","HCL_Bottom",40,szFileName);
    stDeviceConfig.SG_Top = GetPrivateProfileInt("RGB_X","SG_Top",1440,szFileName);
    stDeviceConfig.SG_Bottom = GetPrivateProfileInt("RGB_X","SG_Bottom",1280,szFileName);
    stDeviceConfig.TEMP_Top = GetPrivateProfileInt("RGB_X","TEMP_Top",550,szFileName);
    stDeviceConfig.TEMP_Bottom = GetPrivateProfileInt("RGB_X","TEMP_Bottom",450,szFileName);
// GraphUsage 에서 사용량을 관리할 변수들
    GetPrivateProfileString("GRAPG_USAGE","HCL_Capa" ,"8.0",szBuffer,1024,szFileName);
    stDeviceConfig.HCL_Capa  = atof(szBuffer);
    GetPrivateProfileString("GRAPG_USAGE","HCL_Daily","0.0",szBuffer,1024,szFileName);
    stDeviceConfig.HCL_Daily  = atof(szBuffer);
    GetPrivateProfileString("GRAPG_USAGE","HCL_Total","0.0",szBuffer,1024,szFileName);
    stDeviceConfig.HCL_Total  = atof(szBuffer);
    GetPrivateProfileString("GRAPG_USAGE","OXI_Capa" ,"8.0",szBuffer,1024,szFileName);
    stDeviceConfig.OXI_Capa  = atof(szBuffer);
    GetPrivateProfileString("GRAPG_USAGE","OXI_Daily","0.0",szBuffer,1024,szFileName);
    stDeviceConfig.OXI_Daily  = atof(szBuffer);
    GetPrivateProfileString("GRAPG_USAGE","OXI_Total","0.0",szBuffer,1024,szFileName);
    stDeviceConfig.OXI_Total  = atof(szBuffer);
    GetPrivateProfileString("GRAPG_USAGE","H2O_Capa" ,"8.0",szBuffer,1024,szFileName);
    stDeviceConfig.H2O_Capa  = atof(szBuffer);
    GetPrivateProfileString("GRAPG_USAGE","H2O_Daily","0.0",szBuffer,1024,szFileName);
    stDeviceConfig.H2O_Daily  = atof(szBuffer);
    GetPrivateProfileString("GRAPG_USAGE","H2O_Total","0.0",szBuffer,1024,szFileName);
    stDeviceConfig.H2O_Total  = atof(szBuffer);
// Setting_Control 에서의 설정값
    stDeviceConfig.Control_SubHCL1    = GetPrivateProfileInt("CONTROL","SubHCL1",0,szFileName);
    stDeviceConfig.Control_SubHCL2    = GetPrivateProfileInt("CONTROL","SubHCL2",0,szFileName);
// Setting_SensorChange 에서의 설정값
    stDeviceConfig.ORP_Count = GetPrivateProfileInt("SENSOR_CHANGE","ORP_Count",0,szFileName);
    GetPrivateProfileString("SENSOR_CHANGE","CHANGEDATE_RGB","",stDeviceConfig.szChangeDate_RGB,1024,szFileName);
    GetPrivateProfileString("SENSOR_CHANGE","CHANGEDATE_ORP","",stDeviceConfig.szChangeDate_ORP,1024,szFileName);
    GetPrivateProfileString("SENSOR_CHANGE","CHANGEDATE_HCL","",stDeviceConfig.szChangeDate_HCL,1024,szFileName);
    GetPrivateProfileString("SENSOR_CHANGE","CHANGEDATE_SG" ,"",stDeviceConfig.szChangeDate_SG ,1024,szFileName);
    if (strlen(stDeviceConfig.szChangeDate_ORP) > 8 && stDeviceConfig.ORP_Count > 0) {
      iYear = atoi(stDeviceConfig.szChangeDate_ORP);
      iMonth = atoi(&stDeviceConfig.szChangeDate_ORP[5]);
      iDay = atoi(&stDeviceConfig.szChangeDate_ORP[8]);
      CheckDate = EncodeDate(iYear,iMonth,iDay);
      CheckDate = CheckDate + stDeviceConfig.ORP_Count;
      strcpy(stDeviceConfig.szChangeCheckDate,CheckDate.FormatString("yyyy-mm-dd").c_str());
    }
// Setting_Master 에서의 설정값
    stDeviceConfig.isMasterPassword    = GetPrivateProfileInt("MASTER","isPawword",0,szFileName);
    GetPrivateProfileString("MASTER","PASSWORD" ,"0",stDeviceConfig.szMasterPassword ,1024,szFileName);
  } catch(...) {
  }
// Server Setting
  try {
    ComPort1->Connected = false;
    ComPort1->LoadSettings( stIniFile , "RGB_X_New.ini");
    ComPort1->Connected = true;
  } catch(...) {
  }
  try {
    if (iServerUsed==0x01) {
      ClientSocket1->Active = false;
      ClientSocket1->Address = szServerAddr;
      ClientSocket1->Port = iServerPort;
      ClientSocket1->Active = true;
    }
  } catch(...) {
  }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::FormShow(TObject *Sender)
{
  char  szSendData[32] = { 0x00, };

  DataBase_LocalDB_Initialize();
  DeviceClient_Config_Load();
  Device_Mode_Change();
//  frm_DebugWindow->Show();
  Make_SendMessage(CMD_STATUS_DATA,0x01,szSendData);     // Request Device Status
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::FormClose(TObject *Sender,TCloseAction &Action)
{
  char      szFileName[1024];
  int       iServerPort;

  DataBase_LocalDB_Finitialize();
  strcpy(szFileName,ExtractFilePath(Application->ExeName).c_str());
  strcat(szFileName,"Config.ini");
// Config File Load
  try {
    WritePrivateProfileString("GRAPG_USAGE","HCL_Capa" ,FloatToStr(stDeviceConfig.HCL_Capa).c_str(),szFileName);
    WritePrivateProfileString("GRAPG_USAGE","HCL_Daily",FloatToStr(stDeviceConfig.HCL_Daily).c_str(),szFileName);
    WritePrivateProfileString("GRAPG_USAGE","HCL_Total",FloatToStr(stDeviceConfig.HCL_Total).c_str(),szFileName);
    WritePrivateProfileString("GRAPG_USAGE","OXI_Capa" ,FloatToStr(stDeviceConfig.OXI_Capa).c_str(),szFileName);
    WritePrivateProfileString("GRAPG_USAGE","OXI_Daily",FloatToStr(stDeviceConfig.OXI_Daily).c_str(),szFileName);
    WritePrivateProfileString("GRAPG_USAGE","OXI_Total",FloatToStr(stDeviceConfig.OXI_Total).c_str(),szFileName);
    WritePrivateProfileString("GRAPG_USAGE","H2O_Capa" ,FloatToStr(stDeviceConfig.H2O_Capa).c_str(),szFileName);
    WritePrivateProfileString("GRAPG_USAGE","H2O_Daily",FloatToStr(stDeviceConfig.H2O_Daily).c_str(),szFileName);
    WritePrivateProfileString("GRAPG_USAGE","H2O_Total",FloatToStr(stDeviceConfig.H2O_Total).c_str(),szFileName);
  } catch(...) {
  }

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::Timer1Timer(TObject *Sender)
{
  struct  date d;
  struct  time t_Cur;
  int     iTimeIndex;
  static struct  time t_Pre;
  TDateTime   CurDate;
  char        szCheckDate[32];

  Label1->Caption = Now().FormatString("yyyy-mm-dd hh:nn:ss");
  strcpy(szCheckDate,Now().FormatString("yyyy-mm-dd").c_str());
//
  getdate(&d);
  gettime(&t_Cur);
  if (t_Cur.ti_sec < t_Pre.ti_sec) {  // 분이 바뀌었을때  , 현재상태를 기준으로 DB에 저장
    iTimeIndex = t_Cur.ti_hour * 60 + t_Cur.ti_min;
    DataBase_SensorData_Insert(d.da_year,szCheckDate,iTimeIndex,&stDeviceStat);
    memset((char*)&stDeviceStat,0x00,sizeof(DeviceStatistics));
  }
  if (t_Cur.ti_hour < t_Pre.ti_hour) {  // 날자가  바뀌었을때 GrapgUsage 의 Daily 변수를 초기화
    CurDate = Now() - 1;
    strcpy(szCheckDate,CurDate.FormatString("yyyy-mm-dd").c_str());
    DataBase_GraphUsage_Insert(szCheckDate,stDeviceConfig.HCL_Daily,stDeviceConfig.OXI_Daily,stDeviceConfig.H2O_Daily);
    stDeviceConfig.HCL_Daily = 0;
    stDeviceConfig.OXI_Daily = 0;
    stDeviceConfig.H2O_Daily = 0;
  } 
  t_Pre = t_Cur;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::FormCreate(TObject *Sender)
{
  pBufImage = new TImage(this);
  pBufImage->Width  = PaintBox1->Width;
  pBufImage->Height = PaintBox1->Height;
  pBufImage->Canvas->Brush->Color = clBlack;
  pBufImage->Canvas->FillRect(Rect(0,0,PaintBox1->Width,PaintBox1->Height));
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::WaveDisplay_BasicSetting(TImage *pBufImg,int iSeq,double UCL,double LCL,double SET,double Top,double Bottom)
{
  int   iHeight,iWidth,i,iPx,iPy,iPosition,iSetPos,iMoveMark;
  char  szBuf[1024];

  iWidth  = PaintBox1->Width;
  iHeight = PaintBox1->Height;
  pBufImg->Canvas->Brush->Color = clBlack;
  pBufImg->Canvas->FillRect(Rect(0,0,iWidth,iHeight));
  try {
    iSetPos = iHeight - (((SET-Bottom) * iHeight) / (double)(Top-Bottom));
  } catch(...) {
    iSetPos = iHeight;
  }

  try {
    pBufImg->Canvas->Pen->Color = clGray;
    pBufImg->Canvas->Pen->Style =  psDot;
    for(i=0;i<5;i++) {
      iPosition = 0 + (iHeight-1) * i / 5.0;
      pBufImg->Canvas->MoveTo(0,iPosition);
      pBufImg->Canvas->LineTo(iWidth-1,iPosition);
    }
  } catch(...) {
  }
  try {
    pBufImg->Canvas->Pen->Color = clGray;
    pBufImg->Canvas->Pen->Style = psDot;
    for(i=0;i<20;i++) {
      iPosition = iWidth * (i / 20.0);
      pBufImg->Canvas->MoveTo(iPosition,0);
      pBufImg->Canvas->LineTo(iPosition,iHeight);
//      sprintf(szBuf,"%02d",i);
//      pBufImg->Canvas->TextOutA(iPosition+1,1,szBuf);
    }
  } catch(...) {
  }



  pBufImg->Canvas->Pen->Style = psSolid;
// RGB Graph Set Basis on Set Position
  if (iSeq==0x01) {
    pBufImg->Canvas->Pen->Color = clLime;
    for(i=0;i<iWidth;i++) {
      if (stDeviceConfig.Graph_RGB[i] != 0) {
        iPosition = iHeight - (((stDeviceConfig.Graph_RGB[i]-Bottom) * iHeight) / (double)(Top-Bottom));
        pBufImg->Canvas->MoveTo(i,iSetPos);
        pBufImg->Canvas->LineTo(i,iPosition);
      }
    }
  }
// ORP Graph Set Basis on Set Position
  if (iSeq==0x02) {
    pBufImg->Canvas->Pen->Color = clLime;
    for(i=0;i<iWidth;i++) {
      if (stDeviceConfig.Graph_ORP[i] != 0) {
        iPosition = iHeight - (((stDeviceConfig.Graph_ORP[i]-Bottom) * iHeight) / (double)(Top-Bottom));
        pBufImg->Canvas->MoveTo(i,iSetPos);
        pBufImg->Canvas->LineTo(i,iPosition);
      }
    }
  }
// HCL Graph Set Basis on Set Position
  if (iSeq==0x03) {
    pBufImg->Canvas->Pen->Color = clRed;
    for(i=0;i<iWidth;i++) {
      if (stDeviceConfig.Graph_HCL[i] != 0) {
        iPosition = iHeight - ((((stDeviceConfig.Graph_HCL[i]/100.0)-Bottom) * iHeight) / (double)(Top-Bottom));
        pBufImg->Canvas->MoveTo(i,iSetPos);
        pBufImg->Canvas->LineTo(i,iPosition);
      }
    }
  }
// SG Graph Set Basis on Set Position
  if (iSeq==0x04) {
    pBufImg->Canvas->Pen->Color = clAqua;
    for(i=0;i<iWidth;i++) {
      if (stDeviceConfig.Graph_SG[i] != 0) {
        iPosition = iHeight - ((((stDeviceConfig.Graph_SG[i]/1000.0)-Bottom) * iHeight) / (double)(Top-Bottom));
        pBufImg->Canvas->MoveTo(i,iSetPos);
        pBufImg->Canvas->LineTo(i,iPosition);
      }
    }
  }
// TEMP Graph Set Basis on Set Position
  if (iSeq==0x05) {
    iMoveMark = 0;
    pBufImg->Canvas->Pen->Color = clRed;
    for(i=0;i<iWidth;i++) {
      if (stDeviceConfig.Graph_TEMP[i] != 0) {
        iPosition = iHeight - ((((stDeviceConfig.Graph_TEMP[i]/10.0)-Bottom) * iHeight) / (double)(Top-Bottom));
        if (iMoveMark==0x00) {
          pBufImg->Canvas->MoveTo(i,iPosition);
          iMoveMark = 0x01;
        } else {
          pBufImg->Canvas->LineTo(i,iPosition);
        }
//        pBufImg->Canvas->MoveTo(i,iSetPos);
//        pBufImg->Canvas->LineTo(i,iPosition);
      } else {
        iMoveMark = 0;
      }
    }
  }

  pBufImg->Canvas->Font->Color = clYellow;
// UCL Line Draw
  try {
    iPosition = iHeight - (((UCL-Bottom) * iHeight) / (double)(Top-Bottom));
    pBufImg->Canvas->Pen->Color = clRed;
    pBufImg->Canvas->Pen->Style = psSolid;
    pBufImg->Canvas->MoveTo(0,iPosition);
    pBufImg->Canvas->LineTo(iWidth-1,iPosition);
    if (iSeq==0x01 || iSeq==0x02) sprintf(szBuf,"UCL=%4d",(int)UCL);
    if (iSeq==0x03) sprintf(szBuf,"UCL=%5.2f",UCL);
    if (iSeq==0x04) sprintf(szBuf,"UCL=%5.3f",UCL);
    if (iSeq==0x05) sprintf(szBuf,"UCL=%5.1f",UCL);
    pBufImg->Canvas->TextOutA(5,iPosition+1,szBuf);
  } catch(...) {
  }
// LCL Line Draw
  try {
    iPosition = (iHeight-1) - (((LCL-Bottom) * iHeight) / (double)(Top-Bottom));
    pBufImg->Canvas->Pen->Color = clGreen;
    pBufImg->Canvas->Pen->Style = psSolid;
    pBufImg->Canvas->MoveTo(0,iPosition);
    pBufImg->Canvas->LineTo(iWidth-1,iPosition);
    if (iSeq==0x01 || iSeq==0x02) sprintf(szBuf,"LCL=%4d",(int)LCL);
    if (iSeq==0x03) sprintf(szBuf,"LCL=%5.2f",LCL);
    if (iSeq==0x04) sprintf(szBuf,"LCL=%5.3f",LCL);
    if (iSeq==0x05) sprintf(szBuf,"LCL=%5.1f",LCL);
    pBufImg->Canvas->TextOutA(5,iPosition-14,szBuf);
  } catch(...) {
  }
// SET Line Draw
  try {
    iSetPos = iHeight - (((SET-Bottom) * iHeight) / (double)(Top-Bottom));
    pBufImg->Canvas->Pen->Color = clYellow;
    pBufImg->Canvas->Pen->Style = psSolid;
    pBufImg->Canvas->MoveTo(0,iSetPos);
    pBufImg->Canvas->LineTo(iWidth-1,iSetPos);
    if (iSeq==0x01 || iSeq==0x02) sprintf(szBuf,"SET=%4d",(int)SET);
    if (iSeq==0x03) sprintf(szBuf,"SET=%5.2f",SET);
    if (iSeq==0x04) sprintf(szBuf,"SET=%5.3f",SET);
    if (iSeq!=0x05) pBufImg->Canvas->TextOutA(5,iSetPos+1,szBuf);
  } catch(...) {
  }

  try {
    pBufImg->Canvas->Pen->Color = clGray;
    pBufImg->Canvas->Pen->Style =  psDot;
    for(i=0;i<6;i++) {
      iPosition = 0 + (iHeight-1) * i / 5.0;
      if (iSeq==0x01 || iSeq==0x02) sprintf(szBuf,"%4d",(int)(Bottom+((5-i)*(Top-Bottom)/5.0)));
      if (iSeq==0x03) sprintf(szBuf,"%5.2f",(Bottom+((5-i)*(Top-Bottom)/5.0)));
      if (iSeq==0x04) sprintf(szBuf,"%5.3f",(Bottom+((5-i)*(Top-Bottom)/5.0)));
      if (iSeq==0x05) sprintf(szBuf,"%5.1f",(Bottom+((5-i)*(Top-Bottom)/5.0)));
      pBufImg->Canvas->TextOutA(iWidth-30,iPosition-14,szBuf);
    }
  } catch(...) {
  }

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::PaintBox1Paint(TObject *Sender)
{
// RGB Graph 설정부분
  WaveDisplay_BasicSetting(pBufImage,0x01,stDeviceConfig.CurStatus.RGB_UCL,stDeviceConfig.CurStatus.RGB_LCL,stDeviceConfig.CurStatus.RGB_SET,stDeviceConfig.RGB_Top,stDeviceConfig.RGB_Bottom);
  BitBlt(PaintBox1->Canvas->Handle,0,0,PaintBox1->Width,PaintBox1->Height,pBufImage->Canvas->Handle,0,0,SRCCOPY);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::PaintBox2Paint(TObject *Sender)
{
// ORP Graph 설정부분
  WaveDisplay_BasicSetting(pBufImage,0x02,stDeviceConfig.CurStatus.ORP_UCL,stDeviceConfig.CurStatus.ORP_LCL,stDeviceConfig.CurStatus.ORP_SET,stDeviceConfig.ORP_Top,stDeviceConfig.ORP_Bottom);
  BitBlt(PaintBox2->Canvas->Handle,0,0,PaintBox2->Width,PaintBox2->Height,pBufImage->Canvas->Handle,0,0,SRCCOPY);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::PaintBox3Paint(TObject *Sender)
{
// HCL Graph 설정부분
  WaveDisplay_BasicSetting(pBufImage,0x03,stDeviceConfig.CurStatus.HCL_UCL/100.0,stDeviceConfig.CurStatus.HCL_LCL/100.0,stDeviceConfig.CurStatus.HCL_SET/100.0,stDeviceConfig.HCL_Top/100.0,stDeviceConfig.HCL_Bottom/100.0);
  BitBlt(PaintBox3->Canvas->Handle,0,0,PaintBox3->Width,PaintBox3->Height,pBufImage->Canvas->Handle,0,0,SRCCOPY);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::PaintBox4Paint(TObject *Sender)
{
// SG Graph 설정부분
  WaveDisplay_BasicSetting(pBufImage,0x04,stDeviceConfig.CurStatus.SG_UCL/1000.0,stDeviceConfig.CurStatus.SG_LCL/1000.0,stDeviceConfig.CurStatus.SG_SET/1000.0,stDeviceConfig.SG_Top/1000.0,stDeviceConfig.SG_Bottom/1000.0);
  BitBlt(PaintBox4->Canvas->Handle,0,0,PaintBox4->Width,PaintBox4->Height,pBufImage->Canvas->Handle,0,0,SRCCOPY);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::PaintBox5Paint(TObject *Sender)
{
// TEMP Graph 설정부분
  WaveDisplay_BasicSetting(pBufImage,0x05,stDeviceConfig.CurStatus.TEMP_UCL/10.0,stDeviceConfig.CurStatus.TEMP_LCL/10.0,50.0,stDeviceConfig.TEMP_Top/10.0,stDeviceConfig.TEMP_Bottom/10.0);
  BitBlt(PaintBox5->Canvas->Handle,0,0,PaintBox5->Width,PaintBox5->Height,pBufImage->Canvas->Handle,0,0,SRCCOPY);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::GraphTimerTimer(TObject *Sender)
{
  if (stDeviceConfig.CurSensor.ModePump.bit8.RGB_ORP==0x01) {
    if (stDeviceConfig.CurSensor.ModePump.bit8.OXI_PUMP==0x01) {
      VrBitmapImage1->BitmapIndex = (VrBitmapImage1->BitmapIndex+1) % 10;
      VrBitmapImage1->Visible = true;
      VrBitmapImage2->Visible = false;
    } else if (stDeviceConfig.CurSensor.ModePump.bit8.OXI_PUMP==0x00) {
      VrBitmapImage1->Visible = true;
      VrBitmapImage2->Visible = false;
    }
  } else if (stDeviceConfig.CurSensor.ModePump.bit8.RGB_ORP==0x00) {
    if (stDeviceConfig.CurSensor.ModePump.bit8.OXI_PUMP==0x01) {
      VrBitmapImage1->Visible = false;
      VrBitmapImage2->Visible = true;
      VrBitmapImage2->BitmapIndex = (VrBitmapImage2->BitmapIndex+1) % 10;
    } else if (stDeviceConfig.CurSensor.ModePump.bit8.OXI_PUMP==0x00) {
      VrBitmapImage1->Visible = false;
      VrBitmapImage2->Visible = true;
    }
  }
  if (stDeviceConfig.CurSensor.ModePump.bit8.HCL_PUMP==0x01) {
    VrBitmapImage3->BitmapIndex = (VrBitmapImage3->BitmapIndex+1) % 10;
  } else if (stDeviceConfig.CurSensor.ModePump.bit8.HCL_PUMP==0x00) {
  }
  if (stDeviceConfig.CurSensor.ModePump.bit8.H2O_PUMP==0x01) {
    VrBitmapImage4->BitmapIndex = (VrBitmapImage4->BitmapIndex+1) % 10;
  } else if (stDeviceConfig.CurSensor.ModePump.bit8.H2O_PUMP==0x00) {
  }
  if (stDeviceConfig.CurSensor.Alarm2.bit8.CIRCURATING_PUMP==0x00) {
    VrBitmapImage5->BitmapIndex = (VrBitmapImage5->BitmapIndex+1) % 10;
  } else if (stDeviceConfig.CurSensor.Alarm2.bit8.CIRCURATING_PUMP==0x01) {
  }
}


//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::CommRxTimerTimer(TObject *Sender)
{
  CommRxTimer->Enabled = false;
  CommunicationStatus_SetImage(0x00,0x02);
}


//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::CommTxTimerTimer(TObject *Sender)
{
  CommTxTimer->Enabled = false;
  CommunicationStatus_SetImage(0x01,0x00);
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::ComPort1RxChar(TObject *Sender, int Count)
{
  unsigned char  szBuffer[1024];

  CommRxTimer->Enabled = false;
  CommunicationStatus_SetImage(0x00,0x03);
  CommRxTimer->Enabled = true;
  memset(szBuffer,0x00,sizeof(szBuffer));
  ComPort1->Read(szBuffer,Count);
  Protocol_Check_Verification(szBuffer,Count);
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::ClientSocket1Read(TObject *Sender,
      TCustomWinSocket *Socket)
{
  int   iCount;
  char  szBuffer[1024];

  CommRxTimer->Enabled = false;
  CommunicationStatus_SetImage(0x00,0x03);
  CommRxTimer->Enabled = true;
  iCount = Socket->ReceiveBuf( szBuffer , 1024 );
  if (iCount == -1) return;
  Protocol_Check_Verification(szBuffer,iCount);
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::ClientSocket1Connect(TObject *Sender,
      TCustomWinSocket *Socket)
{
  char  szSendData[32] = { 0x00, };
  Make_SendMessage(CMD_STATUS_DATA,0x01,szSendData);     // Request Device Status
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::ClientSocket1Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
  ErrorCode = 0;
}

//---------------------------------------------------------------------------
unsigned char __fastcall Tfrm_RGB_X_Main::Make_CheckSum(unsigned char *szMsgBuf,int iCount)
{
  unsigned char   CheckSum = 0x00;

  for(int i=0;i<iCount;i++) CheckSum += szMsgBuf[i];
  return(CheckSum);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::SendMessage_ToDevice(char *Data,int length)
{
  if (frm_DebugWindow->Visible==true) frm_DebugWindow->Display_DebugMessage(0x01,Data,length);
  CommTxTimer->Enabled = false;
  CommunicationStatus_SetImage(0x01,0x01);
  CommTxTimer->Enabled = true;
  if (ComPort1->Connected==true) ComPort1->Write(Data,length);
  if (ClientSocket1->Active==true) {
    ClientSocket1->Socket->SendBuf(Data,length);
  }
}


//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::Make_SendMessage(int Command,int DataSize,char *stData)
{
  RequestPacket   stSendMsg;

  stSendMsg.Header = 0x05;
  stSendMsg.SiteID = 0x00;
  stSendMsg.DeviceID = 0x00;
  stSendMsg.Command = Command;
  stSendMsg.DataSize = DataSize;
  if (DataSize > 0) memcpy((char*)&stSendMsg.Data,stData,DataSize);
  stSendMsg.Data[DataSize] = 0x00;
  stSendMsg.Data[DataSize+1] = 0x03;      // ETX
  stSendMsg.Data[DataSize+2] = Make_CheckSum((char*)&stSendMsg,DataSize+7);
  SendMessage_ToDevice((char*)&stSendMsg,DataSize+8);
}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::Protocol_Check_Verification(char *szBuffer,int iCount)
{
  int     i,iLength;
  RequestPacket       *pChkPnt;

  if (iRecvCount==0x00) {
    memset(szRecvBuf,0x00,sizeof(szRecvBuf));
  }
  memcpy((char*)&szRecvBuf[iRecvCount],szBuffer,iCount);
  iRecvCount = iRecvCount + iCount;
  do {
    if (iRecvCount >= 0x08) {   // 명령의 최소크기
      pChkPnt = (RequestPacket*)&szRecvBuf[0];
      if (iRecvCount >= (pChkPnt->DataSize+8)) {
        if (pChkPnt->Header==0x06) {      // ACK 라면..(정상적인 메세지)
          if (pChkPnt->Command==0x00) Protocol_Receive_SensorData(pChkPnt);
          if (pChkPnt->Command==0x01) Protocol_Receive_StatusData(pChkPnt);
  /*
        if (pChkPnt->Command==0x02) Protocol_Receive_RGB_WLED(pChkPnt);
        if (pChkPnt->Command==0x03) Protocol_Receive_SensorShift(pChkPnt);
        if (pChkPnt->Command==0x04) Protocol_Receive_OnOff_Time(pChkPnt);
        if (pChkPnt->Command==0x05) Protocol_Receive_UCL_Set_LCL(pChkPnt);
        if (pChkPnt->Command==0x06) Protocol_Receive_ControlMode(pChkPnt);
  */
          if (frm_DebugWindow->Visible==true) frm_DebugWindow->Display_DebugMessage(0x00,szRecvBuf,pChkPnt->DataSize+8);
          iRecvCount = iRecvCount - (pChkPnt->DataSize+8);
          if (iRecvCount > 0) memcpy(szRecvBuf,&szRecvBuf[pChkPnt->DataSize+8],iRecvCount);
           else iRecvCount = 0;
        } else if (pChkPnt->Header==0x15) {      // NACK 라면..(비정상적인 메세지)
          if (pChkPnt->Command==0x00) Protocol_Receive_NACK(pChkPnt);
          if (pChkPnt->Command==0x01) Protocol_Receive_NACK(pChkPnt);
          if (pChkPnt->Command==0x02) Protocol_Receive_NACK(pChkPnt);
          if (pChkPnt->Command==0x03) Protocol_Receive_NACK(pChkPnt);
          if (pChkPnt->Command==0x04) Protocol_Receive_NACK(pChkPnt);
          if (pChkPnt->Command==0x05) Protocol_Receive_NACK(pChkPnt);
          if (pChkPnt->Command==0x06) Protocol_Receive_NACK(pChkPnt);
          if (frm_DebugWindow->Visible==true) frm_DebugWindow->Display_DebugMessage(0x00,szRecvBuf,pChkPnt->DataSize+8);
          iRecvCount = iRecvCount - (pChkPnt->DataSize+8);
          if (iRecvCount > 0) memcpy(szRecvBuf,&szRecvBuf[pChkPnt->DataSize+8],iRecvCount);
           else iRecvCount = 0;
        } else {
          iRecvCount = iRecvCount - 1;
          if (iRecvCount > 0) memcpy(szRecvBuf,&szRecvBuf[1],iRecvCount);
        }
      }
      if (iRecvCount < (pChkPnt->DataSize+8)) return;
    } else {
      return;
    }
  } while(true);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::Protocol_Receive_NACK(RequestPacket *pChkPnt)
{
  short int   iErrorCode;
  char  szBuffer[1024];

  if (pChkPnt != NULL) {
    iErrorCode = pChkPnt->Data[0];
    sprintf(szBuffer,"ErrorCode = %02X",iErrorCode);
  }
}

//---------------------------------------------------------------------------
// Communication Tx / Rx
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::CommunicationStatus_SetImage(int iSelect,int iMode)
{
  Graphics::TBitmap *BlankScr1 = new Graphics::TBitmap();

  ImageList2->GetBitmap(iMode,BlankScr1);
  if (iSelect==0x00) WCImageButton14->Picture_Normal->Bitmap->Assign(BlankScr1);
  if (iSelect==0x01) WCImageButton1->Picture_Normal->Bitmap->Assign(BlankScr1);
  delete BlankScr1;
  WCImageButton14->Refresh();
  WCImageButton1->Refresh();
}

//---------------------------------------------------------------------------
// Auto_Manual Mode
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::Device_Mode_Change()
{
  Graphics::TBitmap *BlankScr1 = new Graphics::TBitmap();
  Graphics::TBitmap *BlankScr2 = new Graphics::TBitmap();

  if (iAutoMode==0x00) {
    ImageList1->GetBitmap(0x01,BlankScr1);
    ImageList1->GetBitmap(0x02,BlankScr2);
  } else if (iAutoMode==0x01) {
    ImageList1->GetBitmap(0x00,BlankScr1);
    ImageList1->GetBitmap(0x03,BlankScr2);
  }
  WCImageButton5->Picture_Normal->Bitmap->Assign(BlankScr1);
  WCImageButton6->Picture_Normal->Bitmap->Assign(BlankScr2);
  delete BlankScr1;
  delete BlankScr2;
  WCImageButton5->Refresh();
  WCImageButton6->Refresh();
}

//---------------------------------------------------------------------------
// 센서데이터 요청 (Cmd:0x00 , DataSize:0x01)
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::Protocol_Receive_SensorData(RequestPacket *pChkPnt)
{
  SensorData  *pChkData;
  char        szBuffer[1024],szCheckDate[64];

  if (pChkPnt != NULL) {
    pChkData = (SensorData*)&pChkPnt->Data[0];
    TypeConversion(pChkData);
    memcpy((char*)&stDeviceConfig.CurSensor , (char*)pChkData , sizeof(SensorData));
    Label2->Caption = IntToStr(pChkData->FQ_G);
    Label3->Caption = IntToStr(pChkData->ORP);
    sprintf(szBuffer,"%4.2f",pChkData->HCL/100.0);
    Label4->Caption = szBuffer;
    sprintf(szBuffer,"%5.3f",pChkData->SG/1000.0);
    Label5->Caption = szBuffer;
    sprintf(szBuffer,"%4.1f",pChkData->LQ_TEMP/10.0);
    Label6->Caption = szBuffer;
// HCL 에 추가적으로 표시되는 항목
    if (stDeviceConfig.Control_SubHCL1==0x01) {
      sprintf(szBuffer,"%5.2f g/L",(pChkData->HCL/100.0)*36.5);
      Label7->Caption = szBuffer;
      Label7->Visible = true;
    } else if (stDeviceConfig.Control_SubHCL2==0x01) {
      sprintf(szBuffer,"%5.2f %",(pChkData->HCL/100.0)*36.5/10.0/1.380);
      Label7->Caption = szBuffer;
      Label7->Visible = true;
    } else {
      Label7->Visible = false;
    }
    LogMessage_Printf("R=%4d , G=%4d , B=%4d , ORP=%4d , HCL=%5.2f , SG=%5.3f , Temp=%4.1f",pChkData->FQ_R,pChkData->FQ_G,pChkData->FQ_B,pChkData->ORP,pChkData->HCL/100.0,pChkData->SG/1000.0,pChkData->LQ_TEMP/10.0);

// RGB Data Graph Setting
    memcpy((char*)&stDeviceConfig.Graph_RGB[0],(char*)&stDeviceConfig.Graph_RGB[1],sizeof(short int)*(GRAPH_MAX_BUFFER-1));
    stDeviceConfig.Graph_RGB[GRAPH_MAX_BUFFER-1] = pChkData->FQ_G;
// ORP Data Graph Setting
    memcpy((char*)&stDeviceConfig.Graph_ORP[0],(char*)&stDeviceConfig.Graph_ORP[1],sizeof(short int)*(GRAPH_MAX_BUFFER-1));
    stDeviceConfig.Graph_ORP[GRAPH_MAX_BUFFER-1] = pChkData->ORP;
// HCL Data Graph Setting
    memcpy((char*)&stDeviceConfig.Graph_HCL[0],(char*)&stDeviceConfig.Graph_HCL[1],sizeof(short int)*(GRAPH_MAX_BUFFER-1));
    stDeviceConfig.Graph_HCL[GRAPH_MAX_BUFFER-1] = pChkData->HCL;
// SG Data Graph Setting
    memcpy((char*)&stDeviceConfig.Graph_SG[0],(char*)&stDeviceConfig.Graph_SG[1],sizeof(short int)*(GRAPH_MAX_BUFFER-1));
    stDeviceConfig.Graph_SG[GRAPH_MAX_BUFFER-1] = pChkData->SG;
// TEMP Data Graph Setting
    memcpy((char*)&stDeviceConfig.Graph_TEMP[0],(char*)&stDeviceConfig.Graph_TEMP[1],sizeof(short int)*(GRAPH_MAX_BUFFER-1));
    stDeviceConfig.Graph_TEMP[GRAPH_MAX_BUFFER-1] = pChkData->LQ_TEMP;
// Alarm Check
    Protocol_AlarmTable_Process();

// DB에 저장을 하기위해서 들어오는 데이터를 합산한다.(1분 단위로 DB에 저장하면서 초기화한다.)
    stDeviceStat.iStatCount = stDeviceStat.iStatCount + 1;
    stDeviceStat.avg_RGB = stDeviceStat.avg_RGB + pChkData->FQ_G;
    stDeviceStat.avg_ORP = stDeviceStat.avg_ORP + pChkData->ORP;
    stDeviceStat.avg_HCL = stDeviceStat.avg_HCL + (pChkData->HCL/100.0);
    stDeviceStat.avg_SG  = stDeviceStat.avg_SG  + (pChkData->SG/1000.0);
    stDeviceStat.avg_TEMP = stDeviceStat.avg_TEMP + (pChkData->LQ_TEMP/10.0);
    stDeviceStat.AutoMode = iAutoMode;
    PaintBox1Paint(NULL);
    PaintBox2Paint(NULL);
    PaintBox3Paint(NULL);
    PaintBox4Paint(NULL);
    PaintBox5Paint(NULL);
    memcpy((char*)&stDeviceConfig.PrevSensor , (char*)&stDeviceConfig.CurSensor , sizeof(SensorData));
// Mode Pump Data
    if (iAutoMode != pChkData->ModePump.bit8.AUTO_MANUAL) {
      iAutoMode = pChkData->ModePump.bit8.AUTO_MANUAL != 0x00 ? 1 : 0;
      Device_Mode_Change();
    }
  }
}

//---------------------------------------------------------------------------
// 장비상태데이터 요청 (Cmd:0x00 , DataSize:0x01)
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::Protocol_Receive_StatusData(RequestPacket *pChkPnt)
{
  StatusData  *pChkData;
  char        szBuffer[1024];

  if (pChkPnt != NULL) {
    pChkData = (StatusData*)&pChkPnt->Data[0];
    TypeConversion(pChkData);
    memcpy((char*)&stDeviceConfig.CurStatus , (char*)pChkData , sizeof(StatusData));
    stDeviceConfig.CurSensor.ModePump.Value = stDeviceConfig.CurStatus.ModePump.Value;
    stDeviceConfig.CurSensor.Alarm1.Value = stDeviceConfig.CurStatus.Alarm1.Value;
    stDeviceConfig.CurSensor.Alarm2.Value = stDeviceConfig.CurStatus.Alarm2.Value;
    Protocol_AlarmTable_Process();
  }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::Protocol_AlarmTable_Process()
{
  char        szBuffer[1024],szCheckDate[64];

// Alarm DataBase Store
  try {
    if (stDeviceConfig.CurSensor.Alarm1.Value!= 0x00 || stDeviceConfig.CurSensor.Alarm2.Value&0x03) {
      frm_AlarmWindow->Alarm1.Value = stDeviceConfig.CurSensor.Alarm1.Value;
      frm_AlarmWindow->Alarm2.Value = stDeviceConfig.CurSensor.Alarm2.Value;
      frm_AlarmWindow->AlarmWindow_StatusUpdate();
      if (frm_AlarmWindow->Visible==false) frm_AlarmWindow->Show();
      frm_AlarmWindow->BringToFront();
    } else {
      if (frm_AlarmWindow->Visible==true) frm_AlarmWindow->Close();
    }
    strcpy(szCheckDate,Now().FormatString("yyyy-mm-dd hh:nn:ss").c_str());
    if (stDeviceConfig.CurSensor.Alarm1.bit8.RGB_UCL_Alarm==0x01) {
      if (stDeviceConfig.PrevSensor.Alarm1.bit8.RGB_UCL_Alarm==0x00) DataBase_EventLog_Insert(szCheckDate,0x01);
    }
    if (stDeviceConfig.CurSensor.Alarm1.bit8.RGB_LCL_Alarm==0x01) {
      if (stDeviceConfig.PrevSensor.Alarm1.bit8.RGB_LCL_Alarm==0x00) DataBase_EventLog_Insert(szCheckDate,0x02);
    }
    if (stDeviceConfig.CurSensor.Alarm1.bit8.ORP_UCL_Alarm==0x01) {
      if (stDeviceConfig.PrevSensor.Alarm1.bit8.ORP_UCL_Alarm==0x00) DataBase_EventLog_Insert(szCheckDate,0x03);
    }
    if (stDeviceConfig.CurSensor.Alarm1.bit8.ORP_LCL_Alarm==0x01) {
      if (stDeviceConfig.PrevSensor.Alarm1.bit8.ORP_LCL_Alarm==0x00) DataBase_EventLog_Insert(szCheckDate,0x04);
    }
    if (stDeviceConfig.CurSensor.Alarm1.bit8.HCL_UCL_Alarm==0x01) {
      if (stDeviceConfig.PrevSensor.Alarm1.bit8.HCL_UCL_Alarm==0x00) DataBase_EventLog_Insert(szCheckDate,0x05);
    }
    if (stDeviceConfig.CurSensor.Alarm1.bit8.HCL_LCL_Alarm==0x01) {
      if (stDeviceConfig.PrevSensor.Alarm1.bit8.HCL_LCL_Alarm==0x00) DataBase_EventLog_Insert(szCheckDate,0x06);
    }
    if (stDeviceConfig.CurSensor.Alarm1.bit8.SG_UCL_Alarm==0x01) {
      if (stDeviceConfig.PrevSensor.Alarm1.bit8.SG_UCL_Alarm==0x00) DataBase_EventLog_Insert(szCheckDate,0x07);
    }
    if (stDeviceConfig.CurSensor.Alarm1.bit8.SG_LCL_Alarm==0x01) {
      if (stDeviceConfig.PrevSensor.Alarm1.bit8.SG_LCL_Alarm==0x00) DataBase_EventLog_Insert(szCheckDate,0x08);
    }
    if (stDeviceConfig.CurSensor.Alarm2.bit8.TEMP_UCL_Alarm==0x01) {
      if (stDeviceConfig.PrevSensor.Alarm2.bit8.TEMP_UCL_Alarm==0x00) DataBase_EventLog_Insert(szCheckDate,0x09);
    }
    if (stDeviceConfig.CurSensor.Alarm2.bit8.TEMP_LCL_Alarm==0x01) {
      if (stDeviceConfig.PrevSensor.Alarm2.bit8.TEMP_LCL_Alarm==0x00) DataBase_EventLog_Insert(szCheckDate,0x0A);
    }
    stDeviceStat.OXI_Pump = stDeviceStat.OXI_Pump + stDeviceConfig.CurSensor.ModePump.bit8.OXI_PUMP;
    stDeviceStat.HCL_Pump = stDeviceStat.HCL_Pump + stDeviceConfig.CurSensor.ModePump.bit8.HCL_PUMP;
    stDeviceStat.H2O_Pump = stDeviceStat.H2O_Pump + stDeviceConfig.CurSensor.ModePump.bit8.H2O_PUMP;
    stDeviceStat.CircurPump = stDeviceStat.CircurPump + stDeviceConfig.CurSensor.Alarm2.bit8.CIRCURATING_PUMP;
//  GraphUsage 에서 사용량을 관리할 변수들
    if (stDeviceConfig.CurSensor.ModePump.bit8.HCL_PUMP==0x01) {
      stDeviceConfig.HCL_Daily += stDeviceConfig.HCL_Capa / 60.0;
      stDeviceConfig.HCL_Total += stDeviceConfig.HCL_Capa / 60.0;
    }
    if (stDeviceConfig.CurSensor.ModePump.bit8.OXI_PUMP==0x01) {
      stDeviceConfig.OXI_Daily += stDeviceConfig.OXI_Capa / 60.0;
      stDeviceConfig.OXI_Total += stDeviceConfig.OXI_Capa / 60.0;
    }
    if (stDeviceConfig.CurSensor.ModePump.bit8.H2O_PUMP==0x01) {
      stDeviceConfig.H2O_Daily += stDeviceConfig.H2O_Capa / 60.0;
      stDeviceConfig.H2O_Total += stDeviceConfig.H2O_Capa / 60.0;
    }
  } catch(...) {
  }
}



//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::Timer_SensorDataTimer(TObject *Sender)
{
  static int  iToggleSwitch = 0x00;
  char  szSendData[32] = { 0x00, };

  if (iToggleSwitch==0x00) {
    Make_SendMessage(CMD_SENSOR_DATA,0x01,szSendData);     // Request Sensor Status
  } else {
    Make_SendMessage(CMD_STATUS_DATA,0x01,szSendData);     // Request Device Status
  }
  iToggleSwitch = !iToggleSwitch;
}


//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::WCImageButton3Click(TObject *Sender)
{
//  frm_GraphMenu->Left = this->Left + 450;
//  frm_GraphMenu->Top  = this->Top + 150;
//  frm_GraphMenu->ShowModal();
  frm_GraphPopup->Left = this->Left + 470;
  frm_GraphPopup->Top  = this->Top + 200;
  frm_GraphPopup->ShowModal();
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::WCImageButton2Click(TObject *Sender)
{
  if (stDeviceConfig.isMasterPassword==0x01) {
    if (frm_PasswordLogin->ShowModal()!=mrOk) return;
  }
//  frm_SettingMenu->Left = this->Left + 210;
//  frm_SettingMenu->Top  = this->Top + 150;
//  frm_SettingMenu->ShowModal();
  frm_SettingPopup->Left = this->Left + 470;
  frm_SettingPopup->Top  = this->Top + 200;
  frm_SettingPopup->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::WCImageButton5Click(TObject *Sender)
{
  U_Control       ModePump;
  char  szSendData[32] = { 0x00, };

  if (iAutoMode==0x01) {    // 현재 오토모드일 경우에 변경확인 메세지를 뿌린다.
    if (frm_ChangeMode_Confirm->ShowModal()==mrOk) {   // 설정메세지 클릭시
      ModePump.Value = stDeviceConfig.CurSensor.ModePump.Value;
      ModePump.bit8.AUTO_MANUAL = 0x00;
      szSendData[0] = ModePump.Value;
      Make_SendMessage(CMD_MODE_N_PUMP,0x01,szSendData);     // Request Device Status
      Device_Mode_Change();
    }
  }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::WCImageButton6Click(TObject *Sender)
{
  U_Control       ModePump;
  char  szSendData[32] = { 0x00, };

  if (iAutoMode==0x00) {    // 현재 오토모드일 경우에 변경확인 메세지를 뿌린다.
    if (frm_ChangeMode_Confirm->ShowModal()==mrOk) {   // 설정메세지 클릭시
      ModePump.Value = stDeviceConfig.CurSensor.ModePump.Value;
      ModePump.bit8.AUTO_MANUAL = 0x01;
      szSendData[0] = ModePump.Value;
      Make_SendMessage(CMD_MODE_N_PUMP,0x01,szSendData);     // Request Device Status
      Device_Mode_Change();
    }
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::WCImageButton7Click(TObject *Sender)
{
  frm_SettingRange->iDataCode = 0x01;
  strcpy(frm_SettingRange->szDataName,"R G B");
  frm_SettingRange->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::WCImageButton8Click(TObject *Sender)
{
  frm_SettingRange->iDataCode = 0x02;
  strcpy(frm_SettingRange->szDataName,"O R P");
  frm_SettingRange->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::WCImageButton9Click(TObject *Sender)
{
  frm_SettingRange->iDataCode = 0x03;
  strcpy(frm_SettingRange->szDataName,"H C L");
  frm_SettingRange->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::WCImageButton10Click(TObject *Sender)
{
  frm_SettingRange->iDataCode = 0x04;
  strcpy(frm_SettingRange->szDataName,"S . G");
  frm_SettingRange->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::WCImageButton11Click(TObject *Sender)
{
  frm_SettingRange->iDataCode = 0x05;
  strcpy(frm_SettingRange->szDataName,"TEMP");
  frm_SettingRange->ShowModal();
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::VrBitmapImage1Click(TObject *Sender)
{
  U_Control       ModePump;
  char  szSendData[32] = { 0x00, };
  if (iAutoMode==0x00) {  // MANUAL 모드일때만 동작
    ModePump.Value = stDeviceConfig.CurSensor.ModePump.Value;
    ModePump.bit8.OXI_PUMP = !ModePump.bit8.OXI_PUMP;
    szSendData[0] = ModePump.Value;
    Make_SendMessage(CMD_MODE_N_PUMP,0x01,szSendData);     // Request Device Status
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::VrBitmapImage3Click(TObject *Sender)
{
  U_Control       ModePump;
  char  szSendData[32] = { 0x00, };
  if (iAutoMode==0x00) {  // MANUAL 모드일때만 동작
    ModePump.Value = stDeviceConfig.CurSensor.ModePump.Value;
    ModePump.bit8.HCL_PUMP = !ModePump.bit8.HCL_PUMP;
    szSendData[0] = ModePump.Value;
    Make_SendMessage(CMD_MODE_N_PUMP,0x01,szSendData);     // Request Device Status
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::VrBitmapImage4Click(TObject *Sender)
{
  U_Control       ModePump;
  char  szSendData[32] = { 0x00, };
  if (iAutoMode==0x00) {  // MANUAL 모드일때만 동작
    ModePump.Value = stDeviceConfig.CurSensor.ModePump.Value;
    ModePump.bit8.H2O_PUMP = !ModePump.bit8.H2O_PUMP;
    szSendData[0] = ModePump.Value;
    Make_SendMessage(CMD_MODE_N_PUMP,0x01,szSendData);     // Request Device Status
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_RGB_X_Main::WCImageButton4Click(TObject *Sender)
{
  frm_EventLog->ShowModal();  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::WCImageButton13Click(TObject *Sender)
{
  frm_CompanyTitle->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_RGB_X_Main::Action1Execute(TObject *Sender)
{
  frm_DebugWindow->Show();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Log Window Function
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void Tfrm_RGB_X_Main::LogMessage_Printf(const char *pFormat, ...)
{
  FILE      *fp;
  va_list   argptr;
  int       i , iCount , iValue;
  char      szCurPath[1024],szDateTime[1024],szFileName[1024];
  char      pStrBuff[4096] , szMsgBuf[4096];;

  strcpy(szCurPath,ExtractFilePath(Application->ExeName).c_str());
  strcpy(szDateTime,Now().FormatString("yyyymmdd").c_str());
  sprintf(szFileName,"%s\\LogMessage\\Log(%s).txt",szCurPath,szDateTime);

  if (!DirectoryExists(ExtractFileDir(szFileName))) ForceDirectories(ExtractFileDir(szFileName));
  fp = fopen(szFileName,"a+t");
  if (fp != NULL) {
    strcpy(szDateTime,Now().FormatString("hh:nn:ss").c_str());
    va_start(argptr, pFormat);
    vsprintf(pStrBuff, pFormat, argptr);
    va_end(argptr);
    fprintf(fp,"[%s] %s\n",szDateTime,pStrBuff);
  }
  fclose(fp);
}



