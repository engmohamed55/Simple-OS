/*
 * OS.h
 *
 *  Created on: 2019-09-16
 *  Author: AbdElkader
 */

#ifndef OS_H_
#define OS_H_
/**************************************************************************
 * 				            Included files							      *
 *************************************************************************/
#include "standard_types.h"
#include "DIO_operations.h"
#include "function_macros.h"
#include "Memory_map.h"
#include "Timer0_registers.h"

typedef void (*OS_PTR_Function)(void);
/**************************************************************************
 * 				            User Defined types							  *
 *************************************************************************/
typedef enum{
	READY,
	RUNNING,
	WAITING,
	DELETED
}OS_Enum_Task_Status_t;
typedef enum{
OS_OK,
OS_NOT_OK
}OS_Status_t;
typedef struct{
	OS_PTR_Function OS_PTR_Function;
	OS_Enum_Task_Status_t Task_Status;
	uint16 Task_Periodicity;
	uint8 Task_Priority;
	uint16 Task_Temp_Periodicity;
}OS_Str_Tasks_Info_t;
/**************************************************************************
 * Function Name : OS_init
 *
 * Description	 : Set Tick time and initilze tasks buffer
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
extern void OS_init(void);
/**************************************************************************
 * Function Name : Create_Task
 *
 * Description	 : Creating Tasks and assign it in the buffer
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
OS_Status_t Create_Task(OS_PTR_Function OS_PTR_Function,uint8 Task_Priority,uint16 Task_Periodicity,uint16 Task_Temp_Periodicity);
/**************************************************************************
 * Function Name : Delete_Task
 *
 * Description	 : Deleting Tasks and removing them from buffer
 *
 * INPUTS		 : Pointer to function , Task priority ,Task periodicity
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
extern OS_Status_t Delete_Task(OS_PTR_Function OS_PTR_Function);
/**************************************************************************
 * Function Name : OS_Run
 *
 * Description	 : Running the scheduler
 *
 * INPUTS		 : pointer to function
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
extern void OS_Run(void);
/**************************************************************************
 * Function Name : OS_Long_Term
 *
 * Description	 : Callback function to update satus will be called from
 *
 * INPUTS		 : void
 *
 * OUTPUTS 		 : void
 *
 * Return		 : void
 **************************************************************************/
extern void OS_Long_Term(void);

#endif /* OS_H_ */
