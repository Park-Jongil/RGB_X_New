//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "frmRGB_X_Main.h"
#include "frmAlarmPump.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_AlarmPump *frm_AlarmPump;
//---------------------------------------------------------------------------
__fastcall Tfrm_AlarmPump::Tfrm_AlarmPump(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall Tfrm_AlarmPump::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_AlarmPump::Image1DblClick(TObject *Sender)
{
  frm_RGB_X_Main->isPumpStatus = 0x00;
  Close();
}
//---------------------------------------------------------------------------
