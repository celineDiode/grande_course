/*
 * state_machine.h
 *
 *  Created on: 2014-10-28
 *      Author: thor4_000
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "stdlib.h"
#include "sensors.h"
#include "mouvements.h"

enum states_t {DEPART, ATTEINDRE_LIGNE_ROUGE, SUIVRE_LIGNE_ROUGE, ALLER_CENTRE, GARDER_CENTRE};

void* TASK_state_machine (void* a);

#endif /* STATE_MACHINE_H_ */
