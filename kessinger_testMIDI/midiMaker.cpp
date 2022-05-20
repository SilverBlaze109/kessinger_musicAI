#pragma once
#include "midiMaker.h"

midiMaker::midiMaker()
{
    //setup this class's vector
    resetMidi();
}

void midiMaker::resetMidi()
{
    //empty vector
    hexInput.clear();
    //sets up header chunk containing important info
    //input identifier MThd
    hexInput.insert(hexInput.end(), { 0x4D, 0x54, 0x68, 0x64 });
    //input chunklen with 6 bytes following
    hexInput.insert(hexInput.end(), { 0x00, 0x00, 0x00, 0x06 });
    //input format
    hexInput.insert(hexInput.end(), { 0x00, 0x00 });
    //number of tracks
    hexInput.insert(hexInput.end(), { 0x00, 0x01 });
    //input tickdiv or number of divisions for a quarter note
    hexInput.insert(hexInput.end(), { 0x00, 0x20 });
    //sets up track chunk
    hexInput.insert(hexInput.end(), { 0x4D, 0x54, 0x72, 0x6B });
    //set up chunklen with 4 bytes following, more bytes will be added as events are added
    hexInput.insert(hexInput.end(), { 0x00, 0x00, 0x00, 0x04 });

    //setup deltaTime
    deltaTime = 0;
}

void midiMaker::addEvent(int x, int y, int z, int a)
{
    hexInput.insert(hexInput.end(), { x, y, z, a });

    //now we'll add one to the note counter
    int excess = 0;
    for (int x = 21; x > 17; x--)
    {
        if (hexInput[x] + 4 > 255)
        {
            excess = hexInput[x] + 4 - 255;
            hexInput[x] = 255;
        }
        else
        {
            hexInput[x] += 4;
            excess = 0;
        }
    }
}

void midiMaker::playNote(const chord playChord, int power = 100)
{
    for (int x = 0; x < playChord.notes.size(); x++)
    {
        if (playChord.notes[x].compare("") != 0)
        {
            //we'll get the numerical value of the note
            int noteValue = midiNoteToValue(playChord.octave[x], playChord.notes[x]);

            //now we'll insert the note on and off events
            //insert in the time since last event, note on event, note we will play, and power of note
            addEvent(deltaTime, 0x90, noteValue, power);

            //reset deltaTime
            deltaTime = 0;
        }
    }

    for (int x = 0; x < playChord.notes.size(); x++)
    {
        if (playChord.notes[x].compare("") != 0)
        {
            //we'll get the numerical value of the note
            int noteValue = midiNoteToValue(playChord.octave[x], playChord.notes[x]);

            //we'll stop the notes after length number quarter notes
            addEvent(playChord.duration * 20, 0x80, noteValue, power);
        }
    }
}

void midiMaker::addRest(int length)
{
    deltaTime += length * 60;
}

void midiMaker::outputMidi(std::string fileName)
{
    //tell midi that we're at the end of track
    hexInput.insert(hexInput.end(), { 0x00, 0xFF, 0x2F, 0x00 });

    //this will be our midiouput
    std::ofstream midiFile;

    if (fileName.length() < 5 || fileName.substr(fileName.length() - 4, 4).compare(".mid") != 0)
    {
        fileName = fileName + ".mid";
    }

    midiFile.open(fileName, std::ios::binary);
    for (int x = 0; x < hexInput.size(); x++)
    {
        midiFile << std::hex << static_cast<char>(hexInput[x]);
    }

    midiFile.close();
}