# CDL Daemon

`cdl_daemon` is module which is integrated Collector, Store, On/Off Board Provider units.
 - vss_data_collector
    * Collect the vehicle data from vsi.
 - data_store
    * Store the vehicle data in JSON file whenever the vechie data is collected.
 - on_board_provider
    * Provide the vehicle data on board to registered clients what they want.
 - off_board_provider
    * Provide the stored JSON file to external server using RVI.
    
# Installation

### Tested Envrionment
cdl_daemon is implemented and tested on:
* VMWare Workstation 12 Player (12.1.1 build-3770994)
* Ubuntu 14.04 64bit

### Precondition
To build cdl_daemon, following package are required
* VSI
* sqlite 3.8.2 (or later)
* Boost 1.54 (or later)
    * system, thread, log, filesystem, date_time, iostreams
* CommonAPI 3.1.5 (including DBus and Some/IP Runtime)
* python 2.7.6
* [rvi_core 0.5.1](https://github.com/GENIVI/rvi_core/releases)

### Clone Source Codes
Clone source codes from GENIVI GitHub using following command in the terminal window:
#### VSI
Because the latest version of VSI is not compatible with C ++, the vss_data_collector is implemented based on [c2b1c0a](https://github.com/GENIVI/vehicle_signal_interface/tree/c2b1c0ab0124aa36a30ddd486cf8b373be7b2c0f) Commit.

        $ git clone https://github.com/GENIVI/vehicle_signal_interface.git

        $ git checkout c2b1c0a

#### CDL

        $ git clone https://github.com/GENIVI/cat-data-logger.git

        $ git checkout abstract-component-poc

### Build & Install
#### VSI build & install
Before build the VSI, apply patches for installation.
Copy patch files in vss_data_collector(add-make-install.patch, add-package-config-file.patch) to VSI directory and apply patches.

        $ patch -p1 < add-make-install.patch
        $ patch -p1 < add-package-config-file.patch

And build and install VSI using following command:

        $ make
        $ sudo make install

#### cdl_daemon build & install
In cdl_daemon directory of CDL, build & install using following command:

        $ mkdir build
        $ cd build
        $ cmake ..
        $ make
        $ sudo make install

After the installation, you can find the binaries and other file for configuration in the `deploy` directory:
  - `cdl_daemon`
  - `lib` directory including the `CDLClientSomeIp` library
  - configuration files ( `data_config.json`, `VSS`, `vsi`, `store_config_file.json` )

And before run the `cdl_daemon`, copy the python file(`rvi_call.py`) in the `configuration_files` directory to the location where the `rvi_core` installed.

### Run
Prepare a terminal window and navigate to the deploy directory of test.
Before run the `cdl_daemon` application, run the [rvi_server](https://github.com/GENIVI/car-data-logger/tree/abstract-component-poc/rvi_server/README.md) on the CDL(car-data-logger) to confirm the transferred JSON file between cdl_daemon and external server.

Navigate to the `deploy` directory following command:

        $ cd ../deploy

Before run the `cdl_daemon` on the terminal, add library search path for `CDLClientSomeIp` library to the `LD_LIBRARY_PATH` using following command in terminal:

        $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/lib

and run the `cdl_daemon` on the terminal.

        $ ./cdl_daemon


