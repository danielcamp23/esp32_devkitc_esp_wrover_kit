#ifndef _ANALOG_INFO_H_
#define _ANALOG_INFO_H_
 

#define NO_OF_SAMPLES   64     //Numero de muestras para promediar valor analógico
#define ANALOG_RANGE 10         //Rango de detección de cambio en entrada analógica


#define AN01      ADC1_CHANNEL_4 /*!< ADC1 channel 4 is GPIO32 */
#define AN02      ADC1_CHANNEL_5 /*!< ADC1 channel 5 is GPIO33 */
#define AN03      ADC2_CHANNEL_8 /*!< ADC2 channel 8 is GPIO25 */
#define AN04      ADC2_CHANNEL_9 /*!< ADC2 channel 9 is GPIO26 */
#define AN05      ADC2_CHANNEL_7 /*!< ADC2 channel 7 is GPIO27 */
#define AN06      ADC2_CHANNEL_6 /*!< ADC2 channel 6 is GPIO14 */

#define AN01_NAME "AN01"
#define AN02_NAME "AN02"
#define AN03_NAME "AN03"
#define AN04_NAME "AN04"
#define AN05_NAME "AN05"
#define AN06_NAME "AN06"



/*
Poner en "1" o "0" las entradas analógicas del ESP que se van a conectar.
Esto para poder leer el valoy y compar con deltas para el disoaro de mensajes/alarmas/acciones.
*/
#define USE_AN01   1
#define USE_AN02   1
#define USE_AN03   0
#define USE_AN04   0
#define USE_AN05   0
#define USE_AN06   0

#endif