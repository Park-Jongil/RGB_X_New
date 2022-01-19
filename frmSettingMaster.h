//---------------------------------------------------------------------------

#ifndef frmSettingMasterH
#define frmSettingMasterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WCImageButton.hpp"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrm_SettingMaster : public TForm
{
__published:	// IDE-managed Components
  TImage *Image1;
  TWCImageButton *WCImageButton6;
  TWCImageButton *WCImageButton1;
  TWCImageButton *WCImageButton2;
  TWCImageButton *WCImageButton3;
  TWCImageButton *WCImageButton4;
  TWCImageButton *WCImageButton5;
  TImageList *ImageList1;
  void __fastcall WCImageButton6Click(TObject *Sender);
  void __fastcall WCImageButton5Click(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall WCImageButton1Click(TObject *Sender);
  void __fastcall WCImageButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_SettingMaster(TComponent* Owner);
  void __fastcall CreateParams( TCreateParams &Params );
  void __fastcall ImageChange_byID(TWCImageButton *BtnCtrl,int iMode);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_SettingMaster *frm_SettingMaster;
//---------------------------------------------------------------------------
#endif
