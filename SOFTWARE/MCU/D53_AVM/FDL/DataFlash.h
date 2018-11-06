#ifndef		_DATAFLASH_H_
#define		_DATAFLASH_H_

#include	"cpu.h"
#include	"fdl.h"
#include	"fdl_types.h"
#include	"fdl_descriptor.h"

#define		FS_IDLE		0
#define		FS_WRITE	1
#define		FS_READ		2
#define		FS_EREASE	3

#define		DTC_FLAG_INDEX	511
#define		DTC_START_INDEX 0
#define		DID_F18C_INDEX  512
#define		DID_F190_INDEX  1024

#define		DF_STATUS_IDLE			0
#define		DF_STATUS_WRITE_DTC		1
#define		DF_STATUS_WRITE_DID_F190	2
#define		DF_STATUS_WRITE_DID_F010	3
#define		DF_STATUS_WRITE_DID_F18C	4
#define	        DF_STATUS_WRITE_DID_F1FA        5
#define	        DF_STATUS_WRITE_DID_F1A2        6

#define		PS_STATUS_COMPLETE	0
#define		PS_STATUS_EREAE_FLASH	1
#define		PS_STATUS_WRITE_DATA	2

#define		EREASE_BEGIN	0
#define		EREASE_WAIT	1
#define		EREASE_END	2
#define		EREASE_ERR	3

#define		WRITE_BEGIN	0
#define		WRITE_WAIT	1
#define		WRITE_END	2
#define		WRITE_ERR	3

typedef		struct
{
	BYTE	Status;			// Operation status
	BYTE	ProcStatus;		// Status of writting data flash
	WORD	wWriteLen;		// The length of data need to be written
	BYTE	*pData;			// pointer to the data buffer
}stFlash;

extern	stFlash	Flash;
void	DataFlash_Init (void);
BYTE	Data_Flash_Write (WORD wIndex,DWORD *data );
BOOL	Data_Flash_Read (WORD wIndex,DWORD *buffer);
BYTE	Data_Flash_Erease (WORD wBlockIndex);
void	DataFlash_ErrorOccur (void);
#endif