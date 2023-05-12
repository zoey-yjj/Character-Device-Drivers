# Character Device Driver

A character device file represents a slow device that transfers data in streams of bytes, such as a keyboard, mouse, serial ports, or a terminal. The operations on a character device file can include read, write, and ioctl operations. In the kernel, a character device driver is implemented as a collection of functions that handle these operations and interact with the hardware.

A character device driver is created to exposes the "onebyte" hardware device to user space as a character device file. "onebyte" can store only one byte, backed by a single byte of memory.

## Run Device

- load modul:

    ```sudo mknod /dev/onebyte c 52  0```

- check device:

    ```ls -l /dev | grep onebyte```

## Test Driver

Test character device in test.c