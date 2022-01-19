//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmCompanyTitle.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_CompanyTitle *frm_CompanyTitle;
//---------------------------------------------------------------------------
__fastcall Tfrm_CompanyTitle::Tfrm_CompanyTitle(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_CompanyTitle::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_CompanyTitle::Image1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
