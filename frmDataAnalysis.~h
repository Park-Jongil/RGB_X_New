//---------------------------------------------------------------------------

#ifndef frmDataAnalysisH
#define frmDataAnalysisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "WCImageButton.hpp"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_DataAnalysis : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TLabel *Label1;
  TDateTimePicker *DateTimePicker1;
  TWCImageButton *WCImageButton6;
  TComboBox *ComboBox1;
  TWCImageButton *WCImageButton1;
  TPaintBox *PaintBox1;
  TPaintBox *PaintBox2;
  TPaintBox *PaintBox3;
  TPaintBox *PaintBox4;
  TPaintBox *PaintBox5;
  TPaintBox *PaintBox6;
  void __fastcall WCImageButton6Click(TObject *Sender);
  void __fastcall PaintBox1Paint(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall DateTimePicker1Change(TObject *Sender);
  void __fastcall ComboBox1Change(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall PaintBox2Paint(TObject *Sender);
  void __fastcall PaintBox3Paint(TObject *Sender);
  void __fastcall PaintBox4Paint(TObject *Sender);
  void __fastcall PaintBox5Paint(TObject *Sender);
  void __fastcall PaintBox6Paint(TObject *Sender);
  void __fastcall WCImageButton1Click(TObject *Sender);
  void __fastcall PaintBox1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall PaintBox1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall PaintBox1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
private:	// User declarations
  TImage    *pBufImage;
  TImage    *pBarImage;
  int       iSx,iSy,iEx,iEy,iMouseMove,isZoomMode;

public:		// User declarations
  __fastcall Tfrm_DataAnalysis(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
  void __fastcall WaveDisplay_BasicSetting(TImage *pBufImg,int iSeq,double UCL,double LCL,double SET,double Top,double Bottom);
  void __fastcall BarChart_BasicSetting(TImage *pBufImg,int iDataType);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_DataAnalysis *frm_DataAnalysis;     
//---------------------------------------------------------------------------
#endif
