/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmetee-b <cmetee-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:35:50 by cmetee-b          #+#    #+#             */
/*   Updated: 2025/11/04 17:11:21 by cmetee-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "uart.h"


void led_init(void)
{
	DDRB |= (1 << LED_D1) | (1 << LED_D2) | (1 << LED_D3);
	PORTB &= ~((1 << LED_D1) | (1 << LED_D2) | (1 << LED_D3));
}


void led_blink_success(void)
{
	for (uint8_t i = 0; i < 5; i++)
	{
		PORTB |= (1 << LED_D1) | (1 << LED_D2) | (1 << LED_D3);
		_delay_ms(200);
		PORTB &= ~((1 << LED_D1) | (1 << LED_D2) | (1 << LED_D3));
		_delay_ms(200);
	}
}

/*
 * Lit une ligne depuis UART avec echo optionnel
 */
uint8_t read_line(char* buffer, uint8_t max_len, uint8_t hide)
{
	uint8_t i = 0;
	char c;
	
	while (1)
	{
		c = uart_rx();
		
		/* ENTER ou NEWLINE */
		if (c == ENTER || c == NEWLINE)
		{
			buffer[i] = '\0';
			uart_printstr("\r\n");
			return i;
		}
		/* BACKSPACE */
		else if (c == BACKSPACE || c == BACKSPACE_ALT)
		{
			if (i > 0)
			{
				i--;
				uart_tx('\b');
				uart_tx(' ');
				uart_tx('\b');
			}
		}
		/* Caractère normal */
		else if (i < max_len - 1 && c >= 32 && c <= 126)
		{
			buffer[i++] = c;
			
			if (hide)
				uart_tx('*');
			else
				uart_tx(c);
		}
	}
}

int main(void)
{
	char username_input[MAX_INPUT];
	char password_input[MAX_INPUT];
	
	uart_init();
	led_init();
	
	while (1)
	{
		uart_printstr("Enter your login:\r\n");
		uart_printstr("\tusername: ");
		read_line(username_input, MAX_INPUT, 0);
		uart_printstr("\tpassword: ");
		read_line(password_input, MAX_INPUT, 1);
		
		if (strcmp(username_input, USERNAME) == 0 && 
        strcmp(password_input, PASSWORD) == 0)
		{
            uart_printstr("Hello ");
			uart_printstr(username_input);
			uart_printstr("!\r\n");
			uart_printstr("Shall we play a game?\r\n");
			led_blink_success();
			_delay_ms(2000);
		}
		else
		{
            uart_printstr("Bad combinaison username/password\r\n");
			_delay_ms(1000);
		}
        uart_printstr("\r\n");
	}
	
	return 0;
}
