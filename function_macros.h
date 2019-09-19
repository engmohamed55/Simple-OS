/*
 * function_macros.h
 *
 *  Created on: 2019-09-16
 * Author: AbdElkader
 */

#ifndef FUNCTION_MACROS_H_
#define FUNCTION_MACROS_H_

#define Set_Bit(Register,Bit) Register|=(1<<Bit);
#define Clear_Bit(Register,Bit) Register&=~(1<<Bit);
#define Get_Bit(Register,Bit) (Register&(1<<Bit));
#define Toggle_Bit(Register,Bit) Register^=(1<<Bit);
#define BIT_IS_SET(Register,Bit) (Register&(1<<BIT))
#define BIT_IS_CLEAR(Register,Bit) (!(Register&(1<<BIT)))
#endif /* FUNCTION_MACROS_H_ */
