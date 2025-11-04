/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmetee-b <cmetee-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:23:06 by cmetee-b          #+#    #+#             */
/*   Updated: 2025/11/04 15:44:26 by cmetee-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "uart.h"

/*
 * Connexion UART (voir schéma elec42_pool.pdf):
 * - TX (PD1) connecté au CH340G (convertisseur USB-Série)
 * - RX (PD0) connecté au CH340G
 * 
 * Pour lire sur PC:
 * screen /dev/ttyUSB0 115200
 */
int main(void)
{
	uart_init();

	while (1)
	{
		/* Envoi du caractère 'Z' */
		uart_tx('Z');
		
		/* Délai de 1 seconde (1 Hz) */
		_delay_ms(1000);
	}
	
	return 0;
}
