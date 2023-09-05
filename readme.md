This I2C drivers was tested on STM32 F103 (blue pill) controller.

It can configures and work with both I2C1 and I2C2 modules, existing on controller.

Master methods can work only from main process (no needs interrupts).
Slave methods can wark only from I2Cx interrupt function.

Class public methods:

/****************************************************************************/
I2C::getInstance(I2C_TypeDef * i2cType, I2C_Cfg_TypeDef* i2cCfg)
-----------------------------------------------------------------------------
- static class method that initiates I2C_TypeDef instance when necessary with I2C_Cfg_TypeDef
	user configs and returns it

Parameters: 
I2C_TypeDef * i2cType	- defines type i2c module  (I2С1, I2C2) stm32 controller you need to create/get  
I2C_Cfg_TypeDef* i2cCfg	- defines user configurations of  i2c module  (I2С1, I2C2) stm32 controller. It is 
							taken into account only when initializing i2c.						
Return:
I2C* - i2c-pointer to I2C_TypeDef type entity.
	
/****************************************************************************/
I2C::getInstance (I2C_TypeDef * i2cType)
-----------------------------------------------------------------------------
- static class method that initiates I2C_TypeDef instance when necessary with
user configs from i2c_conf.h file and returns it

Parameters: 
I2C_TypeDef * i2cType	- defines type i2c module  (I2С1, I2C2) stm32 controller you need to create/get  						
Return:
I2C* - i2c-pointer to I2C_TypeDef type entity.
	
/****************************************************************************/
enable ()
-----------------------------------------------------------------------------
- enabling i2c-module (PE bit set 1).

Parameters: void					
Return: void
	
/****************************************************************************/
disable ()
-----------------------------------------------------------------------------
- disabling i2c-module (PE bit set 0).

Parameters: void						
Return: void
	
/****************************************************************************/
isEnabled ()
-----------------------------------------------------------------------------
- indicates whether the i2c-module is enable (PE bit set 1).

Parameters: void						
Return:
true - if enabled;
false - if disabled;
	
/****************************************************************************/
isFailures ()
-----------------------------------------------------------------------------
- indicates whether some i2c failures was happened (AF, ARLO, BERR, TIMEOUT bits in SR1 register I2Cx module).

Parameters: void						
Return:
true - if happened;
false - if тще happened;
	
/****************************************************************************/
isStoped()
-----------------------------------------------------------------------------
- indicates whether current i2c-connection was stopped(STOPF bits in SR1 register I2Cx module).

Parameters: void						
Return:
true - if STOPF=1;
false - if STOPF=0;
	
/****************************************************************************/
isMasterWrite ()
isMasterRead ()
isSlaveWrite ()
isSlaveRead ()
-----------------------------------------------------------------------------
- indicates what I2Cx-module mode is active now.

Parameters: void						
Return:
true - the corresponding mode is active
false - the corresponding mode is not active
	
/****************************************************************************/
isMasterEmergencyStopped()
-----------------------------------------------------------------------------
- indicates whether current i2c-connection was emergency stopped by user(by method masterEmergencyStop()).

Parameters: void						
Return:
true - emergency stop was happened;
false - emergency stop wasn't happened;
	
/****************************************************************************/
masterWrite (uint16_t slaveAddr, uint16_t regAddr, uint8_t* buff, uint8_t dataSize)
-----------------------------------------------------------------------------
- sets i2c-connection in master write mode. Sets connection with slave device on slaveAddr-address
and writes datasize bytes data from buff to regAddr register of slave device.
If regAddr = 0xffff connection is made without regAddr register address transfering.
Runs in the current process thread, does not need to use interrupts

Parameters:
uint16_t slaveAddr - slave address
uint16_t regAddr - slave register address
uint8_t* buff - data source pointer		
uint8_t dataSize - size of data to write
Return: void
	
/****************************************************************************/
masterWrite (uint16_t slaveAddr, uint8_t* buff, uint8_t dataSize)
-----------------------------------------------------------------------------
- sets i2c-connection in master write mode. Sets connection with slave device on slaveAddr-address
and writes datasize bytes data from buff to slave device (without regAddr register address transfering).
The same regAddr = 0xffff. 
Runs in the current process thread, does not need to use interrupts

Parameters:
uint16_t slaveAddr - slave address
uint8_t* buff - data source pointer		
uint8_t dataSize - size of data to write
Return: void
	
/****************************************************************************/
masterRead (uint16_t slaveAddr, uint16_t regAddr, uint8_t* buff, uint8_t dataSize)
-----------------------------------------------------------------------------
- sets i2c-connection in master read mode. Sets connection with slave device on slaveAddr-address
and reads datasize bytes data to buff from regAddr register of slave device.
If regAddr = 0xffff connection is made without regAddr register address transfering.
Runs in the current process thread, does not need to use interrupts

Parameters:
uint16_t slaveAddr - slave address
uint16_t regAddr - slave register address
uint8_t* buff - data destination pointer		
uint8_t dataSize - size of data to read
Return: void
	
/****************************************************************************/
masterRead (uint16_t slaveAddr, uint8_t* buff, uint8_t dataSize)
-----------------------------------------------------------------------------
- sets i2c-connection in master read mode. Sets connection with slave device on slaveAddr-address
and reads datasize bytes data to buff from slave device(without regAddr register address transfering).
The same regAddr = 0xffff.
Runs in the current process thread, does not need to use interrupts

Parameters:
uint16_t slaveAddr - slave address
uint8_t* buff - data destination pointer		
uint8_t dataSize - size of data to read
Return: void

/****************************************************************************/
masterEmergencyStop()
-----------------------------------------------------------------------------
- run emergency stop algorithm

Parameters: void
Return: void
	
/****************************************************************************/
slaveWrite(uint8_t *buff, uint8_t dataSize,  bool doOneCycle = false)
-----------------------------------------------------------------------------
- sets i2c-connection in slave write mode. Starts when master send connection request with current slave address
device. It writes (transmits) datasize bytes data from buff source to master device. Can invokes once or in loop
till master device close connection. Must used after slaveRead() function!
Need to use into I2C interupt function:  voidI2C2_EV_IRQHandler(void)!
Using when no need to use register address in buff.

Parameters:
uint8_t* buff - data source pointer	
uint8_t dataSize - size of data stored in buff for cycle
doOneCycle - invokes once or in loop
Return: void
	
/****************************************************************************/
slaveWrite(uint8_t *buff,  bool doOneCycle = false)
-----------------------------------------------------------------------------
- sets i2c-connection in slave write mode. Starts when master send connection request with current slave address
device. It writes (transmits) 1 byte data from buff source to master device. Can invokes once or in loop
till master device close connection. Must used after slaveRead() function!
Need to use into I2C interupt function:  voidI2C2_EV_IRQHandler(void)!
Using when no need to use register address in buff.

Parameters:
uint8_t* buff - data source pointer	
doOneCycle - invokes once or in loop
Return: void
	
/****************************************************************************/
slaveRead(uint8_t *buff, uint8_t dataSize, bool doOneCycle = false)
-----------------------------------------------------------------------------
- sets i2c-connection in slave read mode. Starts when master send connection request with current slave address
device. It reads (recieve) datasize bytes data to buff from master device. Can invokes once or in loop
till master device close connection. Can used separately from slaveWrite() function.
Need to use into I2C interupt function:  voidI2C2_EV_IRQHandler(void)!
Using when no need to use register address in buff.

Parameters:
uint8_t* buff - data destination pointer	
uint8_t dataSize - size of data recieved in buff for cycle
doOneCycle - invokes once or in loop
Return: void
	
/****************************************************************************/
slaveRead(uint8_t *buff, bool doOneCycle = false)
-----------------------------------------------------------------------------
- sets i2c-connection in slave read mode. Starts when master send connection request with current slave address
device. It reads (recieve) 1 byte data to buff from master device. Can invokes once or in loop
till master device close connection. Can used separately from slaveWrite() function.
Need to use into I2C interupt function:  voidI2C2_EV_IRQHandler(void)!
Using when no need to use register address in buff.

Parameters:
uint8_t* buff - data destination pointer	
doOneCycle - invokes once or in loop
Return: void
	
/****************************************************************************/
slaveReadWrite (uint8_t *buff, uint8_t dataSize, bool doOneCycle = false)
-----------------------------------------------------------------------------
- sets i2c-connection in slave read/write mode. Starts when master send connection request with current slave address
device. It reads (recieve) dataSize bytes of data to buff from master device. Can invokes once or in loop
till master device close connection.
Need to use into I2C interupt function:  voidI2C2_EV_IRQHandler(void)!
Using when no need to use register address in buff.

Parameters:
uint8_t* buff - data source/destination pointer	
uint8_t dataSize - size of data recieved/transmitted in buff for cycle
doOneCycle - invokes once or in loop
Return: void
	
/****************************************************************************/
slaveReadWrite (std::unordered_map<uint8_t, uint8_t*>* buff,  uint8_t dataSize, bool doOneCycle = false)
-----------------------------------------------------------------------------
- sets i2c-connection in slave read/write mode. Starts when master send connection request with current slave address
device. It reads (recieve) dataSize bytes of data to buff from master device. Can invokes once or in loop
till master device close connection.
Need to use into I2C interupt function:  voidI2C2_EV_IRQHandler(void)!
Using when you need to use register address in buff like map structure: key=>value, where key = regAddr and 
value = a pointer to a memory location buff.

Parameters:
uint8_t* buff - data source/destination pointers map-structure	
uint8_t dataSize - size of data recieved/transmitted in buff for cycle
doOneCycle - invokes once or in loop
Return: void
	
/****************************************************************************/
slaveReadWrite (uint8_t *buff, bool doOneCycle = false)
-----------------------------------------------------------------------------
- sets i2c-connection in slave read/write mode. Starts when master send connection request with current slave address
device. It reads (recieve) 1 byte of data to buff from master device. Can invokes once or in loop
till master device close connection.
Need to use into I2C interupt function:  voidI2C2_EV_IRQHandler(void)!
Using when no need to use register address in buff.

Parameters:
uint8_t* buff - data source/destination pointer	
doOneCycle - invokes once or in loop
Return: void
	
/****************************************************************************/
slaveReadWrite (std::unordered_map<uint8_t, uint8_t*>* buff,  1, bool doOneCycle = false)
-----------------------------------------------------------------------------
- sets i2c-connection in slave read/write mode. Starts when master send connection request with current slave address
device. It reads (recieve) 1 byte of data to buff from master device. Can invokes once or in loop
till master device close connection.
Need to use into I2C interupt function:  voidI2C2_EV_IRQHandler(void)!
Using when you need to use register address in buff like map structure: key=>value, where key = regAddr and 
value = a pointer to a memory location buff.

Parameters:
uint8_t* buff - data source/destination pointers map-structure	
doOneCycle - invokes once or in loop
Return: void
	
/****************************************************************************/

	