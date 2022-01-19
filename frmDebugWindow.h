//---------------------------------------------------------------------------

#ifndef frmDebugWindowH
#define frmDebugWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tfrm_DebugWindow : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TRichEdit *RichEdit1;
        TBitBtn *BitBtn1;
  TBitBtn *BitBtn2;
  TBitBtn *BitBtn3;
  TSaveDialog *SaveDialog1;
        void __fastcall BitBtn1Click(TObject *Sender);
  void __fastcall BitBtn2Click(TObject *Sender);
  void __fastcall BitBtn3Click(TObject *Sender);
private:	// User declarations
  int   iAppendStatus;
public:		// User declarations
        __fastcall Tfrm_DebugWindow(TComponent* Owner);
        void Display_DebugMessage(int iMode,unsigned char *szCommand, int iSize);

};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_DebugWindow *frm_DebugWindow;
//---------------------------------------------------------------------------
#endif
