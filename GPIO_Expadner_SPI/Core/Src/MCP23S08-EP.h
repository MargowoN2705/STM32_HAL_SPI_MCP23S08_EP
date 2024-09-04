#pragma once
#include "stm32l4xx.h"

#define IODIR 		0x00
#define IPOL 		0x01
#define GPINTEN		0x02
#define DEFVAL 		0x03
#define INTCON 		0x04
#define IOCON 		0x05
#define GPPU 		0x06
#define INTF 		0x07
#define INTCAP 		0x08 // read only
#define GPIO		0x09
#define OLAT		0x0A


typedef enum
{
	GPx_OUTPUT,
	GPx_INPUT

}MCP23S08_EP_PIN_STATE;

typedef enum {
	GPx_SET,
	GPx_RESET

}MCP23S08_EP_PIN_STATE_RS_STATUS;

typedef enum {
	PULL_UP,
	NO_PULL_UP
}PULL_UP_RESISTHOR;

typedef enum
{
	GP0,
	GP1,
	GP2,
	GP3,
	GP4,
	GP5,
	GP6,
	GP7

}MCP23S08_EP_PIN;


void MCP23S08_EP_pinMode(MCP23S08_EP_PIN GPx, MCP23S08_EP_PIN_STATE state);

void MCP23S08_EP_PULL_UP_CONFIG (MCP23S08_EP_PIN GPx, PULL_UP_RESISTHOR PULLx);

void MCP23S08_WRITE_PIN(MCP23S08_EP_PIN GPx, MCP23S08_EP_PIN_STATE_RS_STATUS SET_RESET);

MCP23S08_EP_PIN_STATE_RS_STATUS MCP23S08_EP_READ_PIN(MCP23S08_EP_PIN GPx);

HAL_StatusTypeDef MCP23S08_EP_Init (void);
