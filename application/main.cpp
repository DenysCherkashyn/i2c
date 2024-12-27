/**
 ******************************************************************************
 * @file           : main.cpp
 * @author         :
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 *
 *
 ******************************************************************************
 */

#include <i2c/i2c.h>
#include <stdint.h>
#include "stm32f1xx.h"


// Разрешить исключения.
//void __enable_irq(void);

// Запретить все исключения.
//void __disable_irq(void);

// Разрешить прерывание с номером IRQn,
// IRQn>=0 - только для внешних прерываний.
//void NVIC_EnableIRQ(IRQn_Type IRQn);

// Запретить прерывание с номером IRQn,
// IRQn>=0 - только для внешних прерываний.
//void NVIC_DisableIRQ(IRQn_Type IRQn);

//I2C2_ER_IRQHandler

std::unordered_map<uint8_t, uint8_t*> i2c_buff_it = {};
uint8_t r_data[4];
//uint8_t i2c_buff_pointer = 0;
I2C* i2c;
bool isFirstSkiped = false;

extern "C" void I2C2_EV_IRQHandler(void)
{

   // i2c_buff_pointer = (*(&i2c_buff_it + 1) - i2c_buff_it)-1;
    //i2c->slaveReadWrite(&i2c_buff_it, 1, true);
    //i2c->slaveWrite(&i2c_buff_it, 1, true);
   // i2c->slaveRead(r_data, 1, true);
  // i2c->slaveWrite(&r_data[2], 1, true);
    i2c->slaveReadWrite(r_data,1,true);
   // i2c_buff_pointer = (i2c_buff_pointer>0) ? (i2c_buff_pointer-1) : (*(&i2c_buff_it + 1) - i2c_buff_it);
}

int main(void)
{

	//uint8_t r_data[4];
	uint8_t s_data[4]= {0b00010001, 0b00100010, 0b00110011, 0b01000100};

	i2c_buff_it[1] = r_data;
	i2c_buff_it[2] = &r_data[1];
	i2c_buff_it[3] = &r_data[2];
	i2c_buff_it[4] = &r_data[3];
	r_data[2] = 0b01110111;
	i2c = I2C::getInstance(I2C2);
	NVIC_EnableIRQ(I2C2_EV_IRQn);
	__enable_irq();
	
	I2C* i2c1 = I2C::getInstance(I2C1);
	i2c1->masterWrite(0x02, s_data, 2);
	i2c1->masterRead(0x02, s_data, 3);
	//i2c1->masterRead(0b0100111, 0, s_data, 3);
	//i2c1->masterWrite(0x02, 2, s_data, 3);
//	++i2c_buff_it;
	//i2c1->masterRead(0x02, 8, s_data, 3);
	/* Loop forever */
	/*
	while(1){

	}
*/
	return 0;
}
