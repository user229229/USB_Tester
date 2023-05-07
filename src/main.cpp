#include <Arduino.h>
// https://github.com/Danjovic/DigistumpArduino/tree/master/digistump-avr/libraries/DigisparkKeyboard
#include "DigiKeyboard.h" 

#define KEYCODE_NUMLOCK 83
#define int_LED 1

int intr_count = 0;
int sec = 0;

ISR(TIMER0_OVF_vect) // Interrupt vector for Timer0
{
  if (intr_count == 20) // waiting for 63 because to get 1 sec delay
  {
    PORTB ^= (1 << PB1); // toggling the LED
    intr_count = 0; // making intr_count=0 to repeat the count
    ++sec;
  }
  else
    intr_count++; // incrementing c upto 63ello Digispark!Hello Digispark!

}

void timer_setup()
{
  DDRB |= (1 << PB1); // set PB1 as output(LED)
  TCCR0A = 0x00;      // Normal mode
  TCCR0B = 0x00;
  TCCR0B |= (1 << CS00) | (1 << CS02); // prescaling with 1024
  sei();                               // enabling global interrupt
  TCNT0 = 0;
  TIMSK |= (1 << TOIE0); // enabling timer0 interrupt
  PORTB |= (1 << PB1);
}

void setup()
{
  pinMode(int_LED, OUTPUT);
  digitalWrite(int_LED, 1);
  timer_setup();

  DigiKeyboard.sendKeyStroke(0);
}

void loop()
{
    DigiKeyboard.sendKeyPress(KEY_NUM_LOCK);
    DigiKeyboard.sendKeyPress(0);
    DigiKeyboard.delay(200);
  
  if (DigiKeyboard.getLEDs() & NUM_LOCK)
  {
    TIMSK = 0;
    digitalWrite(int_LED, 1);
  }
}