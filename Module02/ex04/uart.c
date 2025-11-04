/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmetee-b <cmetee-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:31:38 by cmetee-b          #+#    #+#             */
/*   Updated: 2025/11/04 16:34:07 by cmetee-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "uart.h"


void uart_init(void)
{
	/* Calcul du baud rate: UBRR = (F_CPU / (8 * BAUDRATE)) - 1 */
	uint16_t ubrr = (F_CPU / (8UL * UART_BAUDRATE)) - 1;
	
	/* Configuration du baud rate (High puis Low) */
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)(ubrr);
	
	/* Mode double vitesse pour meilleure précision */
	UCSR0A = (1 << U2X0);
	
	/* Activation du transmetteur et du récepteur */
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	
	/* Format: 8 bits de données, 1 stop bit, pas de parité */
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

/*
 * Transmet un caractère via UART
 */
void uart_tx(char c)
{
	/* Attente que le buffer de transmission soit prêt */
	while (!(UCSR0A & (1 << UDRE0)))
		;
	
	/* Envoi du caractère */
	UDR0 = c;
}

/*
 * Réceptionne un caractère via UART
 */
char uart_rx(void)
{
	/* Attente de la réception d'un caractère */
	while (!(UCSR0A & (1 << RXC0)))
		;
	
	/* Lecture et retour du caractère reçu */
	return UDR0;
}

/*
 * Transmet une chaîne de caractères via UART
 */
void uart_printstr(const char* str)
{
	/* Envoi caractère par caractère jusqu'au '\0' */
	while (*str)
	{
		uart_tx(*str);
		str++;
	}
}
