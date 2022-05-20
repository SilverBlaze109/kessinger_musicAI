#pragma once
#include <ctype.h>
#include <stdexcept>
#include <iostream>

//this will take the octave, note, and if the not is sharp or not
//this returns the appropriate integer value for a note for a MIDI file
int midiNoteToValue(int, std::string);