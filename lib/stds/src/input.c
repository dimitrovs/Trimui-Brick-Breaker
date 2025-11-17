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

  int event_count = 0;
  while ( SDL_PollEvent( &event ) ) {
    event_count++;
    SDL_GetMouseState( &app.mouse.x, &app.mouse.y );
    
    // Log all events for debugging
    if ( event.type != SDL_MOUSEMOTION ) {  // Don't spam with mouse motion
      printf("DEBUG: SDL Event type: %d\n", event.type);
    }
    
    switch ( event.type ) {
    case SDL_QUIT:
      printf("DEBUG: SDL_QUIT event\n");
      exit( EXIT_SUCCESS );
      break;
    case SDL_KEYDOWN:
      printf("DEBUG: SDL_KEYDOWN event - scancode: %d\n", event.key.keysym.scancode);
      key_pressed( &event.key );
      break;
    case SDL_KEYUP:
      printf("DEBUG: SDL_KEYUP event - scancode: %d\n", event.key.keysym.scancode);
      key_released( &event.key );
      break;
    case SDL_MOUSEBUTTONDOWN:
      printf("DEBUG: SDL_MOUSEBUTTONDOWN at %d,%d button: %d\n", app.mouse.x, app.mouse.y, event.button.button);
      mouse_pressed( &event.button );
      break;
    case SDL_MOUSEBUTTONUP:
      printf("DEBUG: SDL_MOUSEBUTTONUP at %d,%d button: %d\n", app.mouse.x, app.mouse.y, event.button.button);
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
  
  if ( event_count > 0 ) {
    printf("DEBUG: Processed %d events this frame\n", event_count);
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
  printf("DEBUG: Checking for game controllers...\n");
  for ( int i = 0; i < SDL_NumJoysticks(); i++ ) {
    if ( SDL_IsGameController( i ) ) {
      controller = SDL_GameControllerOpen( i );
      if ( controller ) {
        printf("DEBUG: Controller found and opened: %s\n", SDL_GameControllerName( controller ));
        break;
      }
    }
  }
  if ( !controller ) {
    printf("DEBUG: No game controller found\n");
  }
}

/*
 * Handle controller button presses
 */
static void
controller_button_pressed( SDL_ControllerButtonEvent *event ) {
  printf("DEBUG: Controller button pressed: %d\n", event->button);
  
  switch ( event->button ) {
    case SDL_CONTROLLER_BUTTON_A:
    case SDL_CONTROLLER_BUTTON_B:
      // A/B button = Space (start game) or action button
      app.keyboard[SDL_SCANCODE_SPACE] = 1;
      button_a_pressed = true;
      printf("DEBUG: A/B button pressed - action triggered (selected button: %d)\n", selected_button_index);
      break;
    case SDL_CONTROLLER_BUTTON_X:
    case SDL_CONTROLLER_BUTTON_Y:
      // X/Y button = Pause
      app.keyboard[SDL_SCANCODE_P] = 1;
      printf("DEBUG: X/Y button pressed - pause\n");
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
      // Move selection up in menu
      selected_button_index--;
      if ( selected_button_index < 0 ) selected_button_index = MAX_MENU_BUTTONS - 1;
      printf("DEBUG: DPAD UP - button index now: %d\n", selected_button_index);
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
      // Move selection down in menu
      selected_button_index++;
      if ( selected_button_index >= MAX_MENU_BUTTONS ) selected_button_index = 0;
      printf("DEBUG: DPAD DOWN - button index now: %d\n", selected_button_index);
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
      app.keyboard[SDL_SCANCODE_LEFT] = 1;
      printf("DEBUG: DPAD LEFT pressed\n");
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
      app.keyboard[SDL_SCANCODE_RIGHT] = 1;
      printf("DEBUG: DPAD RIGHT pressed\n");
      break;
    case SDL_CONTROLLER_BUTTON_START:
      // Start = Pause
      app.keyboard[SDL_SCANCODE_P] = 1;
      printf("DEBUG: START pressed - pause\n");
      break;
    case SDL_CONTROLLER_BUTTON_BACK:
      // Back/Select = Escape (return to menu)
      app.keyboard[SDL_SCANCODE_ESCAPE] = 1;
      printf("DEBUG: SELECT/BACK pressed - return to menu\n");
      break;
    case SDL_CONTROLLER_BUTTON_GUIDE:
      printf("DEBUG: MENU pressed\n");
      break;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
      printf("DEBUG: L1 pressed\n");
      break;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
      printf("DEBUG: R1 pressed\n");
      break;
    default:
      printf("DEBUG: Unknown button %d pressed\n", event->button);
      break;
  }
}

/*
 * Handle controller button releases
 */
static void
controller_button_released( SDL_ControllerButtonEvent *event ) {
  printf("DEBUG: Controller button released: %d\n", event->button);
  
  switch ( event->button ) {
    case SDL_CONTROLLER_BUTTON_A:
    case SDL_CONTROLLER_BUTTON_B:
      app.keyboard[SDL_SCANCODE_SPACE] = 0;
      button_a_pressed = false;
      printf("DEBUG: A/B button released\n");
      break;
    case SDL_CONTROLLER_BUTTON_X:
    case SDL_CONTROLLER_BUTTON_Y:
      app.keyboard[SDL_SCANCODE_P] = 0;
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
      app.keyboard[SDL_SCANCODE_LEFT] = 0;
      printf("DEBUG: DPAD LEFT released\n");
      break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
      app.keyboard[SDL_SCANCODE_RIGHT] = 0;
      printf("DEBUG: DPAD RIGHT released\n");
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
