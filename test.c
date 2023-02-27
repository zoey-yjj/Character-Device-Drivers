#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define DEVICE_FILE "/dev/onebyte"

int main(int argc, char *argv[]) 
{
    int fd;
    char buffer[1];
    int ret;

    // Open the device file
    fd = open(DEVICE_FILE, O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "Failed to open %s: %s\n", DEVICE_FILE, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Read a byte from the device -- check initial value of the device
    memset(buffer, 0, sizeof(buffer));
    ret = read(fd, buffer, 1);
    if (ret == -1) {
        fprintf(stderr, "Failed to read from %s: %s\n", DEVICE_FILE, strerror(errno));
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("initial content of device is %d\n", buffer[0]);

    // Close the device file
    close(fd);

    printf("Success!\n");
}