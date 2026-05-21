#include <reg51.h>
#include <stdio.h>

// LCD control pins
sbit RS = P2^0;
sbit EN = P2^1;

// Hall sensor input
sbit hall = P3^2;

// Variables
unsigned int rotationCount = 0;
float distance = 0;
float fare = 0;

float baseFare = 30;
float ratePerKm = 15;
float ratePerMin = 2;

unsigned int timeSeconds = 0;

// Delay function
void delay(unsigned int ms) {
    unsigned int i, j;
    for(i=0;i<ms;i++)
        for(j=0;j<1275;j++);
}

// LCD functions
void lcd_cmd(unsigned char cmd) {
    P1 = cmd;
    RS = 0;
    EN = 1;
    delay(2);
    EN = 0;
}

void lcd_data(unsigned char dat) {
    P1 = dat;
    RS = 1;
    EN = 1;
    delay(2);
    EN = 0;
}

void lcd_init() {
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

// Interrupt for hall sensor
void external0_ISR(void) interrupt 0 {
    rotationCount++;
}

// Timer interrupt (1 sec)
void timer0_ISR(void) interrupt 1 {
    timeSeconds++;
}

// Main
void main() {
    char buffer[16];

    lcd_init();

    // Enable interrupts
    IT0 = 1;  // Edge triggered
    EX0 = 1;  // Enable external interrupt
    EA = 1;   // Global interrupt

    // Timer setup (for time counting)
    TMOD = 0x01;
    TH0 = 0xFC;  // approx 1 sec delay
    TL0 = 0x66;
    ET0 = 1;
    TR0 = 1;

    while(1) {

        // Distance calculation
        distance = (rotationCount * 0.2) / 1000; // km

        // Time in minutes
        float timeMinutes = timeSeconds / 60.0;

        // Fare calculation
        fare = baseFare + (distance * ratePerKm) + (timeMinutes * ratePerMin);

        // Display Distance
        lcd_cmd(0x80);
        sprintf(buffer, "D:%.2f km", distance);
        for(int i=0; buffer[i]!=0; i++)
            lcd_data(buffer[i]);

        // Display Fare
        lcd_cmd(0xC0);
        sprintf(buffer, "Fare:%.2f", fare);
        for(int i=0; buffer[i]!=0; i++)
            lcd_data(buffer[i]);

        delay(500);
    }
}