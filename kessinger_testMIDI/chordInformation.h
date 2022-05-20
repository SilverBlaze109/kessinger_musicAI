#pragma once
#include<iostream>
#include<vector>

struct chordInfo
{
	//the order of chords for all arrays is: C G Cm F A# Am G# D# Dm Fm
	int transitionProb[10][10] = { { 0, 34, 0, 29, 9, 12, 2, 4, 8, 2 },
									{ 36, 0, 8, 25, 3, 16, 3, 2, 6, 1 },
									{ 0, 5, 0, 7, 25, 0, 31, 21, 1, 10 },
									{ 46, 28, 5, 0, 4, 7, 3, 2, 3, 2 },
									{ 14, 3, 32, 27, 0, 1, 12, 6, 0, 5 },
									{ 15, 29, 1, 42, 2, 0, 2, 0, 7, 2 },
									{ 4, 12, 15, 1, 31, 0, 0, 25, 0, 12 },
									{ 6, 5, 10, 13, 39, 0, 13, 0, 3, 11 },
									{ 29, 22, 5, 25, 2, 11, 0, 4, 0, 2 },
									{ 11, 11, 31, 0, 16, 3, 14, 14, 0, 0 } };

	std::vector<std::vector<std::string>> cChord = { {"C ", "E ", "G "},
								{"C ", "E ", "G ", "Bb"},
								{"C ", "E ", "G ", "B "},
								{"C ", "E ", "G ", "A "}};

	std::vector<std::vector<std::string>> gChord = { {"G ", "B ", "D "},
								{"G ", "B ", "D ", "F "},
								{"G ", "B ", "D ", "F#"},
								{"G ", "B ", "D ", "E "}};

	std::vector<std::vector<std::string>> cMChord = { {"Cm", "Eb", "G "},
								{"Cm", "Eb", "G ", "Bb"},
								{"Cm", "Eb", "G ", "B "},
								{"Cm", "Eb", "G ", "A "}};

	std::vector<std::vector<std::string>> fChord = { {"F ", "A ", "C "},
								{"F ", "A ", "C ", "Eb"},
								{"F ", "A ", "C ", "E "},
								{"F ", "A ", "C ", "D "}};

	std::vector<std::vector<std::string>> aSChord = { {"A#", "D ", "F "},
								{"A#", "D ", "F ", "G#"},
								{"A#", "D ", "F ", "A "},
								{"A#", "D ", "F ", "G "}};

	std::vector<std::vector<std::string>> aMChord = { {"Am", "C ", "E "},
								{"Am", "C ", "E ", "G "},
								{"Am", "C#", "E ", "G#"},
								{"Am", "C#", "E ", "F#"}};

	std::vector<std::vector<std::string>> gSChord = { {"G#", "C ", "Eb"},
								{"G#", "C ", "Eb", "F#"},
								{"G#", "C ", "D#", "G "},
								{"G#", "C ", "D#", "F "}};

	std::vector<std::vector<std::string>> dSChord = { {"D#", "G ", "Bb"},
								{"D#", "G ", "A#", "C#"},
								{"D#", "G ", "A#", "D "},
								{"D#", "G ", "A#", "C "}};

	std::vector<std::vector<std::string>> dMChord = { {"Dm", "F ", "A "},
								{"Dm", "F ", "A ", "C "},
								{"Dm", "F ", "A ", "C#"},
								{"Dm", "F ", "A ", "B "}};

	std::vector<std::vector<std::string>> fMChord = { {"Fm", "Ab", "C "},
								{"Fm", "Ab", "C ", "Eb"},
								{"Fm", "Ab", "C ", "E "},
								{"Fm", "Ab", "C ", "D "}};

	std::vector<std::vector<std::vector<std::string>>> chordNotes = { cChord,
																	gChord,
																	cMChord,
																	fChord,
																	aSChord,
																	aMChord,
																	gSChord,
																	dSChord,
																	dMChord,
																	fMChord };
};