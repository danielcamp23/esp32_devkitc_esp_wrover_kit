#include "authentication.h"
#include "key_provisioning.h"

/**
 *  Loads aws certificates 
 */
void authentication_init(){
    key_prov_load_keys();
}