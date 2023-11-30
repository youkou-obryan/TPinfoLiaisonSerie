
/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief
 *      utilisation d'un arduino uno pour transfmettre une chaine de char par liaison série
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
#define MYUBRR FOSC/16/BAUD-1

/*! \brief USART_INIT function / initialisation
 * la fonction permet d'aurotiser la transmission et de choisir le nombre de bit de stop avec à l'aide des registres UCSR0B et UCSR0C
 */
void USART_Init(unsigned int ubrr)
{
/*Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/*autoriser  transmitter allumer le bit n3 */
UCSR0B = (1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

/*! \brief USART_Transmit function / transmission
la fonction sert à transmettre une chaine de caractère
 */
void USART_Transmit(unsigned char data)
{
/* Wait for empty transmit buffer */
while (!(UCSR0A & (1<<UDRE0)))
;
/* Put data into buffer, sends the data */
UDR0 = data;
}
/*! \brief Main function 
utilisée pour appeler les fonctions init et et démarrer la transmmission 
 */
int main(void)
{
  USART_Init(MYUBRR);

while(1)
{
USART_Transmit('O');
_delay_ms(100);
}
}
