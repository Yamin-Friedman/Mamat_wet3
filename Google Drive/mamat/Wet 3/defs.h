#ifndef _Defs_h
#define _Defs_h


/**includes & defines**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ARG 10					// for main input line
#define MAX_INPUT_LINE 256			// for main input line
#define APC_MAX_Soldiers 6			// for APC
#define MAX_ID_LENGTH 8			    // for Structs IDs
#define NUM_POSITIONS 5
#define SOLDIER_ID_LEN 4
#define SQUAD_ID_LEN 5
#define WARZONE_ID_LEN 4

#define MALLOC_ERR_MSG "Error: Cant perform Malloc\n"
#define ARG_ERR_MSG "Error: Function's Args Error\n"
#define NO_B_ERR "Error: No Battlefield\n"
#define NO_W_ERR "Error: No Such War Zone\n"
#define NO_SQ_ERR "Error: No Such Squad\n"
#define NO_A_ERR "Error: No Such APC\n"
#define NO_S_ERR "Error: No Such Soldier\n"
typedef enum Result_ { FAILURE, SUCCESS } Result;


#endif
