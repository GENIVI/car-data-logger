
# Car Data Logger For PoC

This is the CDL proof of concept for AC.

There are some modules that can operate with `cdl_daemon` such as `cluster_hmi_application`, `can_router`, `rvi_server`.

- CAN Router
  * Store the vehicle data received from the `GENIVI VehicleSimulator` using `VSI`.
- CDLDaemon
  * Collect, Store, Provide with On/Off-BoardProvider vehicle Data.
- Cluster
  * Received the vehicle data from vehicle-data-consumer.
  * Display the vehicle data(speed, rpm).
- RVIServer
  * Receive the data(file of JSON format) from the `OffBoardProvider` using `RVI`.
  * Display the transferred data(file of JSON format) with a graph (Historical View).
- vehicle-data-consumer
  * Received the vehicle data(speed, rpm) from `OnBoardProvider` in the `cdl_daemon` using DBus.
  * Provide the vehicle data to cluster-hmi-application.
  
## Precondition
* [GENIVI] Vehicle Simulator
    * Download pre-build binary :
       * [dropbox](https://www.dropbox.com/sh/jh3pyz7umhtmv0p/AABdQmwAl7LWcT4qlXvhUuS3a?dl=0)   
    * Run :
       * [Unity 5.3.4](https://unity3d.com/kr/)
    * Reference :
       * [GENIVI Vehicle Simulator Project Page](https://at.projects.genivi.org/wiki/display/PROJ/GENIVI+Vehicle+Simulator)
      
## Operation
1. Run the `rvi_server`.
2. Run the `can_router`, `cdl_daemon`, `vehicle_data_consumer`, `cluster_hmi_application`.
  * `can_router` stores the vehicleData after the VehicleSimulator runs.
  * `cdl_daemon` starts to collect vehicle data after the vehicle data is stored using VSI from `can_router`.
  * `vehicle_data_consumer` registers to `on_board_provider` in `cdl_daemon` to receive the vehicle data using dbus.
3. Run the `Vehicle Simulator` GENIVI Component.

### Operated device
#### DeskTop
* GENIVI VehicleSimulator
#### RaspberryPi 3
* can_router
* cdl_daemon
* vehicle_data_consumer
* cluster_hmi_application
#### DeskTop
* rvi_server

Installation and Run categories are on the page of each module.

Please refer to page for more detail.

