#include "../include/input.h"

static int16_t previous_frame_key = -1;
static SDL_GameController *controller = NULL;
int selected_button_index = 0;  // Make this global so menu can access it
const int MAX_MENU_BUTTONS = 3;
static bool button_a_pressed = false;

static void key_pressed( SDL_KeyboardEvent * );
static void key_released( SDL_KeyboardEvent * );
static void mouse_pressed( SDL_MouseButtonEvent * );
static void mouse_released( SDL_MouseButtonEvent * );
static void controller_button_pressed( SDL_ControllerButtonEvent * );
static void controller_button_released( SDL_ControllerButtonEvent * );
static void init_controller( void );

/*
 * Starts the SDL event loop.
 * 
 * @param void.
 * 
 * @return void.
 */
void
process_input( void ) {
  SDL_Event event;

  // Initialize controller if not already done
  if ( controller == NULL ) {
    init_controller();
  }

  while ( SDL_PollEvent( &event ) ) {
    SDL_GetMouseState( &app.mouse.x, &app.mouse.y );
    
    switch ( event.type ) {
    case SDL_QUIT:
      exit( EXIT_SUCCESS );
      break;
    case SDL_KEYDOWN:
      key_pressed( &event.key );
      break;
    case SDL_KEYUP:
      key_released( &event.key );
      break;
    case SDL_MOUSEBUTTONDOWN:
      mouse_pressed( &event.button );
      break;
    case SDL_MOUSEBUTTONUP:
      mouse_released( &event.button );
      break;
    case SDL_MOUSEWHEEL:
      app.mouse.wheel = event.wheel.y;
      break;
    case SDL_CONTROLLERBUTTONDOWN:
      controller_button_pressed( &event.cbutton );
      break;
    case SDL_CONTROLLERBUTTONUP:
      controller_button_released( &event.cbutton );
      break;
    default:
      break;
    }
  }
}

/*
 *
 */
static void
key_pressed( SDL_KeyboardEvent *event ) {
  if ( event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS ) {
    app.keyboard[event->keysym.scancode] = 1;
  }
}

/*
 *
 */
static void
key_released( SDL_KeyboardEvent *event ) {
  if ( event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS ) {
    app.keyboard[event->keysym.scancode] = 0;
  }
}

/*
 *
 */
static void
mouse_pressed( SDL_MouseButtonEvent *event ) {
  app.mouse.button[event->button] = 1;
}

/*
 *
 */
static void
mouse_released( SDL_MouseButtonEvent *event ) {
  app.mouse.button[event->button] = 0;
}

/*
 * Initialize game controller
 */
static void
init_controller( void ) {
  for ( int i = 0; i < SDL_NumJoysticks(); i++ ) {
    if ( SDL_IsGameController( i ) ) {
      controller = SDL_GameControllerOpen( i );
      if ( controller ) {
        break;
      }
    }
  }
}

/*
 * Handle controller button presses
 */
static void
controller_button_pressed( SDL_ControllerButtonEvent *event ) {
  switch ( event->button ) {
    case SDL_CONTROLLER_BUTTON_A:
    case SDL_CONTROLLER_BUTTON_B:
      // A/B button = Space (start game) or action button
      app.keyboard[SDL_SCANCODE_SPACE] = 1;
      button_a_pressed = true;
      break;
    case SDL_CONTROLLER_BUTTON_X:
    case SDL_CONTROLLER_BUTTON_Y:
      // X/Y button = Pause
      app.keyboard[SDL_SCANCODE_P] = 1;
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
      // Move selection up in menu
      selected_button_index--;
      if ( selected_button_index < 0 ) selected_button_index = MAX_MENU_BUTTONS - 1;
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
      // Move selection down in menu
      selected_button_index++;
      if ( selected_button_index >= MAX_MENU_BUTTONS ) selected_button_index = 0;
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
      app.keyboard[SDL_SCANCODE_LEFT] = 1;
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
      app.keyboard[SDL_SCANCODE_RIGHT] = 1;
      break;
    case SDL_CONTROLLER_BUTTON_START:
      // Start = Pause
      app.keyboard[SDL_SCANCODE_P] = 1;
      break;
    case SDL_CONTROLLER_BUTTON_BACK:
      // Back/Select = Escape (return to menu)
      app.keyboard[SDL_SCANCODE_ESCAPE] = 1;
      break;
    case SDL_CONTROLLER_BUTTON_GUIDE:
      break;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
      break;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
      break;
    default:
      break;
  }
}

/*
 * Handle controller button releases
 */
static void
controller_button_released( SDL_ControllerButtonEvent *event ) {
  switch ( event->button ) {
    case SDL_CONTROLLER_BUTTON_A:
    case SDL_CONTROLLER_BUTTON_B:
      app.keyboard[SDL_SCANCODE_SPACE] = 0;
      button_a_pressed = false;
      break;
    case SDL_CONTROLLER_BUTTON_X:
    case SDL_CONTROLLER_BUTTON_Y:
      app.keyboard[SDL_SCANCODE_P] = 0;
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
      app.keyboard[SDL_SCANCODE_LEFT] = 0;
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
      app.keyboard[SDL_SCANCODE_RIGHT] = 0;
      break;
    case SDL_CONTROLLER_BUTTON_START:
      app.keyboard[SDL_SCANCODE_P] = 0;
      break;
    case SDL_CONTROLLER_BUTTON_BACK:
      app.keyboard[SDL_SCANCODE_ESCAPE] = 0;
      break;
  }
}

/*
 * Check if action button was just pressed (for menu selection)
 */
bool
is_action_button_pressed( void ) {
  return button_a_pressed;
}

/*
 * Get current selected button index
 */
int
get_selected_button_index( void ) {
  return selected_button_index;
}
