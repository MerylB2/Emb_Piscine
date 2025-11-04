/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmetee-b <cmetee-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:09:39 by cmetee-b          #+#    #+#             */
/*   Updated: 2025/11/04 16:18:47 by cmetee-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "uart.h"

int main(void)
{
	char c;
	uart_init();

	while (1)
	{
		/* Réception d'un caractère (bloquant) */
		c = uart_rx();
		
		/* Renvoi du caractère */
		uart_tx(c);
	}
	return 0;
}
