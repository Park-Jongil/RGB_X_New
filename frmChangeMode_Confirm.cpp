//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmChangeMode_Confirm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma resource "*.dfm"
Tfrm_ChangeMode_Confirm *frm_ChangeMode_Confirm;
//---------------------------------------------------------------------------
__fastcall Tfrm_ChangeMode_Confirm::Tfrm_ChangeMode_Confirm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_ChangeMode_Confirm::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_ChangeMode_Confirm::WCImageButton1Click(
      TObject *Sender)
{
  ModalResult = mrOk;
//  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_ChangeMode_Confirm::WCImageButton2Click(
      TObject *Sender)
{
  ModalResult = mrCancel;  
//  Close();
}
//---------------------------------------------------------------------------
