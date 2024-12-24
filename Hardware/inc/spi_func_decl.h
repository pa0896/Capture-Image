#ifndef SPI_FUNC_DECL
#define SPI_FUNC_DECL

#include <stdint.h>
#include "stm32g0xx.h"
#include <stdio.h>
#include <stdbool.h>
#include "i2c_func_decl.h"

#define ARDUCHIP_TEST1 		0x00
#define FIFO_CLEAR_MASK		0x01
#define FIFO_START_MASK		0x02
#define ARDUCHIP_FIFO 		0x04
#define BURST_FIFO_READ		0x3C
#define SINGLE_FIFO_READ	0x3D
#define CS_LOW				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET)
#define CS_HIGH				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET)

bool check_camspi(void);
void flush_fifo(void);
void clear_fifo_flag(void);
void set_fifo_burst(void);
uint8_t read_fifo(void);
uint8_t spi_readwritebyte(uint8_t data);
void set_bit(uint8_t addr, uint8_t bit);
void clear_bit(uint8_t addr, uint8_t bit);
uint8_t read_reg(uint8_t addr);
void write_reg(uint8_t addr, uint8_t data);
uint8_t bus_read(uint8_t address);
uint8_t bus_write(uint8_t address, uint8_t value);
void start_capture(void);
uint8_t get_bit(uint8_t addr, uint8_t bit);
uint32_t read_fifo_length(void);
void debug_spi_func(uint8_t num);
void ov2640_capture(void);
void send_pic(uint8_t num);

#endif
