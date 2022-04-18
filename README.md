# KasperskyOS Night Practice Demo

This example shows a possible way to maintain a cross-platform project for both Linux and KasperskyOS.

## Getting started

### Prerequisites

For KasperskyOS build you need to download and install
[KasperskyOS Community Edition](https://os.kaspersky.com/development/download/).  
For Linux build you need:
* CMake 3.16.3 or higher;
* GCC 9.4.0 or higher.

### Usage

In order to build the example and run the result you can use the following scripts:
* `linux-build.sh` - for Linux;
* `cross-build.sh` - for KasperskyOS.

## Additional notes

### Limitations

This project was created for demonstration purpose only and should not be considered as production-quality code.

Usage of the same network interface for Cathode and Anode in KasperskyOS version is a known limitation. 
The reason lies in the fact that Raspberry Pi version, which is used as a target hardware for KasperskyOS Community
Edition, has only one network interface.
