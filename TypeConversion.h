//---------------------------------------------------------------------------

#ifndef TypeConversionH
#define TypeConversionH
unsigned short int Convert_Endian(unsigned short int iChkData);
void  TypeConversion(SensorData *pChkPnt);
void  TypeConversion(StatusData *pChkPnt);
void  TypeConversion(Sensor_ShiftData *pChkPnt);
void  TypeConversion(UCL_SET_DATA *pChkPnt);
BOOL  PointInPolygon(int iCx,int iCy,int *iPx,int *iPy,int iCount); 
//---------------------------------------------------------------------------
#endif
