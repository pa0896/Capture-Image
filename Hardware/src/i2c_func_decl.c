/*
 * i2c_func_decl.c
 *
 *  Created on: Oct 8, 2024
 *      Author: ampellicht
 */

#include "i2c_func_decl.h"


extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6;
extern I2C_HandleTypeDef hi2c1;

void delay_us(int us){
	__HAL_TIM_SET_COUNTER(&htim6,0);
	while(__HAL_TIM_GET_COUNTER(&htim6) < us);
}

uint8_t i2c_send(uint8_t addr, uint8_t reg, uint8_t *value){
	return HAL_I2C_Mem_Write(&hi2c1,addr,reg,1,value,1,100);
}

uint8_t i2c_receive(uint8_t addr, uint8_t reg, uint8_t *value){
	HAL_I2C_Mem_Read(&hi2c1,addr,reg,1,value,1,HAL_MAX_DELAY);
	return *value;
}

void ov2640_init(void){
	uint8_t values[2] = {0x01,0x80};
	i2c_send(DEV_ADDR_SEND,0xff,&values[0]);		//Set to page 1
	i2c_send(DEV_ADDR_SEND,0x12,&values[1]);	//Software reset
	HAL_Delay(10);  //100 ms
}

void ov2640_write(const struct sensor_reg *reg_vals){
	uint8_t value;
	while((reg_vals->reg_addr != 0xff) || (reg_vals->value != 0xff)){
		value = reg_vals->value;
		i2c_send(DEV_ADDR_SEND,reg_vals->reg_addr,&value);
		HAL_Delay(10);
		reg_vals++;
	}
}

void ov2640_config(const struct sensor_reg *config_vals){
	uint8_t value = config_vals->value;
	i2c_send(DEV_ADDR_SEND, config_vals->reg_addr, &value);
	HAL_Delay(10);
}

void ov2640_config_bulk(const struct sensor_reg *config_vals){
	uint8_t value;
	while((config_vals->reg_addr != 0xff) || (config_vals->value != 0xff)){
		value = config_vals->value;
		i2c_send(DEV_ADDR_SEND,config_vals->reg_addr,&value);
		HAL_Delay(10);
		config_vals++;
	}
}

void ov2640_specialeffects(const struct sensor_reg *special_vals){
	ov2640_config(special_vals);
}

void ov2640_simplewhitebalance(void){
	uint8_t data[2] = {0x00,0x10};
	i2c_send(DEV_ADDR_SEND,0xff,&data[0]);
	HAL_Delay(1);
}

void ov2640_advancedwhitebalance(void){
	uint8_t data[2] = {0x00,0x00};
	i2c_send(DEV_ADDR_SEND,0xff,&data[0]);
	HAL_Delay(1);
	i2c_send(DEV_ADDR_SEND,0xc7,&data[1]);
}

void ov2640_brightness(const struct sensor_reg *bright_vals){
	ov2640_config(bright_vals);
}

void ov2640_lightvals(const struct sensor_reg *light_vals){
	ov2640_config(light_vals);
}

void ov2640_saturation(const struct sensor_reg *sat_vals){
	ov2640_config(sat_vals);
}

void ov2640_contrast(const struct sensor_reg *contrast_vals){
	ov2640_config(contrast_vals);
}

void i2c_config(void){
	ov2640_init();
    ov2640_config_bulk(OV2640_JPEG_INIT);
	ov2640_config_bulk(OV2640_YUV422);
	ov2640_config_bulk(OV2640_JPEG);
	ov2640_config(init1);
	ov2640_config(init2);
	ov2640_config_bulk(OV2640_640x480_JPEG);
	//ov2640_config_bulk(OV2640_SHARPNESS_LEVEL6);
}

bool check_cami2c(void){
	uint8_t vid, pid;
	uint8_t value = 0x01;
	i2c_send(DEV_ADDR_SEND,0xff,&value);
	vid = i2c_receive(DEV_ADDR_RECV,OV2640_CHIPID_HIGH,&vid);
	pid = i2c_receive(DEV_ADDR_RECV,OV2640_CHIPID_LOW,&pid);
	if((vid != 0x26) && ((pid != 0x41) || (pid != 0x42))){
		return false;
	}
	else{
		return true;
	}
}



