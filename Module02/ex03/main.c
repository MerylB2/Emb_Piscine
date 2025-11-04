/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmetee-b <cmetee-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:22:13 by cmetee-b          #+#    #+#             */
/*   Updated: 2025/11/04 16:26:31 by cmetee-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "uart.h"

/*
 * ISR (Interrupt Service Routine) de réception UART
 * 
 * Cette fonction est appelée automatiquement quand un caractère
 * est reçu sur l'UART (flag RXC0 = 1)
 * 
 * USART_RX_vect: vecteur d'interruption de réception UART
 */
ISR(USART_RX_vect)
{
	char c;
	
	c = UDR0;                       // Lecture du caractère reçu
	
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	else if (c >= 'A' && c <= 'Z')
		c = c + 32;
	/* Sinon, le caractère reste inchangé (chiffres, ponctuation, etc.) */
	
	uart_tx(c);                     // Renvoi du caractère transformé
}

int main(void)
{
	uart_init();
	sei();                          // Activation globale des interruptions

	while (1)
	{}
	
	return 0;
}