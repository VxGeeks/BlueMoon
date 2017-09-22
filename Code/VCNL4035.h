#ifndef VCNL4035_H
#define VCNL4035_H

typedef unsigned char uint8_t;

#define VCNL4035_I2C_ADDR 0x60




#define VNCL4035_ALS_CONF_ADDR  0x00
#define VNCL4035_ALS_THDH_ADDR  0x01
#define VNCL4035_ALS_THDL_ADDR  0x02


#define VNCL4035_PS_CONF12_ADDR  0x03
#define VNCL4035_PS_CONF3_ADDR   0x04
#define VNCL4035_PS_MS_ADDR     0x04

#define VNCL4035_PS_CNCL_ADDR   0x05

#define VNCL4035_PS_THDL_ADDR   0x06
#define VNCL4035_PS_THDH_ADDR   0x07

#define VNCL4035_PROX1_ADDR     0x08
#define VNCL4035_PROX2_ADDR     0x09
#define VNCL4035_PROX3_ADDR     0x0A


#define VNCL4035_ALS_ADDR       0x0B
#define VNCL4035_WHITE_ADDR     0x0C

#define VNCL4035_FLAGS_ADDR     0x0D

#define VNCL4035_CHIP_ID_ADDR   0x0E

#define GESTURE_NONE    0
#define GESTURE_LEFT    1
#define GESTURE_RIGHT   2
#define GESTURE_UP      3
#define GESTURE_DOWN    4


extern int baseline_Prox[];
extern int newVal_Prox[3];
extern int triggerVal_Prox[3];
extern int valALS;
extern int valWHITE;

int VCNL_init(void);

int VCNL_readSensor(void);

int VCNL_GetGesture(void);

int VCNL_read(uint8_t reg, uint8_t len, uint8_t *buf);

int VCNL_write(uint8_t reg, uint8_t len, uint8_t *buf);
#endif // VCNL4035_H
