<!-- Please do not change this logo with link -->
[![MCHP](images/microchip.png)](https://www.microchip.com)

# Training on OPAMP, XOSCHF and MVIO

This training consists of 6 assignments exploring some of the new features of the AVR® DB, namely: The Analog Signal Conditioning (OPAMP), the High Frequency Crystal Oscillator (XOSCHF) and the Multi Voltage I/O (MVIO). 

The OPAMP peripheral features up to three internal operational amplifiers (op amps). The op amps can be configured in a multitude of different operations using internal multiplexers and resistor ladders. 

The XOSCHF enables the use of an external crystal or an external clock signal up to 32 MHz. This can be used as a clock source for the Main Clock (CLK_MAIN), the Real-Time Counter (RTC) and the 12-bit Timer/Counter Type D (TCDn).

The MVIO allows PORTC of the AVR DB to run on a different voltage domain (VDDIO2) than the rest of the PORTC.   

* **Assignment 1:**
External High-Frequency Oscillator (XOSCHF) and Clock Failure Detection (CDF)
* **Assignment 2:**
High Frequency TCD using PLL
* **Assignment 3:**
Votage Follower
* **Assignment 4:**
Instrumentation Amplifier
* **Assignment 5:**
Op Amp as a Regulated Power Supply for VDDIO2
* **Assignment 6:**
VDDIO2 Failure Detection

Each assignment also comes with a solution project found in the corresponding solution folder. 

**Click on the below image for Training video**
<p align="left">
<br><a href="https://www.youtube.com/playlist?list=PL9B4edd-p2ag0ErR65zx306mtoHysMyPh" rel="nofollow"><img src="images/YT_Training_AVR_DB.png" alt="AVR DB" width="500"/></a>
</p>

## Related Documentation

* [Training Getting Started with AVR DB OPAMP, XOSCHF and MVIO - MPLAB](https://microchip.com/DS40002278)
* [AVR128DB48 Device Page](https://www.microchip.com/wwwproducts/en/AVR128DB48)
* [AVR128DB48 Curiosity Nano User Guide](https://www.microchip.com/DS50003037)

### Future Reading
* [TB3286 - Getting Started with Analog Signal Conditioning (OPAMP)](https://microchip.com/DS90003286)
* [TB3272 - Getting Started with External High-Frequency Oscillator on AVR DB](https://microchip.com/DS90003272)
* [TB3287 - Getting Started With MVIO](https://microchip.com/DS90003287)

## Software Used

* [MPLAB® X IDE](https://www.microchip.com/mplab/mplab-x-ide) 5.40 or later
* [MPLAB® Code Configurator (MCC)](https://www.microchip.com/mplab/mplab-code-configurator) 4..0.2 or later
* [MPLAB® Code Configurator (MCC) Device Libraries 8-bit AVR MCUs](https://www.microchip.com/mplab/mplab-code-configurator) 2.5.0 or later 
* [MPLAB® XC8](http://www.microchip.com/mplab/compilers) 2.30 or later
* MPLAB AVR-Dx_DFP version 1.4.75 or later
* [MPLAB® Data Visualizer Stand alone](https://www.microchip.com/mplab/mplab-data-visualizer) version 1.1.793 or later
* [MPLAB® Mindi™ Analog Simulator](https://www.microchip.com/mplab/mplab-mindi)
* For the Atmel Studio version of these projects, please go to [this repository](https://github.com/microchip-pic-avr-examples/avr128db48-training-on-opamp-xoschf-mvio-studio)


## Hardware Used

* [AVR128DB48 Curiosity Nano](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/EV35L43A)

## Setup

Most assignments can be completed using the AVR128DB48 Curiosity Nano without any extra components, but some assignments require the MPLAB® Data Visualizer Stand alone, MPLAB® Mindi™ Analog Simulator, a logic analyzer or hardware modifications. See the training manual for setup of specific assignments.

![MCHP](images/avr128db48-cnano.png)

## Operation

* Connect the AVR128DB48 Curiosity Nano to the computer using a USB cable
* Clone the repository or download the zip to get the source code
* Open the .X projects with MPLAB in the assignment folder for the desired assignment
* Complete the assignment according to the training manual 
* Press *Make and Program Device* to run the example

![SetUpAssignment](images/MplabSetUp.png)


## Conclusion

After completing the training you should have a better understanding of some of the new features of the AVR DB such as the OPAMP, XOSCHF and MVIO.
