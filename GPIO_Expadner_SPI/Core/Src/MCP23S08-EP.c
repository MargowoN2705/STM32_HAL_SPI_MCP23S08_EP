#include"MCP23S08-EP.h"

#include "spi.h"


static void write_reg(uint8_t ADDR, uint8_t reg, uint8_t Data)
{
    uint8_t sendData[3] = {ADDR, reg, Data};
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
    if (HAL_SPI_Transmit(&hspi1, sendData, 3, 100) != HAL_OK) {
        Error_Handler();
    }
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}
static void MCP23S08_EP_Write_Reg (uint8_t reg, uint8_t Data)
{
	write_reg(0x40, reg, Data);
}

static uint8_t read_reg(uint8_t ADDR, uint8_t reg)
{
    uint8_t receiveData[2] = {ADDR, reg};
    uint8_t data = 0;

    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);

    if (HAL_SPI_Transmit(&hspi1, receiveData, 2, 100) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_SPI_Receive(&hspi1, &data, 1, 100) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

    return data;
}

static uint8_t  MCP23S08_EP_Read_Reg (uint8_t reg)
{
	uint8_t data = read_reg(0x41, reg);
	return data;


}

void MCP23S08_EP_pinMode(MCP23S08_EP_PIN GPx, MCP23S08_EP_PIN_STATE state)
{

    uint8_t iodir = MCP23S08_EP_Read_Reg(IODIR);

    switch (GPx)
    {
        case GP0: state == GPx_INPUT ? (iodir |= 1 << 0) : (iodir &= ~(1 << 0)); break;
        case GP1: state == GPx_INPUT ? (iodir |= 1 << 1) : (iodir &= ~(1 << 1)); break;
        case GP2: state == GPx_INPUT ? (iodir |= 1 << 2) : (iodir &= ~(1 << 2)); break;
        case GP3: state == GPx_INPUT ? (iodir |= 1 << 3) : (iodir &= ~(1 << 3)); break;
        case GP4: state == GPx_INPUT ? (iodir |= 1 << 4) : (iodir &= ~(1 << 4)); break;
        case GP5: state == GPx_INPUT ? (iodir |= 1 << 5) : (iodir &= ~(1 << 5)); break;
        case GP6: state == GPx_INPUT ? (iodir |= 1 << 6) : (iodir &= ~(1 << 6)); break;
        case GP7: state == GPx_INPUT ? (iodir |= 1 << 7) : (iodir &= ~(1 << 7)); break;
        default: break;

            return;
    }


    MCP23S08_EP_Write_Reg(IODIR, iodir);
}

void MCP23S08_EP_PULL_UP_CONFIG (MCP23S08_EP_PIN GPx, PULL_UP_RESISTHOR PULLx)
{
	uint8_t gppu = MCP23S08_EP_Read_Reg(GPPU);

	switch (GPx)
	{
			case GP0: PULLx == PULL_UP ? (gppu |= 1 << 0) : (gppu &= ~(1 << 0)); break;

	        case GP1: PULLx == PULL_UP ? (gppu |= 1 << 1) : (gppu &= ~(1 << 1)); break;

	        case GP2: PULLx == PULL_UP ? (gppu |= 1 << 2) : (gppu &= ~(1 << 2)); break;

	        case GP3: PULLx == PULL_UP ? (gppu |= 1 << 3) : (gppu &= ~(1 << 3)); break;

	        case GP4: PULLx == PULL_UP ? (gppu |= 1 << 4) : (gppu &= ~(1 << 4)); break;

	        case GP5: PULLx == PULL_UP ? (gppu |= 1 << 5) : (gppu &= ~(1 << 5)); break;

	        case GP6: PULLx == PULL_UP ? (gppu |= 1 << 6) : (gppu &= ~(1 << 6)); break;

	        case GP7: PULLx == PULL_UP ? (gppu |= 1 << 7) : (gppu &= ~(1 << 7)); break;

	        default : break ;
	        return;
	}

	MCP23S08_EP_Write_Reg(GPPU, gppu);
}

void MCP23S08_WRITE_PIN(MCP23S08_EP_PIN GPx, MCP23S08_EP_PIN_STATE_RS_STATUS SET_RESET)
{
    uint8_t iodir = MCP23S08_EP_Read_Reg(IODIR);


    if (iodir & (1 << GPx))
    {
        return;
    }


    uint8_t olat = MCP23S08_EP_Read_Reg(OLAT);


    switch (GPx)
    {
        case GP0:
            olat = (SET_RESET == GPx_SET) ? (olat | (1 << 0)) : (olat & ~(1 << 0));
            break;
        case GP1:
            olat = (SET_RESET ==  GPx_SET) ? (olat | (1 << 1)) : (olat & ~(1 << 1));
            break;
        case GP2:
            olat = (SET_RESET ==  GPx_SET) ? (olat | (1 << 2)) : (olat & ~(1 << 2));
            break;
        case GP3:
            olat = (SET_RESET ==  GPx_SET) ? (olat | (1 << 3)) : (olat & ~(1 << 3));
            break;
        case GP4:
            olat = (SET_RESET ==  GPx_SET) ? (olat | (1 << 4)) : (olat & ~(1 << 4));
            break;
        case GP5:
            olat = (SET_RESET ==  GPx_SET) ? (olat | (1 << 5)) : (olat & ~(1 << 5));
            break;
        case GP6:
            olat = (SET_RESET ==  GPx_SET) ? (olat | (1 << 6)) : (olat & ~(1 << 6));
            break;
        case GP7:
            olat = (SET_RESET ==  GPx_SET) ? (olat | (1 << 7)) : (olat & ~(1 << 7));
            break;
        default:
            return;
    }


    MCP23S08_EP_Write_Reg(OLAT, olat);
}


MCP23S08_EP_PIN_STATE_RS_STATUS MCP23S08_EP_READ_PIN(MCP23S08_EP_PIN GPx)
{
    uint8_t gpio = MCP23S08_EP_Read_Reg(GPIO);


    switch (GPx)
    {
        case GP0: return (gpio & (1 << 0)) ? GPx_SET : GPx_RESET;	break;
        case GP1: return (gpio & (1 << 1)) ? GPx_SET : GPx_RESET;	break;
        case GP2: return (gpio & (1 << 2)) ? GPx_SET : GPx_RESET;	break;
        case GP3: return (gpio & (1 << 3)) ? GPx_SET : GPx_RESET;	break;
        case GP4: return (gpio & (1 << 4)) ? GPx_SET : GPx_RESET;	break;
        case GP5: return (gpio & (1 << 5)) ? GPx_SET : GPx_RESET;	break;
        case GP6: return (gpio & (1 << 6)) ? GPx_SET : GPx_RESET;	break;
        case GP7: return (gpio & (1 << 7)) ? GPx_SET : GPx_RESET;	break;
        default: return GPx_RESET; break;
    }
}


HAL_StatusTypeDef MCP23S08_EP_Init (void)
{
    if (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY) {
        return HAL_ERROR;
    }
	  	MCP23S08_EP_Write_Reg(IODIR, 0x00); // Wszystkie piny jako wyjścia
	    MCP23S08_EP_Write_Reg(GPPU, 0x00);	// bez pullup'ow

	    if (MCP23S08_EP_Read_Reg(IODIR)!=0x00 || MCP23S08_EP_Read_Reg(GPPU) != 0x00)
	    {
	    	return HAL_ERROR;
	    }

	    return HAL_OK;
}

