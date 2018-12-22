#ifndef _OTA_CLIEN_STATIC_H_
#define _OTA_CLIEN_STATIC_H_
#include "aws_ota_client.h"

/* The OTA agent has completed the update job or determined that we're in
 * self test mode. If it was accepted, we want to activate the new image.
 * This typically means we should reset the device to run the new firmware.
 * If now is not a good time to reset the device, it may be activated later
 * by your user code. If the update was rejected, just return without doing
 * anything and we'll wait for another job. If it reported that we should
 * start test mode, normally we would perform some kind of system checks to
 * make sure our new firmware does the basic things we think it should do
 * but we'll just go ahead and set the image as accepted for demo purposes.
 * The accept function varies depending on your platform. Refer to the OTA
 * PAL implementation for your platform in aws_ota_pal.c to see what it
 * does for you.
 * 
 */

/**
 * El OTA agent ha terminado el job.
 * Si la descarga fue ok, validar si es buen momento para activar la nueva imagen,
 * lo que implica el reset del dispositivo.
 * Si la ctualización fue rechazada, no se hace nada y se espera por otro job.
 * 
 * 
*/

static void _ota_client_complete_callback(OTA_JobEvent_t eEvent);

#endif