/*
 * spi_func_decl.c
 *
 *  Created on: Oct 8, 2024
 *      Author: ampellicht
 */

#include "spi_func_decl.h"

extern SPI_HandleTypeDef hspi2;
extern UART_HandleTypeDef huart2;

uint32_t sample_buffer;
uint8_t len = 0;
uint32_t length;
uint8_t Buf1[16000] = {0};
uint8_t *picbuf = 0;
int i = 0;

uint8_t rx_spi_buf;
uint8_t iden = 0;	// used to determine if the spi is reading or writing

uint8_t bus_read(uint8_t address){
	uint8_t value;
	CS_LOW;
	spi_readwritebyte(address);
	iden = 0;
	value = spi_readwritebyte(0x00);
	CS_HIGH;
	return value;
}


uint8_t bus_write(uint8_t address, uint8_t value){
	iden = 1;
	CS_LOW;
	delay_us(100);
	spi_readwritebyte(address);
	delay_us(100);
	spi_readwritebyte(value);
	delay_us(100);
	CS_HIGH;
	return 1;
}

uint8_t read_reg(uint8_t addr){
	uint8_t data;
	data = bus_read(addr&0x7F);
	return data;
}

void write_reg(uint8_t addr, uint8_t data){
	bus_write(addr|0x80,data);
}

uint8_t spi_readwritebyte(uint8_t data){
	uint8_t retry = 0;
	uint8_t ret_val = 0;
	while(__HAL_SPI_GET_FLAG(&hspi2,SPI_FLAG_TXE) == RESET){
		retry++;
		if(retry > 200)
			return 0;
	}
	HAL_SPI_Transmit(&hspi2,&data,1,100);
	retry = 0;
	while(__HAL_SPI_GET_FLAG(&hspi2, SPI_FLAG_BSY) == SET)
	{
		retry++;
		//debug_spi_func(retry);
		if(retry>200){
			return 0;
		}
	}
	if(!iden){
		HAL_SPI_Receive(&hspi2,&ret_val,1,HAL_MAX_DELAY);
		iden = 1;
		return ret_val;
	}
	else
		return 1;
}

void flush_fifo(void){
	uint8_t temp;
	write_reg(ARDUCHIP_FIFO,FIFO_CLEAR_MASK);
	temp = read_reg(ARDUCHIP_FIFO);
	debug_spi_func(temp);
}

void clear_fifo_flag(void){
	write_reg(ARDUCHIP_FIFO,FIFO_CLEAR_MASK);
}

uint8_t read_fifo(void){
	uint8_t data;
	data = bus_read(SINGLE_FIFO_READ);
	return data;
}

void start_capture(void){
	write_reg(ARDUCHIP_FIFO,FIFO_START_MASK);
}

uint8_t get_bit(uint8_t addr, uint8_t bit){
	uint8_t temp;
	temp = read_reg(addr);
	temp = temp & bit;
	return temp;
}

void set_bit(uint8_t addr, uint8_t bit){
	uint8_t temp;
	temp = read_reg(addr);
	write_reg(addr,temp|bit);
}

uint32_t read_fifo_length(void){
	uint32_t len1,len2,len3,len=0;
	len1 = read_reg(0x42);
	len2 = read_reg(0x43);
	len3 = read_reg(0x44) & 0x7f;
	len = ((len3 << 16) | (len2 << 8) | len1) & 0x07fffff;
	return len;
}

void clear_bit(uint8_t addr, uint8_t bit){
	uint8_t temp;
	temp = read_reg(addr);
	write_reg(addr,temp & (~bit));
}

void set_fifo_burst(void){
	uint8_t burst_fifo_read = 0x3C;
	uint8_t empty;
	HAL_SPI_TransmitReceive(&hspi2,&burst_fifo_read,&empty,1,HAL_MAX_DELAY);
}

void ov2640_capture(void){
	flush_fifo();
	clear_fifo_flag();
	start_capture();
	while(!get_bit(0x41,0x08));
	length = read_fifo_length();
	//implement something to dynamically change the buffers
	sample_buffer = (length >= 16000) ? 16000 : length;
	picbuf = Buf1;
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
	set_fifo_burst();
	HAL_SPI_Receive(&hspi2,picbuf,sample_buffer,HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
	for( i = 0 ; i < sample_buffer; i++)
			send_pic(Buf1[i]);
}

void send_pic(uint8_t num){
	char send[20];
	HAL_UART_Transmit(&huart2,(uint8_t *)send,sprintf(send,"%02x",num),100);
}

bool check_camspi(void){
	write_reg(0x07,0x80);
	HAL_Delay(100);
	write_reg(0x07,0x00);
	HAL_Delay(100);
	uint8_t temp;
	char *status[] = {
		"Error\n\r",
		"Success\n\r",
	};
	write_reg(ARDUCHIP_TEST1,0x55);
	temp = read_reg(ARDUCHIP_TEST1);
	if(temp != 0x55){
		//HAL_UART_Transmit(&huart2,(uint8_t *)status[0],strlen(status[0]),HAL_MAX_DELAY);
		return false;
	}
	else{
		//HAL_UART_Transmit(&huart2,(uint8_t *)status[1],strlen(status[1]),HAL_MAX_DELAY);
		return true;
	}
}

void debug_spi_func(uint8_t num){
	char res[8];
	int len = sprintf(res,"%u",num);
	HAL_UART_Transmit(&huart2,(uint8_t *)res,len,1);
}

