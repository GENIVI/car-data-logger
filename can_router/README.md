# CAN Router
CAN Router is an application operating between GENIVI VehicleSimulator and CDLDaemon.

It is implemented as a Server using socket to communicate with the VehicleSimulator(Implemented Socket Client).

After receiving the vehicle data(speed, rpm) from VehicleSimulator, it stores them using VSI.

## Installation
### Tested Environment
CAN Router Application is implemented and tested on:
* VMWare Workstation 12 Player (12.1.1 build-3770994)
* Ubuntu 14.04 64bit
* Qt 5.6.1

### Precondition
To build CAN Router, following package are required
* automotive-dlt 2.15 (or later)
* VSI
   * Install & Build : [VSI Build (cdl_daemon README)](https://github.com/GENIVI/car-data-logger/tree/abstract-component-poc/cdl_daemon/README.md)

### Clone Source Codes
Clone source codes from GENIVI GitHub using following command in the terminal window:

#### CDL

      $ git clone https://github.com/GENIVI/cat-data-logger.git

      $ git checkout abstract-component-poc

### Build & Install
#### CAN Router build & install
In CAN Router directory of CDL, build & install using following command:

      $ qmake -r -spec linux-g++
      $ make
      $ make install

After the installation, you can find binary(can_router) in `deploy/x86` directory.

## Usage

### Run
#### Build for testing on Desktop
Prepare one terminal window and navigate to the `deploy/x86` directory.

And run can_router on terminal:

      $ ./can_router

