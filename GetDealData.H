#ifndef _GetData_H_
#define _GetData_H_

#include  "ADC1.H"

#define  ROUND(n)	((int)(n+0.5))
/*************************************�ⲿ���ñ�������************************************/
extern int ac_final,brAdFinal;
extern int ac_ad[2],br_ad,br_ad1;//��·���ŵ�ADֵ
extern unsigned int ac_data;
extern ubyte acRealiableFlag;
/*************************************��������************************************/
void acDeal();//���Ų����ܺ���
void get_ac_AD();//��ȡ��·���ŵ�ADֵ
void DataDeal(int acData);//�������ߵ���
void delay(int ms);
void brDeal();//ɲ�������ܺ���
int acChangeLimit(int ac); //���ű仯������

#endif 