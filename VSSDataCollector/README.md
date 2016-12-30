# VSS Data Collector

VSS Data Collector is module collecting vehicle data defined with [VSS(Vehicle Signal Specification)](https://github.com/GENIVI/vehicle_signal_specification) using [VSI(Vehicle Signal Inteface)](https://github.com/GENIVI/vehicle_signal_interface)

# Installation

### Tested Envrionment
VSS Data Collector is implemented and tested on:
* VMWare Workstation 12 Player (12.1.1 build-3770994)
* Ubuntu 14.04 64bit
* Qt 5.6.1 (for test application)

### Precondition
To build VSS Data Collector, following package are required
* VSI
* Boost 1.54 (or later)
    * system, thread, log

### Clone Source Codes
Clone source codes from GENIVI GitHub using following command in the terminal window:
#### VSI
Because the latest version of VSI is not compatible with C ++, the VSS Data Collector is implemented based on [c2b1c0a](https://github.com/GENIVI/vehicle_signal_interface/tree/c2b1c0ab0124aa36a30ddd486cf8b373be7b2c0f) Commit.

        $ git clone https://github.com/GENIVI/vehicle_signal_interface.git

        $ git checkout c2b1c0a

#### CDL

        $ git clone https://github.com/GENIVI/cat-data-logger.git

        $ git checkout trial-integration-with-rvi

### Build & Install
#### VSI build & install
Before build the VSI, apply patches for installation.
Copy patch files in VSSDataCollector(add-make-install.patch, add-package-config-file.patch) to VSI directory and apply patches.

        $ patch -p1 < add-make-install.patch
        $ patch -p1 < add-package-config-file.patch

And build and install VSI using following command:

        $ make
        $ sudo make install

#### VSS Data Collector build & install
In VSSDataCollector directory of CDL, build & install using following command:

        $ mkdir build
        $ cd build
        $ cmake ..
        $ make
        $ sudo make install

#### Test Application build & install
Navigate to the test directory of VSSDataCollector, and build & install using following command:

        $ qmake -r -spec linux-g++
        $ make
        # make install

After the installation, you can find binaries(Data Generator, VSSDataCollector Test Application) and other files for configuration and generated VSS JSON, VSI files using tool `vspec2json.py` and `vspec2vsi.py` in deploy directory

# Usage

### Run
Prepare two terminal windows and navigate to the deploy directory of test.
Before run applications, add library search path for `VSI` and `VSSDataCollector` library to the `LD_LIBRARY_PATH` using following command in terminal:

        $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

Run DataGenerator application on one terminal

        $ ./DataGenerator

and run VSSDataCollectorTestApp on the other terminal.

        $ ./VSSDataCollectorTestApp

The DataGenerator generates vehicle data randomly, and flushes data into VSI.
On VSSDataCollector side, you can check data collection status including data validation results.

### Configuration file for data collection
Configuration file element explanation:
* Cycle
Contains the data that should be collected periodically.
   * {cycle} (array)
   Specifies the data and collection cycle(miliseconds).
* Event (array)
Contains the data that should be collected by event.

Example

         {
             "Cycle":
             {
                 "1000":
                 [
                     "Signal.Drivetrain.Transmission.Speed",
                     "Signal.Chassis.SteeringWheel.Angle",
                     "Signal.Chassis.SteeringWheel.Extension",
                     "Signal.Drivetrain.FuelSystem.AverageConsumption"
                 ],
                 "2000":
                 [
                     "Signal.Drivetrain.InternalCombustionEngine.Torque",
                     "Signal.Drivetrain.InternalCombustionEngine.TPS",
                     "Signal.Chassis.Accelerator.PedalPosition",
                     "Signal.Chassis.Brake.PedalPosition"
                 ],
                 "3000":
                 [
                     "Signal.Chassis.Axle.Row1.Wheel.Right.Tire.Pressure",
                     "Signal.Chassis.Axle.Row1.Wheel.Left.Tire.Pressure",
                     "Signal.Chassis.Axle.Row1.Wheel.Right.Tire.Temperature",
                     "Signal.Chassis.Axle.Row2.Wheel.Right.Tire.PressureLow",
                     "Signal.Drivetrain.InternalCombustionEngine.Power"
                 ]
             },
             "Event":
             [
                 "Signal.Drivetrain.Transmission.Gear",
                 "Signal.Body.Mirrors.Left.Heater.Status",
                 "Vehicle.Light.Front.Left",
                 "Vehicle.Light.Front.Right"
             ]
         }

### Environment variables
VSS Data Collector needs 3 environment variables for run such as generated VSS JSON file, VSS VSI file and configuration file for data collecton. VSS Data Collector reads specified files or if not specified, reads default file in current working directory.
* VSS_JSON_FILE
generated from vspec file using `vsepc2json` (e.g. vss_rel_1.json)

* VSS_COLLECTOR_CONFIGURATION_FILE
user defined configuration file for data collection

* VSS_VSI_FILE
generated from vspec file using `vspec2vsi` (e.g. vss_rel_1.vsi)

