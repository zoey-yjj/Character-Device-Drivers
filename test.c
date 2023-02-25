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

    // Close the device file
    close(fd);

    printf("Success!\n");
}