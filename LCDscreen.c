#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"

//TimerISR sets this to 1. C programmer should clear to 0.
volatile unsigned char TimerFlag = 0;

//Internal variables for mapping AVR's ISR to our cleaner TImerISR model
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1ms
unsigned long _avr_timer_cntcurr = 0; // Current internal countdown count of 1ms ticks.

void TimerOn(){
    // AVR timer/counter controller register TCCR1
    TCCR1B = 0x0B;
    
    // AVR output compare register OCR1A
    OCR1A = 125;
    
    // AVR timer interrupt mask register
    TIMSK1 = 0x02;
    
    // Initialize AVR counter
    TCNT1 = 0;
    
    // TimerISR will be called every _avr_timer_cntcurr milliseconds
    _avr_timer_cntcurr = _avr_timer_M;
    
    // Enable global interrupts: 0x80: 1000000
    SREG = 0x80;
}

void TimerOff() {
    TCCR1B = 0x00;
}

void TimerISR() {
    unsigned char i;
    for ( i = 0; i < numTasks; i++ ) {
        // Task is ready to tick
        if ( tasks[i]->elapsedTime == tasks[i]->period ) {
            // Setting next state for task
            tasks[i]->state =
            tasks[i]->TickFct(tasks[i]->state);
            // Reset elapsed time for next tick.
            tasks[i]->elapsedTime = 0;
        }
        tasks[i]->elapsedTime += 1;
    }
}

ISR(TIMER1_COMPA_vect) {
    _avr_timer_cntcurr--;
    if (_avr_timer_cntcurr == 0) {
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

//My Code

// SM that keeps track of Score
enum SCORE_LCD { wait_score, increment_score } score_lcd;
void SM_Score(){

  switch(score_lcd){
    case wait_score:
      break;
    case increment_score:
      break;
  }
  
  switch(score_lcd){
    case wait_score:
      break;
    case increment_score:
      break;
  }

}

// SM that keeps track of life
enum LIFE_LCD { wait_life, decrement_life } life_lcd;
void SM_life(){

  switch(life_lcd){
    case wait_life:
      break;
    case decrement_life:
      break;
  }
  
  switch(life_lcd){
    case wait_life:
      break;
    case decrement_life:
      break;
  }

}

// SM that combines all state machines for LCD Screen
enum FULL_LCD { Menu_lcd, Gameplay_lcd, GameOver_lcd} full_lcd;
void SM_Full(void) {

  switch(full_lcd){
    case Menu_lcd:
      break;
    case Gameplay_lcd:
      break;
    case GameOver_lcd:
      break;
  }
  
  switch(screen_lcd){
    case Menu_lcd:
      break;
    case Gameplay_lcd:
      SM_score();
      SM_life();
      break;
    case GameOver_lcd:
      break;
  }
}


int main(void)
{
  
    while(1) {
    }
    return 0;
}
