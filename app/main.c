#include <msp430.h> 


/**
 * main.c
 */


// 2D Array, each array is a row, each item is a column.

char keyPad[][4] = {{'1', '2', '3', 'A'},  // Top Row
                    {'4', '5', '6', 'B'},
                    {'7', '8', '9', 'C'},
                    {'*', '0', '#', 'D'}}; // Bottom Row
/*                    ^              ^
 *                    |              |
 *                    Left Column    Right Column
 */

int column, row = 0;

char keyPressed = 0;

char passCode[] = {'2', '6', '5', '9'};
char inputCode[] = {'0', '0', '0', '0'};
int index = 0;
int state = 0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    //---------------- Configure TB0 ----------------
    TB0CTL |= TBCLR;            // Clear TB0 timer and dividers
    TB0CTL |= TBSSEL__SMCLK;    // Select SMCLK as clock source
    TB0CTL |= MC__UP;            // Choose UP counting

    TB0CCR0 = 1000;             // TTB0CCR0 = 1000, since 1/MHz * 1000 = 1 ms
    TB0CCTL0 &= ~CCIFG;         // Clear CCR0 interrupt flag
    TB0CCTL0 |= CCIE;           // Enable interrupt vector for CCR0

    //---------------- End Configure TB0 ----------------

    //---------------- Configure P3 ----------------
    // Configure P3 for digital I/O
    P3SEL0 &= 0x00;
    P3SEL1 &= 0x00;

    P3DIR &= 0x0F;  // CLEARING bits 7 - 4, that way they are set to INPUT mode
    P3DIR |= 0X0F;  // SETTING bits 0 - 3, that way they are set to OUTPUT mode

    P3REN |= 0xF0;  // ENABLING the resistors for bits 7 - 4
    P3OUT &= 0x00;   // CLEARING output register. This both clears our outputs on bits 0 - 3, and sets pull-down resistors
                    // for bits 7 - 4

    P3IFG = 0x00; // Clear IFG flags for port 3
    //P3IE = 0xF0; // Enable interrupt for bits 7 - 4 on port 3
    //---------------- End Configure P3 ----------------

    __enable_interrupt();       // Enable Global Interrupts
    PM5CTL0 &= ~LOCKLPM5;       // Clear lock bit

    while(1) {}


	return 0;
}

//-------------------------------------------------------------------------------
// Interrupt Service Routines
//-------------------------------------------------------------------------------

//---------------- START ISR_TB0_SwitchColumn ----------------
//-- CCR0 interrupt, read row data from column, shift roll read column right
#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_SwitchColumn(void)
{

    switch (column) {
        case 0:
            P3OUT = 0b00001000; //Enable reading far left column
            break;
        case 1:
            P3OUT = 0b00000100; // Enable reading center left column
            break;
        case 2:
            P3OUT = 0b00000010; // Enable reading center right column
            break;
        default: // Case 3
            P3OUT = 0b00000001; // Enable reading far right column
    }

    if(P3IN > 15){  // If a button is being pressed

        if(P3IN & BIT4){
            row = 3;
        }else if(P3IN & BIT5){
            row = 2;
        }else if(P3IN & BIT6){
            row = 1;
        }else if(P3IN & BIT7){
            row = 0;
        }

        keyPressed = keyPad[row][column];

        while(P3IN > 15){} // Hold until button is released

    }

    if(P3IN < 16){ // Checks if pins 7 - 4 are on, that means a button is being held down; don't shift columns
        if (++column >= 4) {column = 0;} // Add one to column, if it's 4 reset back to 0.
    }
    TB0CCTL0 &= ~TBIFG;
}
//---------------- End ISR_TB0_SwitchColumn ----------------
