# Ex00 - Communication UART

## Description
Ce programme configure l'UART de l'ATmega328P pour communiquer avec un PC à 115200 bauds (8N1).
Il envoie le caractère 'Z' toutes les secondes sur le port série.

## Configuration matérielle
- Microcontrôleur : ATmega328P @ 16MHz
- Interface : UART0 (PD0/RX, PD1/TX)
- Convertisseur USB-Série : CH340G (voir schéma)
- Baud rate : 115200
- Format : 8 bits de données, pas de parité, 1 bit de stop (8N1)

## Compilation
```bash
make
```
Cette commande compile et flashe automatiquement le programme.

Pour compiler seulement sans flasher :
```bash
make hex
```

Pour voir la taille du programme :
```bash
make size
```

## Utilisation sur PC
Pour lire les données depuis le PC :
```bash
screen /dev/ttyUSB0 115200
```

Pour quitter screen : `Ctrl-A` puis `K` puis `Y`

Alternative avec minicom :
```bash
minicom -D /dev/ttyUSB0 -b 115200
```

## Calcul du UBRR
Formule (datasheet p.179) :
```
UBRR = (F_CPU / (16 * BAUDRATE)) - 1
UBRR = (16000000 / (16 * 115200)) - 1
UBRR = 8.68 ≈ 8
```

Erreur de 0.2% (acceptable selon Table 19-12 p.181 de la datasheet)

## Références datasheet
- Section 19: USART (p.165-195)
- Registres UBRR0H/L : p.179
- Registre UCSR0B : p.192
- Registre UCSR0C : p.193
- Registre UCSR0A : p.190
- Registre UDR0 : p.194