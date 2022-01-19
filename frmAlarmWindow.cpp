//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UserDefine.h"
#include "frmAlarmWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WCImageButton"
#pragma link "AdvOfficeButtons"
#pragma resource "*.dfm"
Tfrm_AlarmWindow *frm_AlarmWindow;
//---------------------------------------------------------------------------
__fastcall Tfrm_AlarmWindow::Tfrm_AlarmWindow(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_AlarmWindow::CreateParams( TCreateParams &Params )
{
    TForm::CreateParams( Params ); // to call basic class
//    Params.Style &= ~WS_CAPTION; // remove Caption
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_AlarmWindow::AlarmWindow_StatusUpdate()
{
  AdvOfficeCheckBox1->Checked = Alarm1.bit8.RGB_UCL_Alarm;
  AdvOfficeCheckBox2->Checked = Alarm1.bit8.RGB_LCL_Alarm;
  AdvOfficeCheckBox3->Checked = Alarm1.bit8.ORP_UCL_Alarm;
  AdvOfficeCheckBox4->Checked = Alarm1.bit8.ORP_LCL_Alarm;
  AdvOfficeCheckBox5->Checked = Alarm1.bit8.HCL_UCL_Alarm;
  AdvOfficeCheckBox6->Checked = Alarm1.bit8.HCL_LCL_Alarm;
  AdvOfficeCheckBox7->Checked = Alarm1.bit8.SG_UCL_Alarm;
  AdvOfficeCheckBox8->Checked = Alarm1.bit8.SG_LCL_Alarm;
  AdvOfficeCheckBox9->Checked = Alarm2.bit8.TEMP_UCL_Alarm;
  AdvOfficeCheckBox10->Checked = Alarm2.bit8.TEMP_LCL_Alarm;
  AdvOfficeCheckBox1->Visible = AdvOfficeCheckBox1->Checked;
  AdvOfficeCheckBox2->Visible = AdvOfficeCheckBox2->Checked;
  AdvOfficeCheckBox3->Visible = AdvOfficeCheckBox3->Checked;
  AdvOfficeCheckBox4->Visible = AdvOfficeCheckBox4->Checked;
  AdvOfficeCheckBox5->Visible = AdvOfficeCheckBox5->Checked;
  AdvOfficeCheckBox6->Visible = AdvOfficeCheckBox6->Checked;
  AdvOfficeCheckBox7->Visible = AdvOfficeCheckBox7->Checked;
  AdvOfficeCheckBox8->Visible = AdvOfficeCheckBox8->Checked;
  AdvOfficeCheckBox9->Visible = AdvOfficeCheckBox9->Checked;
  AdvOfficeCheckBox10->Visible = AdvOfficeCheckBox10->Checked;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_AlarmWindow::WCImageButton1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
