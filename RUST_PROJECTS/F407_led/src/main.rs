#![no_std]
#![no_main]

// Imports
use cortex_m_rt::entry;
use panic_halt as _;
use stm32f4xx_hal::{
    gpio::Pin,
    pac::{self},
    prelude::*,
};

#[entry]
fn main() -> ! {
    // Setup handler for device peripherals
    let dp = pac::Peripherals::take().unwrap();

    // Configure the LED pin as a push pull ouput and obtain handler.
    // On the Nucleo FR401 theres an on-board LED connected to pin PA5.
    let gpiod = dp.GPIOD.split();
    let mut led_green = gpiod.pd12.into_push_pull_output();
    let mut led_orange = gpiod.pd13.into_push_pull_output();
    let mut led_red = gpiod.pd14.into_push_pull_output();
    let mut led_blue = gpiod.pd15.into_push_pull_output();
    // Configure the button pin (if needed) and obtain handler.
    // On the Nucleo FR401 there is a button connected to pin PC13.
    // Pin is input by default
    let gpioa = dp.GPIOA.split();
    let button = gpioa.pa0;

    // Create and initialize a delay variable to manage delay loop
    let mut del_var = 10000000_u32;

    // Initialize LED to on or off
    led_green.set_low();
    led_orange.set_low();
    led_red.set_high();
    led_blue.set_high();

    // Application Loop
    loop {
        // Call delay function and update delay variable once done
        del_var = loop_delay(del_var, &button);

        // Toggle LED
        led_green.toggle();
        led_orange.toggle();
        led_red.toggle();
        led_blue.toggle();

    }
}

// Delay Function
fn loop_delay<const P: char, const N: u8>(mut del: u32, but: &Pin<P, N>) -> u32 {
    // Loop for until value of del
    for _i in 1..del {
        // Check if button got pressed
        if but.is_low() {
            // If button pressed decrease the delay value
            del = del - 2_5000_u32;
            // If updated delay value reaches zero then reset it back to starting value
            if del < 2_5000 {
                del = 10_0000_u32;
            }
            // Exit function returning updated delay value if button pressed
            return del;
        }
    }
    // Exit function returning original delay value if button no pressed (for loop ending naturally)
    del
}

