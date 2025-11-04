/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmetee-b <cmetee-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:19:25 by cmetee-b          #+#    #+#             */
/*   Updated: 2025/11/04 16:28:10 by cmetee-b         ###   ########.fr       */
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

#endif