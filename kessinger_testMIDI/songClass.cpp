#include "songClass.h"
#include "functions.h"
#include<cstdlib>


//get a chord number and return a randomly made chord
chord makeChord(chordInfo mChordInfo, int chordType, int startOctave, int chordVariation)
{
	chord madeChord;

	//we'll put the chord's index in chordInfo
	madeChord.chordIndex = chordType;

	//then, we'll add the notes

	//we have a 50 chance to have the notes be a different octave
	//int changeOctave = ((rand() % 2) == 0);

	//we'll add the first note to the chord and its octave
	//madeChord.notes.push_back(mChordInfo.chordNotes[chordType][0]);
	madeChord.octave.push_back(startOctave);

	//this will track if we add the second and third notes to the chord
	//there's an 33% chance to add each one
	std::vector<bool> chordExisting;
	int notesExisting;
	bool flag = true;

	int possibleNote = (mChordInfo.chordNotes[chordType][chordVariation]).size();

	while (flag)
	{
		notesExisting = 0;
		for (int x = 0; x < possibleNote; x++)
		{
			bool temp = rand() % 3 == 0;
			chordExisting.push_back(temp);
			notesExisting += temp;
			if (temp)
			{
				flag = false;
			}
		}
	}

	flag = false;
	//for the other two notes of the chord...
	for (int x = 0; x < possibleNote; x++)
	{
		//if we should add the chord...
		if (chordExisting[x])
		{
			//...we'll add the note to the chord
			madeChord.notes.push_back(mChordInfo.chordNotes[chordType][chordVariation][x]);

			//now we'll add the octave
			/*
			if (changeOctave)
			{
				bool noteChange = (rand() % 3) == 0;
				//if we're changing the octave
				if (flag || noteChange || notesExisting == 1)
				{
					madeChord.octave.push_back(startOctave - changeOctave);

					flag = true;
				}
				else
				{
					madeChord.octave.push_back(startOctave);
				}
			}
			else
			{
				//if we don't change the octave, we just add the octave
				madeChord.octave.push_back(startOctave);
			}
			*/

			if (midiNoteToValue(startOctave, mChordInfo.chordNotes[chordType][chordVariation][0]) > midiNoteToValue(startOctave, mChordInfo.chordNotes[chordType][chordVariation][x]))
			{
				madeChord.octave.push_back(startOctave + 1);
			}
			else
			{
				madeChord.octave.push_back(startOctave);
			}
		}

		notesExisting--;
	}

	//now we'll determine the duration

	//there's a 65% chance for a quarter note, 35% for half, 5% for third, and 0% for whole
	int randDuration = rand() % 20;


	if (randDuration < 13)
	{
		madeChord.duration = 1;
	}
	else if (randDuration < 19)
	{
		madeChord.duration = 2;
	}
	else
	{
		madeChord.duration = 3;
	}
	/*
	else
	{
		madeChord.duration = 4;
	}
	*/

	return madeChord;
}

songClass::songClass(int numChords)
{
	resetSong(numChords);
}

void songClass::resetSong(int numChords)
{
	//reset vector
	song.clear();

	//randomly determine starting chord and octave, make the chord, and add it to the song
	int currentChord = rand() % 10;
	int currentOctave = (rand() % 3) + 4;
	song.push_back(makeChord(mChordInfo, currentChord, currentOctave, 0));
	
	int previousChord = currentChord;

	//from previous chord, randomly create the next chord using mChordInfo
	for (int a = 1; a < numChords; a++)
	{
		//first we'll determine the next chord by first getting a number between 1-100
		int randNum = (rand() % 100) + 1;
		int totalNum = 0;
		bool foundChord = false;

		//to find what chord is next, we'll create a sum array
		int sumArray[10];
		sumArray[0] = mChordInfo.transitionProb[currentChord][0];
		for (int x = 1; x < 10; x++)
		{
			sumArray[x] = sumArray[x - 1] + mChordInfo.transitionProb[currentChord][x];
		}

		//then start checking which chord corrosponds to our random number
		if (randNum <= sumArray[0])
		{
			currentChord = 0;
			foundChord = true;
		}

		for (int x = 1; x < 10; x++)
		{
			if (!foundChord && randNum <= sumArray[x])
			{
				currentChord = x;
				foundChord = true;
			}
		}

		//then we'll see if we change octaves, there's a 10% chance to change
		randNum = rand() % 10;
		if (randNum < 1)
		{
			//if we need to change octave, it's a 50/50 chance to go up/down an octave
			randNum = rand() % 10;
			if (randNum <= 5 && currentOctave > 3)
				randNum--;
			else if (currentOctave < 6)
				currentOctave++;
		}

		//now that we've adjusted the chord and octave, we'll add the next chord
		song.push_back(makeChord(mChordInfo, currentChord, currentOctave, 0));
	}
}

std::vector<chord> songClass::getSong()
{
	return song;
}


//crossover function for home function
void songClass::crossOver(int startPos, int endPos, songClass &otherSongClass)
{
	std::vector<chord> returnV = otherSongClass.crossOverCont(startPos, endPos, song);
	
	int y = 0;
	for (int x = startPos; x <= endPos; x++)
	{
		song[x] = returnV[y];
		y++;
	}

}

//crossover function for other function
std::vector<chord> songClass::crossOverCont(int startPos, int endPos, std::vector<chord> otherSong)
{
	std::vector<chord> returnVector;
	
	for (int x = startPos; x <= endPos; x++)
	{
		returnVector.push_back(song[x]);
		song[x] = otherSong[x];
	}

	return returnVector;
}

//mutation function
void songClass::mutate(int position)
{
	//get a random chord to make and the octave it should be
	int randNum = rand() % 10;
	int currentOctave = (song[position].octave)[0];

	//replace chord
	song[position] = makeChord(mChordInfo, randNum, currentOctave, 0);
}

//invert int1 . int2
void songClass::invert(int startPos, int endPos)
{
	//get iterators for where we want to start and end the inverse and do it
	std::vector<chord>::iterator startIterator = song.begin() + startPos;
	std::vector<chord>::iterator endIterator = song.begin() + endPos;
	
	std::reverse(startIterator, endIterator);
}

double songClass::fitnessFunc(int groupSize)
{
	//currGrade is how many points has been scored
	//maxGrade is the number of possible points
	double currGrade = 0, maxGrade = 0;

	std::vector<std::vector<int>> prevDiff;

	int currVecIndex0 = 0;
	//we'll go through the deck group by group
	for (int x = 0; x < song.size(); x += groupSize)
	{
		//we add a new vector to our 2D vector
		std::vector<int> newColumn;
		prevDiff.push_back(newColumn);

		//we'll compare the current group to the next
		for (int y = x; y < x + groupSize - 1; y++)
		{
			if (y + groupSize < song.size())
			{
				//noteVal1 is the numeric value of the next group's chord
				int noteVal1 = midiNoteToValue((song[y + groupSize].octave[0]), (song[y + groupSize].notes[0]));
				//noteVal0 is the numeric value of the current group's chord
				int noteVal0 = midiNoteToValue((song[y].octave[0]), (song[y].notes[0]));

				//now we get the difference between notes
				prevDiff[currVecIndex0].push_back(abs(noteVal1 - noteVal0));
			}
		}

		currVecIndex0++;
	}

	int currDiff;

	for (int x = 0; x < prevDiff.size(); x++)
	{
		currDiff = 0;

		for (int y = 0; y < prevDiff[x].size(); y++)
		{
			currDiff += prevDiff[x][y];
		}

		if (currDiff <= 5)
		{
			currGrade++;
		}

		maxGrade++;
	}

	//return the rating of the song
	return (currGrade/maxGrade) * 10;
}