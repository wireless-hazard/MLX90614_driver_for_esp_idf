/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "MLX90614_API.h"
#include "MLX90614_SMBus_Driver.h"

#define MLX90614_DEFAULT_ADDRESS 0x1 // default chip address(slave address) of MLX90614

#define MLX90614_SDA_GPIO GPIO_NUM_21 // sda for MLX90614
#define MLX90614_SCL_GPIO GPIO_NUM_22 // scl for MLX90614
#define MLX90614_VCC_GPIO 14 // vcc for MLX90614


void app_main()
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    // setup gpio for MLX90614
    gpio_pad_select_gpio(MLX90614_VCC_GPIO);
    gpio_set_direction(MLX90614_VCC_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(MLX90614_VCC_GPIO, 1);
    vTaskDelay(1000/portTICK_RATE_MS);
    MLX90614_SMBusInit(MLX90614_SDA_GPIO, MLX90614_SCL_GPIO, 50000); // sda scl and 50kHz
    // MLX90614_SMBusInit(GPIO_NUM_16, GPIO_NUM_17, 50000); // sda scl and 50kHz

    float to = 0; // temperature of object
    float ta = 0; // temperature of ambient
    uint16_t dumpInfo = 0;
    uint16_t eminem = 0;
    printf("Getting %d\n", MLX90614_GetSlaveAddr((uint16_t)MLX90614_DEFAULT_ADDRESS, &eminem));
    printf("Current address: %x\n", eminem);

    // printf("Setting %d\n", MLX90614_SetSlaveAddr((uint16_t)MLX90614_DEFAULT_ADDRESS, 0x4))   ;
    printf("Getting %d\n", MLX90614_GetSlaveAddr((uint16_t)0x2, &eminem));
    printf("Current address: %x\n", eminem);
    // loop
    while (1)
    {
        MLX90614_GetTo(MLX90614_DEFAULT_ADDRESS, &to);
        MLX90614_GetTa(MLX90614_DEFAULT_ADDRESS, &ta);
        printf("Temperature sensor 1:%lf %lf\r\n", to, ta);
        MLX90614_GetTo(0x2, &to);
        MLX90614_GetTa(0x2, &ta);
        printf("Temperature sensor 2:%lf %lf\r\n", to, ta);
        vTaskDelay(1000/portTICK_RATE_MS);
    }
}
