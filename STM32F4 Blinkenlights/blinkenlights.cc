#include "mbed.h"

DigitalOut myled(PD_15);

int main() {
    while (1) {
        myled = !myled;
        wait(2);
    }
}
