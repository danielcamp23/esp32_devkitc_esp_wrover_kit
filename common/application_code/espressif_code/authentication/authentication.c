#include "authentication.h"
#include <stdlib.h>
#include <stdint.h>

#include "aws_dev_mode_key_provisioning.h"

//#include "key_provisioning.h"
#include <stdio.h>

/**
 *  Loads aws certificates 
 */
void authentication_init(){
    
    printf("authentication...\n");
    vDevModeKeyProvisioning();
    printf("OK\n");
}