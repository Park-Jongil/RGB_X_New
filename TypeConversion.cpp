//---------------------------------------------------------------------------
#pragma hdrstop

#include "UserDefine.h"
#include "TypeConversion.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
unsigned short int Convert_Endian(unsigned short int iChkData)
{
  unsigned short int   iChkRet;

  iChkRet = (iChkData%0x100)*0x100 + (iChkData/0x100);
  return(iChkRet);
}
//---------------------------------------------------------------------------
BOOL PointInPolygon(int iCx,int iCy,int *iPx,int *iPy,int iCount) {
  BOOL bPointInPolygon = FALSE;
  int iCrosses = 0;

  for(int i = 0; i < iCount; i++ ) {
    int j = ( i + 1 ) % iCount; //점(point)이 선분(m_apnt[i], m_apnt[j])의 y좌표 사이에 있음
    if (( iPy[i] > iCy ) != ( iPy[j] > iCy ) ) { //atX는 점(point)을 지나는 수평선과 선분(m_apnt[i], m_apnt[j])의 교점
      double atX = ( ( (double)(iPx[j]-iPx[i])/(iPy[j]-iPy[i]) )*( iCy - iPy[i] ) ) + iPx[i]; //atX가 오른쪽 반직선과의 교점이 맞으면 교점의 개수를 증가시킨다.
      if( iCx < atX ) iCrosses++;
    }
  } // 홀수면 내부, 짝수면 외부에 있음
  if( 0 == ( iCrosses % 2 ) ) bPointInPolygon = FALSE;
   else bPointInPolygon = TRUE;
  return bPointInPolygon;
}

//---------------------------------------------------------------------------
void  TypeConversion(SensorData *pChkPnt)
{
  pChkPnt->FQ_R = Convert_Endian(pChkPnt->FQ_R);
  pChkPnt->FQ_G = Convert_Endian(pChkPnt->FQ_G);
  pChkPnt->FQ_B = Convert_Endian(pChkPnt->FQ_B);
  pChkPnt->ORP = Convert_Endian(pChkPnt->ORP);
  pChkPnt->HCL = Convert_Endian(pChkPnt->HCL);
  pChkPnt->SG = Convert_Endian(pChkPnt->SG);
  pChkPnt->LQ_TEMP = Convert_Endian(pChkPnt->LQ_TEMP);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void  TypeConversion(StatusData *pChkPnt)
{
  pChkPnt->R_SHIFT = Convert_Endian(pChkPnt->R_SHIFT);
  pChkPnt->G_SHIFT = Convert_Endian(pChkPnt->G_SHIFT);
  pChkPnt->B_SHIFT = Convert_Endian(pChkPnt->B_SHIFT);
  pChkPnt->ORP_SHIFT = Convert_Endian(pChkPnt->ORP_SHIFT);
  pChkPnt->HCL_SHIFT = Convert_Endian(pChkPnt->HCL_SHIFT);
  pChkPnt->SG_SHIFT = Convert_Endian(pChkPnt->SG_SHIFT);
  pChkPnt->TEMP_SHIFT = Convert_Endian(pChkPnt->TEMP_SHIFT);
  pChkPnt->RGB_UCL = Convert_Endian(pChkPnt->RGB_UCL);
  pChkPnt->RGB_SET = Convert_Endian(pChkPnt->RGB_SET);
  pChkPnt->RGB_LCL = Convert_Endian(pChkPnt->RGB_LCL);
  pChkPnt->ORP_UCL = Convert_Endian(pChkPnt->ORP_UCL);
  pChkPnt->ORP_SET = Convert_Endian(pChkPnt->ORP_SET);
  pChkPnt->ORP_LCL = Convert_Endian(pChkPnt->ORP_LCL);
  pChkPnt->HCL_UCL = Convert_Endian(pChkPnt->HCL_UCL);
  pChkPnt->HCL_SET = Convert_Endian(pChkPnt->HCL_SET);
  pChkPnt->HCL_LCL = Convert_Endian(pChkPnt->HCL_LCL);
  pChkPnt->SG_UCL = Convert_Endian(pChkPnt->SG_UCL);
  pChkPnt->SG_SET = Convert_Endian(pChkPnt->SG_SET);
  pChkPnt->SG_LCL = Convert_Endian(pChkPnt->SG_LCL);
  pChkPnt->TEMP_UCL = Convert_Endian(pChkPnt->TEMP_UCL);
  pChkPnt->TEMP_LCL = Convert_Endian(pChkPnt->TEMP_LCL);
}
//---------------------------------------------------------------------------
void  TypeConversion(Sensor_ShiftData *pChkPnt)
{
  pChkPnt->R_SHIFT = Convert_Endian(pChkPnt->R_SHIFT);
  pChkPnt->G_SHIFT = Convert_Endian(pChkPnt->G_SHIFT);
  pChkPnt->B_SHIFT = Convert_Endian(pChkPnt->B_SHIFT);
  pChkPnt->ORP_SHIFT = Convert_Endian(pChkPnt->ORP_SHIFT);
  pChkPnt->HCL_SHIFT = Convert_Endian(pChkPnt->HCL_SHIFT);
  pChkPnt->SG_SHIFT = Convert_Endian(pChkPnt->SG_SHIFT);
  pChkPnt->TEMP_SHIFT = Convert_Endian(pChkPnt->TEMP_SHIFT);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void  TypeConversion(UCL_SET_DATA *pChkPnt)
{
  pChkPnt->RGB_UCL = Convert_Endian(pChkPnt->RGB_UCL);
  pChkPnt->RGB_SET = Convert_Endian(pChkPnt->RGB_SET);
  pChkPnt->RGB_LCL = Convert_Endian(pChkPnt->RGB_LCL);
  pChkPnt->ORP_UCL = Convert_Endian(pChkPnt->ORP_UCL);
  pChkPnt->ORP_SET = Convert_Endian(pChkPnt->ORP_SET);
  pChkPnt->ORP_LCL = Convert_Endian(pChkPnt->ORP_LCL);
  pChkPnt->HCL_UCL = Convert_Endian(pChkPnt->HCL_UCL);
  pChkPnt->HCL_SET = Convert_Endian(pChkPnt->HCL_SET);
  pChkPnt->HCL_LCL = Convert_Endian(pChkPnt->HCL_LCL);
  pChkPnt->SG_UCL = Convert_Endian(pChkPnt->SG_UCL);
  pChkPnt->SG_SET = Convert_Endian(pChkPnt->SG_SET);
  pChkPnt->SG_LCL = Convert_Endian(pChkPnt->SG_LCL);
  pChkPnt->TEMP_UCL = Convert_Endian(pChkPnt->TEMP_UCL);
  pChkPnt->TEMP_LCL = Convert_Endian(pChkPnt->TEMP_LCL);
}



