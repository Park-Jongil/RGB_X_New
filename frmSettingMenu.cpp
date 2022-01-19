//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmSettingParameter.h"
#include "frmSettingCompensation.h"
#include "frmSettingControl.h"
#include "frmSettingSensorChange.h"
#include "frmSettingMaster.h"
#include "frmSettingMenu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma resource "*.dfm"
Tfrm_SettingMenu *frm_SettingMenu;
//---------------------------------------------------------------------------
__fastcall Tfrm_SettingMenu::Tfrm_SettingMenu(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingMenu::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingMenu::WCImageButton6Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingMenu::WCImageButton1Click(TObject *Sender)
{
  frm_SettingParameter->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_SettingMenu::WCImageButton2Click(TObject *Sender)
{
  frm_SettingCompensation->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingMenu::WCImageButton3Click(TObject *Sender)
{
  frm_SettingControl->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingMenu::WCImageButton4Click(TObject *Sender)
{
  frm_SettingSensorChange->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_SettingMenu::WCImageButton5Click(TObject *Sender)
{
  frm_SettingMaster->ShowModal();
}
//---------------------------------------------------------------------------

