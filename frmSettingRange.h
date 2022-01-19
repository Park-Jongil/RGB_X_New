//---------------------------------------------------------------------------

#ifndef frmSettingRangeH
#define frmSettingRangeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvEdBtn.hpp"
#include "advedit.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "AdvEdit.hpp"
#include "AdvSpin.hpp"
#include <Mask.hpp>
#include <jpeg.hpp>
#include "WCImageButton.hpp"
//---------------------------------------------------------------------------
class Tfrm_SettingRange : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TLabel *Label1;
  TWCImageButton *WCImageButton1;
  TWCImageButton *WCImageButton2;
  TWCImageButton *WCImageButton3;
  TWCImageButton *WCImageButton4;
  TWCImageButton *WCImageButton5;
  TWCImageButton *WCImageButton6;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label4;
  TLabel *Label5;
  TLabel *Label6;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall WCImageButton6Click(TObject *Sender);
  void __fastcall WCImageButton1Click(TObject *Sender);
  void __fastcall WCImageButton2Click(TObject *Sender);
  void __fastcall WCImageButton3Click(TObject *Sender);
  void __fastcall WCImageButton4Click(TObject *Sender);
  void __fastcall WCImageButton5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  int             iDataCode;
  char            szDataName[1024];
  UCL_SET_DATA    stSetData;

  void __fastcall CreateParams( TCreateParams &Params );
  __fastcall Tfrm_SettingRange(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_SettingRange *frm_SettingRange;
//---------------------------------------------------------------------------
#endif
