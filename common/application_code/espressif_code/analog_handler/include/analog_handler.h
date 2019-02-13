#ifndef _ANALOG_HANDLER_H_
#define _ANALOG_HANDLER_H_




/*
Inicializa módulo de entradas analógicas
@Params:
@Return:
*/
void analog_handler_init();


/*
Tarea de lectura de las entradas analógicas
@Params:
@Return: 
*/
void analog_handler_task(void * pvParameters);

#endif