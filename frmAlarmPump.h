//---------------------------------------------------------------------------

#ifndef frmAlarmPumpH
#define frmAlarmPumpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class Tfrm_AlarmPump : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  void __fastcall Image1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_AlarmPump(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_AlarmPump *frm_AlarmPump;
//---------------------------------------------------------------------------
#endif
