#ifndef __ESP_H
#define __ESP_H
 
#include "usart.h"
#include "stm32f10x.h"                  // Device header
#include "delay.h"

void esp_config(void);
void esp_rst(void);
void esp_connect(void);
void esp_mode(void);
void esp_tcp_connec_status(void);
void esp_clipsart(void);
void esp_send(char* data,char* length);
void esp_sendbuf(char* data);
void esp_tcp_close(void);
void esp_cipserver(void);
void esp_cipmux(void);
void esp_get_ip(void);
 
#endif
