
#include <msp430.h> 
int i;
char text[] = "I am an MSP430\r\n";
void ser_output(char *str);
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    P1SEL = BIT1|BIT2;
    P1SEL2 = BIT1|BIT2;

    UCA0CTL1 |= UCSWRST+UCSSEL_2;
    //UCA0BR0 = 52;  //settings for 19200 baud
    UCA0BR0 = 104; // 1MHz 9600
    UCA0BR1 = 0;
    UCA0MCTL = UCBRS_0;
    UCA0CTL1 &= ~UCSWRST;

    while(1){
        ser_output(text);
    }
}
void ser_output(char *str){
    while(*str != 0) {
        while (!(IFG2&UCA0TXIFG));
        UCA0TXBUF = *str++;
        }
}
