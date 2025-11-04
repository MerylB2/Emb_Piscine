/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmetee-b <cmetee-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:44:29 by cmetee-b          #+#    #+#             */
/*   Updated: 2025/11/04 15:53:38 by cmetee-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "uart.h"

/*
 * Utilisation du Timer1 en mode CTC (Clear Timer on Compare Match)
 * pour générer une interruption toutes les 2 secondes
 * 
 * Calcul pour 2 secondes:
 * - F_CPU = 16 MHz
 * - Prescaler = 1024
 * - Fréquence du timer = 16MHz / 1024 = 15625 Hz
 * - Pour 2 secondes: 15625 * 2 = 31250
 * - Comme OCR1A max = 65535, on peut utiliser 31250 directement
 */

/* Compteur pour atteindre 2 secondes */
volatile uint8_t timer_overflow_count = 0;

/*
 * ISR (Interrupt Service Routine) du Timer1 Compare Match A
 * Cette fonction est appelée automatiquement quand TCNT1 = OCR1A
 * 
 * TIMER1_COMPA_vect: vecteur d'interruption Timer1 Compare Match A
 */
ISR(TIMER1_COMPA_vect)
{
	timer_overflow_count++;
	
	/* Après 2 overflows (2 x 1 sec = 2 secs) */
	if (timer_overflow_count >= 2)
	{
		uart_printstr("Hello World!\r\n");
    
		timer_overflow_count = 0;
	}
}

/*
 * Initialise le Timer1 en mode CTC avec interruption
 * Configure pour une interruption toutes les 1 sec
 */
void timer1_init(void)
{
	/* Mode CTC (Clear Timer on Compare match)
	 * WGM13:12:11:10 = 0100 pour mode CTC avec OCR1A comme TOP
	 * WGM11:10 dans TCCR1A = 00
	 * WGM13:12 dans TCCR1B = 01
	 */
	TCCR1A = 0;
	
	/* Configuration de TCCR1B
	 * - WGM12 = 1 (mode CTC)
	 * - CS12:CS11:CS10 = 101 pour prescaler 1024
	 */
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
	
	/* Valeur de comparaison pour 1 seconde
	 * OCR1A = (F_CPU / prescaler) - 1 = (16000000 / 1024) - 1 = 15624
	 * Pour 2 secondes, on compte 2 interruptions
	 */
	OCR1A = 15624;
	
	/* Réinitialisation du compteur */
	TCNT1 = 0;
	
	/* Activation de l'interruption Compare Match A
	 * OCIE1A: Output Compare Interrupt Enable bit 1
	 */
	TIMSK1 = (1 << OCIE1A);
	
	/* Activation globale des interruptions */
	sei();
}

/*
 * 
 * Initialise l'UART et le Timer1, puis reste en boucle vide
 * L'affichage se fait automatiquement via l'interruption du timer
 */
int main(void)
{
	uart_init();
	timer1_init();

	while (1)
	{}
	return 0;
}
