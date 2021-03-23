/**
  ******************************************************************************
  * File Name          : sdram.c
  * Description        : .
  * Author             : CSY
  * Date               : 2021年3月22日
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "sdram.h"

/* Send command to SDRAM. */
uint8_t SDRAM_Send_CMD(uint8_t bank_num, uint8_t cmd, uint8_t refresh, uint16_t regval)
{
  uint32_t target_bank = 0;
  FMC_SDRAM_CommandTypeDef Command;

  if ( 0 == bank_num )
  {
    target_bank = FMC_SDRAM_CMD_TARGET_BANK1;
  }
  else
  {
    if ( 1 == bank_num )
    {
      target_bank = FMC_SDRAM_CMD_TARGET_BANK2;
    }
  }
  Command.CommandMode            = cmd;
  Command.CommandTarget          = target_bank;
  Command.AutoRefreshNumber      = refresh;
  Command.ModeRegisterDefinition = regvel;

  if ( HAL_SDRAM_SendCommand( &hsdram, &Command, 0x1000 ) == HAL_OK )
  {
    return 0;
  }
  else
    return 1;
}

/* Send SDRAM Init Sequence. */
void SDRAM_Init_Sequence( SDRAM_HandleTypeDef *hsdram )
{
  uint32_t temp = 0;

  SDRAM_Send_CMD(0, FMC_SDRAM_CMD_CLK_ENABLE, 1, 0);
  HAL_Delay(500);
  SDRAM_Send_CMD(0, FMC_SDRAM_CMD_PALL, 1, 0);
  SDRAM_Send_CMD(0, FMC_SDRAM_CMD_AUTOREFRESH_MODE, 8, 0);

  temp = ( uint32_t ) SDRAM_MODEREG_BURST_LENGTH_1 |
                      SDARM_MODEREG_BURST_TYPE_SEQUENTIAL |
                      SDRAM_MODEREG_CAS_LATENCY_3 |
                      

  SDRAM_Send_CMD(0, FMC_SDRAM_CMD_LOAD_MODE, 1, temp);
}

void FMC_SDRAM_WriteBuffer( uint8_t *pBuffer, uint32_t WriteAddr, uint32_t number )
{
	for ( ; number != 0 ; number--) {
		*( uint8_t* ) (Bank5_SDRAM_ADDR + WriteAddr ) = *pBuffer;
		WriteAddr++;
		pBuffer++;
	}
}

void FMC_SDRAM_ReadBuffer( uint8_t *pBuffer, uint32_t ReadAddr, uint32_t number )
{
	for (; number !=0 ; number-- ) {
		*pBuffer++ = *(uint8_t*)( Bank5_SDRAM_ADDR + ReadAddr );
		ReadAddr++;
	}
}

/**
  * @}
  */


/************************************END OF FILE*******************************/

