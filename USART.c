
#include "usart.h"
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "CRC.h"

u8 start_reciev_massage =0;
u8 flag_process_massage =0;
u8 lenght_sms					 =0;
char messages[80] = "80";
uint8_t id = 0;
uint8_t cmd = 0;

void USART_Config(USART_TypeDef* USARTx,uint32_t baud)
{
	GPIO_InitTypeDef	GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	
	if(USARTx==USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);

		/* Configure USARTy Rx as input floating */
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* Configure USARTy Tx as alternate function push-pull */
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOA, &GPIO_InitStruct);


		/* Initialize USART */
		USART_InitStructure.USART_BaudRate = baud;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		/* Configure USART1 */
		USART_Init(USART1, &USART_InitStructure);

		/* Enable USART1 Receive and Transmit interrupts */
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

		/* Enable the USART1 */
		USART_Cmd(USART1, ENABLE);

		/* Configure the NVIC Preemption Priority Bits */  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

		/* Enable the USARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	
	
	if(USARTx==USART2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
		/* Configure USARTy Rx as input floating */
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* Configure USARTy Tx as alternate function push-pull */
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOA, &GPIO_InitStruct);


		/* Initialize USART */
		USART_InitStructure.USART_BaudRate = baud;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		/* Configure USART2 */
		USART_Init(USART2, &USART_InitStructure);

		/* Enable USART2 Receive and Transmit interrupts */
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

		/* Enable the USART2 */
		USART_Cmd(USART2, ENABLE);

		/* Configure the NVIC Preemption Priority Bits */  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

		/* Enable the USARTy Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	
}


void USART_PutChar(USART_TypeDef* USARTx,char c)
{
	// Wait until transmit data register is empty
	while (!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));
	// Send a char using USART2
	USART_SendData(USARTx, c);
}


void USART_SendString_(USART_TypeDef* USARTx, char *s)
{
	// Send a string
	
			while (*s)
		{
			USART_PutChar(USARTx,*s++);
		}
}
void USART1_IRQHandler(void)
{
	char str[80]="";
	unsigned char dat;

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // Ngat nhan USART_IT_RXNE duoc kich hoat
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE) ;
		dat = USART_ReceiveData(USART1);	// Doc du lieu
		
		if(start_reciev_massage== 1)
		{
			if(flag_process_massage == 0)
			{
				if (dat == '#')	// end message
				{
					flag_process_massage = 1;
				}
				else
				{
					lenght_sms++;
					sprintf(str, "%c",dat);
					strcat(messages, str);
				}
			}
		}
		else if(dat == '$')//Receiv start message
		{
			start_reciev_massage=1;
			sprintf(messages,"");
			memset(messages,NULL,80);
		}
	}
}

void USART2_IRQHandler(void)
{
	char str[80]="";
	unsigned char dat;

	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // Ngat nhan USART_IT_RXNE duoc kich hoat
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE) ;
		dat = USART_ReceiveData(USART2);	// Doc du lieu
		
		if(start_reciev_massage== 1)
		{
			if(flag_process_massage == 0)
			{
				if (dat == '#')	// end message
				{
					flag_process_massage = 1;
				}
				else
				{
					lenght_sms++;
					sprintf(str, "%c",dat);
					strcat(messages, str);
				}
			}
		}
		else if(dat == '$')//Receiv start message
		{
			start_reciev_massage=1;
			sprintf(messages,"");
			memset(messages,NULL,80);
		}
	}
}

int8_t _sms_process(char * msg, uint8_t len)
{
//		uint8_t crc_cal = 0;
//    uint8_t crc_read = 0;
    char * p[MAX_FIELD];
 //  uint8_t crc_cal = 0;
 //   uint8_t crc_read = 0;
    uint8_t count = 0;
    uint8_t count_field = 0;

    /* gan con tro NULL truoc khi su dung */
    for (count = 0; count < MAX_FIELD; count++)
        p[count] = NULL;
    /* Tim so dau phay */
    count = 0;
    count_field = 1;
    /* Gan con tro dau tien */
    p[0] = (char *) & msg[0];
    /* Lay crc truong cmd gan vao con tro p */
    while (count < len - 1)
    {
        if (msg[count] == ',' && ((char *) &msg[count + 1]) != NULL)
        {
            /* Gan con tro */
            p[count_field] = (char *) & msg[count + 1];
            count_field++;
        }
        count++;
    }

//    /* Tinnh crc */
//    crc_cal = Cal_CRC8((uint8_t *) p[0],(uint16_t) (p[count_field - 1] - p[0] - 1));
//    /* crc doc duoc */
//    crc_read = atoi(p[count_field - 1]);
//    /* So sanh 2 crc */
//    if (crc_read != crc_cal)
//    {
//      return 1;
//    }
    /* tach truong du lieu (thay dau , bang NULL) */
    for (count = 1; count < count_field; count++)
    {
      * (p[count] - 1) = NULL;
    }
		
    /* Lay id */
    id = atoi(p[0]);
		
    /* Lay cmd */
    cmd = atoi(p[1]);
		
		action();
		return 1;
}

void process_message_master(void)
{
	u8 temp_complete=0;
	if(flag_process_massage == 1)
	{
		temp_complete = _sms_process(messages,lenght_sms);
		if(temp_complete == 1)
		{
			flag_process_massage = 0;
			start_reciev_massage = 0;
			lenght_sms					 = 0;
			memset(messages,NULL,80);
		}
	}
}

void action(void)
{
	switch (id)
	{
		case 0:
			switch (cmd)
			{
				case 1:
					return_status1();// return trang hoat dong cua thiet bi 1
					U2_return_status1();
					break;
				case 2:
					return_status2();// return trang hoat dong cua thiet bi 2
					U2_return_status2();
					break;
				
			}
			break;
			
		case 1:
			switch (cmd)
			{
				case 1:
					GPIO_SetBits(GPIOD,GPIO_Pin_0);
					break;
				case 0:
					GPIO_ResetBits(GPIOD,GPIO_Pin_0);
					break;
			}
			break;
		case 2:
			switch (cmd)
			{
				case 1:
					GPIO_SetBits(GPIOD,GPIO_Pin_6);
					break;
				case 0:
					GPIO_ResetBits(GPIOD,GPIO_Pin_6);
					break;
			}
			break;
//		case 3:
//			switch (cmd)
//			{
//				case 1:
//					GPIO_SetBits(GPIOD,GPIO_Pin_0);
//					break;
//				case 0:
//					GPIO_ResetBits(GPIOD,GPIO_Pin_0);
//					break;
//			}
//			break;
//		case 4:
//			switch (cmd)
//			{
//				case 1:
//					GPIO_SetBits(GPIOD,GPIO_Pin_0);
//					break;
//				case 0:
//					GPIO_ResetBits(GPIOD,GPIO_Pin_0);
//					break;
//			}
//			break;
//		case 5:
//			switch (cmd)
//			{
//				case 1:
//					GPIO_SetBits(GPIOD,GPIO_Pin_0);
//					break;
//				case 0:
//					GPIO_ResetBits(GPIOD,GPIO_Pin_0);
//					break;
//			}
//			break;
//			
			// Ngat nguon
		case 6:
			switch (cmd)
			{
				case 1:
					GPIO_SetBits(GPIOB,GPIO_Pin_7);
					break;
				case 0:
					GPIO_ResetBits(GPIOB,GPIO_Pin_7);
					break;
			}
			break;
		case 7:
			switch (cmd)
			{
				case 1:
					GPIO_SetBits(GPIOE,GPIO_Pin_1);
					break;
				case 0:
					GPIO_ResetBits(GPIOE,GPIO_Pin_1);
					break;
			}
			break;
//		case 8:
//			switch (cmd)
//			{
//				case 1:
//					GPIO_SetBits(GPIOD,GPIO_Pin_0);
//					break;
//				case 0:
//					GPIO_ResetBits(GPIOD,GPIO_Pin_0);
//					break;
//			}
//			break;
//			
//		case 9:
//			switch (cmd)
//			{
//				case 1:
//					GPIO_SetBits(GPIOD,GPIO_Pin_0);
//					break;
//				case 0:
//					GPIO_ResetBits(GPIOD,GPIO_Pin_0);
//					break;
//			}
//			break;
//			
//			case 10:
//			switch (cmd)
//			{
//				case 1:
//					GPIO_SetBits(GPIOD,GPIO_Pin_0);
//					break;
//				case 0:
//					GPIO_ResetBits(GPIOD,GPIO_Pin_0);
//					break;
//			}
//			break;
	}
			
}

void return_status1(void)
{
		if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_0)==0)
		{

			USART_SendString_(USART1,"AT+CIPSEND=0,");
			USART_PutChar(USART1,'5');
			USART_PutChar(USART1,0x0D);
			USART_PutChar(USART1,0x0A);
			DelayMs(100);
			USART_SendString_(USART1,"$1,0#");

		}
		else
		{
			USART_SendString_(USART1,"AT+CIPSEND=0,");
			USART_PutChar(USART1,'5');
			USART_PutChar(USART1,0x0D);
			USART_PutChar(USART1,0x0A);
			DelayMs(100);
			USART_SendString_(USART1,"$1,1#");
		}		
}

void return_status2(void)
{
			if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_6)==0)
		{
			USART_SendString_(USART1,"AT+CIPSEND=0,");
			USART_PutChar(USART1,'5');
			USART_PutChar(USART1,0x0D);
			USART_PutChar(USART1,0x0A);
			DelayMs(100);
			USART_SendString_(USART1,"$2,0#");
		}
		else
		{
			USART_SendString_(USART1,"AT+CIPSEND=0,");
			USART_PutChar(USART1,'5');
			USART_PutChar(USART1,0x0D);
			USART_PutChar(USART1,0x0A);
			DelayMs(100);
			USART_SendString_(USART1,"$2,1#");
		}
}

void U2_return_status1(void)
{
		if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_0)==0)
		{
			USART_SendString_(USART2,"$1,0#");

		}
		else
		{
			USART_SendString_(USART2,"$1,1#");
		}		
}

void U2_return_status2(void)
{
			if(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_6)==0)
		{
			USART_SendString_(USART2,"$2,0#");
		}
		else
		{
			USART_SendString_(USART2,"$2,1#");
		}
}
