#ifndef KEYBOARD_LINUX_H
#define KEYBOARD_LINUX_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <linux/input.h>

int get_key_state( Display *dpy, char key )
{
    char keys[32];
    XQueryKeymap( dpy, keys );

    int byte = floor( key / 4 );
    int bit = key - ( byte * 4 );

    switch( bit )
    {
        case 0:
            return keys[byte] & 0x01;

        case 1:
            return keys[byte] & 0x02;

        case 2:
            return keys[byte] & 0x04;

        case 3:
            return keys[byte] & 0x08;

        default:
            break;
    }

    printf( "Error! Byte: %d Bit: %d\n", byte, bit );
    return 0;
}

#endif  // KEYBOARD_LINUX_H
