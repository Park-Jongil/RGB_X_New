//---------------------------------------------------------------------------

#ifndef frmCompanyTitleH
#define frmCompanyTitleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class Tfrm_CompanyTitle : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  void __fastcall Image1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_CompanyTitle(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_CompanyTitle *frm_CompanyTitle;
//---------------------------------------------------------------------------
#endif
