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

static float temp_obj[4]{0};
static float temp_amb[4]{0};

extern "C" void app_main(){

	while(true)
    {

        i2c0.begin(SDA, SCL, 10000);
        i2c1.begin(SDA1, SCL1, 10000);

        uint16_t temp_addr;

        for (uint8_t i = 0x1; i <= uint8_t{4}; i++)
        {
            temp_addr = 0;

            MLX90614_GetSlaveAddr(((i%2U) == 0U) ? I2C_NUM_1 : I2C_NUM_0, uint8_t{i}, &temp_addr);
            MLX90614_GetTo(((i%2U) == 0U) ? I2C_NUM_1 : I2C_NUM_0, uint8_t{i}, &temp_obj[i-1U]);
            MLX90614_GetTa(((i%2U) == 0U) ? I2C_NUM_1 : I2C_NUM_0, uint8_t{i}, &temp_amb[i-1U]);
            // uint16_t eeData = 0;
            // MLX90614_DumpEE(((i%2U) == 0U) ? I2C_NUM_1 : I2C_NUM_0, uint8_t{i}, &eeData);


            if (temp_addr!=i)
            {
                // TODO error message
                temp_amb[i-1U] = -1;   
                temp_obj[i-1U] = -1;
            }
            ESP_LOGI(TAG,"Object %d's Temperature: %f\n", i, temp_obj[i-1U]);

        }

        ESP_LOGI("","\n");

        i2c0.close();
        i2c1.close();

        vTaskDelay(500);
    }
}