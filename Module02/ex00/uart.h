#ifndef UART_H
#define UART_H

#include <util/delay.h>
#include <avr/io.h>

/* Configuration UART */
# define UART_BAUDRATE 115200

/* Initialisation de l'UART */
void uart_init(void);

/* Transmission d'un caractère via UART */
void uart_tx(char c);

#endif