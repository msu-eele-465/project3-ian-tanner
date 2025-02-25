#include "msp430fr2355.h"
#include <msp430.h>
#include <stdbool.h>
//Global variables
int rgb_led = 0;
int led_bar = 0;
int inner_delay = 0;
int outer_delay = 0;
int step_0 = 0;
int step_1 = 0;
int step_2 = 0;
int step_3 = 0;
int step_4 = 0;
int transition = 32768;
float trans_scalar = 0;
unsigned char counter_1 = 0;
unsigned char counter_2 = 255;

/**
 * main.c
 */
int main(void)
{

	 WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

	 //Setup LEDs

	 //Heartbeat LEDs
	 P1DIR |= BIT0;            //Config P1.0 (LED1) as output
	 P1OUT |= BIT0;            //LED1 = 1 to start

	 P6DIR |= BIT6;            //Config P6.6 (LED2) as output
	 P6OUT &= ~BIT6;           //LED2 = 0 to start

	 //RGB LEDs
	 P1DIR |= BIT7;            //Config P1.0 (RED) as output
	 P1OUT &= ~BIT7;           //RED = 0 to start

	 P1DIR |= BIT6;            //Config P6.6 (BLUE) as output
	 P1OUT &= ~BIT6;           //BLUE = 0 to start

     P1DIR |= BIT5;            //Config P1.0 (GREEN) as output
	 P1OUT &= ~BIT5;           //GREEN = 0 to start

	 //LED box
	 P1DIR |= BIT2;            //Config P1.2 (A) as output
	 P1OUT &= ~BIT2;           //A = 0 to start

	 P1DIR |= BIT3;            //Config P1.3 (B) as output
	 P1OUT &= ~BIT3;           //B = 0 to start

     P1DIR |= BIT1;            //Config P1.1 (C) as output
	 P1OUT &= ~BIT1;           //C = 0 to start

	 P5DIR |= BIT4;            //Config P5.4 (D) as output
	 P5OUT &= ~BIT4;           //D = 0 to start

	 P4DIR |= BIT5;            //Config P4.5 (E) as output
	 P4OUT &= ~BIT5;           //E = 0 to start

     P5DIR |= BIT0;            //Config P5.0 (F) as output
	 P5OUT &= ~BIT0;           //F = 0 to start

	 P5DIR |= BIT2;            //Config P5.2 (G) as output
	 P5OUT &= ~BIT2;           //G = 0 to start

	 P5DIR |= BIT1;            //Config P5.1 (H) as output
	 P5OUT &= ~BIT1;           //H = 0 to start


	 PM5CTL0 &= ~LOCKLPM5;

	 //Setup Timers
	 TB1CTL |= TBCLR;          //clear timer1 and dividers
	 TB1CTL |= TBSSEL__ACLK;   //source = ACLK
	 TB1CTL |= MC__UP;         //mode = up
	 TB2CTL |= TBCLR;          //clear timer2 and dividers
	 TB2CTL |= TBSSEL__ACLK;   //source = ACLK
	 TB3CTL |= MC__UP;         //mode = up
	 TB3CTL |= TBCLR;          //clear timer3 and dividers
	 TB3CTL |= TBSSEL__ACLK;   //source = ACLK
	 TB2CTL |= MC__UP;         //mode = up
	 TB1CCR0 = 32768;		   //TB1CCR0 = 32768
	 TB2CCR0 = 500;            //TB2CCR0 = 500
	 TB2CCR1 = 27;             //TB2CCR1 = 27
	 TB3CCR0 = transition;          //TB3CCR0 = 32768
	 
	 TB1CCTL0 |= CCIE;         //enable TB1 CCR0 Overflow IRQ
	 TB1CCTL0 &= ~CCIFG;       //clear CCR0 flag
	 TB2CCTL0 |= CCIE;         //enable TB2 CCR0 Overflow IRQ
	 TB2CCTL0 &= ~CCIFG;       //clear CCR0 flag
	 TB2CCTL1 |= CCIE;         //enable TB2 CCR1 Overflow IRQ
	 TB2CCTL1 &= ~CCIFG;       //clear CCR1 flag
	 TB3CCTL0 |= CCIE;         //enable TB3 CCR0 Overflow IRQ
	 TB3CCTL0 &= ~CCIFG;       //clear CCR0 flag

	 __enable_interrupt();     //enable maskable IRQs

	 //main loop
	 while(1)                  //loop forever
	 {               
	 	
	 }

	return 0;
}

//interrupt service routines
#pragma vector = TIMER1_B0_VECTOR
__interrupt void ISR_TB1_CCR0(void)
{
	//Heartbeat LEDs
    P1OUT ^= BIT0;				 //Toggle P1.0(LED1)
	P6OUT ^= BIT6;			     //Toggle P6.6(LED2)
	
    TB1CCTL0 &= ~CCIFG;          //clear CCR0 flag

}

#pragma vector = TIMER2_B0_VECTOR
__interrupt void ISR_TB2_CCR0(void)
{
	
    if (rgb_led == 0)			//locked mode
	{

		P1OUT |= BIT7;

	}

	else if (rgb_led == 1)		//unlocking mode
	{

		P1OUT |= BIT7;
		P1OUT |= BIT5;

	}

	else if (rgb_led == 2)		//unlocked mode
	{

		P1OUT |= BIT6;
		P1OUT |= BIT5;

	}

	else if (rgb_led == 3)		//LED pattern 0
	{
		
		P1OUT |= BIT7;
		P1OUT |= BIT6;
		P1OUT |= BIT5;

	}

	else if (rgb_led == 4)		//LED pattern 1
	{

		P1OUT |= BIT7;
		P1OUT |= BIT6;
		P1OUT |= BIT5;

	}

	else if (rgb_led == 5)		//LED pattern 2
	{

		P1OUT |= BIT7;
		P1OUT |= BIT6;
		
	}

	else if (rgb_led == 6)		//LED pattern 3
	{

		P1OUT |= BIT7;
		P1OUT |= BIT5;

	}

	else if (rgb_led == 7)		//LED pattern 4
	{

		P1OUT |= BIT6;
		P1OUT |= BIT5;

	}

	else if (rgb_led == 8)		//LED pattern 5
	{

		P1OUT |= BIT7;
		P1OUT |= BIT6;
		P1OUT |= BIT5;

	}

	else if (rgb_led == 9)		//LED pattern 6
	{

		P1OUT |= BIT7;
		P1OUT |= BIT6;

	}

	else if (rgb_led == 10)		//LED pattern 7
	{

		P1OUT |= BIT7;
		P1OUT |= BIT5;

	}
	
    TB2CCTL0 &= ~CCIFG;          //clear CCR0 flag

}

#pragma vector = TIMER2_B1_VECTOR
__interrupt void ISR_TB2_CCR1(void){

    if (rgb_led == 0)			//locked mode
	{

		P1OUT |= BIT7;

	}

	else if (rgb_led == 1)		//unlocking mode
	{

		TB2CCR1 = 27;           //TB2CCR1 = 27
		P1OUT &= ~BIT5;

	}

	else if (rgb_led == 2)		//unlocked
	{

		TB2CCR1 = 200;          //TB2CCR1 = 200
		P1OUT &= ~BIT5;

	}

	else if (rgb_led == 3)		//LED pattern 0
	{

		TB2CCR1 = 27;           //TB2CCR1 = 27
		P1OUT &= ~BIT6;
		P1OUT &= ~BIT5;

	}

	else if (rgb_led == 4)		//LED pattern 1
	{

		TB2CCR1 = 200;          //TB2CCR1 = 200
		P1OUT &= ~BIT7;
		P1OUT &= ~BIT6;
		P1OUT &= ~BIT5;

	}

	else if (rgb_led == 5)		//LED pattern 2
	{

		TB2CCR1 = 27;           //TB2CCR1 = 27
		P1OUT &= ~BIT7;
		P1OUT &= ~BIT6;

	}

	else if (rgb_led == 6)		//LED pattern 3
	{

		TB2CCR1 = 200;          //TB2CCR1 = 200
		P1OUT &= ~BIT7;

	}

	else if (rgb_led == 7)		//LED pattern 4
	{

		TB2CCR1 = 200;           //TB2CCR1 = 200
		P1OUT &= ~BIT6;

	}

	else if (rgb_led == 8)		//LED pattern 5
	{

		TB2CCR1 = 27;          //TB2CCR1 = 27
		P1OUT &= ~BIT6;
		P1OUT &= ~BIT5;

	}

	else if (rgb_led == 9)		//LED pattern 6
	{

		TB2CCR1 = 27;           //TB2CCR1 = 27
		P1OUT &= ~BIT6;

	}

	else if (rgb_led == 10)		//LED pattern 7
	{

		TB2CCR1 = 100;          //TB2CCR1 = 100
		P1OUT &= ~BIT5;

	}

    TB2CCTL1 &= ~CCIFG;         //clear CCR1 flag

}

#pragma vector = TIMER3_B0_VECTOR
__interrupt void ISR_TB3_CCR0(void)
{

    switch (led_bar)
	{

		case 0:
					//LEDs off to start
	 				P1OUT &= ~BIT2;           //A = 0 to start
	 				P1OUT &= ~BIT3;           //B = 0 to start
	 				P1OUT &= ~BIT1;           //C = 0 to start
	 				P5OUT &= ~BIT4;           //D = 0 to start
	 				P4OUT &= ~BIT5;           //E = 0 to start
	 				P5OUT &= ~BIT0;           //F = 0 to start
	 				P5OUT &= ~BIT2;           //G = 0 to start
	 				P5OUT &= ~BIT1;           //H = 0 to start
					break;

		case 1:
					//LED pattern 0
					TB3CCR0 = transition;     //TB3CCR0 = base transition period

	 				P1OUT |=  BIT2;           //A = 1 
	 				P1OUT &= ~BIT3;           //B = 0 
	 				P1OUT |=  BIT1;           //C = 1 
	 				P5OUT &= ~BIT4;           //D = 0 
	 				P4OUT |=  BIT5;           //E = 1 
	 				P5OUT &= ~BIT0;           //F = 0 
	 				P5OUT |=  BIT2;           //G = 1 
	 				P5OUT &= ~BIT1;           //H = 0 
					break;

		case 2:
					//LED pattern 1
					TB3CCR0 = transition;     //TB3CCR0 = base transition period

					if (step_0 == 0)
					{

	 					P1OUT |=  BIT2;       //A = 1 
	 					P1OUT &= ~BIT3;       //B = 0 
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT &= ~BIT4;       //D = 0 
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT &= ~BIT0;       //F = 0 
	 					P5OUT |=  BIT2;       //G = 1 
	 					P5OUT &= ~BIT1;       //H = 0 
						step_0 = 1;

					}

					else if (step_0 == 1)
					{

	 					P1OUT &= ~BIT2;       //A = 0 
	 					P1OUT |=  BIT3;       //B = 1
	 					P1OUT &= ~BIT1;       //C = 0 
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT |=  BIT0;       //F = 1 
	 					P5OUT &= ~BIT2;       //G = 0 
	 					P5OUT |=  BIT1;       //H = 1 
						step_0 = 0;

					}

					break;

		case 3:
					//LED pattern 2
					trans_scalar = 2;					   //trans_scalar = 2
					TB3CCR0 = transition/trans_scalar;     //TB3CCR0 = base transition period / trans_scalar

					//Set A (bit 0 of the counter)
					if (counter_1 & 0x01) 
					{

        				P1OUT |= BIT2;

    				} 
					
					else 
					{

       				 	P1OUT &= ~BIT2;

    				}

    				//Set B (bit 1 of the counter)
    				if (counter_1 & 0x02) 
					{

       					 P1OUT |= BIT3;

   					} 

					else 
					{

        				P1OUT &= ~BIT3;

    				}

    				//Set C (bit 2 of the counter)
    				if (counter_1 & 0x04) 
					{

        				P1OUT |= BIT1;

    				} 

					else 
					{

        				P1OUT &= ~BIT1;

    				}

    				//Set D (bit 3 of the counter)
    				if (counter_1 & 0x08) 
					{

        				P5OUT |= BIT4;

    				} 

					else 
					{

        				P5OUT &= ~BIT4;

   		 			}

    				//Set E (bit 4 of the counter)
    				if (counter_1 & 0x10) 
					{

        				P4OUT |= BIT5;

    				} 
					
					else 
					{

        				P4OUT &= ~BIT5;

    					}

    				//Set F (bit 5 of the counter)
    				if (counter_1 & 0x20) 
					{

        				P5OUT |= BIT0;

    				} 
					
					else 
					{

        				P5OUT &= ~BIT0;

    				}

    				//Set G (bit 6 of the counter)
    				if (counter_1 & 0x40) 
					{

       	 				P5OUT |= BIT2;

    				} 
					
					else 
					{

        				P5OUT &= ~BIT2;

    				}

    				//Set H (bit 7 of the counter)
    				if (counter_1 & 0x80) 
					{

        				P5OUT |= BIT1;

    				} 
					
					else 
					{

        				P5OUT &= ~BIT1;

    				}

					counter_1++;            //increment counter

					break;

		case 4:
				//LED pattern 3
				trans_scalar = 2;					   //trans_scalar = 2
				TB3CCR0 = transition/trans_scalar;     //TB3CCR0 = base transition period / trans_scalar

				if (step_1 == 0)
				{

					P1OUT &= ~BIT2;       //A = 0 
	 				P1OUT &= ~BIT3;       //B = 0 
	 				P1OUT &= ~BIT1;       //C = 0 
	 				P5OUT |=  BIT4;       //D = 1
	 				P4OUT |=  BIT5;       //E = 1 
	 				P5OUT &= ~BIT0;       //F = 0 
	 				P5OUT &= ~BIT2;       //G = 0 
	 				P5OUT &= ~BIT1;       //H = 0 

					step_1 = 1;           //increment step_1
				}

				else if (step_1 == 1)
				{

					P1OUT &= ~BIT2;       //A = 0 
	 				P1OUT &= ~BIT3;       //B = 0 
	 				P1OUT |=  BIT1;       //C = 1
	 				P5OUT &= ~BIT4;       //D = 0 
	 				P4OUT &= ~BIT5;       //E = 0 
	 				P5OUT |=  BIT0;       //F = 1
	 				P5OUT &= ~BIT2;       //G = 0 
	 				P5OUT &= ~BIT1;       //H = 0 

					step_1 = 2;           //increment step_1
				}

				else if (step_1 == 2)
				{

					P1OUT &= ~BIT2;       //A = 0 
	 				P1OUT |=  BIT3;       //B = 1
	 				P1OUT &= ~BIT1;       //C = 0 
	 				P5OUT &= ~BIT4;       //D = 0 
	 				P4OUT &= ~BIT5;       //E = 0 
	 				P5OUT &= ~BIT0;       //F = 0 
	 				P5OUT |=  BIT2;       //G = 1
	 				P5OUT &= ~BIT1;       //H = 0 

					step_1 = 3;           //increment step_1
				}

				else if (step_1 == 3)
				{

					P1OUT |=  BIT2;       //A = 1
	 				P1OUT &= ~BIT3;       //B = 0 
	 				P1OUT &= ~BIT1;       //C = 0 
	 				P5OUT &= ~BIT4;       //D = 0 
	 				P4OUT &= ~BIT5;       //E = 0 
	 				P5OUT &= ~BIT0;       //F = 0 
	 				P5OUT &= ~BIT2;       //G = 0 
	 				P5OUT |=  BIT1;       //H = 1 

					step_1 = 4;			  //increment step_1
				}

				else if (step_1 == 4)
				{

					P1OUT &= ~BIT2;       //A = 0 
	 				P1OUT |=  BIT3;       //B = 1
	 				P1OUT &= ~BIT1;       //C = 0 
	 				P5OUT &= ~BIT4;       //D = 0 
	 				P4OUT &= ~BIT5;       //E = 0 
	 				P5OUT &= ~BIT0;       //F = 0 
	 				P5OUT |=  BIT2;       //G = 1
	 				P5OUT &= ~BIT1;       //H = 0 

					step_1 = 5;			  //increment step_1
				}

				else if (step_1 == 5)
				{

					P1OUT &= ~BIT2;       //A = 0 
	 				P1OUT &= ~BIT3;       //B = 0 
	 				P1OUT |=  BIT1;       //C = 1 
	 				P5OUT &= ~BIT4;       //D = 0 
	 				P4OUT &= ~BIT5;       //E = 0 
	 				P5OUT |=  BIT0;       //F = 1 
	 				P5OUT &= ~BIT2;       //G = 0 
	 				P5OUT &= ~BIT1;       //H = 0 

					step_1 = 0;           //repeat step_1
				}

				break;

				case 5:
					//LED pattern 4
					trans_scalar = 4;					   //trans_scalar = 4
					TB3CCR0 = transition/trans_scalar;     //TB3CCR0 = base transition period / trans_scalar

					//Set A (bit 0 of the counter)
					if (counter_2 & 0x01) 
					{

        				P1OUT |= BIT2;

    				} 
					
					else 
					{

       				 	P1OUT &= ~BIT2;

    				}

    				//Set B (bit 1 of the counter)
    				if (counter_2 & 0x02) 
					{

       					 P1OUT |= BIT3;

   					} 

					else 
					{

        				P1OUT &= ~BIT3;

    				}

    				//Set C (bit 2 of the counter)
    				if (counter_2 & 0x04) 
					{

        				P1OUT |= BIT1;

    				} 

					else 
					{

        				P1OUT &= ~BIT1;

    				}

    				//Set D (bit 3 of the counter)
    				if (counter_2 & 0x08) 
					{

        				P5OUT |= BIT4;

    				} 

					else 
					{

        				P5OUT &= ~BIT4;

   		 			}

    				//Set E (bit 4 of the counter)
    				if (counter_2 & 0x10) 
					{

        				P4OUT |= BIT5;

    				} 
					
					else 
					{

        				P4OUT &= ~BIT5;

    					}

    				//Set F (bit 5 of the counter)
    				if (counter_2 & 0x20) 
					{

        				P5OUT |= BIT0;

    				} 
					
					else 
					{

        				P5OUT &= ~BIT0;

    				}

    				//Set G (bit 6 of the counter)
    				if (counter_2 & 0x40) 
					{

       	 				P5OUT |= BIT2;

    				} 
					
					else 
					{

        				P5OUT &= ~BIT2;

    				}

    				//Set H (bit 7 of the counter)
    				if (counter_2 & 0x80) 
					{

        				P5OUT |= BIT1;

    				} 
					
					else 
					{

        				P5OUT &= ~BIT1;

    				}

					counter_2--;            //decrement counter

					break;

				case 6:
					//LED pattern 5
					trans_scalar = 1.5;					   //trans_scalar = 1.5
					TB3CCR0 = transition*trans_scalar;     //TB3CCR0 = base transition period * trans_scalar

					if (step_2 == 0)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT &= ~BIT3;       //B = 0 
	 					P1OUT &= ~BIT1;       //C = 0 
	 					P5OUT &= ~BIT4;       //D = 0
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT &= ~BIT0;       //F = 0 
	 					P5OUT &= ~BIT2;       //G = 0 
	 					P5OUT &= ~BIT1;       //H = 0 

						step_2 = 1;           //increment step_1
					}

					else if (step_2 == 1)
					{

						P1OUT &= ~BIT2;       //A = 0 
	 					P1OUT |=  BIT3;       //B = 1 
	 					P1OUT &= ~BIT1;       //C = 0
	 					P5OUT &= ~BIT4;       //D = 0 
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT &= ~BIT0;       //F = 0
	 					P5OUT &= ~BIT2;       //G = 0 
	 					P5OUT &= ~BIT1;       //H = 0 

						step_2 = 2;           //increment step_1
					}

					else if (step_2 == 2)
					{

						P1OUT &= ~BIT2;       //A = 0 
	 					P1OUT &= ~BIT3;       //B = 0
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT &= ~BIT4;       //D = 0 
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT &= ~BIT0;       //F = 0 
	 					P5OUT &= ~BIT2;       //G = 0
	 					P5OUT &= ~BIT1;       //H = 0 

						step_2 = 3;           //increment step_1
					}

					else if (step_2 == 3)
					{

						P1OUT &= ~BIT2;       //A = 0
	 					P1OUT &= ~BIT3;       //B = 0 
	 					P1OUT &= ~BIT1;       //C = 0 
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT &= ~BIT0;       //F = 0 
	 					P5OUT &= ~BIT2;       //G = 0 
	 					P5OUT &= ~BIT1;       //H = 0 

						step_2 = 4;			  //increment step_1
					}

					else if (step_2 == 4)
					{

						P1OUT &= ~BIT2;       //A = 0 
	 					P1OUT &= ~BIT3;       //B = 0
	 					P1OUT &= ~BIT1;       //C = 0 
	 					P5OUT &= ~BIT4;       //D = 0 
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT &= ~BIT0;       //F = 0 
	 					P5OUT &= ~BIT2;       //G = 0
	 					P5OUT &= ~BIT1;       //H = 0 

						step_2 = 5;			  //increment step_1
					}

					else if (step_2 == 5)
					{

						P1OUT &= ~BIT2;       //A = 0 
	 					P1OUT &= ~BIT3;       //B = 0 
	 					P1OUT &= ~BIT1;       //C = 0 
	 					P5OUT &= ~BIT4;       //D = 0 
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT |=  BIT0;       //F = 1 
	 					P5OUT &= ~BIT2;       //G = 0 
	 					P5OUT &= ~BIT1;       //H = 0 

						step_2 = 6;           //repeat step_1
					}

					else if (step_2 == 6)
					{

						P1OUT &= ~BIT2;       //A = 0 
	 					P1OUT &= ~BIT3;       //B = 0
	 					P1OUT &= ~BIT1;       //C = 0 
	 					P5OUT &= ~BIT4;       //D = 0 
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT &= ~BIT0;       //F = 0 
	 					P5OUT |=  BIT2;       //G = 1
	 					P5OUT &= ~BIT1;       //H = 0 

						step_2 = 7;			  //increment step_1
					}

					else if (step_2 == 7)
					{

						P1OUT &= ~BIT2;       //A = 0 
	 					P1OUT &= ~BIT3;       //B = 0 
	 					P1OUT &= ~BIT1;       //C = 0 
	 					P5OUT &= ~BIT4;       //D = 0 
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT &= ~BIT0;       //F = 0 
	 					P5OUT &= ~BIT2;       //G = 0 
	 					P5OUT |=  BIT1;       //H = 1 

						step_2 = 0;           //repeat step_1
					}

					break;

				case 7:
					//LED pattern 6
					trans_scalar = 2;					       //trans_scalar = 0.5
					TB3CCR0 = transition/trans_scalar;     //TB3CCR0 = base transition period / trans_scalar

					if (step_3 == 0)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT |=  BIT3;       //B = 1 
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT |=  BIT4;       //D = 1
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT |=  BIT0;       //F = 1 
	 					P5OUT |=  BIT2;       //G = 1 
	 					P5OUT &= ~BIT1;       //H = 0 

						step_3 = 1;           //increment step_1
					}

					else if (step_3 == 1)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT |=  BIT3;       //B = 1 
	 					P1OUT |=  BIT1;       //C = 1
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT |=  BIT0;       //F = 1
	 					P5OUT &= ~BIT2;       //G = 0 
	 					P5OUT |=  BIT1;       //H = 1 

						step_3 = 2;           //increment step_1
					}

					else if (step_3 == 2)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT |=  BIT3;       //B = 1
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT &= ~BIT0;       //F = 0 
	 					P5OUT |=  BIT2;       //G = 1
	 					P5OUT |=  BIT1;       //H = 1 

						step_3 = 3;           //increment step_1
					}

					else if (step_3 == 3)
					{

						P1OUT |=  BIT2;       //A = 1
	 					P1OUT |=  BIT3;       //B = 1 
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT |=  BIT0;       //F = 1 
	 					P5OUT |=  BIT2;       //G = 1 
	 					P5OUT |=  BIT1;       //H = 1 

						step_3 = 4;			  //increment step_1
					}

					else if (step_3 == 4)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT |=  BIT3;       //B = 1
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT &= ~BIT4;       //D = 0 
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT |=  BIT0;       //F = 1 
	 					P5OUT |=  BIT2;       //G = 1
	 					P5OUT |=  BIT1;       //H = 1 

						step_3 = 5;			  //increment step_1
					}

					else if (step_3 == 5)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT |=  BIT3;       //B = 1 
	 					P1OUT &= ~BIT1;       //C = 0 
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT |=  BIT0;       //F = 1 
	 					P5OUT |=  BIT2;       //G = 1 
	 					P5OUT |=  BIT1;       //H = 1 

						step_3 = 6;           //repeat step_1
					}

					else if (step_3 == 6)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT &= ~BIT3;       //B = 0
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT |=  BIT0;       //F = 1 
	 					P5OUT |=  BIT2;       //G = 1
	 					P5OUT |=  BIT1;       //H = 1 

						step_3 = 7;			  //increment step_1
					}

					else if (step_3 == 7)
					{

						P1OUT &= ~BIT2;       //A = 0 
	 					P1OUT |=  BIT3;       //B = 1 
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT |=  BIT0;       //F = 1 
	 					P5OUT |=  BIT2;       //G = 1 
	 					P5OUT |=  BIT1;       //H = 1 

						step_3 = 0;           //repeat step_1
					}

					break;
			
				case 8:
					//LED pattern 7
					TB3CCR0 = transition;     //TB3CCR0 = base transition period

					if (step_4 == 0)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT &= ~BIT3;       //B = 0 
	 					P1OUT &= ~BIT1;       //C = 0 
	 					P5OUT &= ~BIT4;       //D = 0
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT &= ~BIT0;       //F = 0 
	 					P5OUT &= ~BIT2;       //G = 0 
	 					P5OUT &= ~BIT1;       //H = 0 

						step_4 = 1;           //increment step_1
					}

					else if (step_4 == 1)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT |=  BIT3;       //B = 1 
	 					P1OUT &= ~BIT1;       //C = 0
	 					P5OUT &= ~BIT4;       //D = 0 
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT &= ~BIT0;       //F = 0
	 					P5OUT &= ~BIT2;       //G = 0 
	 					P5OUT &= ~BIT1;       //H = 0 

						step_4 = 2;           //increment step_1
					}

					else if (step_4 == 2)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT |=  BIT3;       //B = 1
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT &= ~BIT4;       //D = 0 
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT &= ~BIT0;       //F = 0 
	 					P5OUT &= ~BIT2;       //G = 0
	 					P5OUT &= ~BIT1;       //H = 0 

						step_4 = 3;           //increment step_1
					}

					else if (step_4 == 3)
					{

						P1OUT |=  BIT2;       //A = 1
	 					P1OUT |=  BIT3;       //B = 1 
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT &= ~BIT5;       //E = 0 
	 					P5OUT &= ~BIT0;       //F = 0 
	 					P5OUT &= ~BIT2;       //G = 0 
	 					P5OUT &= ~BIT1;       //H = 0 

						step_4 = 4;			  //increment step_1
					}

					else if (step_4 == 4)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT |=  BIT3;       //B = 1
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT &= ~BIT0;       //F = 0 
	 					P5OUT &= ~BIT2;       //G = 0
	 					P5OUT &= ~BIT1;       //H = 0 

						step_4 = 5;			  //increment step_1
					}

					else if (step_4 == 5)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT |=  BIT3;       //B = 1 
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT |=  BIT0;       //F = 1 
	 					P5OUT &= ~BIT2;       //G = 0 
	 					P5OUT &= ~BIT1;       //H = 0 

						step_4 = 6;           //repeat step_1
					}

					else if (step_4 == 6)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT |=  BIT3;       //B = 1
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT |=  BIT0;       //F = 1 
	 					P5OUT |=  BIT2;       //G = 1
	 					P5OUT &= ~BIT1;       //H = 0 

						step_4 = 7;			  //increment step_1
					}

					else if (step_4 == 7)
					{

						P1OUT |=  BIT2;       //A = 1 
	 					P1OUT |=  BIT3;       //B = 1 
	 					P1OUT |=  BIT1;       //C = 1 
	 					P5OUT |=  BIT4;       //D = 1 
	 					P4OUT |=  BIT5;       //E = 1 
	 					P5OUT |=  BIT0;       //F = 1 
	 					P5OUT |=  BIT2;       //G = 1 
	 					P5OUT |=  BIT1;       //H = 1 

						step_4 = 0;           //repeat step_1
					}

					break;

	}

    TB3CCTL0 &= ~CCIFG;          //clear CCR1 flag

}
