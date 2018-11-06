#include	"DataFlash.h"


extern __far const fal_descriptor_t fal_descriptor_str;
 fal_status_t FalStatus;
 stFlash	Flash;
 
 __far const fal_u08 *my_version_string;
 
 __near fal_request_t  request_pstr;
 
 

void	DataFlash_Init (void)
{
	Flash.Status = DF_STATUS_IDLE;
	Flash.wWriteLen = 0;
	Flash.ProcStatus = PS_STATUS_COMPLETE;
	FalStatus = FAL_Init((__far fal_descriptor_t*)&fal_descriptor_str );
	if(FalStatus == FAL_OK)//DataFlash_ErrorOccur();
	{
		my_version_string = FAL_GetVersionString();
		FAL_Open();
	}
}


BYTE	Data_Flash_Write (WORD wIndex,DWORD *data )
{
	static BYTE status = WRITE_BEGIN;
	if(status == WRITE_BEGIN)
	{
		request_pstr.data_u32 = *data;
		request_pstr.index_u16 = wIndex;
		request_pstr.command_enu = FAL_CMD_WRITE_WORD;
		FAL_Execute(&request_pstr);
		FAL_Handler();
		status = WRITE_WAIT;
		return WRITE_WAIT;
	}

	if(request_pstr.status_enu == FAL_BUSY)
	{
		FAL_Handler();
		return EREASE_WAIT;
	}
	else
	{
		status = EREASE_BEGIN;
		if(request_pstr.status_enu == FAL_OK)
		{
			return WRITE_END;
		}
		else
		{
			return WRITE_ERR;
		}
	}
	return WRITE_ERR;
}

BOOL	Data_Flash_Read (WORD wIndex,DWORD *buffer)
{
	// Read
	request_pstr.data_u32 = 0x00;
	request_pstr.index_u16 = wIndex;
	request_pstr.command_enu = FAL_CMD_READ_WORD;
	FAL_Execute(&request_pstr);
	if(request_pstr.status_enu == FAL_OK)
	{
		*buffer = request_pstr.data_u32;
		return	TRUE;
	}
	return	FALSE;
}

BYTE	Data_Flash_Erease (WORD wBlockIndex)
{
	static BYTE	status = EREASE_BEGIN;
	if(status == EREASE_BEGIN)
	{
		request_pstr.data_u32 = 0x00;
		request_pstr.index_u16 = wBlockIndex;
		request_pstr.command_enu = FAL_CMD_ERASE_BLOCK;
	
		FAL_Execute(&request_pstr);
		FAL_Handler();
		status = EREASE_WAIT;
		return EREASE_WAIT;
	}
	if(status == EREASE_WAIT)
	{
		if(request_pstr.status_enu == FAL_BUSY)
		{
			FAL_Handler();
			return EREASE_WAIT;
		}
		else
		{
			status = EREASE_BEGIN;
			if(request_pstr.status_enu == FAL_OK)
			{
				return EREASE_END;
			}
			else
			{
				return EREASE_ERR;
			}
		}
		
	}
	return EREASE_ERR;
}
	
void	DataFlash_ErrorOccur (void)
{
	
}