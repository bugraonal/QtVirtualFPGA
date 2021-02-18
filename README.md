# QtVirtualFPGA
Qt application simulating an FPGA board with digits, leds, buttons and switches. This app is intended to be used for FPGA lab lectures.

## Installation
Currently Linux and MacOS are natively supported. Binaries can be found in the release section. 
The following are required:
* [Verilator](https://github.com/verilator/verilator)
* CMake (version > 3.8)
* Boost libraries (version 1.65)
* Qt (version 5.15.1)

For Windows users, we have created a WSL image. Link to image can be found in the relase description. Instructions for using this image can also be found in that link.

## Usage
In order to add a Verilog project to the program do the following:
1. Click "File -> Open"
1. In the pop-up dialog add your Verilog files using the "Browse" button.
1. Add wrapper top file. Example wrapper files can be found in the [examples](https://github.com/bugraonal/resources/examples) directory. 
1. Press "Done"
1. In the main window press "Start"

The program will now start running you can interract with the buttons and the switches. 

To the right of the main window, you will see board customization options. These can be used to change the number of elements on your board. (This feature has not been completed, thus please do not use it)

You can also configure various ssettings from "Options -> Settings"

## Support
For help with setting up and usage you can use the [issues](https://github.com/bugraonal/QtVirtualFPGA/issues) section. 

For any other questions you can contact me at:
onalbugra@gmail.com
