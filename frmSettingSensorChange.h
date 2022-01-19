//---------------------------------------------------------------------------

#ifndef frmSettingSensorChangeH
#define frmSettingSensorChangeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "WCImageButton.hpp"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_SettingSensorChange : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TWCImageButton *WCImageButton6;
  TWCImageButton *WCImageButton1;
  TDateTimePicker *DateTimePicker1;
  TDateTimePicker *DateTimePicker2;
  TDateTimePicker *DateTimePicker3;
  TDateTimePicker *DateTimePicker4;
  TLabel *Label20;
  void __fastcall WCImageButton6Click(TObject *Sender);
  void __fastcall WCImageButton1Click(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_SettingSensorChange(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_SettingSensorChange *frm_SettingSensorChange;
//---------------------------------------------------------------------------
#endif
