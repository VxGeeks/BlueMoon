#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

#include "VCNL4035.h"

#include "Delay.h"

/**
 * Read set of registers via I2C using "repeated start" condition.
 *
 * Two I2C messages are being sent by this function:
 *   1. I2C write operation (write register address) with no STOP bit in the end
 *   2. I2C read operation
 *
 * @client: I2C client structure
 * @reg: register address (subaddress)
 * @len: bytes count to read
 * @buf: buffer which will contain read data
 *
 * Returns 0 on success or negative value on error.
 */

static int i2c_file;

#define PROX_TRIGGER_TRHLD      150
#define MAX_ACTIVE_WINDOW_CTR   5

int baseline_Prox[3]= {0,0,0};
int newVal_Prox[3]= {0,0,0};
int triggerVal_Prox[3]= {0,0,0};
int trigger_Swipe = 0;
int trigger_ActiveWindow_Counter = MAX_ACTIVE_WINDOW_CTR;
int valALS = 0;
int valWHITE = 0;

int gestureDetected = GESTURE_NONE;

int VCNL_init(void)
{

    uint8_t temp_buf[2];

    int i, j;

    if((i2c_file = open("/dev/i2c-1", O_RDWR )) < 0)
    {
            return -1;  //failed
    }
    else
    {
        if(ioctl(i2c_file,I2C_SLAVE,VCNL4035_I2C_ADDR) < 0)
        {
            return -2;  //failed some other way
        }
        else
        {
            VCNL_read(0x0B,2,temp_buf);

             // // Configure VCNL
            // Set LED current
            temp_buf[0]=0x08;
            temp_buf[1]=0x01;
            VCNL_write(VNCL4035_PS_MS_ADDR,2,temp_buf);
            // Set LED Duty Cycle
            temp_buf[0]=0x4E;
            temp_buf[1]=0x48;
            VCNL_write(VNCL4035_PS_CONF1_ADDR,2,temp_buf);
            // Set Ambient Light Integration Time
            temp_buf[0]=0x40;
            temp_buf[1]=0x00;
            VCNL_write(VNCL4035_ALS_CONF_ADDR,2,temp_buf);
            // Set Prox Threshold
            temp_buf[0]=0xff;
            temp_buf[1]=0x01;
            VCNL_write(VNCL4035_PS_THDL_ADDR,2,temp_buf);


            // Set baseline for Prox Sensors
            for (i = 0; i<3; i++)
            {
                long accum = 0;

                for (j = 0; j<8; j++)
                {
                    // Reset prox sensor scan
                    temp_buf[0]=0x0C;
                    temp_buf[1]=0x01;
                    VCNL_write(VNCL4035_PS_MS_ADDR,2,temp_buf);

                    Delay_Ms(34);

                    VCNL_read(VNCL4035_PROX1_ADDR + i,2,temp_buf);

                    accum += (((int) temp_buf[1] << 8) + (int) temp_buf[0]);
                }

                baseline_Prox[i] = accum / 8;
            }

        }

    }

    //opened OK
    return 0;
}


int VCNL_readSensor(void)
{
    uint8_t temp_buf[2];

    int i, j;


    for (i=0; i<100; i++)
    {
        VCNL_read(VNCL4035_PROX1_ADDR,2,temp_buf);    //PROX1
        newVal_Prox[0] = (((int) temp_buf[1] << 8) + (int) temp_buf[0] ) - baseline_Prox[0];

        VCNL_read(VNCL4035_PROX2_ADDR,2,temp_buf);    //PROX2
        newVal_Prox[1] = (((int) temp_buf[1] << 8) + (int) temp_buf[0] ) - baseline_Prox[1];

        VCNL_read(VNCL4035_PROX3_ADDR,2,temp_buf);    //PROX3
        newVal_Prox[2] = (((int) temp_buf[1] << 8) + (int) temp_buf[0] ) - baseline_Prox[2];

        // Setup Next Read
        temp_buf[0]=0x0C;
        temp_buf[1]=0x01;
        VCNL_write(VNCL4035_PS_MS_ADDR,2,temp_buf);

        // Check trigger condition
        int new_trigger_Swipe = 0;
        for (j = 0; j<3; j++)
        {
            if (newVal_Prox[j] > PROX_TRIGGER_TRHLD)
            {
                new_trigger_Swipe |= (0x01 << j);
            }
        }

        if (i == 0) // if first read
        {

            triggerVal_Prox[0] = newVal_Prox[0];
            triggerVal_Prox[1] = newVal_Prox[1];
            triggerVal_Prox[2] = newVal_Prox[2];



            if(new_trigger_Swipe == 0)
            {
                break;
            }
            else
            {
                trigger_Swipe = new_trigger_Swipe;
            }
        }
        else // if here trigger was detected
        {
            if(trigger_Swipe != new_trigger_Swipe )
            {
                // Get Direction
                if ((trigger_Swipe == 0x01) && ((new_trigger_Swipe & 0x04 ) == 0x04))
                {
                    gestureDetected = GESTURE_RIGHT;
                    break;
                }
                else if ((trigger_Swipe == 0x04) && ((new_trigger_Swipe & 0x01 ) == 0x01))
                {
                    gestureDetected = GESTURE_LEFT;
                    break;
                }
            }
        }

        Delay_Ms(5);

    }


    VCNL_read(VNCL4035_ALS_ADDR,2,temp_buf);    //ALS
    valALS = (((int) temp_buf[1] << 8) + (int) temp_buf[0] );


    VCNL_read(VNCL4035_WHITE_ADDR,2,temp_buf);
    valWHITE = (((int) temp_buf[1] << 8) + (int) temp_buf[0] );


    VCNL_read(VNCL4035_FLAGS_ADDR,2,temp_buf);
//    ui->label_Flags->setText(QString::number((char)temp_buf[1],2 ));

    return 0;
}

int VCNL_GetGesture()
{
    int tmp;

    tmp = gestureDetected;

    if (gestureDetected != GESTURE_NONE)
    {
        trigger_Swipe = 0;
        gestureDetected = GESTURE_NONE;
    }
    return tmp;
}

int VCNL_read(uint8_t reg, uint8_t len, uint8_t *buf)
{
    struct i2c_msg msg[2] = {
        {
            //.addr = client->addr,
            .addr = VCNL4035_I2C_ADDR,
            .flags = 0,
            .len = 1,
            .buf = &reg,
        },
        {
            //.addr = client->addr,
            .addr = VCNL4035_I2C_ADDR,
            .flags = I2C_M_RD,
            .len = len,
            .buf = buf,

        }
    };

    struct i2c_rdwr_ioctl_data rdwr_data;

    rdwr_data.msgs = msg;
    rdwr_data.nmsgs = 2;

    if(ioctl(i2c_file, I2C_RDWR,&rdwr_data)<0)
    {
    return -1;
    }
    return 0;
}

int VCNL_write(uint8_t reg, uint8_t len, uint8_t *buf)
{
    uint8_t writebuf[len+1];
    writebuf[0] = reg;
    writebuf[1] = buf[0];
    writebuf[2] = buf[1];

    write(i2c_file,writebuf,len+1);

    return 0;
}
