/*-
 * OS.c
 *
*  Created on: 2019-09-16
 * Author: AbdElkader
 */

#include "OS.h"
#include "OS_cfg.h"
OS_Str_Tasks_Info_t Str_Array_Tasks[MAX_NUM_TASKS];
static uint8 u8_Tasks_Index=0u;
static uint8 u8_MAX_Priority=0u;
volatile static uint16 OS_TickCounter=0;
void OS_init(void)
{
	uint8 Array_Index;

	global_interrupt_enable();
	timer0_init();
	Set_OCR_Value(OS_TickTIme_ms);
	OS_SetCallBack(OS_Long_Term);
	for(Array_Index=0;Array_Index<MAX_NUM_TASKS;Array_Index++)
	{
		Str_Array_Tasks[Array_Index].OS_PTR_Function=NULL;
		Str_Array_Tasks[Array_Index].Task_Priority=0u;
		Str_Array_Tasks[Array_Index].Task_Periodicity=0u;
		Str_Array_Tasks[Array_Index].Task_Status=WAITING;

	}
}
OS_Status_t Create_Task(OS_PTR_Function OS_PTR_Function,uint8 Task_Priority,uint16 Task_Periodicity,uint16 Task_Temp_Periodicity)
{
	OS_Status_t Ret_Value;
	/*Check for first Null*/
	if(u8_Tasks_Index<MAX_NUM_TASKS)
	{
		Str_Array_Tasks[u8_Tasks_Index].OS_PTR_Function = OS_PTR_Function;
		Str_Array_Tasks[u8_Tasks_Index].Task_Priority = Task_Priority;
		Str_Array_Tasks[u8_Tasks_Index].Task_Periodicity = Task_Periodicity;
		Str_Array_Tasks[u8_Tasks_Index].Task_Status = WAITING;
		Str_Array_Tasks[u8_Tasks_Index].Task_Temp_Periodicity=Task_Temp_Periodicity;
		u8_Tasks_Index++;
		Ret_Value=OS_OK;
	}
	else
	{
		Ret_Value=OS_NOT_OK;
	}
	return Ret_Value;
}
OS_Status_t Delete_Task(OS_PTR_Function OS_PTR_Function)
{
	uint8 Array_Index;
	OS_Status_t Ret_Value=OS_NOT_OK;
	for(Array_Index=0;Array_Index<u8_Tasks_Index;Array_Index++)
	{
		if(Str_Array_Tasks[Array_Index].OS_PTR_Function==OS_PTR_Function)
		{
			Str_Array_Tasks[Array_Index].OS_PTR_Function=NULL;
			Str_Array_Tasks[Array_Index].Task_Priority=0u;
			Str_Array_Tasks[Array_Index].Task_Periodicity=0u;
			Str_Array_Tasks[Array_Index].Task_Status=DELETED;
			Str_Array_Tasks[Array_Index].Task_Temp_Periodicity=0u;


			Ret_Value=OS_OK;
		}
	}
	return Ret_Value;
}
extern void OS_Run(void)
{
	uint8 Array_Index;
	uint8 Priority_Index;
	while(1)
	{
		for(Array_Index = 0 ;Array_Index < u8_Tasks_Index ; Array_Index++)
		{
			if( Str_Array_Tasks[Array_Index].Task_Status == READY)
			{
				for(Priority_Index = 0 ; Priority_Index <= MAX_NUM_TASKS ; Priority_Index++)
				{
					if( Str_Array_Tasks[Array_Index].Task_Priority == Priority_Index )
					{
						Str_Array_Tasks[Array_Index].Task_Status = RUNNING;
						Str_Array_Tasks[Array_Index].OS_PTR_Function();
					}
				}
			}
		}
	}
}
void OS_Long_Term(void)
{
	uint8 Array_Index;
	for(Array_Index = 0 ;Array_Index < u8_Tasks_Index ; Array_Index++)
	{
		if( Str_Array_Tasks[Array_Index].Task_Temp_Periodicity == OS_TickCounter )
		{
			Str_Array_Tasks[Array_Index].Task_Temp_Periodicity = Str_Array_Tasks[Array_Index].Task_Periodicity + OS_TickCounter ;
			Str_Array_Tasks[Array_Index].Task_Status = READY;
			if( u8_MAX_Priority < Str_Array_Tasks[Array_Index].Task_Priority )
			{
				u8_MAX_Priority = Str_Array_Tasks[Array_Index].Task_Priority;
			}
		}
		else
		{
			Str_Array_Tasks[Array_Index].Task_Status = WAITING;
		}

	}
	OS_TickCounter++;
}
