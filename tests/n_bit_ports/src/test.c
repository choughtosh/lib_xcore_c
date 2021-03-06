// Copyright (c) 2016, XMOS Ltd, All rights reserved

#include <stdio.h>
#include "xcore_c.h"
#include "debug_print.h"

void port_test_output(chanend c)
{
  port p = port_enable(XS1_PORT_4A);

  chan_input_word(c); // Wait for ack

  for (int i = 0; i < 16; ++i) {
    port_output(p, i);
    chan_input_word(c); // Wait for ack
  }

  port_disable(p);

  // Get information about the tile/core running the server for debug messages
  unsigned tile_id = get_local_tile_id();
  unsigned core_id = get_logical_core_id();
  debug_printf("%x:%d: output done\n", tile_id, core_id);
}

/*
 * Test inputting from a port. Waits for the value to change to the desired value.
 */
void port_test_input(chanend c)
{
  port p = port_enable(XS1_PORT_4C);

  port_input(p);
  chan_output_word(c, 0); // Send ack

  for (int i = 0; i < 16; ++i) {
    if (port_input_when_pinseq(p, i) != i) {
      debug_printf("Error\n");
    }
    chan_output_word(c, 0); // Send ack
  }

  port_disable(p);

  // Get information about the tile/core running the server for debug messages
  unsigned tile_id = get_local_tile_id();
  unsigned core_id = get_logical_core_id();
  debug_printf("%x:%d: input done\n", tile_id, core_id);
}