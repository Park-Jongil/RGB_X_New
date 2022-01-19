//---------------------------------------------------------------------------

#ifndef frmAlarmWindowH
#define frmAlarmWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WCImageButton.hpp"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "AdvOfficeButtons.hpp"
//---------------------------------------------------------------------------
class Tfrm_AlarmWindow : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TWCImageButton *WCImageButton1;
  TAdvOfficeCheckBox *AdvOfficeCheckBox1;
  TAdvOfficeCheckBox *AdvOfficeCheckBox2;
  TAdvOfficeCheckBox *AdvOfficeCheckBox3;
  TAdvOfficeCheckBox *AdvOfficeCheckBox4;
  TAdvOfficeCheckBox *AdvOfficeCheckBox5;
  TAdvOfficeCheckBox *AdvOfficeCheckBox6;
  TAdvOfficeCheckBox *AdvOfficeCheckBox7;
  TAdvOfficeCheckBox *AdvOfficeCheckBox8;
  TAdvOfficeCheckBox *AdvOfficeCheckBox9;
  TAdvOfficeCheckBox *AdvOfficeCheckBox10;
  void __fastcall WCImageButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  U_Alarm1        Alarm1;
  U_Alarm2        Alarm2;
  __fastcall Tfrm_AlarmWindow(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
  void __fastcall AlarmWindow_StatusUpdate();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_AlarmWindow *frm_AlarmWindow;
//---------------------------------------------------------------------------
#endif
