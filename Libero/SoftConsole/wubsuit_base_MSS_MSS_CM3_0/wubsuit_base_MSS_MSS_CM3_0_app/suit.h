#ifndef SUIT_H_
#define SUIT_H_

#include <inttypes.h>
#include "constants.h"

// NOTE: Baud values based on 100MHz clock
#define BAUD_VALUE_115200    		53 //Possibly a problem because not exactly 53 (53.2535)
#define BAUD_VALUE_31250    		199

#define COREUARTAPB0_BASE_ADDR      0x40050000
#define COREUARTAPB1_BASE_ADDR      0x40050100
#define COREUARTAPB2_BASE_ADDR      0x40050200
#define MAX_RX_DATA_SIZE    		512
#define LIGHT_CHANNELS				6
#define XBEE_PACKET_LENGTH			6
#define MIDI_PACKET_LENGTH			3

typedef struct _XBeeState {
	uint8_t valid;
	uint8_t data[XBEE_PACKET_LENGTH];
	int packetPointer;
} XBeeState;

typedef struct _MIDIState {
	uint8_t valid;
	uint8_t data[MIDI_PACKET_LENGTH];
	int packetPointer;
} MIDIState;

typedef struct _SuitState {
	State state;
	uint8_t accelX, accelY, accelZ;
	uint8_t flexValue;
	uint8_t handHeight;
	uint8_t activeLights;
	uint8_t waitingForInput;
	InputType inputType;
	uint8_t noteActive;
	Note activeNote;
} SuitState;

typedef struct _Settings {
	// 0 - Head, 1 - Left Arm, 2 - Right Arm, 3 - Left Leg, 4 - Right Leg, 5 - Chest
	Note suitLightMappings[LIGHT_CHANNELS];
	uint8_t handHeightMapping;
	uint8_t handHeightMin, handHeightMax;
	Note LPiezoMapping, RPiezoMapping;
	Note minNote, maxNote;
	Note* valueToMapTo;
	KeySignature keySignature;
	uint8_t suitLightsMIDIChannel;
	uint8_t outputMIDIChannel;
	uint8_t accelMin, accelMax;
	uint8_t pitchBendMin, pitchBendMax;
} Settings;

void Suit_init();
void Suit_setMode(State state);

// Input

void Suit_capButtonPressed();
void Suit_capButtonReleased();
void Suit_LPiezoPressed();
void Suit_RPiezoPressed();
void Suit_newSensorValues();
void Suit_handleMIDIMessage(uint8_t *message, uint16_t length);

// Utility

uint8_t Suit_MIDIToLightChannel(uint8_t note);
void Suit_turnOnLightChannel(uint8_t channel);
void Suit_turnOffLightChannel(uint8_t channel);
uint8_t Suit_mapValue(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max);

#endif /* SUIT_H_ */
