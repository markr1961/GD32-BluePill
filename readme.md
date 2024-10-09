## An IAR project with a GD32F303CC on a Bluepill PCB in place of the usual xxF103C6/C8
https://github.com/markr1961/GD32-BluePill.git

## To Do
- adjust ROM and RAM size to match 303CC.

## Processor
GD32F303CC running at 120MHz (default)

## Build environment
IAR 7.80.4  
requires GigaDevices IAR extension  
expects GD32F30x library one level up.  

### include paths
$PROJ_DIR$\Inc  
$PROJ_DIR$\..\GD32f30x_Firmware_Library_V2.1.5\Firmware\CMSIS  
$PROJ_DIR$\..\GD32f30x_Firmware_Library_V2.1.5\Firmware\CMSIS\GD\GD32F30x\Include  
$PROJ_DIR$\..\GD32f30x_Firmware_Library_V2.1.5\Firmware\GD32F30x_standard_peripheral\Include  

### pre-processor defines
GD32F30X_CL  
USE_STDPERIPH_DRIVER  
__ICCARM__  

## Design info
[STM32 Blue Pill](https://www.land-boards.com/blwiki/index.php?title=STM32_Blue_Pill) at Land Boards.  
[original schematic](https://stm32-base.org/assets/pdf/boards/original-schematic-STM32F103C8T6-Blue_Pill.pdf) at stm32-base.org.  

### I/O
PC13    LED  
no button.  
Vbat on header, no cap  
Not all boards have correct USB resistors  
Boot0/Boot1 jumpers.  
SWIO/SWCLK pins (also need reset)  

