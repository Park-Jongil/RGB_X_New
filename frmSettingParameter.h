//---------------------------------------------------------------------------

#ifndef frmSettingParameterH
#define frmSettingParameterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "AdvSpin.hpp"
#include "WCImageButton.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class Tfrm_SettingParameter : public TForm
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
  TLabel *Label10;
  TLabel *Label11;
  TLabel *Label12;
  TLabel *Label13;
  TLabel *Label15;
  TWCImageButton *WCImageButton1;
  TWCImageButton *WCImageButton2;
  TWCImageButton *WCImageButton3;
  TWCImageButton *WCImageButton4;
  TWCImageButton *WCImageButton5;
  TWCImageButton *WCImageButton7;
  TWCImageButton *WCImageButton8;
  TWCImageButton *WCImageButton9;
  TWCImageButton *WCImageButton10;
  TWCImageButton *WCImageButton11;
  TWCImageButton *WCImageButton12;
  TWCImageButton *WCImageButton13;
  TWCImageButton *WCImageButton14;
  TWCImageButton *WCImageButton16;
  TWCImageButton *WCImageButton17;
  TWCImageButton *WCImageButton18;
  TWCImageButton *WCImageButton19;
  TWCImageButton *WCImageButton20;
  TWCImageButton *WCImageButton21;
  TWCImageButton *WCImageButton22;
  TWCImageButton *WCImageButton23;
  TLabel *Label16;
  TLabel *Label17;
  TLabel *Label18;
  TLabel *Label19;
  TLabel *Label20;
  TLabel *Label21;
  TLabel *Label22;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall WCImageButton6Click(TObject *Sender);
  void __fastcall WCImageButton1Click(TObject *Sender);
  void __fastcall WCImageButton2Click(TObject *Sender);
  void __fastcall WCImageButton3Click(TObject *Sender);
  void __fastcall WCImageButton4Click(TObject *Sender);
  void __fastcall WCImageButton5Click(TObject *Sender);
  void __fastcall WCImageButton7Click(TObject *Sender);
  void __fastcall WCImageButton8Click(TObject *Sender);
  void __fastcall WCImageButton9Click(TObject *Sender);
  void __fastcall WCImageButton10Click(TObject *Sender);
  void __fastcall WCImageButton11Click(TObject *Sender);
  void __fastcall WCImageButton12Click(TObject *Sender);
  void __fastcall WCImageButton13Click(TObject *Sender);
  void __fastcall WCImageButton14Click(TObject *Sender);
  void __fastcall WCImageButton16Click(TObject *Sender);
  void __fastcall WCImageButton17Click(TObject *Sender);
  void __fastcall WCImageButton18Click(TObject *Sender);
  void __fastcall WCImageButton19Click(TObject *Sender);
  void __fastcall WCImageButton20Click(TObject *Sender);
  void __fastcall WCImageButton21Click(TObject *Sender);
  void __fastcall WCImageButton22Click(TObject *Sender);
  void __fastcall WCImageButton23Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_SettingParameter(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_SettingParameter *frm_SettingParameter;
//---------------------------------------------------------------------------
#endif
