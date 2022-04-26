//
// Created by Administrator on 2020/3/26.
//

#ifndef TMP_I2CBUS_I2CBUS_MODULE_BASE_H
#define TMP_I2CBUS_I2CBUS_MODULE_BASE_H

#define I2C_SLAVE	0x0703
#define I2C_TENBIT	0x0704
#define I2C_SLAVE_FORCE	0x0706

#define I2C_ADDR 		 	0x78  //从机地址
#define I2C_ADDRV			0xc0  //从机地址
#define DATA_LEN 			2
#define I2C_SLAVE			0x0703
#define I2C_TENBIT			0x0704
#define I2C_SLAVE_FORCE	0x0706	/* Use this slave address, even if it is already in use by a driver! */

#define I2C_2631_A	0x20
#define I2C_2631_B 0x24

//#define I2C_1115_A		0x90
//#define I2C_1115_B 		0x92
//#define I2C_MUX_1			0x84
//#define I2C_MUX_2			0xb4
//#define I2C_RATE			0xe3
#define I2C_1115_A	0x90    //温度
#define I2C_1115_B  0x92    //绝压
#define I2C_1115_C  0x94    //差压
#define I2C_1115_D  0x96
#define I2C_MUX_1	0xaa
#define I2C_MUX_2	0x9a
#define I2C_MUX_3	0xba
#define I2C_RATE	0x83



extern int GiFd;
extern int GiFd2631;
int gpio_export(int pin);
int gpio_unexport(int pin);
int gpio_direction(int pin, int dir);
int gpio_write(int pin, int value);
int gpio_read(int pin);
int gpio_edge(int pin, int edge);


#endif //TMP_I2CBUS_I2CBUS_MODULE_BASE_H
