//---------------------------------------------------------------------------

#ifndef frmGraph_Y_AxisH
#define frmGraph_Y_AxisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "WCImageButton.hpp"
#include "AdvSpin.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class Tfrm_Graph_Y_Axis : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TWCImageButton *WCImageButton4;
  TWCImageButton *WCImageButton5;
  TWCImageButton *WCImageButton6;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  void __fastcall WCImageButton6Click(TObject *Sender);
  void __fastcall WCImageButton4Click(TObject *Sender);
  void __fastcall WCImageButton5Click(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
  int             iDataCode;
  char            szDataName[1024];
  __fastcall Tfrm_Graph_Y_Axis(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_Graph_Y_Axis *frm_Graph_Y_Axis;
//---------------------------------------------------------------------------
#endif
