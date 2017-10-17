# Vehicle Data Consumer Cluster
`vehicle_data_consumer_cluster` is connected with `on_board_provider` in `cdl_daemon` to receive the vehicle data using dbus.
After receiving the vehicle data, provides them to cluster-hmi-applpication.

## Installation
### Tested Environment
`vehicle_data_consumer_cluster` is implemented and tested on:
* VMWare Workstation 12 Player (12.1.1 build-3770994)
* Ubuntu 14.04 64bit
* Qt 5.6.1

### Precondition
To build `vehicle_data_consumer_cluster`, following package are required
* CommonAPI 3.1.5 (including DBus and SOME/IP Runtime)
* Boost 1.54 (or later)
   * log, system, thread

### Clone Source Codes
Clone source codes from GENIVI GitHub using following command in the terminal window:

#### CDL

      $ git clone https://github.com/GENIVI/cat-data-logger.git
    
      $ git checkout abstract-component-poc
      
### Build & Install
#### vehicle_data_consumer_cluster build & install
In `vehicle_data_consumer_cluster` directory of CDL, build & install using following command:

      $ qmake -r -spec linux-g++
      $ make
      $ make install
      
After the installation, you can find binary(`vehicle_data_consumer_cluster`) in `deploy/x86` directory.

## Usage

### Run
#### Build on Qt Environment
Prepare one terminal window and navigate to the `deploy/x86` directory.
      
And run `vehicle_data_consumer_cluster` on terminal:
      
      $ ./vehicle_data_consumer_cluster


