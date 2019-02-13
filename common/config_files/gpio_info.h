#ifndef _GPIO_INFO_H_
#define _GPIO_INFO_H_

#define GPIO_DI01      36   /* GPIO36 */
#define GPIO_DI02      39   /* GPIO39 */
#define GPIO_DI03      34   /* GPIO33 */
#define GPIO_DI04      35   /* GPIO35 */

#define GPIO_DI05      19   /* GPIO19 */
#define GPIO_DI06      23   /* GPIO23 */
#define GPIO_DI07      22   /* GPIO22 */
#define GPIO_DI08      21   /* GPIO21 */


//PRUEBA DE GPIOS EN LA MISMA DIRECCION DE ADC
//#define GPIO_DI09      32   /* GPIO19 */
//#define GPIO_DI10      33   /* GPIO23 */
//#define GPIO_DI11      25   /* GPIO22 */
//#define GPIO_DI12      26   /* GPIO21 */
//#define GPIO_DI13      27   /* GPIO21 */
//#define GPIO_DI14      14   /* GPIO21 */


#define GPIO_DO01       8   /* GPIO08 */
#define GPIO_DO02       7   /* GPIO07 */
#define GPIO_DO03       6   /* GPIO06 */
#define GPIO_DO04      11   /* GPIO11 */


/*
Poner en "1" o "0" las entradas digitales del ESP que se van a conectar.
Esto para poder generar interrupciones de esos pines.
*/
#define USE_GPIO_DI01   0
#define USE_GPIO_DI02   0
#define USE_GPIO_DI03   0
#define USE_GPIO_DI04   0
#define USE_GPIO_DI05   0
#define USE_GPIO_DI06   1
#define USE_GPIO_DI07   1
#define USE_GPIO_DI08   0

//PRUEBA DE GPIOS EN LA MISMA DIRECCION DE ADC
//#define USE_GPIO_DI09   1
//#define USE_GPIO_DI10   1
//#define USE_GPIO_DI11   1
//#define USE_GPIO_DI12   1
//#define USE_GPIO_DI13   1
//#define USE_GPIO_DI14   1



#endif