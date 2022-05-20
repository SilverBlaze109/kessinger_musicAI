#pragma once
#include "functions.h"

int midiNoteToValue(int octave, std::string note)
{
	//this will hold the integer equivalent of the note inputted
	int noteValue;

	//we want to only deal with lower case for consistency
	char tempNote = tolower(note[0]);
	//get appropriate value for noteValue
	switch (tempNote)
	{
	case 'c':
		noteValue = 0;
		break;
	case 'd':
		noteValue = 2;
		break;
	case 'e':
		noteValue = 4;
		break;
	case 'f':
		noteValue = 5;
		break;
	case 'g':
		noteValue = 7;
		break;
	case 'a':
		noteValue = 9;
		break;
	case 'b':
		noteValue = 11;
		break;
	default:
		//if we're here, then the note's invalid
		throw std::invalid_argument("received invalid note");
	}

	//if the note is sharp and we can make it sharp, we do
	if (note[1] == '#')
		noteValue++;

	if (note[1] == 'b')
		noteValue--;

	//return the value
	return (octave * 12) + noteValue;
}

