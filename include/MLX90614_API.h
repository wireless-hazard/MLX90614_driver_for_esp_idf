/**
 * @copyright (C) 2017 Melexis N.V.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef _MLX614_API_H_
#define _MLX614_API_H_
#include "esp_system.h"
#include "driver/i2c.h"


#ifdef __cplusplus
extern "C" {
#endif

    int MLX90614_DumpEE(i2c_port_t i2c_num, uint8_t slaveAddr, uint16_t *eeData);
    int MLX90614_GetTa(i2c_port_t i2c_num, uint8_t slaveAddr, float *ta);
    int MLX90614_GetTo(i2c_port_t i2c_num, uint8_t slaveAddr, float *to);
    int MLX90614_GetTo2(i2c_port_t i2c_num, uint8_t slaveAddr, float *to2);
    int MLX90614_GetIRdata1(i2c_port_t i2c_num, uint8_t slaveAddr, uint16_t *ir1);
    int MLX90614_GetIRdata2(i2c_port_t i2c_num, uint8_t slaveAddr, uint16_t *ir2);
    int MLX90614_GetSlaveAddr(i2c_port_t i2c_num, uint8_t slaveAddr, uint16_t *current_addr);
    int MLX90614_SetSlaveAddr(i2c_port_t i2c_num, uint8_t slaveAddr, uint16_t current_addr);
    int MLX90614_SetEEPROM_Reg(i2c_port_t i2c_num, uint16_t slaveAddr, uint16_t value);
    int MLX90614_GetEmissivity(i2c_port_t i2c_num, uint8_t slaveAddr, float *emissivity);
    int MLX90614_SetEmissivity(i2c_port_t i2c_num, uint8_t slaveAddr, float value);
    int MLX90614_GetFIR(i2c_port_t i2c_num, uint8_t slaveAddr, uint8_t *fir);
    int MLX90614_SetFIR(i2c_port_t i2c_num, uint8_t slaveAddr, uint8_t value);
    int MLX90614_GetIIR(i2c_port_t i2c_num, uint8_t slaveAddr, uint8_t *iir);
    int MLX90614_SetIIR(i2c_port_t i2c_num, uint8_t slaveAddr, uint8_t value);
    float MLX90614_TemperatureInFahrenheit(float temperature);
    int16_t MLX90614_ConvertIRdata(uint16_t ir);

#ifdef __cplusplus
}
#endif

#endif

