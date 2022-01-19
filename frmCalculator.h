//---------------------------------------------------------------------------

#ifndef frmCalculatorH
#define frmCalculatorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "WCImageButton.hpp"
//---------------------------------------------------------------------------
class Tfrm_Calculator : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TWCImageButton *WCImageButton12;
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
  TWCImageButton *WCImageButton13;
  TWCImageButton *WCImageButton14;
  TWCImageButton *WCImageButton15;
  TWCImageButton *WCImageButton16;
  TWCImageButton *WCImageButton17;
  TLabel *Label1;
  TLabel *Label2;
  void __fastcall WCImageButton16Click(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall WCImageButton9Click(TObject *Sender);
  void __fastcall WCImageButton10Click(TObject *Sender);
  void __fastcall WCImageButton11Click(TObject *Sender);
  void __fastcall WCImageButton17Click(TObject *Sender);
  void __fastcall WCImageButton15Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  int         iMode;
  AnsiString  szValue;
  __fastcall Tfrm_Calculator(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_Calculator *frm_Calculator;
//---------------------------------------------------------------------------
#endif
