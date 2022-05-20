#pragma once
#include<iostream>
#include<vector>
#include<random>
#include<string>
#include "chordInformation.h"

struct chord
{
	std::vector<std::string> notes;
	std::vector<int> octave;
	double duration = 0;
	int chordIndex;
};

class songClass
{
public:
	//constructor sets up variables and calls resetSong
	songClass(int);

	//returns song vector
	std::vector<chord> getSong();

	//crossover function for home function
	void crossOver(int, int, songClass&);

	//crossover function for other function
	std::vector<chord> crossOverCont(int, int, std::vector<chord>);

	//mutation function
	void mutate(int);

	//invert int1 . int2
	void invert(int, int);
	
	//destroys current song and 
	void resetSong(int);

	//grades song and returns a number (0-10) that represents how good the song is
	double fitnessFunc(int);

private:
	//has all the chords to create a song
	std::vector<chord> song;

	//has the information to make the song
	chordInfo mChordInfo;
};

chord makeChord(chordInfo mChordInfo, int chordType, int startOctave, int chordVariation);