/*
|NOTICE
|-------------------------------------------------------------------------------
|                              
|   This software is the property of GUANGDA Technologies. 
|
|END----------------------------------------------------------------------------
|FILE INFORMATION START
|-------------------------------------------------------------------------------
|     File Name: 
|   Description: Implementation of the CAN driver
|Target systems: RRS
|    Target CPU: upd78F1828
|           IDE: CS+ V20200                           
|      Compiler: CC78k0r
|END----------------------------------------------------------------------------
|PROJECT INFORMATION START 
|-------------------------------------------------------------------------------
| Project Name: 
|
|  Description: 
|
|END----------------------------------------------------------------------------
|REVISION HISTORY
|-------------------------------------------------------------------------------
| Version        Date          Author              Description
| --------   -----------      ---------     ------------------------------------
| 00.01.00    2015-08-04                           first version
|-------------------------------------------------------------------------------
*/

#if defined (START_WITH_IF)
/*******************************************************************************
*   CAN Communication Stack START
*******************************************************************************/

/*******************************************************************************
*   CAN Driver START 
*******************************************************************************/
#elif defined (CAN_START_SEC_VAR_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CAN_START_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_STOP_SEC_VAR_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CAN_STOP_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_START_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CAN_START_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_START_SEC_CONST_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CAN_START_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_STOP_SEC_CONST_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CAN_STOP_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_START_SEC_PUBLIC_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CAN_START_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_STOP_SEC_PUBLIC_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CAN_STOP_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_START_SEC_PRIVATE_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CAN_START_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_STOP_SEC_PRIVATE_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CAN_STOP_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_START_SEC_ISR_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CAN_START_SEC_ISR_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_STOP_SEC_ISR_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CAN_STOP_SEC_ISR_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_START_SEC_APPL_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CAN_START_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CAN_STOP_SEC_APPL_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CAN_STOP_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
/*******************************************************************************
*   CAN Driver END 
*******************************************************************************/
 
/*******************************************************************************
*   CAN Interface START 
*******************************************************************************/
#elif defined (CANIF_START_SEC_VAR_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CANIF_START_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CANIF_STOP_SEC_VAR_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CANIF_STOP_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CANIF_START_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CANIF_START_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CANIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CANIF_START_SEC_CONST_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CANIF_START_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CANIF_STOP_SEC_CONST_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CANIF_STOP_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CANIF_START_SEC_PUBLIC_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CANIF_START_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CANIF_STOP_SEC_PUBLIC_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CANIF_STOP_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CANIF_START_SEC_PRIVATE_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CANIF_START_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CANIF_STOP_SEC_PRIVATE_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CANIF_STOP_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CANIF_START_SEC_APPL_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CANIF_START_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CANIF_STOP_SEC_APPL_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CANIF_STOP_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
/*******************************************************************************
*   CAN Interface END 
*******************************************************************************/

/*******************************************************************************
*   DCM START 
*******************************************************************************/
#elif defined (DCM_START_SEC_VAR_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  DCM_START_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (DCM_STOP_SEC_VAR_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  DCM_STOP_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (DCM_START_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  DCM_START_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (DCM_STOP_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  DCM_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (DCM_START_SEC_CONST_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  DCM_START_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (DCM_STOP_SEC_CONST_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  DCM_STOP_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (DCM_START_SEC_PUBLIC_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  DCM_START_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (DCM_STOP_SEC_PUBLIC_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  DCM_STOP_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (DCM_START_SEC_PRIVATE_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  DCM_START_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (DCM_STOP_SEC_PRIVATE_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  DCM_STOP_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (DCM_START_SEC_APPL_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  DCM_START_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (DCM_STOP_SEC_APPL_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  DCM_STOP_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
/*******************************************************************************
*   DCM END 
*******************************************************************************/



/*******************************************************************************
*   CANTP START 
*******************************************************************************/
#elif defined (CANTP_START_SEC_VAR_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CANTP_START_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CANTP_STOP_SEC_VAR_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CANTP_STOP_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CANTP_START_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CANTP_START_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CANTP_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CANTP_START_SEC_CONST_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CANTP_START_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CANTP_STOP_SEC_CONST_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CANTP_STOP_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (CANTP_START_SEC_PUBLIC_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CANTP_START_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CANTP_STOP_SEC_PUBLIC_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CANTP_STOP_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CANTP_START_SEC_PRIVATE_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CANTP_START_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CANTP_STOP_SEC_PRIVATE_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CANTP_STOP_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CANTP_START_SEC_APPL_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CANTP_START_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (CANTP_STOP_SEC_APPL_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CANTP_STOP_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
/*******************************************************************************
*   CANTP END 
*******************************************************************************/

/*******************************************************************************
*   CCP START 
*******************************************************************************/
#elif defined (CCP_START_SEC_VAR_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CCP_START_SEC_VAR_UNSPECIFIED 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_STOP_SEC_VAR_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CCP_STOP_SEC_VAR_UNSPECIFIED 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_START_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CCP_START_SEC_CONFIG_DATA_UNSPECIFIED 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_STOP_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CCP_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_START_SEC_CONST_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CCP_START_SEC_CONST_UNSPECIFIED 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_STOP_SEC_CONST_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CCP_STOP_SEC_CONST_UNSPECIFIED 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_START_SEC_PUBLIC_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CCP_START_SEC_PUBLIC_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_STOP_SEC_PUBLIC_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CCP_STOP_SEC_PUBLIC_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_START_SEC_PRIVATE_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CCP_START_SEC_PRIVATE_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_STOP_SEC_PRIVATE_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CCP_STOP_SEC_PRIVATE_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_START_SEC_ISR_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CCP_START_SEC_ISR_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_STOP_SEC_ISR_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CCP_STOP_SEC_ISR_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_START_SEC_APPL_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  CCP_START_SEC_APPL_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (CCP_STOP_SEC_APPL_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  CCP_STOP_SEC_APPL_CODE 
      /* Add #pragma code here */
  #endif
/*******************************************************************************
*   CCP END 
*******************************************************************************/


/*******************************************************************************
*   COM START 
*******************************************************************************/
#elif defined (COM_START_SEC_VAR_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  COM_START_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (COM_STOP_SEC_VAR_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  COM_STOP_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (COM_START_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  COM_START_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (COM_START_SEC_CONST_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  COM_START_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (COM_STOP_SEC_CONST_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  COM_STOP_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (COM_START_SEC_PUBLIC_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  COM_START_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (COM_STOP_SEC_PUBLIC_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  COM_STOP_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (COM_START_SEC_PRIVATE_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  COM_START_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (COM_STOP_SEC_PRIVATE_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  COM_STOP_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (COM_START_SEC_APPL_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  COM_START_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (COM_STOP_SEC_APPL_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  COM_STOP_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
/*******************************************************************************
*   COM END 
*******************************************************************************/

/*******************************************************************************
*   OSEKNM START 
*******************************************************************************/
#elif defined (OSEKNM_START_SEC_VAR_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  OSEKNM_START_SEC_VAR_UNSPECIFIED 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_STOP_SEC_VAR_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  OSEKNM_STOP_SEC_VAR_UNSPECIFIED 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_START_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  OSEKNM_START_SEC_CONFIG_DATA_UNSPECIFIED 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_STOP_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  OSEKNM_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_START_SEC_CONST_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  COSEKNM_START_SEC_CONST_UNSPECIFIED 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_STOP_SEC_CONST_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  COSEKNM_STOP_SEC_CONST_UNSPECIFIED 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_START_SEC_PUBLIC_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  OSEKNM_START_SEC_PUBLIC_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_STOP_SEC_PUBLIC_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  OSEKNM_STOP_SEC_PUBLIC_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_START_SEC_PRIVATE_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  OSEKNM_START_SEC_PRIVATE_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_STOP_SEC_PRIVATE_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  OSEKNM_STOP_SEC_PRIVATE_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_START_SEC_ISR_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  OSEKNM_START_SEC_ISR_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_STOP_SEC_ISR_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  OSEKNM_STOP_SEC_ISR_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_START_SEC_APPL_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  OSEKNM_START_SEC_APPL_CODE 
      /* Add #pragma code here */
  #endif
#elif defined (OSEKNM_STOP_SEC_APPL_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  OSEKNM_STOP_SEC_APPL_CODE 
      /* Add #pragma code here */
  #endif
/*******************************************************************************
*   OSEKNM END 
*******************************************************************************/

/*******************************************************************************
*   CAN Communication Stack END
*******************************************************************************/

/*******************************************************************************
*   LIN Communication Stack START
*******************************************************************************/

/*******************************************************************************
*   Lin Driver START 
*******************************************************************************/

#elif defined (LIN_START_SEC_VAR_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LIN_START_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (LIN_STOP_SEC_VAR_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LIN_STOP_SEC_VAR_UNSPECIFIED 
   /* Add #pragma code here */
  #endif
#elif defined (LIN_START_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LIN_START_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (LIN_STOP_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LIN_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (LIN_START_SEC_CONST_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LIN_START_SEC_CONST_UNSPECIFIED 
   /* Add #pragma code here */
  #endif
#elif defined (LIN_STOP_SEC_CONST_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LIN_STOP_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (LIN_START_SEC_PUBLIC_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LIN_START_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (LIN_STOP_SEC_PUBLIC_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LIN_STOP_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (LIN_START_SEC_PRIVATE_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LIN_START_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (LIN_STOP_SEC_PRIVATE_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LIN_STOP_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (LIN_START_SEC_ISR_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LIN_START_SEC_ISR_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (LIN_STOP_SEC_ISR_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LIN_STOP_SEC_ISR_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (LIN_START_SEC_APPL_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LIN_START_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (LIN_STOP_SEC_APPL_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LIN_STOP_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
/*******************************************************************************
*   Lin Driver END 
*******************************************************************************/

/*******************************************************************************
*   Lin Interface START 
*******************************************************************************/

#elif defined (LINIF_START_SEC_VAR_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LINIF_START_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (LINIF_STOP_SEC_VAR_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LINIF_STOP_SEC_VAR_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (LINIF_START_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LINIF_START_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (LINIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LINIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (LINIF_START_SEC_CONST_UNSPECIFIED)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LINIF_START_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (LINIF_STOP_SEC_CONST_UNSPECIFIED)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LINIF_STOP_SEC_CONST_UNSPECIFIED 
    /* Add #pragma code here */
  #endif
#elif defined (LINIF_START_SEC_PUBLIC_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LINIF_START_SEC_PUBLIC_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (LINIF_STOP_SEC_PUBLIC_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LINIF_STOP_SEC_PUBLIC_CODE 
     /* Add #pragma code here */
  #endif
#elif defined (LINIF_START_SEC_PRIVATE_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LINIF_START_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (LINIF_STOP_SEC_PRIVATE_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LINIF_STOP_SEC_PRIVATE_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (LINIF_START_SEC_APPL_CODE)
  #ifdef SECTION_STARTED
    #error "Section is not stopped"
  #else
    #define SECTION_STARTED
    #undef  LINIF_START_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
#elif defined (LINIF_STOP_SEC_APPL_CODE)
  #ifndef SECTION_STARTED
    #error "Section is not started"
  #else
    #undef  SECTION_STARTED
    #undef  LINIF_STOP_SEC_APPL_CODE 
    /* Add #pragma code here */
  #endif
/*******************************************************************************
*   Lin Interface END 
*******************************************************************************/


/*******************************************************************************
*   LIN Communication Stack END
*******************************************************************************/



#endif/* START_WITH_IF */
