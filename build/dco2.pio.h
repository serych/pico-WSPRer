// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// --- //
// dco //
// --- //

#define dco_wrap_target 0
#define dco_wrap 8

static const uint16_t dco_program_instructions[] = {
            //     .wrap_target
    0x6040, //  0: out    y, 32                      
    0xb822, //  1: mov    x, y            side 2     
    0x0042, //  2: jmp    x--, 2                     
    0xb522, //  3: mov    x, y            side 1 [1] 
    0x0044, //  4: jmp    x--, 4                     
    0xb922, //  5: mov    x, y            side 2 [1] 
    0x0046, //  6: jmp    x--, 6                     
    0xb522, //  7: mov    x, y            side 1 [1] 
    0x0048, //  8: jmp    x--, 8                     
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program dco_program = {
    .instructions = dco_program_instructions,
    .length = 9,
    .origin = -1,
};

static inline pio_sm_config dco_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + dco_wrap_target, offset + dco_wrap);
    sm_config_set_sideset(&c, 3, true, false);
    return c;
}

#define PIOASM_DELAY_CYCLES 3       // fixed delay cycles per halfperiod
/// @brief Inicialization of PIO oscilator
/// @param pio PIO number
/// @param sm Status machine number
/// @param pio offset PIO program offset
/// @param pio pin Output pin (we use two pins for output [pin] and [pin + 1])
/// @return No return. It just starts the PIO 
static inline void dco_program_init(PIO pio, uint sm, uint offset, uint pin)
{
    pio_sm_config c = dco_program_get_default_config(offset);
    sm_config_set_out_shift(&c, true, true, 32);    // Autopull from FIFO
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);  // Join RX and TX FIFOs
    sm_config_set_out_pins(&c, pin, 2);				// Two output pins
    sm_config_set_sideset_pins(&c, pin);            // Sideset pins
    pio_gpio_init(pio, pin);                        // Init first pin
	pio_gpio_init(pio, pin+1); 					    // Init second pin
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 2, true); //Set pins to output
    sm_config_set_clkdiv_int_frac(&c, 1u, 0u);      // PIO CLK = system CLK 
    pio_sm_init(pio, sm, offset, &c);               // PIO initialized 
    pio_sm_set_enabled(pio, sm, true);              // PIO started
}

#endif

