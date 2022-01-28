//---------------------------------------------------------------------------

#ifndef frmGraphPopupH
#define frmGraphPopupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class Tfrm_GraphPopup : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall Image1DblClick(TObject *Sender);
  void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_GraphPopup(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_GraphPopup *frm_GraphPopup;
//---------------------------------------------------------------------------
#endif
