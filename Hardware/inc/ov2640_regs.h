#ifndef OV2640_REGS_H
#define OV2640_REGS_H

#define OV2640_CHIPID_HIGH 	0x0A
#define OV2640_CHIPID_LOW 	0x0B

#include <stdint.h>

struct sensor_reg {
	uint16_t reg_addr;
	uint8_t value;
};

extern const struct sensor_reg OV2640_QVGA[];
extern const struct sensor_reg OV2640_JPEG_INIT[];
extern const struct sensor_reg OV2640_JPEG[];
extern const struct sensor_reg init1[];
extern const struct sensor_reg init2[];
extern const struct sensor_reg OV2640_YUV422[];
extern const struct sensor_reg OV2640_160x120_JPEG[];
extern const struct sensor_reg OV2640_176x144_JPEG[];
extern const struct sensor_reg OV2640_320x240_JPEG[];
extern const struct sensor_reg OV2640_352x288_JPEG[];
extern const struct sensor_reg OV2640_640x480_JPEG[];
extern const struct sensor_reg OV2640_800x600_JPEG[];
extern const struct sensor_reg OV2640_1024x768_JPEG[];
extern const struct sensor_reg OV2640_1280x1024_JPEG[];
extern const struct sensor_reg OV2640_1600x1200_JPEG[];
extern const unsigned char OV2640_CONTRAST0[];
extern const unsigned char OV2640_CONTRAST1[];
extern const unsigned char OV2640_CONTRAST2[];
extern const unsigned char OV2640_SATURATION0[];
extern const unsigned char OV2640_SATURATION1[];
extern const unsigned char OV2640_SATURATION2[];
extern const unsigned char OV2640_BRIGHTNESS0[];
extern const unsigned char OV2640_BRIGHTNESS1[];
extern const unsigned char OV2640_BRIGHTNESS2[];
extern const unsigned char OV2640_SPECIAL_EFFECTS_NORMAL[];
extern const unsigned char OV2640_SPECIAL_EFFECTS_ANTIQUE[];
extern const unsigned char OV2640_SPECIAL_EFFECTS_BLACK_NEGATIVE[];
extern const unsigned char OV2640_SPECIAL_EFFECTS_BLUISH[];
extern const unsigned char OV2640_SPECIAL_EFFECTS_BLACK[];
extern const unsigned char OV2640_SPECIAL_EFFECTS_NEGATIVE[];
extern const unsigned char OV2640_SPECIAL_EFFECTS_GREENISH[];
extern const unsigned char OV2640_SPECIAL_EFFECTS_REDDISH[];
extern const unsigned char OV2640_LIGHT_MODE_AUTO[];
extern const unsigned char OV2640_LIGHT_MODE_SUNNY[];
extern const unsigned char OV2640_LIGHT_MODE_CLOUDY[];
extern const unsigned char OV2640_LIGHT_MODE_OFFICE[];
extern const unsigned char OV2640_LIGHT_MODE_HOME[];
extern const unsigned char OV2640_SHARPNESS_LEVEL1[];
extern const unsigned char OV2640_SHARPNESS_LEVEL2[];
extern const unsigned char OV2640_SHARPNESS_LEVEL3[];
extern const unsigned char OV2640_SHARPNESS_LEVEL4[];
extern const unsigned char OV2640_SHARPNESS_LEVEL5[];
extern const unsigned char OV2640_SHARPNESS_LEVEL6[];
extern const unsigned char OV2640_SHARPNESS_MANUAL[];
extern const unsigned char OV2640_SHARPNESS_AUTO[];

#endif

