//---------------------------------------------------------------------------

#ifndef frmGraphExcelH
#define frmGraphExcelH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "WCImageButton.hpp"
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrm_GraphExcel : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TWCImageButton *WCImageButton6;
  TLabel *Label1;
  TDateTimePicker *DateTimePicker1;
  TAdvStringGrid *AdvStringGrid1;
  TWCImageButton *WCImageButton1;
  TSaveDialog *SaveDialog1;
  void __fastcall WCImageButton6Click(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall DateTimePicker1Change(TObject *Sender);
  void __fastcall AdvStringGrid1GetAlignment(TObject *Sender, int ARow,
          int ACol, TAlignment &HAlign, TVAlignment &VAlign);
  void __fastcall WCImageButton1Click(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_GraphExcel(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_GraphExcel *frm_GraphExcel;
//---------------------------------------------------------------------------
#endif
