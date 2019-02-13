#ifndef _ANALOG_HANDLER_STATIC_H_
#define _ANALOG_HANDLER_STATIC_H_

#include <stdbool.h>
#include <stdint.h>


/*

@Params: 
@Return: 
*/
static void analog_handler_check_efuse();

/*
Configura los canales (entradas) que se utilizarán
@Params:
@Return: 
*/
static void analog_handler_check_efuse();


/*
Recibe la lectura pasada y la actual para hacer una comparación y eliminar ruido de la selam
@Params: - past_val: lectura pasada
         - cur_val: lectura actual
@Return: true si hay un cambio significativo en la lectura (no es ruido), false en el caso contrario
*/
static bool analog_handler_compare(uint32_t past_val, uint32_t cur_val);
#endif