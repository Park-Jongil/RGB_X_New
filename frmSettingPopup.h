//---------------------------------------------------------------------------

#ifndef frmSettingPopupH
#define frmSettingPopupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class Tfrm_SettingPopup : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_SettingPopup(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_SettingPopup *frm_SettingPopup;
//---------------------------------------------------------------------------
#endif
