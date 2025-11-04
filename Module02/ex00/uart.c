/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmetee-b <cmetee-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:40:24 by cmetee-b          #+#    #+#             */
/*   Updated: 2025/11/04 15:34:09 by cmetee-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "uart.h"

/*
 * Initialisation de l'UART en mode 115200 8N1
 * 
 * Registres utilisés (ATmega48A/88A/PA/168A/PA/328/P Datasheet - p.200):
 * - UBRR0: USART Baud Rate Register
 * - UCSR0B: USART Control and Status Register B 
 * - UCSR0C: USART Control and Status Register C 
 * 
 * Configuration 8N1: (20.4 Frame Formats - p.183)
 * - 8 bits de données
 * - Pas de parité (None)
 * - 1 bit de stop
 * 
 * Formule UBRR (mode asynchrone Double speed, p.182):
 * UBRR = (F_CPU / (8 * BAUDRATE)) - 1
 * 20.3.2 Double Speed Operation (U2Xn) :"The transfer rate can be doubled 
 * by setting the U2Xn bit in UCSRnA. Setting this bit only has effect for the
 * asynchronous operation. Setting this bit will reduce the divisor of 
 * the baud rate divider from 16 to 8, effectively doubling the transfer 
 * rate for asynchronous communication"...
 */
void uart_init(void)
{
	/* Calcul du Baud Rate Register avec U2X0 activé (mode double vitesse)
	 * Formule avec U2X0=1 (datasheet p.182):
	 * UBRR = (F_CPU / (8 * BAUDRATE)) - 1
	 * 
	 * Pour F_CPU=16MHz et BAUDRATE=115200:
	 * UBRR = (16000000 / (8 * 115200)) - 1 = 16.36 ≈ 16
	 * Erreur: 2.1% avec U2X0=0, mais 0.0% avec U2X0=1 et UBRR=16
	 * (voir Table 20-1 p.182)
	 */
	uint16_t ubrr = (F_CPU / (8UL * UART_BAUDRATE)) - 1;
	
	/* Configuration du baud rate (p.182) 
    * "UBRRnContents of the UBRRnH and UBRRnL Registers, (0-4095)"
    * voir aussi : USART initialization code example (20.5 - p 184-185)
    */
	UBRR0H = (uint8_t)(ubrr >> 8);    // High byte
	UBRR0L = (uint8_t)(ubrr);         // Low byte
	
	/* Activation du mode double vitesse U2X0 (20.3.2 - p.182)
     * Bit 1 – U2Xn: Double the USART Transmission Speed (p.201)
	 * Permet une meilleure précision du baud rate
	 */
	UCSR0A = (1 << U2X0);
	
	/* Activation du transmetteur (20.6 - p.185-186)
     * 20.11.3 UCSRnB – USART Control and Status Register n B (p.201-202)
	 * bit 3 – TXEN0: Transmitter Enable
	 */
	UCSR0B = (1 << TXEN0);
	
	/* Configuration du format: 8 bits, 1 stop bit, pas de parité (p.186-187)
	 * UCSZ01:UCSZ00 = 11 pour 8 bits de données (Table 20-11 p.203)
	 * USBS0 = 0 pour 1 bit de stop (table 20-10 p.203)
	 * UPM01:UPM00 = 00 pour pas de parité (Table 20-9 p.203)
     * 20.11.4 UCSRnC – USART Control and Status Register n C
	 */
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

/*
 * Transmet un caractère via UART
 * 
 * Registres utilisés:
 * - UCSR0A: USART Control and Status Register A (p.200)
 * - UDRE0 (bit 5): Data Register Empty flag
 * - UDR0: USART I/O Data Register (20.11.1 - p.200)
 */
void uart_tx(char c)
{
	/* 20.11.2 - p.200
	 * Attente que le buffer de transmission soit vide (p.200)
	 * UDRE0 (bit 5) = 1 quand UDR0 est prêt à recevoir des données
	 */
	while (!(UCSR0A & (1 << UDRE0)))
		;
		
	UDR0 = c;
}
