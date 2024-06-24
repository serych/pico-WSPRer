// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// --------- //
// timer_PIO //
// --------- //

#define timer_PIO_wrap_target 0
#define timer_PIO_wrap 13

static const uint16_t timer_PIO_program_instructions[] = {
            //     .wrap_target
    0xa04b, //  0: mov    y, !null                   
    0xa02b, //  1: mov    x, !null                   
    0x2020, //  2: wait   0 pin, 0                   
    0x20a0, //  3: wait   1 pin, 0                   
    0x0086, //  4: jmp    y--, 6                     
    0x0000, //  5: jmp    0                          
    0x00c4, //  6: jmp    pin, 4                     
    0x00ca, //  7: jmp    pin, 10                    
    0x0047, //  8: jmp    x--, 7                     
    0x0000, //  9: jmp    0                          
    0xa0ca, // 10: mov    isr, !y                    
    0x8000, // 11: push   noblock                    
    0xa0c9, // 12: mov    isr, !x                    
    0x8000, // 13: push   noblock                    
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program timer_PIO_program = {
    .instructions = timer_PIO_program_instructions,
    .length = 14,
    .origin = -1,
};

static inline pio_sm_config timer_PIO_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + timer_PIO_wrap_target, offset + timer_PIO_wrap);
    return c;
}

static inline void timer_PIO_program_init(PIO pio, uint sm, uint offset) {
	pio_sm_config c = timer_PIO_program_get_default_config(offset);
	sm_config_set_in_pins(&c, 2);  // Use GPIO 2 for input (PPS)
	sm_config_set_jmp_pin(&c, 2);  // Use GPIO 2 for input (PPS)
    pio_sm_set_consecutive_pindirs(pio, sm, 2, 1, false);  // Set pin 2 as input
	pio_sm_init(pio, sm, offset, &c);
	pio_sm_set_enabled(pio, sm, true);
}

#endif

