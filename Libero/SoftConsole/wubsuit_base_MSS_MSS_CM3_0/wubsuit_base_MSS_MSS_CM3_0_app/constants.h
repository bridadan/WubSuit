#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define MAX_NOTES 128
#define MAX_KEYSIGNATURES 3
#define WAITING_MESSAGE "..."

typedef enum {
	C0, CS0, D0, DS0, E0, F0, FS0, G0, GS0, A0, AS0, B0,
	C1, CS1, D1, DS1, E1, F1, FS1, G1, GS1, A1, AS1, B1,
	C2, CS2, D2, DS2, E2, F2, FS2, G2, GS2, A2, AS2, B2,
	C3, CS3, D3, DS3, E3, F3, FS3, G3, GS3, A3, AS3, B3,
	C4, CS4, D4, DS4, E4, F4, FS4, G4, GS4, A4, AS4, B4,
	C5, CS5, D5, DS5, E5, F5, FS5, G5, GS5, A5, AS5, B5,
	C6, CS6, D6, DS6, E6, F6, FS6, G6, GS6, A6, AS6, B6,
	C7, CS7, D7, DS7, E7, F7, FS7, G7, GS7, A7, AS7, B7,
	C8, CS8, D8, DS8, E8, F8, FS8, G8, GS8, A8, AS8, B8,
	C9, CS9, D9, DS9, E9, F9, FS9, G9, GS9, A9, AS9, B9,
	C10, CS10, D10, DS10, E10, F10, FS10, G10
} Note;

typedef enum {
	CHROMATIC, CMAJOR, CMINOR
} KeySignature;


typedef enum {
	CONFIG, PERFORMANCE
} State;

typedef enum {
	ARRAY, MIDI, SENSOR, VALUE
} InputType;

#endif /* CONSTANTS_H_ */
