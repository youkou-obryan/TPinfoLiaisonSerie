/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
*
* \brief
*      utilisation d'un arduino uno pour transmettre une chaine de char par liaison série
*
*
* \par Application note:
*      ATmega328p
*
* \par Documentation
*      For comprehensive code documentation, supported compilers, compiler
*      settings and supported devices see readme.html*/




/*! \brief fréquence du qwark du µcontroller*/
#define FOSC 16000000
/*! \brief nombre de changement d'état par seconde(vitesse d'envoi de données)*/
#define BAUD 9600
/*! \brief calcul servant à trouver le numéro du registre*/
#define MYUBRR FOSC / 16 / BAUD - 1
unsigned char flag_0 = 0,flag_3=0;
unsigned char data;






/*! \brief USART0_INIT function / initialisation
* la fonction permet d'aurotiser la transmission et de choisir le nombre de bit de stop avec à l'aide des registres UCSR0B et UCSR0C
*/
void USART0_Init(unsigned int ubrr) {
 /*Set baud rate */
 UBRR0H = (unsigned char)(ubrr >> 8);
 UBRR0L = (unsigned char)ubrr;
 /*autoriser  transmitter allumer le bit n3 */
 UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
 /* Set frame format: 8data, 2stop bit */
 UCSR0C = (3 << UCSZ00);
 DDRB = 0B00100000;
 PORTB = 0B00000000;
}

/*! \brief USART0_INIT function / initialisation
* la fonction permet d'aurotiser la transmission et de choisir le nombre de bit de stop avec à l'aide des registres UCSR0B et UCSR0C
*/
void USART3_Init(unsigned int ubrr) {
 /*Set baud rate */
 UBRR3H = (unsigned char)(ubrr >> 8);
 UBRR3L = (unsigned char)ubrr;
 /*autoriser  transmitter allumer le bit n3 */
 UCSR3B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
 /* Set frame format: 8data, 2stop bit */
 UCSR3C = (3 << UCSZ30);
 /*DDRB = 0B00100000;//TEST DE L'INTERRUPTION
 PORTB = 0B00000000;*/
}


/*! \brief USART0_Transmit function / transmission
la fonction sert à transmettre un caractère
*/
void USART0_Transmit(unsigned char data) {
 /* Wait for empty transmit buffer */
 while (!(UCSR0A & (1 << UDRE0)))
   ;
 /* Put data into buffer, sends the data */
 UDR0 = data;
}


/*! \brief USART3_Transmit function / transmission
la fonction sert à transmettre un caractère
*/
void USART3_Transmit(unsigned char data) {
 /* Wait for empty transmit buffer */
 while (!(UCSR3A & (1 << UDRE3)))
   ;
 /* Put data into buffer, sends the data */
 UDR3 = data;
}



/*! \brief USART_Receive function / recetption
la fonction sert à recevoir une chaine de caractère
*/
unsigned char USART0_Receive(void) {
 /* Wait for data to be received */
 while (!(UCSR0A & (1 << RXC0)))
   ;
 /* Get and return received data from buffer */
 return UDR0;
}

/*! \brief USART3_Receive function / recetption
la fonction sert à recevoir une chaine de caractère
*/
unsigned char USART3_Receive(void) {
 /* Wait for data to be received */
 while (!(UCSR3A & (1 << RXC3)))
   ;
 /* Get and return received data from buffer */
 return UDR3;
}




/*! \brief fonction d'interruption
la fonction sera éxécutée quand l'interruption sera cativée
*/
ISR(USART0_RX_vect) {
 data = UDR0;
 flag_0 = 1;
}
/*! \brief fonction d'interruption pour USART3
la fonction sera éxécutée quand l'interruption sera cativée
*/
ISR(USART3_RX_vect) {
 data = UDR3;
 flag_3 = 1;
}


/*! \brief fonction transmission
envoie d'une chaîne de caractères
*/
void USART0_puts(unsigned char *str)
{
do
{
USART0_Transmit(*str);
} while (*++str!=0);
}

/*! \brief fonction transmission pour USART3
envoie d'une chaîne de caractères
*/
void USART3_puts(unsigned char *str)
{
do
{
USART3_Transmit(*str);
} while (*++str!=0);
}


/*! \brief Main function
utilisée pour appeler les fonctions init et et démarrer les transmmission
*/
int main(void) {


 USART0_Init(MYUBRR);
 USART3_Init(MYUBRR);
 sei();
 while (1) 
 {
   if (flag_0 == 1) 
   {
      //PORTB=0B00100000;//Allumer la led quand l'interruption est réalisée
    // USART_Transmit(data + 1);
    //USART_puts("iut");
    USART3_Transmit(data);
    flag_0=0;
   }
     if (flag_3 == 1) 
   {
    USART0_Transmit(data);
    flag_3=0;
   }

   _delay_ms(1);
 }
}
