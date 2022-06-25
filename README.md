# GPIO - Linux drivers

#### Study on operating systems, working with GPIO.

This project contains the GPIO command where a seven segment display is controlled with a Raspberry Pi. xTwo different libraries are used, each of which implements GPIO. The first library is `WiringPi`, and was required to be user. The second library is `BCM2835`. I chose this one to use in a more generic way for the Raspberry Pi. The program can be compiled using `CMake`, an instruction is given below.
Now follows an overview of the various program functionalities that are supported, and to which the seven segment display shows numbers.
- The option `--display` or `-d`. This will display a hexadecimal number between `0x0` and `0xF`. You can use it as `./GPIO_HEX_DRIVER --display 0xA` or `./GPIO_HEX_DRIVER -d 0xA`.
- The `--countup` or `-cu` option. This option counts from the number as argument to `0xF`. You can use it as `./GPIO_HEX_DRIVER --countup 0xA` or `./GPIO_HEX_DRIVER -cu 0xA`.
- The `--countdown` or `-cd` option. This option counts from the number as argument to `0x0`. You can use it as `./GPIO_HEX_DRIVER --countdown 0xA` or `./GPIO_HEX_DRIVER -cd 0xA`.

## Build and execute

To compile this program I use `CMake`. To be able to use this on a Raspberry Pi you have to go through a number of steps. These steps are shown below:

1. Create a new folder in the project. This folder is used for various configuration files, and ultimately the program's executable. For example, create this folder like this and go into that specific folder (name doesn't matter):
    ```shell
    ../GPIO_LINUX:~$ mkdir cmake-build
    ../GPIO_LINUX:~$ cd cmake-build
    ```
   
2. Now all the different CMake files should be generated. This is necessary too eventually.
     ```shell
     ../GPIO_LINUX/cmake-build:~$ cmake -DUSE_WIRINGPI:BOOL=ON ..
     ```

    In the above case, the GPIO library used is `WiringPi`. To change this to the `BCM2835` library, you have to turn of that variable with `CMake` again. It is possible as follows:
    ```shell
    ../GPIO_LINUX/cmake-build:~$ cmake cmake -DUSE_WIRINGPI:BOOL=OFF ..
    ```
