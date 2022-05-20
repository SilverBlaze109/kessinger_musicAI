#include <iostream>
#include <fstream>
#include <vector>
#include "functions.h"
#include "songClass.h"

class midiMaker
{
private:
    //creates vector that will hold all hex values
    std::vector<int> hexInput;
    //this holds the time between notes
    int deltaTime;

public:
    //default constructor, set up vector
    midiMaker();

    //reset vector
    void resetMidi();

    //add generic event
    void addEvent(int, int, int, int);

    //add a note on event
    void playNote(const chord, int);

    //inputs rest
    void addRest(int);

    //output midifile
    void outputMidi(std::string);
};