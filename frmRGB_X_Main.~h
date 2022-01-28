//---------------------------------------------------------------------------

#ifndef frmRGB_X_MainH
#define frmRGB_X_MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WCImageButton.hpp"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
#include "VrAnimate.hpp"
#include "VrControls.hpp"
#include "VrDesign.hpp"
#include "VrSystem.hpp"
#include "CPort.hpp"
#include <ScktComp.hpp>
#include <ImgList.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class Tfrm_RGB_X_Main : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TWCImageButton *WCImageButton1;
  TWCImageButton *WCImageButton2;
  TWCImageButton *WCImageButton3;
  TWCImageButton *WCImageButton4;
  TWCImageButton *WCImageButton5;
  TWCImageButton *WCImageButton6;
  TWCImageButton *WCImageButton7;
  TWCImageButton *WCImageButton8;
  TWCImageButton *WCImageButton9;
  TWCImageButton *WCImageButton10;
  TWCImageButton *WCImageButton11;
  TLabel *Label1;
  TTimer *Timer1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TPaintBox *PaintBox1;
  TPaintBox *PaintBox2;
  TPaintBox *PaintBox3;
  TPaintBox *PaintBox4;
  TPaintBox *PaintBox5;
  TVrBitmapImage *VrBitmapImage1;
  TVrBitmapList *VrBitmapList1;
  TTimer *GraphTimer;
  TVrBitmapImage *VrBitmapImage2;
  TVrBitmapImage *VrBitmapImage3;
  TVrBitmapImage *VrBitmapImage4;
  TVrBitmapImage *VrBitmapImage5;
  TWCImageButton *WCImageButton12;
  TComPort *ComPort1;
  TTimer *Timer_SensorData;
  TClientSocket *ClientSocket1;
  TImageList *ImageList1;
  TWCImageButton *WCImageButton13;
  TImageList *ImageList2;
  TLabel *Label7;
  TActionList *ActionList1;
  TAction *Action1;
  TTimer *CommRxTimer;
  TWCImageButton *WCImageButton14;
  TTimer *CommTxTimer;
  TWCImageButton *WCImageButton15;
  void __fastcall WCImageButton1Click(TObject *Sender);
  void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
  void __fastcall PaintBox1Paint(TObject *Sender);
  void __fastcall PaintBox2Paint(TObject *Sender);
  void __fastcall PaintBox3Paint(TObject *Sender);
  void __fastcall PaintBox4Paint(TObject *Sender);
  void __fastcall PaintBox5Paint(TObject *Sender);
  void __fastcall GraphTimerTimer(TObject *Sender);
  void __fastcall ComPort1RxChar(TObject *Sender, int Count);
  void __fastcall Timer_SensorDataTimer(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall ClientSocket1Read(TObject *Sender,
          TCustomWinSocket *Socket);
  void __fastcall ClientSocket1Connect(TObject *Sender,
          TCustomWinSocket *Socket);
  void __fastcall WCImageButton3Click(TObject *Sender);
  void __fastcall WCImageButton6Click(TObject *Sender);
  void __fastcall WCImageButton5Click(TObject *Sender);
  void __fastcall ClientSocket1Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
  void __fastcall WCImageButton7Click(TObject *Sender);
  void __fastcall WCImageButton8Click(TObject *Sender);
  void __fastcall WCImageButton9Click(TObject *Sender);
  void __fastcall WCImageButton10Click(TObject *Sender);
  void __fastcall WCImageButton11Click(TObject *Sender);
  void __fastcall VrBitmapImage1Click(TObject *Sender);
  void __fastcall VrBitmapImage3Click(TObject *Sender);
  void __fastcall VrBitmapImage4Click(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall WCImageButton4Click(TObject *Sender);
  void __fastcall WCImageButton13Click(TObject *Sender);
  void __fastcall WCImageButton2Click(TObject *Sender);
  void __fastcall Action1Execute(TObject *Sender);
  void __fastcall CommRxTimerTimer(TObject *Sender);
  void __fastcall CommTxTimerTimer(TObject *Sender);
  void __fastcall WCImageButton15Click(TObject *Sender);
private:	// User declarations
  TImage          *pBufImage;
  int             iAutoMode;    // 0x00:Manual , 0x01:Auto
  int             iRecvCount;
  unsigned char   szRecvBuf[1024];
  
public:		// User declarations
  __fastcall Tfrm_RGB_X_Main(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
  void __fastcall DeviceClient_Config_Load();
  void __fastcall WaveDisplay_BasicSetting(TImage *pBufImg,int iSeq,double UCL,double LCL,double SET,double Top,double Bottom);

  unsigned char __fastcall Make_CheckSum(unsigned char *szMsgBuf,int iCount);
  void __fastcall SendMessage_ToDevice(char *Data,int length);
  void __fastcall Make_SendMessage(int Command,int DataSize,char *stData);
  void __fastcall Device_Mode_Change();
  void __fastcall CommunicationStatus_SetImage(int iSelect,int iMode);
  void __fastcall Protocol_Check_Verification(char *szBuffer,int iCount);
  void __fastcall Protocol_Receive_NACK(RequestPacket *pChkPnt);
  void __fastcall Protocol_Receive_SensorData(RequestPacket *pChkPnt);
  void __fastcall Protocol_Receive_StatusData(RequestPacket *pChkPnt);
  void __fastcall Protocol_AlarmTable_Process();
  void LogMessage_Printf(const char *pFormat, ...);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_RGB_X_Main *frm_RGB_X_Main;
//---------------------------------------------------------------------------
#endif
