// Copyright (c) 2016, XMOS Ltd, All rights reserved

#include <stdio.h>
#include "xcore_c.h"
#include "debug_print.h"

// For XS1 support all values passed to the event_setup function must have bit 16 set
typedef enum {
  EVENT_CHAN_C = EVENT_ENUM_BASE,
  EVENT_CHAN_D
} event_choice_t;

void channel_example(chanend c, chanend d)
{
  event_clear_all();

  // Setup the channels to generate events
  event_setup_chanend(c, EVENT_CHAN_C);
  event_setup_chanend(d, EVENT_CHAN_D);

  for (int count = 0; count < 10; count++) {
    event_choice_t choice = event_select();
    switch (choice) {
      case EVENT_CHAN_C: {
        // Read value and clear event
        int x = chan_input_word(c);
        debug_printf("Received %d on channel c\n", x);
        break;
      }
      case EVENT_CHAN_D: {
        // Read value and clear event
        int x = chan_input_word(d);
        debug_printf("Received %d on channel d\n", x);
        break;
      }
    }
  }
}
