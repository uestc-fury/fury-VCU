//****************************************************************************
// @Module        General Purpose Timer Unit (GPT1)
// @Filename      GPT1.C
// @Project       test3.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2267M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.0
//
// @Description   This file contains functions that use the GPT1 module.
//
//----------------------------------------------------------------------------
// @Date          2018/11/1 16:59:45
//
//****************************************************************************

// USER CODE BEGIN (GPT1_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (GPT1_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (GPT1_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (GPT1_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (GPT1_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (GPT1_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (GPT1_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (GPT1_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (GPT1_General,9)

// USER CODE END


//****************************************************************************
// @Function      void GPT1_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the GPT1 function 
//                library. It is assumed that the SFRs used by this library 
//                are in reset state. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2018/11/1
//
//****************************************************************************

// USER CODE BEGIN (Init,1)

// USER CODE END

void GPT1_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END
  ///  -----------------------------------------------------------------------
  ///  Configuration of Timer Block Prescaler 1:
  ///  -----------------------------------------------------------------------
  GPT12E_KSCCFG  =  0x0003;      // Module Enable

  _nop_();  // one cycle delay 

  _nop_();  // one cycle delay 



  ///  -----------------------------------------------------------------------
  ///  Configuration of Timer Block Prescaler 1:
  ///  -----------------------------------------------------------------------
  ///  - prescaler for timer block 1 is 4


  ///  -----------------------------------------------------------------------
  ///  Configuration of the GPT1 Core Timer 3:
  ///  -----------------------------------------------------------------------
  ///  - timer 3 works in timer mode
  ///  - external up/down control is disabled
  ///  - prescaler factor is 512
  ///  - up/down control bit is reset
  ///  - alternate output function T3OUT (P7.0) is disabled
  ///  - timer 3 output toggle latch (T3OTL) is set to 0

  GPT12E_T3CON   =  0x0807;      // load timer 3 control register
  GPT12E_T3      =  0xFCF3;      // load timer 3 register
  ///  - prescaler for timer block 1 is 4

  ///  -----------------------------------------------------------------------
  ///  Configuration of the GPT1 Auxiliary Timer 2:
  ///  -----------------------------------------------------------------------
  ///  - timer 2 works in timer mode
  ///  - external up/down control is disabled
  ///  - prescaler factor is 4
  ///  - up/down control bit is reset
  ///  - timer 2 run bit is reset

  GPT12E_T2CON   =  0x0000;      // load timer 2 control register
  GPT12E_T2      =  0x0007;      // load timer 2 register
  ///  - prescaler for timer block 1 is 4

  ///  -----------------------------------------------------------------------
  ///  Configuration of the GPT1 Auxiliary Timer 4:
  ///  -----------------------------------------------------------------------
  ///  - timer 4 works in timer mode
  ///  - external up/down control is disabled
  ///  - prescaler factor is 4
  ///  - up/down control bit is reset
  ///  - timer 4 run bit is reset

  GPT12E_T4CON   =  0x0000;      // load timer 4 control register
  GPT12E_T4      =  0x0000;      // load timer 4 register
  ///  - prescaler for timer block 1 is 4

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used GPT1 Port Pins:
  ///  -----------------------------------------------------------------------



  ///  -----------------------------------------------------------------------
  ///  Configuration of the used GPT1 Interrupts:
  ///  -----------------------------------------------------------------------
  ///  timer 3 service request node configuration:
  ///  - timer 3 interrupt priority level (ILVL) = 14
  ///  - timer 3 interrupt group level (GLVL) = 3
  ///  - timer 3 group priority extension (GPX) = 0

  GPT12E_T3IC    =  0x007B;     

  ///  Use PEC channel 3 for GPT1 T3 INT:
  ///  - normal interrupt
  ///  - pointers are not modified
  ///  - transfer a word
  ///  - service End of PEC interrrupt by a EOP interrupt node is disabled
  ///  - channel link mode is disabled

  PECC3          =  0x0000;      // load PECC3 control register



  // USER CODE BEGIN (GPT1_Function,3)

  // USER CODE END

  GPT12E_T3CON_T3R  =  1;        // set timer 3 run bit

} //  End of function GPT1_viTmr4


//****************************************************************************
// @Function      void GPT1_viTmr3(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the GPT1 timer 3. 
//                It is called up in the case of over or underflow of the 
//                timer 3 register.
//                If the incremental interface mode is selected it is called 
//                up if count edge or count direction was detected.
//                
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2018/11/1
//
//****************************************************************************

// USER CODE BEGIN (Tmr3,1)
ubyte can0_send[8]={0};//VCU�����ݸ�K60����������
ubyte can0_send1[8]={0};
ubyte can0_send_old[8]={0};
unsigned int timeFlag=0;

unsigned int allFlag=0;

int temp=0;
//   ������־	   ����ɲ���ɿ�		 ��ʻ״̬		 ����		 ���п���
ubyte startFlag=0,acBrReliableFlag=1,driveReadyFlag=0,beepFlag=0,runFlag=0,SafetyFlag,brFlag=0;
//����ʱ�����
unsigned int beepTimer=0;

 unsigned int can1WatchDog=0,can2WatchDog=0;	
// USER CODE END

void GPT1_viTmr3(void) interrupt T3INT
{
  // USER CODE BEGIN (Tmr3,2)
  	can1WatchDog++;
	if(can1WatchDog>500)  can1WatchDog=500;
	if(can1WatchDog>100)
	{
		 BatVoltage=9999;
		 BatCurrent=9999;
		 BatSoc=999;
		 MaxTemp=999;	
	}
	if(can2WatchDog>500)  can2WatchDog=500;
	if(can2WatchDog>100)
	{
		 RotateSpeed=9999;
		 mcFlag=999;
		 mcuTemp=999;
		 motorTemp=999;	
	}
  // USER CODE END


  // USER CODE BEGIN (Tmr3,5)

	acDeal(); //��ȡ�������������ݣ���������Ϊ ac_final��acRealiableFlag
	brDeal(); //��ȡ�������������ݣ���������Ϊ brAdFinal

	if (brAdFinal>BREAK && StartButton == 0)		//start_flag ������־
		startFlag = 1;

	 //�ƶ��ɿ��Լ�鲿������
	if(acBrReliableFlag == 1 && ac_final > 15 && brAdFinal > 15)		 	//�ƶ��ɿ�����ֵ�޸�
		acBrReliableFlag = 0;
	if(acBrReliableFlag == 0 & ac_final < 5)
		acBrReliableFlag = 1;
	//���������ʹ���������
	if(startFlag == 1 && acRealiableFlag == 1 && acBrReliableFlag == 1)
		runFlag = 1;
	else
		runFlag =0; 
	 //���������ʹ��������� ��������ε����ź��ƶ�����޶������
	if(ac_ad[0]<5||ac_ad[1]<5)  
		runFlag =0; 	

	//�����ʻ״̬
	if(startFlag == 1 && runFlag == 1 && SafetyLoopDetection==0&& McBTB==0)// 
	{
		driveReadyFlag = 1; 
		DriveReadyLed = 1;
		beepFlag = 1;
	}
	//�˳���ʻ״̬		
	if(SafetyLoopDetection==1 || McBTB==1  )//	
	{
		startFlag=0;
		driveReadyFlag = 0;	
		DriveReadyLed = 0;		   		//�߱߿���2 ��ʻָʾ����
		beepFlag = 0;
		beepTimer=0;
	}	   			
	
	if( brAdFinal>BREAK){ //ɲ���ƿ���  driveReadyFlag == 1 && startFlag == 1 &&
			BreakLed = 1;
			brFlag=1;
	}
	else{
		BreakLed = 0;
		brFlag=0;
	}	

	//���ѿ���
	if(beepFlag == 1&& beepTimer<BEEPTIME )
	{	
		beepTimer ++;
		Beep = 1;				//�߱߿���1	 ��������   
	}	
	else	Beep = 0;				//�߱߿���1	 ����ֹͣ


	if(SafetyLoopDetection==0)	  	  SafetyFlag=1;//�������
	else if(SafetyLoopDetection==1)	  SafetyFlag=0;//�쳣���
	allFlag=acRealiableFlag*1+acBrReliableFlag*2+startFlag*4+runFlag*8	//���ͱ�־����
			+ driveReadyFlag*16+SafetyFlag*32+brFlag*64;
	 
	sendToMc();
	sendToK60();

	GPT12E_T3=0xF9E6;	   		//���ö�ʱ��ʱ��

  // USER CODE BEGIN (Tmr3,5)

  // USER CODE END

} //  End of function GPT1_viTmr3




// USER CODE BEGIN (GPT1_General,10)

 void sendToK60(){//CAN2
 	 	int i=0;
	ubyte repeat=0;
	
	timeFlag++;
	temp+=10;
	temp=temp>9000?0:temp;

	 if(timeFlag%2==1){//ת�٣��ٶ���ʾҪʵʱ�ԣ�5ms����һ��
	 	//ת�ٷ���
		can0_send[0]=0x01;
		can0_send[1]=(ubyte)(RotateSpeed/256);	 //RotateSpeed
		can0_send[2]=(ubyte)(RotateSpeed%256);
		//�ٶȷ���
		can0_send[4]=0x02;
		can0_send[5]=(ubyte)(RotateSpeed/256);	//	 RotateSpeed
		can0_send[6]=(ubyte)(RotateSpeed%256);
	}
    else if(timeFlag%2==0){	//ʵʱ��Ҫ�󲻸�  2,4,6   50ms����һ��
		if(timeFlag%10==2){//2
			//SOC
			can0_send[0]=0x03;
			can0_send[1]=(ubyte)(BatSoc/256); //  BatSoc
			can0_send[2]=(ubyte)(BatSoc%256);
			//����¶�
			can0_send[4]=0x04;
			can0_send[5]=(ubyte)(MaxTemp/256);	 //	  MaxTemp
			can0_send[6]=(ubyte)(MaxTemp%256);
		}
		else if(timeFlag%10==4){//4
			//��ص�ѹ
			can0_send[0]=0x05;
			can0_send[1]=(ubyte)(BatVoltage/256); //  BatVoltage
			can0_send[2]=(ubyte)(BatVoltage%256);
			//��ص���
			can0_send[4]=0x06;
			can0_send[5]=(ubyte)(BatCurrent/256);	 //	  BatCurrent
			can0_send[6]=(ubyte)(BatCurrent%256);
		}
		else if(timeFlag%10==6){//6
			
			can0_send[0]=0x07;
			can0_send[1]=(ubyte)(ac_final%256);	//���� 	  0~100			 //	 ac_final
			can0_send[2]=(ubyte)(brAdFinal%256);	//ɲ�� 0~100		 //brAdFinal
			
			can0_send[4]=0x08;
			can0_send[5]=(ubyte)(allFlag%256);  //allFlag	0~128	   //	  allFlag
			can0_send[6]=(ubyte)(gear%256);  //gear		0~6			  //	  gear
		}
		else if(timeFlag%10==8){//8
			
			can0_send[0]=0x09;
			can0_send[1]=(ubyte)(mcFlag%256);	//���״̬��־		 //	   mcFlag

			
			can0_send[4]=0x0a;
			can0_send[5]=(ubyte)(motorTemp%256);  //����¶�	   //	 motorTemp
		}
		else if(timeFlag%10==0){//10
			
			can0_send[0]=0x0b;
			can0_send[1]=(ubyte)(mcuTemp%256);	//��ؿ������¶�	//	mcuTemp
		}
	 }

	for(i=0;i<8;i++){
		if(can0_send_old[i]!=can0_send[i]){
			repeat++;
			break;
		}
			
	}
	if(repeat!=0){//���ⷢ���ظ�����Ϣ����������ʹ��
		CAN_vLoadData(0,can0_send);	//0Ϊ��Ϣ��ţ�ADΪ���ݵ�ַ�����ȣ�ID֡��Dave�����á�
		CAN_vTransmit(0);
		repeat=0;
	}
    for(i=0;i<8;i++)							 
		can0_send_old[i]=can0_send[i];

  timeFlag=timeFlag>100?0:timeFlag;
}

ubyte control_period=0;
int finalSend_old=0;
int finalSend=0;
void sendToMc(){ //CAN0		 ��������3651

 										 			

//	can1_send2[2] = 0x64;		  			// 0xFC	 			��λ��ǰ
//	can1_send2[3] = 0x00;					// 0x3F  ʾ��50%	��λ�ں�

	if(control_period >=4)  //��������     20ms
		control_period = 0;
	control_period ++;

	if(control_period==4)		  //��������     20ms
	{
	//	
		/*
		�ٷֱ�	10%   20%   30%	   40%		50% 	60% 	70% 	80% 	90% 	99%	
		��Ȩֵ	1	  2		3	   4		5		6		7		8		9		10	 gearWeight
	*/	
		ac_final=acChangeLimit(ac_final); //���ż��ٱ仯���޷�  10 Ϊ0.5S
		ac_final=ac_final>99? 99:ac_final;
		ac_final=ac_final<0? 0:ac_final;
		finalSend=torqueChange();	 //	���͸�ת��ʱת�����

		
		/**************�޸��˴˴�***********/
		if(	(finalSend-	finalSend_old )>50&&finalSend>500){
			finalSend=finalSend_old+50;
		}
		finalSend_old=finalSend;
		


		finalSend=finalSend>999?999:finalSend;
		finalSend=finalSend<0?0:finalSend;
		can1_send2[2] = (ubyte)(finalSend % 256);		  			// 0x64	 			��λ��ǰ  ��������������λ��
		can1_send2[3] = (ubyte)(finalSend >> 8);					// 0x00  ʾ��10%	��λ�ں�  ��������������λ��
		if(driveReadyFlag ==1 & runFlag==1)
		{
			CAN_vLoadData(1,can1_send2);	//0Ϊ��Ϣ��ţ�D_commandΪ���ݵ�ַ�����ȣ��ڵ㣬ID֡��Dave�����á�
			CAN_vTransmit(1);
		}
		if(runFlag==0)
		{
			can1_send2[2] = 0;		  			// 0x64	 			��λ��ǰ  ��������������λ��
			can1_send2[3] = 0;					// 0x00  ʾ��10%	��λ�ں�  ��������������λ��
			CAN_vLoadData(1,can1_send2);	//0Ϊ��Ϣ��ţ�N_commandΪ���ݵ�ַ�����ȣ��ڵ㣬ID֡��Dave�����á�
			CAN_vTransmit(1);
		}
	} //�������ڿ��ƽ���
}

/*******************************************************************************************/
/*************************************���ż��ٱ仯���޷�*************************************/
/*********���룺��������         ���أ����ƺ����������************************************/
/*******************************************************************************************/
int ac_old=0;
int acChangeLimit(int ac){
	
 	if(ac-ac_old>AC_CHANGE_LIMIT)
		ac=ac_old+AC_CHANGE_LIMIT;
	
	 ac_old=ac;
 	 return ac;
 }	

 /*******************************************************************************************/
/*************************************���͸�ת��ʱת�����***********************************/
/*********���룺�������Ʊ仯�ʺ��ת��*******************************************************/
/*********���أ���ת��ʱ���𲽽���ת�غ�*****************************************************/
/*******************************************************************************************/

int torqueChange(){
	int torqueFinal =0,torqueLimit= 0;
	RotateSpeed=RotateSpeed<0?0:RotateSpeed;
	/*
	if (RotateSpeed>4500){
		torqueLimit = (int)(150 + 50 * (1 - ((1.0*RotateSpeed - 4500) / 300)));
		torqueLimit = torqueLimit<150 ? 150 : torqueLimit;
	}
	else if (RotateSpeed>4200){
		torqueLimit = (int)(200 + 150 * (1 - ((1.0*RotateSpeed - 4200) / 300)));	
	}
	else if (RotateSpeed>3500){
		torqueLimit = (int)(350 + (150 * (1 - ((1.0*RotateSpeed - 3500) / 700))));

	}
	else if (RotateSpeed>3000){
		torqueLimit = (int)(500 + (200 * (1 - ((1.0*RotateSpeed - 3000) / 500))));
	}
	else if (RotateSpeed>2000){
		torqueLimit = (int)(700 + (299 * (1 - ((1.0*RotateSpeed - 2000) / 1000))));
	}
	else torqueLimit = 999;	  */
	if (RotateSpeed>4500){
		torqueLimit = 200;
	}
	else if (RotateSpeed>4200){
		torqueLimit = (int)(100 + 100 * (1 - ((1.0*RotateSpeed - 4200) / 300)));
	}
	else if (RotateSpeed>3900){
		torqueLimit = (int)(200 + (150 * (1 - ((1.0*RotateSpeed - 3900) / 300))));
	}
	else if (RotateSpeed>3600){
		torqueLimit = (int)(350 + (150 * (1 - ((1.0*RotateSpeed - 3600) / 300))));
	}
	else if (RotateSpeed>3300){
		torqueLimit = (int)(500 + (100 * (1 - ((1.0*RotateSpeed - 3300) / 300))));
	}
	else if (RotateSpeed>3000){
		torqueLimit = (int)(600 + (100 * (1 - ((1.0*RotateSpeed - 3000) / 300))));
	}
	else if (RotateSpeed>2700){
		torqueLimit = (int)(700 + (50 * (1 - ((1.0*RotateSpeed - 2700) / 300))));

	}
	else if (RotateSpeed>2400){
		torqueLimit = (int)(750 + (100 * (1 - ((1.0*RotateSpeed - 2400) / 300))));
	}
	else if (RotateSpeed>2100){
		torqueLimit = (int)(850 + (50 * (1 - ((1.0*RotateSpeed - 2100) / 300))));
	}
	else if (RotateSpeed>1800){
		torqueLimit = (int)(900 + (25 * (1 - ((1.0*RotateSpeed - 1800) / 300))));
	}
	else if (RotateSpeed>1500){
		torqueLimit = (int)(925 + (25 * (1 - ((1.0*RotateSpeed - 1500) / 300))));
	}
	else if (RotateSpeed>1200){
		torqueLimit = (int)(950 + (50 * (1 - ((1.0*RotateSpeed - 1200) / 300))));
	}
	else torqueLimit = 999;
	torqueLimit = torqueLimit >(99*gearWeight)?(99*gearWeight):torqueLimit;
	torqueLimit = torqueLimit<0 ? 0 : torqueLimit;
	torqueFinal = (1.0*torqueLimit/100)*ac_final;
	
	
	return torqueFinal;						   
}
// USER CODE END
