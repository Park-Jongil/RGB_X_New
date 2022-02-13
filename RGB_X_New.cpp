//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("frmRGB_X_Main.cpp", frm_RGB_X_Main);
USEFORM("frmDebugWindow.cpp", frm_DebugWindow);
USEFORM("frmChangeMode_Confirm.cpp", frm_ChangeMode_Confirm);
USEFORM("frmSettingRange.cpp", frm_SettingRange);
USEFORM("frmCalculator.cpp", frm_Calculator);
USEFORM("frmAlarmWindow.cpp", frm_AlarmWindow);
USEFORM("frmEventLog.cpp", frm_EventLog);
USEFORM("frmGraphMenu.cpp", frm_GraphMenu);
USEFORM("frmDataAnalysis.cpp", frm_DataAnalysis);
USEFORM("frmCompanyTitle.cpp", frm_CompanyTitle);
USEFORM("frmGraph_Y_Axis.cpp", frm_Graph_Y_Axis);
USEFORM("frmGraphUsage.cpp", frm_GraphUsage);
USEFORM("frmGraphExcel.cpp", frm_GraphExcel);
USEFORM("frmSettingMenu.cpp", frm_SettingMenu);
USEFORM("frmSettingParameter.cpp", frm_SettingParameter);
USEFORM("frmSettingCompensation.cpp", frm_SettingCompensation);
USEFORM("frmSettingControl.cpp", frm_SettingControl);
USEFORM("frmSettingSensorChange.cpp", frm_SettingSensorChange);
USEFORM("frmSettingMaster.cpp", frm_SettingMaster);
USEFORM("frmPasswordLogin.cpp", frm_PasswordLogin);
USEFORM("frmGraphPopup.cpp", frm_GraphPopup);
USEFORM("frmSettingPopup.cpp", frm_SettingPopup);
USEFORM("frmControl_Confirm.cpp", frm_Control_Confirm);
USEFORM("frmAlarmPump.cpp", frm_AlarmPump);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->CreateForm(__classid(Tfrm_RGB_X_Main), &frm_RGB_X_Main);
     Application->CreateForm(__classid(Tfrm_DebugWindow), &frm_DebugWindow);
     Application->CreateForm(__classid(Tfrm_ChangeMode_Confirm), &frm_ChangeMode_Confirm);
     Application->CreateForm(__classid(Tfrm_SettingRange), &frm_SettingRange);
     Application->CreateForm(__classid(Tfrm_Calculator), &frm_Calculator);
     Application->CreateForm(__classid(Tfrm_AlarmWindow), &frm_AlarmWindow);
     Application->CreateForm(__classid(Tfrm_EventLog), &frm_EventLog);
     Application->CreateForm(__classid(Tfrm_GraphMenu), &frm_GraphMenu);
     Application->CreateForm(__classid(Tfrm_DataAnalysis), &frm_DataAnalysis);
     Application->CreateForm(__classid(Tfrm_CompanyTitle), &frm_CompanyTitle);
     Application->CreateForm(__classid(Tfrm_Graph_Y_Axis), &frm_Graph_Y_Axis);
     Application->CreateForm(__classid(Tfrm_GraphUsage), &frm_GraphUsage);
     Application->CreateForm(__classid(Tfrm_GraphExcel), &frm_GraphExcel);
     Application->CreateForm(__classid(Tfrm_SettingMenu), &frm_SettingMenu);
     Application->CreateForm(__classid(Tfrm_SettingParameter), &frm_SettingParameter);
     Application->CreateForm(__classid(Tfrm_SettingCompensation), &frm_SettingCompensation);
     Application->CreateForm(__classid(Tfrm_SettingControl), &frm_SettingControl);
     Application->CreateForm(__classid(Tfrm_SettingSensorChange), &frm_SettingSensorChange);
     Application->CreateForm(__classid(Tfrm_SettingMaster), &frm_SettingMaster);
     Application->CreateForm(__classid(Tfrm_PasswordLogin), &frm_PasswordLogin);
     Application->CreateForm(__classid(Tfrm_GraphPopup), &frm_GraphPopup);
     Application->CreateForm(__classid(Tfrm_SettingPopup), &frm_SettingPopup);
     Application->CreateForm(__classid(Tfrm_Control_Confirm), &frm_Control_Confirm);
     Application->CreateForm(__classid(Tfrm_AlarmPump), &frm_AlarmPump);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  catch (...)
  {
     try
     {
       throw Exception("");
     }
     catch (Exception &exception)
     {
       Application->ShowException(&exception);
     }
  }
  return 0;
}
//---------------------------------------------------------------------------
