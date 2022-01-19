//---------------------------------------------------------------------------

#ifndef frmEventLogH
#define frmEventLogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "WCImageButton.hpp"
#include <ComCtrls.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Grids.hpp>
//---------------------------------------------------------------------------
class Tfrm_EventLog : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TPanel *Panel1;
  TLabel *Label1;
  TDateTimePicker *DateTimePicker1;
  TWCImageButton *WCImageButton6;
  TPanel *Panel2;
  TLabel *Label2;
  TAdvStringGrid *AdvStringGrid1;
  TWCImageButton *WCImageButton2;
  TWCImageButton *WCImageButton1;
  void __fastcall WCImageButton6Click(TObject *Sender);
  void __fastcall DateTimePicker1Change(TObject *Sender);
  void __fastcall WCImageButton1Click(TObject *Sender);
  void __fastcall WCImageButton2Click(TObject *Sender);
  void __fastcall AdvStringGrid1RowChanging(TObject *Sender, int OldRow,
          int NewRow, bool &Allow);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
  int   iCurRow;
public:		// User declarations
  __fastcall Tfrm_EventLog(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_EventLog *frm_EventLog;
//---------------------------------------------------------------------------
#endif
