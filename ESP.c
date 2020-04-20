#include "esp.h"

void esp_config(void)
{
	USART_SendString_(USART1,"AT");
	USART_PutChar(USART1,0x0D);
	USART_PutChar(USART1,0x0A);
	DelayMs(200);
	
//	USART_SendString_(USART1,"AT+CWJAP_DEF=");
//	USART_PutChar(USART1,0x22);
//	USART_SendString_(USART1,"Tang 3");
//	USART_PutChar(USART1,0x22);
//	USART_SendString_(USART1,",");
//	USART_PutChar(USART1,0x22);
//	USART_SendString_(USART1,"168154727ESA");
//	USART_PutChar(USART1,0x22);
//	USART_PutChar(USART1,0x0D);
//	USART_PutChar(USART1,0x0A);
//	
//	DelayMs(5000);
}
void esp_rst(void)
{
	USART_SendString_(USART1,"AT+RST");
	USART_PutChar(USART1,0x0D);
	USART_PutChar(USART1,0x0A);
	DelayMs(5000);
}
void esp_connect(void)
{

}
void esp_mode(void)
{
	USART_SendString_(USART1,"AT+CWMODE=3");
	USART_PutChar(USART1,0x0D);
	USART_PutChar(USART1,0x0A);
	DelayMs(200);
}
void esp_tcp_connec_status(void)
{
	
}
	
void esp_clipsart(void);
void esp_send(char* data,char* length)
{
	USART_SendString_(USART1,"AT+CIPSEND=0,");
	USART_SendString_(USART1,length);
	USART_PutChar(USART1,0x0D);
	USART_PutChar(USART1,0x0A);
	DelayMs(200);
	USART_SendString_(USART1,data);
}
void esp_sendbuf(char* data);
void esp_tcp_close(void)
{
	USART_SendString_(USART1,"AT+CIPCLOSE");
	USART_PutChar(USART1,0x0D);
	USART_PutChar(USART1,0x0A);
	DelayMs(200);
}
void esp_cipserver(void)
{
	USART_SendString_(USART1,"AT+CIPSERVER=1,80");
	USART_PutChar(USART1,0x0D);
	USART_PutChar(USART1,0x0A);
	DelayMs(200);
}
void esp_cipmux(void)
{
	USART_SendString_(USART1,"AT+CIPMUX=1");
	USART_PutChar(USART1,0x0D);
	USART_PutChar(USART1,0x0A);
	DelayMs(200);
}
void esp_get_ip(void)
{
	USART_SendString_(USART1,"AT+CIFSR");
	USART_PutChar(USART1,0x0D);
	USART_PutChar(USART1,0x0A);
	DelayMs(200);
}
