#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// define chipset pin: P1_16
#define SYSFS_GPIO_EXPORT           "/sys/class/gpio/export"  
#define SYSFS_GPIO_RST_PIN_VAL      "48"   
#define SYSFS_GPIO_RST_DIR          "/sys/class/gpio/gpio48/direction"
#define SYSFS_GPIO_RST_DIR_VAL      "OUT"  
#define SYSFS_GPIO_RST_VAL          "/sys/class/gpio/gpio48/value"
#define SYSFS_GPIO_RST_VAL_H        "1"
#define SYSFS_GPIO_RST_VAL_L        "0"
#define SYSFS_GPIO_EXPORT           "/sys/class/gpio/export"  
#define SYSFS_GPIO_RST_PIN_VAL      "48"   
#define SYSFS_GPIO_RST_DIR          "/sys/class/gpio/gpio48/direction"
#define SYSFS_GPIO_RST_DIR_VAL      "OUT"  
#define SYSFS_GPIO_RST_VAL          "/sys/class/gpio/gpio48/value"
#define SYSFS_GPIO_RST_VAL_H        "1"
#define SYSFS_GPIO_RST_VAL_L        "0"


int main(void)
{
    int fd = 0;

    // open /sys/class/gpio # echo 48 > export
    fd = open(SYSFS_GPIO_EXPORT, O_WRONLY);
    if (fd < 0) {
        printf("ERR: Radio hard reset pin open error.\n");
        return EXIT_FAILURE;
    }

    write(fd, SYSFS_GPIO_RST_PIN_VAL, sizeof(SYSFS_GPIO_RST_PIN_VAL));
    close(fd);

    // set direction
    fd = open(SYSFS_GPIO_RST_DIR, O_WRONLY);
    if (fd < 0) {
        printf("ERR: Radio hard reset pin direction open error.\n");
        return EXIT_FAILURE;
    }

    write(fd, SYSFS_GPIO_RST_DIR_VAL, sizeof(SYSFS_GPIO_RST_DIR_VAL));
    close(fd);

    // set signal high
    fd = open(SYSFS_GPIO_RST_VAL, O_WRONLY);
    if (fd < 0) {
        printf("ERR: Radio hard reset pin value open error.\n");
        return EXIT_FAILURE;
    }

    write(fd, SYSFS_GPIO_RST_VAL_H, sizeof(SYSFS_GPIO_RST_VAL_H));
    close(fd);

    printf("INFO: set GPIO 48 success\n");
    return 0;
}
