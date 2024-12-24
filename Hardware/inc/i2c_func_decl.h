#ifndef I2C_FUNC_DECL
#define I2C_FUNC_DECL

#include <stdint.h>
#include <stdbool.h>
#include <stm32g0xx.h>
#include "ov2640_regs.h"
#include "string.h"

#define OV2640_CHIPID_HIGH 	0x0A
#define OV2640_CHIPID_LOW 	0x0B
#define I2C_DELAY			1
#define DEV_ADDR_SEND		0x60
#define DEV_ADDR_RECV		0x61

void ov2640_init(void);
uint8_t i2c_send(uint8_t addr, uint8_t reg, uint8_t *value);
uint8_t i2c_receive(uint8_t addr, uint8_t reg, uint8_t *value);
void i2c_config(void);
bool check_cami2c(void);
void ov2640_write(const struct sensor_reg *reg_vals);
void ov2640_config(const struct sensor_reg *config_vals);
void ov2640_config_bulk(const struct sensor_reg *config_vals);
void ov2640_specialeffects(const struct sensor_reg *sensor_vals);
void ov2640_simplewhitebalance(void);
void ov2640_advancedwhitebalance(void);
void ov2640_brightness(const struct sensor_reg *bright_vals);
void ov2640_lightmode(const struct sensor_reg *light_vals);
void ov2640_saturation(const struct sensor_reg *sat_vals);
void ov2640_contrast(const struct sensor_reg *contrast_vals);
void delay_us(int us);

#endif

