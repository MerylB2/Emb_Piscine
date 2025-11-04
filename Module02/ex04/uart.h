/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmetee-b <cmetee-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:31:15 by cmetee-b          #+#    #+#             */
/*   Updated: 2025/11/04 16:57:58 by cmetee-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UART_H
#define UART_H

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

# define UART_BAUDRATE 115200

/* Credentials */
#define USERNAME "Meryl"
#define PASSWORD "Piscine"
/* Buffer sizes */
#define MAX_INPUT 32

/* LED pins */
#define LED_D1 PB0
#define LED_D2 PB1  
#define LED_D3 PB2

/* Codes de contrôle */
#define BACKSPACE 127
#define BACKSPACE_ALT 8
#define ENTER 13
#define NEWLINE 10

/* Initialisation de l'UART */
void uart_init(void);

/* Transmission d'un caractère via UART */
void uart_tx(char c);

/* Réception d'un caractère via UART (bloquant) */
char uart_rx(void);

/* Transmission d'une chaîne de caractères via UART */
void uart_printstr(const char* str);

#endif