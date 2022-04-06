#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "driver/gpio.h"

#include "MLX90614_SMBus_Driver.h"
#include "MLX90614_API.h"

#include "I2Cbus.hpp"

static const char* TAG = "SPIDER"; 

static constexpr gpio_num_t SDA = GPIO_NUM_21;
static constexpr gpio_num_t SCL = GPIO_NUM_22;

static constexpr gpio_num_t SDA1 = GPIO_NUM_25;
static constexpr gpio_num_t SCL1 = GPIO_NUM_33;

static float temp_obj{0};
static float temp_amb{0};

static constexpr uint8_t old_address = 0x5A; //Current address stored on the sensor
static constexpr uint8_t new_address = 0x01; //Address to be written on the sensor
static constexpr i2c_port_t current_bus = I2C_NUM_0; //Current i2c bus, could be I2C_NUM_0 or I2C_NUM_1

/** Steps to successfully write a new address on the temperature sensor
	This is a temporary solution

1 - set the old_address variable to the current value stored on the sensor
(if you don't know what it is, set old_address to 0x0).
2 - In the MLX90614_API.c file, make sure that in the MLX90614_SetSlaveAddr function, the
following line is uncommented MLX90614_SMBusWrite(i2c_num, slaveAddr, 0x2E, 0x0000)
3 - Write this program to the device.
4 - Wait until the error message stops being printed and a new message showing Success, appears.
5 - Comment the line MLX90614_SMBusWrite(i2c_num, slaveAddr, 0x2E, 0x0000) in the MLX90614_API.c file and
repeat steps 3 and 4.
6 - Unplug your device from the power supply (that being the USB from your computer or not).
7 - The new addres should be now written on your device. You can check using this same program, only change the
"#if 1" to "#if 0"
*/

extern "C" void app_main(){

    i2c0.begin(SDA, SCL, 10000);
    i2c1.begin(SDA1, SCL1, 10000);


    uint16_t temp_addr;

    temp_addr = 0;

    #if 0 //Writes new address to the temperature sensor
    MLX90614_SetSlaveAddr(current_bus, old_address, new_address);
    #endif
    #if 1 //Writes a new configuration into the 
    MLX90614_SetEEPROM_Reg(current_bus, 0x01, 0x9FB4);
    #endif
    ESP_LOGI("","Success!!\n");

    MLX90614_GetSlaveAddr(current_bus, new_address, &temp_addr);
    MLX90614_GetTo(current_bus, new_address, &temp_obj); //Gets the Object Temperature
    MLX90614_GetTa(current_bus, new_address, &temp_amb); //Gets the Ambient Temperature
    
    ESP_LOGI(TAG,"Object's Temperature: %f\n", temp_obj);


    i2c1.close();
    i2c0.close();
}