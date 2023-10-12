<h1 align = "center"> Micro Gardener </h1>


<p align="center">
  <img src="figures/Microgardner Logo.png"  />
</p>

<p align = "center">
Turn an ESP8266 Microcontroller into a Gardener!
</p>

## Table of Contents  
- [What does this code do?](#what-does-this-code-do) 

- [Structure Overview](#structure-overview)
  - [Main](#main)
  - [Executor](#executor)
  - [ECSensor](#ecsensor)
  - [Relay](#relay)
  - [Request](#request)
  - [base_grav](#base_grav)
  - [pHSensor](#phsensor)
  - [pH_grav](#ph_grav)
  - [tempSensor](#tempsensor)

- [How to run the code](#how-to-run-the-code)
  - [Cloning the Repository](#cloning-the-repository)
  - [Running the Code](#running-the-code)

## What does this code do?

This code is made to be uploaded onto an ESP8266 microcontroller that controls the environment in a hydroponic garden system. This code enables the microcontroller to communicate with nutrient and pH sensors while controlling light and water actuators to respond to real time commands. The microgardener itself does not make any decisions on when to control these actuators or collect information from its sensors. Instead, it gets commands which were created by a lambda function from a database.

<p align="center">
  <img src="figures/MicroGardener (1).png"  />
</p>

In a sense, the microgardner is acting as the physical eyes and ears for a web server. This setup is advantageous as it dramatically reduces required computational overhead for each microcontroller. However, it does introduce some added complexity. Namely, the microcontroller has to constantly stay connected to an internet source in order to receive the most recent commands.


## Structure Overview

Micro Gardener is composed of **main**, the build file which calls and combines all of the libraries, and eight libraries which contain all of the interfacing code for connecting to the web server, relays, and sensors. This section will give an overview of the functionality of each of these.

<p align="center">
  <img src="figures/MicroG Code Overview (1).png"  />
</p>

### Main
The Main file runs as an infinite loop, repeating the same basic process: connect to the internet if not already connected, check the webserver for a new command, and if there is a new command interpret and run it. Connecting to the internet is handled by the initial setup code in main, the request library handles pulling the command from the server, and the executor actually parses the JSON to interpret what needs to be done. Depending on the type of command, the Micro Gardener will proceed to either control a relay or collect a sensor reading. Each command from the web server will only have a single task at a time, and the Micro Gardener will update the task as complete once it is finished.

### Executor
Executor is responsible for interpreting what a command from the web server actually means. Generally, there are two paths. The first web server command would be to change a relay, turning on or off the water supply or lights. The second path is a request to collect a sensor measurement. The server will often do this to update its modeling, which will influence future commands. The first section of Executor handles parsing the JSON into an actionable form and the second tells main what other code it needs to call. For example, if the webserver send a pH measurement request then Executor will direct main to run code from the **pHSensor** library and then send the resulting measurement back to the server. Executor relies on the **Request** to provide it with the latest commands from the server. 

### ECSensor
ECSensor is a wrapper library we created to interact with the external **base_grav** library for our nutrient sensor. This was done to preserve the external library code and make debugging easier (i.e. we can narrow any issue to code we wrote in ECSensor). Therefore, when **main** requires a nutrient level measurement, it calls ECSensor which then handles all of the calls to **base_grav** to actually receive the measurement over serial.

### Relay
Relay refers to a relay in a circuit, which can either turn it on or off. In this case, the Relay library controls either turning water flow or lighting on or off. Relays electrical components rely on a simple high or low signal, so no external libraries were required to handle this aspect of the code. 

### Request
Request is what actually goes to the server's url, provides login credentials, and then downloads the latest commands. Request itself does not parse the JSON. Instead, it passes the JSON received from the server to **Executor** to have the command parsed, interpereted, and run. Request also handles sending updates to the server whether it be the completion of a task or requested sensor readings.

### base_grav
base_grav is an external library which handles the connection and interpretation of measurements from the nutrient sensor. The **Main** executable does not call this library directly, but rather, receives measurements from the **ECSensor** library which calls base_grav.

### pHSensor
Like ECSensor, pHSensor is a wrapper that handles making calls to the **ph_grav** external sensor library. **Main** will call this wrapper which will then handles asking for, receiving, and passing up to date measurements back to **Main**.

### ph_grav
ph_grav is an external libary which handles interfacing with and interpreting data from the pH sensor. The **pHSensor** calls this library to receive recent measurements before passing them to **Main**. 

## How to run the code


### Cloning the Repository
First, clone this directory onto your computer. To do this, click the green "code" button at the top of the screen. From there, either copy the SSH link or the HTTPS link. Then, in your terminal, run 
  ```
  git clone copy_link_here
  ```
### Running the Code
Once you have cloned the repository, open it in an embedded systems interactive developer environment (IDE), such as the PlatformIO extension for VSCode, and build it for the esp8266. Then flash the built code onto the microcontroller for it to begin running.

### Dependencies
You need to install the following libraries to run this code:
- ArduinoJson.h
- Ezo_uart_lib.h
- Unity.h

On PlatformIO, you can install these libraries by going to PIO Home -> libraries, then searching the name of the library, and selecting "add to project."
