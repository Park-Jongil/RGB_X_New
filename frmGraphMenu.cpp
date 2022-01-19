//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmDataAnalysis.h"
#include "frmGraphUsage.h"
#include "frmGraphExcel.h"
#include "frmGraphMenu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma resource "*.dfm"
Tfrm_GraphMenu *frm_GraphMenu;
//---------------------------------------------------------------------------
__fastcall Tfrm_GraphMenu::Tfrm_GraphMenu(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphMenu::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphMenu::WCImageButton6Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphMenu::WCImageButton1Click(TObject *Sender)
{
  frm_GraphUsage->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_GraphMenu::WCImageButton2Click(TObject *Sender)
{
  frm_DataAnalysis->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_GraphMenu::WCImageButton3Click(TObject *Sender)
{
  frm_GraphExcel->ShowModal();
}
//---------------------------------------------------------------------------

