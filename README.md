# Car Data Logger Trial Integration with RVI

This is trial integration of CDL with RVI (components)

The goal of this implementation is to implement the function of collecting, storing and providing data using various components of GENIVI.
So the following functions will be implemented:
* collect vehicle data defined in VSS format using VSI
* store collected data to file
* provide data to clients running on-board using CommonAPI (DBus and SOME/IP)
* transfer data to off-board server using RVI

The software platform level requirements collected while implementing the functions defined above will continue to be updated on the [CDL wiki](https://collab.genivi.org/wiki/display/genivi/cdl+software+platform+level+use+cases) page.

# Status

### Implemented Modules
* VSS Data Collector : please refer to [VSSDataCollector](https://github.com/GENIVI/car-data-logger/blob/trial-integration-with-rvi/VSSDataCollector/README.md) page for more detail
* Data Store         : please refer to [DataStore](https://github.com/GENIVI/car-data-logger/blob/trial-integration-with-rvi/DataStore/README.md) page for more detail
* On Board Provider  : please refer to [OnBoardProvider](https://github.com/GENIVI/car-data-logger/blob/trial-integration-with-rvi/OnBoardProvider/README.md) page for more detail
* Off Board Provider : please refer to [OffBoardProvider](https://github.com/GENIVI/car-data-logger/blob/trial-integration-with-rvi/OffBoardProvider/README.md) page for more detail
