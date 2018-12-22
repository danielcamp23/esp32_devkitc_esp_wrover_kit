#ifndef _OTA_CLIENT_H_
#define _OTA_CLIENT_H_


/**
 * Esta funcion se ejecuta a ciertas horas específicas
 * Lanza la tarea "aws_ota_agent" para vrificar si hay versiones por descargar
*/


void ota_client_check_firmware();

#endif