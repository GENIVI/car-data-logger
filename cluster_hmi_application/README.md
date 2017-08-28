# Cluster HMI Application
Cluster is an application displaying the infomation of vehicle such as fuel, speed, RPM, etc.
It communicates with the on_board_provider using DBus.

## Installation
### Tested Environment
`cluster_hmi_application` is implemented and tested on:
* VMWare Workstation 12 Player (12.1.1 build-3770994)
* Ubuntu 14.04 64bit
* Qt 5.6.1

### Precondition
To build `cluster_hmi_applciation`, following package are required
* CommonAPI 3.1.5 (including DBus and SOME/IP Runtime)
* automotive-dlt 2.15 (or later)

### Clone Source Codes
Clone source codes from GENIVI GitHub using following command in the terminal window:

#### CDL

      $ git clone https://github.com/GENIVI/cat-data-logger.git

      $ git checkout abstract-component-poc

### Build & Install
#### Cluster HMI Application build & install
In cluster hmi application directory of CDL, build & install using following command:

      $ qmake -r -spec linux-g++
      $ make
      $ make install

After the installation, you can find binary(cluster_hmi_application) in `deploy/x86` directory.

## Usage
### Run

Prepare one terminal window and navigate to the `deploy/x86` directory.

And run `cluster_hmi_application` on terminal:

      $ ./cluster_hmi_application

