#ifndef INPUT_H
#define INPUT_H

#include "stds.h"
#include <stdbool.h>

extern app_t app;

extern void process_input( void );
extern bool is_action_button_pressed( void );
extern int get_selected_button_index( void );

#endif // INPUT_H
 