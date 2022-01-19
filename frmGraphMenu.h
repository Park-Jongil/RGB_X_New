//---------------------------------------------------------------------------

#ifndef frmGraphMenuH
#define frmGraphMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WCImageButton.hpp"
#include <jpeg.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_GraphMenu : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TWCImageButton *WCImageButton6;
  TWCImageButton *WCImageButton1;
  TWCImageButton *WCImageButton2;
  TWCImageButton *WCImageButton3;
  void __fastcall WCImageButton6Click(TObject *Sender);
  void __fastcall WCImageButton1Click(TObject *Sender);
  void __fastcall WCImageButton2Click(TObject *Sender);
  void __fastcall WCImageButton3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_GraphMenu(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_GraphMenu *frm_GraphMenu;
//---------------------------------------------------------------------------
#endif
