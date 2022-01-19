//---------------------------------------------------------------------------

#ifndef frmGraphUsageH
#define frmGraphUsageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "WCImageButton.hpp"
#include "AdvSpin.hpp"
#include <Mask.hpp>
#include <Chartfx3.hpp>
#include <OleCtrls.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <ComCtrls.hpp>
#include <Series.hpp>
//---------------------------------------------------------------------------
class Tfrm_GraphUsage : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TWCImageButton *WCImageButton6;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label4;
  TLabel *Label5;
  TLabel *Label6;
  TLabel *Label7;
  TLabel *Label8;
  TLabel *Label9;
  TChart *Chart1;
  TDateTimePicker *DateTimePicker1;
  TBarSeries *Series1;
  TBarSeries *Series2;
  TBarSeries *Series3;
  TWCImageButton *WCImageButton17;
  TWCImageButton *WCImageButton1;
  TWCImageButton *WCImageButton2;
  TLabel *Label20;
  TLabel *Label10;
  TLabel *Label11;
  TLabel *Label12;
  TLabel *Label13;
  TLabel *Label14;
  TLabel *Label15;
  TLabel *Label16;
  TLabel *Label17;
  TLabel *Label18;
  TLabel *Label19;
  TLabel *Label21;
  TWCImageButton *WCImageButton3;
  TWCImageButton *WCImageButton4;
  TWCImageButton *WCImageButton5;
  void __fastcall WCImageButton6Click(TObject *Sender);
  void __fastcall DateTimePicker1Change(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall WCImageButton17Click(TObject *Sender);
  void __fastcall WCImageButton1Click(TObject *Sender);
  void __fastcall WCImageButton2Click(TObject *Sender);
  void __fastcall WCImageButton3Click(TObject *Sender);
  void __fastcall WCImageButton4Click(TObject *Sender);
  void __fastcall WCImageButton5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_GraphUsage(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_GraphUsage *frm_GraphUsage;
//---------------------------------------------------------------------------
#endif
