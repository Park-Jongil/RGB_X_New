//---------------------------------------------------------------------------

#ifndef frmControl_ConfirmH
#define frmControl_ConfirmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WCImageButton.hpp"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class Tfrm_Control_Confirm : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TWCImageButton *WCImageButton1;
  TWCImageButton *WCImageButton2;
  void __fastcall WCImageButton1Click(TObject *Sender);
  void __fastcall WCImageButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_Control_Confirm(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_Control_Confirm *frm_Control_Confirm;
//---------------------------------------------------------------------------
#endif
