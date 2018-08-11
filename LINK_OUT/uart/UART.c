#include "UART.h"
#include "stdio.h"

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

void UART1_Initial(u32 boad_rate)
{
USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
	
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	
GPIO_PinRemapConfig(AFIO_MAPR_USART1_REMAP, ENABLE);

	
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����������50MHz
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ������GPIOx�Ĵ���

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����������50MHz
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ������GPIOx�Ĵ���

USART_InitStructure.USART_BaudRate = boad_rate;//������
USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ����
USART_InitStructure.USART_StopBits = USART_StopBits_1;//��֡��β����1��ֹͣλ
USART_InitStructure.USART_Parity = USART_Parity_No;//��У��
USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//���ͺͽ��ն�ʹ��
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ��������ʧ��
USART_Init(USART1,&USART_InitStructure);

USART_Cmd(USART1, ENABLE);//ʹ��USART����

USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//ʹ��ָ����USART�ж�

NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
NVIC_Init(&NVIC_InitStructure);

}
