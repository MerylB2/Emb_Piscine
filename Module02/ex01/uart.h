/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmetee-b <cmetee-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:39:55 by cmetee-b          #+#    #+#             */
/*   Updated: 2025/11/04 15:54:10 by cmetee-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UART_H
#define UART_H

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

# define UART_BAUDRATE 115200

/* Initialisation de l'UART */
void uart_init(void);

/* Transmission d'un caractère via UART */
void uart_tx(char c);

/* Transmission d'une chaîne de caractères via UART */
void uart_printstr(const char* str);

#endif