
A Bluepill project with a GD32F303CC in place of the usual xxF103C6/C8

## To Do
- adjust ROM and RAM size to match 303CC.

## Build environmnet
IAR 7.80.4  
requires GigaDevices IAR extension  
expects GD32F30x library on level up.   

### include paths
$PROJ_DIR$\Inc  
$PROJ_DIR$\..\GD32f30x_Firmware_Library_V2.1.5\Firmware\CMSIS  
$PROJ_DIR$\..\GD32f30x_Firmware_Library_V2.1.5\Firmware\CMSIS\GD\GD32F30x\Include  
$PROJ_DIR$\..\GD32f30x_Firmware_Library_V2.1.5\Firmware\GD32F30x_standard_peripheral\Include  

### pre-processor defines
GD32F30X_CL  
USE_STDPERIPH_DRIVER  
__ICCARM__  
