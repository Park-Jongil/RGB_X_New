//---------------------------------------------------------------------------

#ifndef frmSettingMenuH
#define frmSettingMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WCImageButton.hpp"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class Tfrm_SettingMenu : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TWCImageButton *WCImageButton6;
  TWCImageButton *WCImageButton1;
  TWCImageButton *WCImageButton2;
  TWCImageButton *WCImageButton3;
  TWCImageButton *WCImageButton4;
  TWCImageButton *WCImageButton5;
  void __fastcall WCImageButton6Click(TObject *Sender);
  void __fastcall WCImageButton1Click(TObject *Sender);
  void __fastcall WCImageButton2Click(TObject *Sender);
  void __fastcall WCImageButton3Click(TObject *Sender);
  void __fastcall WCImageButton4Click(TObject *Sender);
  void __fastcall WCImageButton5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_SettingMenu(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_SettingMenu *frm_SettingMenu;
//---------------------------------------------------------------------------
#endif
