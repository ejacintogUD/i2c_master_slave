/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "PinNamesTypes.h"
#include <mbed.h>
#include <cstdio>

int S1 = 34;
int S2 = 45;
int S3 = 88;

char sensores[9];
char s1c[2];
char s2c[2];
char s3c[2];
//DigitalIn sda(D14, PullUp);
//DigitalIn scl(D15, PullUp);

I2CSlave slave(D14, D15);


int main()
{
    
    char buf[10];
    char msg[] = "Slave!";
    slave.frequency(400000);

    slave.address(0x50); // 80 en decimal 
    printf("Arranque del sistema\n\r");

    while (1) {
        int i = slave.receive();
        switch (i) {
            case I2CSlave::ReadAddressed:
                sprintf(sensores, "%2u,%2u,%2u", S1,S2,S3);
                slave.write(sensores, 8);
                printf("Rama Leer\n\r");
                break;
            case I2CSlave::WriteGeneral:

                slave.read(buf, 6);
                printf("Read WG: %s\n", buf);
                break;
            case I2CSlave::WriteAddressed:
                
                slave.read(buf, 7);

                if (buf[0] == 1)
                    printf("Read WA 1: %s\n", buf);
                else if (buf[0] == 2)
                   printf("Read WA 2: %s\n", buf);     
                break;
        }
        for (int i = 0; i < 10; i++) {
            buf[i] = 0;    // Clear buffer
        }
    }
}