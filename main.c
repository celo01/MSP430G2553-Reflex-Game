/*
 *  Advisor: Prof. Dr. Mustafa GÖK
 *
 *
 *  This code was written by Celil BAYRAKDAR
 *                           2019514011
 *
 *
 *  This project was done for the "Introduction to Embedded Systems" course.
 *
 */


/***************************** INCLUDE OF LIBRARIES BEGIN ***********************************************************************************************/
#include <msp430.h>
#include "string.h"
#include "lcdLib.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
/***************************** INCLUDE OF LIBRARIES END *************************************************************************************************/



/***************************** IDENTIFICATION OF VARIABLES BEGIN ****************************************************************************************/
volatile uint8_t  startCount=0;
volatile uint8_t  gameCount=0;  // it keeps how many times game is startCount (max.5)
volatile uint8_t  ledSelect;          // to understand which led will be on 0 for red 1 for green

volatile uint8_t  Player1_Score;      // it keeps player1's score
volatile uint8_t  Player2_Score;     // it keeps player2's score

volatile uint8_t  Green1_Pressed=0;  // it keeps player1's button pressed or not (it could be bool)
volatile uint8_t  Red1_Pressed=0;
volatile uint8_t  Green2_Pressed=0; // it keeps player2's button pressed or not (it could be bool)
volatile uint8_t  Red2_Pressed=0;

volatile uint16_t  Green1_Time;    // it keeps player1's time after it pressed green led button
volatile uint16_t  Green2_Time;  // it keeps player2's time after it pressed green led button
volatile uint16_t  Red1_Time;      // it keeps player1's time after it pressed red led button
volatile uint16_t  Red2_Time;     // it keeps player2's time after it pressed red led button

volatile uint32_t counter ;
/***************************** IDENTIFICATION OF VARIABLES END*******************************************************************************************/



/***************************** DEFINITION OF FUNCTIONS BEGIN *******************************************************************************************/
void TimerSetup(void);
void PinSetup(void);
void GameStart();
/***************************** DEFINITION OF FUNCTIONS END *********************************************************************************************/


/***************************** VOID MAIN FUNCTIONS BEGIN ***********************************************************************************************/
void main(void){

   WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer

   /***************************** STARTING THE USED FUNCTIONS BEGIN ************************************************************************************/
   TimerSetup();
   PinSetup();
   lcdInit();
   __enable_interrupt();
   GameStart();
   /***************************** STARTING THE USED FUNCTIONS END **************************************************************************************/


     /************************************** MAIN LOOP BEGIN *******************************************************************************************/
     while(1)
     {


     if(Player1_Score <3 && Player2_Score <3) // Game still active
     {

     /***************************** GAME FINISHED CHECK THE RESULT BEGIN*****************************/
     if(((Green1_Pressed !=0 && Green2_Pressed !=0) || (Red1_Pressed !=0 && Red2_Pressed !=0) ) && startCount ==0)
     {
       Green1_Pressed =0;
       Green2_Pressed =0;
       Red1_Pressed =0;
       Red2_Pressed =0;
       GameStart();
     }
     /*********************** GAME FINISHED CHECK THE RESULT END **********************************/



      /*********************** CHECK THE GREEN GAME BEGIN ******************************************/
      if(ledSelect == 1 &&  Green1_Pressed !=0  && Green2_Pressed !=0 && startCount ==1) // Green led game played
      {
      if(Green2_Time > Green1_Time) // Player1 won
      {
      lcdClear();
      lcdSetText("P1 WON:      ms ",0,0);
      lcdSetText("(    ms) faster",0,1);
      lcdSetInt(Green1_Time,8,0);
      lcdSetInt(10*(Green2_Time-Green1_Time) ,1,1);
      Player1_Score++;
      }
      else
      {
      lcdClear();
      lcdSetText("P2 WON:      ms ",0,0);
      lcdSetText("(    ms) faster",0,1);
      lcdSetInt(Green2_Time,8,0);
      lcdSetInt(10*(Green1_Time-Green2_Time) ,1,1);
      Player2_Score++; // Player2 won
      }
      counter=0;
      startCount =0;
      __delay_cycles(2000000);
      Red1_Time = 0;
      Red2_Time = 0;
      Green1_Time =0;
      Green2_Time = 0;
      }
      /****************************** CHECK THE GREEN GAME END* **********************************/



      /****************************** CHECK THE RED GAME BEGIN ***********************************/
      if(ledSelect == 0 &&  Red1_Pressed !=0  && Red2_Pressed !=0 && startCount ==1) // Red led game played
      {
      if(Red2_Time > Red1_Time) // Player1 won
      {
      lcdClear();
      lcdSetText("P1 WON:      ms ",0,0);
      lcdSetText("(    ms) faster",0,1);
      lcdSetInt(Red1_Time,8,0);
      lcdSetInt(10*(Red2_Time-Red1_Time) ,1,1);
      Player1_Score++;
      }
      else
      {
      lcdClear();
      lcdSetText("P2 WON:      ms ",0,0);
      lcdSetText("(    ms) faster",0,1);
      lcdSetInt(Red2_Time,8,0);
      lcdSetInt(10*(Red1_Time-Red2_Time) ,1,1);
      Player2_Score++; // Player2 won
      }
      counter=0;
      startCount =0;
      __delay_cycles(2000000);
      Red1_Time = 0;
      Red2_Time = 0;
      Green1_Time =0;
      Green2_Time = 0;
      }
      /******************************CHECK THE RED GAME END***************************************/



      /****************** SEND LAST SCORE TO SCREEN BEGIN*************************************************/
      if((Player1_Score ==3 || Player2_Score == 3) && gameCount >2) // game is over show the last result
      {
      lcdClear();
      if(Player1_Score>Player2_Score) {
      lcdSetText("Player 1 WON",0,0);
      lcdSetText("P1:    P2: ",0,1);
      lcdSetInt(Player1_Score,3,1);
      lcdSetInt(Player2_Score,10,1);
      }
      else if(Player1_Score<Player2_Score) {
      lcdSetText("Player 2 WON",0,0);
      lcdSetText("P1:    P2: ",0,1);
      lcdSetInt(Player1_Score,3,1);
      lcdSetInt(Player2_Score,10,1);
      }
      __delay_cycles(5000000);
      startCount =0;
      Player1_Score=0;
      Player2_Score=0;
      }
         /****************** SEND LAST SCORE TO SCREEN END**************************************************/
    } //Game Still Active Parenthesis

  } //While(1) Parenthesis
    /*************************************** MAIN LOOP END *********************************************************************************************/
} //void main(void) Parenthesis
/***************************** VOID MAIN FUNCTIONS END *************************************************************************************************/



/***************************** TIMER FUNCTIONS BEGIN ***************************************************************************************************/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TimA0_IT(void)
{
   counter++;  // Counter variable
   if (counter >= 2100)  // Assuming the timer is configured for 1MHz. 2100=21s but if game led off, this time =15s
       {
           P1OUT |= BIT0; // Green Led On
           // Enter low-power mode 4, ---------CPU AND ALL CLOCKS ARE DISABLED--------
           __bic_SR_register(GIE);
           __bis_SR_register(LPM4_bits);
       }
}
/***************************** TIMER FUNCTIONS END *****************************************************************************************************/



/***************************** TIMER SETUP FUNCTION BEGIN **********************************************************************************************/
void TimerSetup(void)
{
    BCSCTL1 = CALBC1_1MHZ;   // Calibration of DCO to 1MHz
    DCOCTL = CALDCO_1MHZ;    // Setting the DCO to 1 MHz

    // TIMER A SET PARAMETERS
    TA0CTL = TASSEL_2 ;    // DCO Up mode
    TA0CCR0 = 10000-1;     // The number that the timer counts
    TACCTL0 |= CCIE;       // Enable interrupt for CCR0.
    TA0CTL |= MC_1;        // Start Timer
}
/***************************** TIMER SETUP END *********************************************************************************************************/



/***************************** PIN SETUP BEGIN *********************************************************************************************************/
void PinSetup(void)
{
    /********************* LED SETUP BEGIN *************************************************/
    P1DIR |= BIT0 + BIT6 + BIT7;    // P1.6 and P1.7  LEDs
    P1OUT &= ~(BIT0 + BIT6 + BIT7); // LEDs closed
    /********************* LED SETUP END****************************************************/


    /********************* BUTTON SETUP BEGIN***********************************************/
    P1DIR &= ~BIT1; // P1.1 to P1.4 set buton
    P1DIR &= ~BIT2;
    P1DIR &= ~BIT3;
    P1DIR &= ~BIT4;
    P1REN |= BIT1+ BIT2+ BIT3+ BIT4;  // Resistor enable
    P1OUT |= BIT1+ BIT2+ BIT3+ BIT4;  // Select pull-up resistor
    P1IES |= BIT1+ BIT2+ BIT3+ BIT4;  // Select High-Edge
    P1IE |= BIT1+ BIT2+ BIT3+ BIT4;   // Activate Interrupts
    P1IFG &=~(BIT1+BIT2+BIT3+BIT4);   // Interrupt Flag
    /********************* BUTTON SETUP END************************************************/
}
/***************************** PIN SETUP END **********************************************************************************************************/



/***************************** GAME START FUNCTION BEGIN **********************************************************************************************/
void GameStart()
{
    /********************* RESET VARIABLE BEFORE GAME BEGIN*******************************/
    lcdClear();
    lcdSetText("Reflex Game",0,0);
    lcdSetText("Starting Round",0,1);
    __delay_cycles(2000000);
    /********************* RESET VARIABLE BEFORE GAME BEGIN*******************************/


    /********************* RESET VARIABLE BEFORE GAME BEGIN*******************************/
    P1OUT &=~BIT7;
    P1OUT &=~BIT6;

    Red1_Time = 0;
    Red2_Time = 0;
    Green1_Time =0;
    Green2_Time = 0;
    Green1_Pressed=0;
    Red1_Pressed=0;
    Green2_Pressed=0;
    Red2_Pressed=0;
    /********************* RESET VARIABLE BEFORE GAME END*********************************/



    /********************* RANDOM SELECT LED BEGIN ***************************************/
    ledSelect = (rand() %2);

    startCount =1;

    gameCount++;

    lcdClear();
    lcdSetText("****************",0,0);
    __delay_cycles(1000000);

    if(ledSelect == 1){
    P1OUT |= BIT7; // GREEN Led
    __delay_cycles(1000000);
    P1OUT &=~ BIT7; // GREEN Led
    }

    if(ledSelect == 0 )
    {
    P1OUT |= BIT6; // RED Led
    __delay_cycles(1000000);
    P1OUT &=~ BIT6;
    }
    /********************* RANDOM SELECT LED END ******************************************/
}
/***************************** GAME START FUNCTION END ***********************************************************************************************/



/***************************** INTERRUPT CONFIGURATION BEGIN ******************************************************************************************/
#pragma vector=PORT1_VECTOR
__interrupt void Button_IT(void)
{

 /********* P1 GREEN BUTTON INTERRUPT CONFIGURATION BEGIN ********************************/
    if( !(P1IN & BIT1))
    {
    __delay_cycles(1000);
      if( !(P1IN & BIT1)) // debounce check
      {
      Green1_Time = counter;
      Green1_Pressed =1;
      P1IFG &=~(BIT1);
      }
    }
 /********* P1 GREEN BUTTON INTERRUPT CONFIGURATION END***********************************/



 /********* P1 RED BUTTON INTERRUPT CONFIGURATION ****************************************/
    if(!(P1IN & BIT2) )
    {
    __delay_cycles(1000);
      if(!(P1IN & BIT2))
      {
      Red1_Time = counter;
      Red1_Pressed =1;
      P1IFG &=~(BIT2);
      }
    }
  /********* P1 RED BUTTON INTERRUPT CONFIGURATION END************************************/



  /********* P2 RED BUTTON INTERRUPT CONFIGURATION****************************************/
     if((P1IFG & BIT4))
     {
     __delay_cycles(1000);
       if((P1IFG & BIT4))
       {
       Red2_Time = counter;
       Red2_Pressed =1;
       P1IFG &= ~(BIT4);
       }
     }
   /********* P2 RED BUTTON INTERRUPT CONFIGURATION END**********************************/



   /********* P2 GREEN BUTTON INTERRUPT CONFIGURATION BEGIN******************************/
     if((P1IFG & BIT3))
     {
     __delay_cycles(1000);
       if((P1IFG & BIT3))
       {
       Green2_Time = counter;
       Green2_Pressed =1;
       P1IFG &= ~(BIT3);
       }
     }
    /********* P2 GREEN BUTTON INTERRUPT CONFIGURATION END******************************/

      P1IFG = 0x0; //Clear Interrupt Flag

}
/***************************** INTERRUPT CONFIGURATION END ********************************************************************************************/

