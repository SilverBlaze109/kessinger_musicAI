#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include "midiMaker.h"
#include "songClass.h"

std::vector<songClass> geneticAl(int popSize, int barSize);

std::vector<int> barOrderMaker(int size);

std::vector<chord> makeMeasureVariant(int randomSel, std::vector<chord> startingChord);

int main()
{
    chordInfo mChordInfo;
    const int POPSIZE = 100;

    //give rand a seed for everything that'll use it
    srand(time(NULL));

    for (int j = 0; j < 3; j++)
    {
        //this will hold the population of songs
        std::vector< std::vector< std::vector<chord> > > bestBars(3);
        std::vector< std::vector<int> > verseOrder;
        int barSize[3] = { 4, 5, 3 };
        int barOrder[8] = { 0, 1, 0, 1, 0, 2, 0, 1 };

        //setup our MIDI maker
        midiMaker midiM;

        //for the 3 different bars
        for (int x = 0; x < 3; x++)
        {
            //create the first measure
            bestBars[x].push_back((geneticAl(POPSIZE, 4))[POPSIZE - 1].getSong());
            //create the blueprint for the verse
            verseOrder.push_back(barOrderMaker(barSize[x]));

            std::cout << "verseOrder: ";
            //we'll count the number of changes we need to make
            int verseMaxNum = 0;
            for (int y = 0; y < verseOrder[x].size(); y++)
            {
                if (verseOrder[x][y] > verseMaxNum)
                {
                    verseMaxNum = verseOrder[x][y];
                }
                std::cout << verseOrder[x][y];
            }

            std::cout << "\nverseMaxNum: " << verseMaxNum << "\n";

            //for each measure after the first
            for (int y = 1; y <= verseMaxNum; y++)
            {
                std::cout << "start y loop\n";
                //randomly select a chord to be altered and the varaition we'll use
                int chordChange = rand() % 3;
                int typeChange = rand() % 4;

                std::cout << "before mMV\n";
                std::cout << "size of bestBars " << bestBars[x].size() << " and y = " << y << "\n";
                bestBars[x].push_back(makeMeasureVariant(typeChange, bestBars[x][0]));
                std::cout << "before mMV\n";
            }
        }

        std::cout << "before song creation\n";
        //for every bar in the song (barOrder)
        for (int x = 0; x < 8; x++)
        {
            //we'll add the respective verse
            for (int y = 0; y < verseOrder.size(); y++)
            {
                std::cout << "before tempInt\n";
                int tempInt = verseOrder[barOrder[x]][y];
                std::cout << "before newSong\n";
                std::cout << "bestBars size: " << bestBars.size() << " " << bestBars[barOrder[x]].size() << "\n";
                std::cout << "verseOrder: " << verseOrder[barOrder[x]][y] << "\n";
                std::wcout << "after output\n";
                std::vector<chord> newSong = bestBars[barOrder[x]][verseOrder[barOrder[x]][y]];
                std::wcout << "before loop newSong\n";
                for (int a = 0; a < newSong.size(); a++)
                {
                    midiM.playNote(newSong[a], 100);
                }
            }
        }

        /*

                    std::vector<chord> newSong = bestBars[barOrder[x]][verseOrder[a]];
                    for (int y = 0; y < newSong.size(); y++)
                    {
                        midiM.playNote(newSong[y], 100);
                    }
        */

        midiM.outputMidi("structuredSong" + std::to_string(j));
    }
    //pause program to display any output
    std::cout << "Program end reached. Enter any character to continue...\n";
    char ending;
    std::cin >> ending;

    return 0;
}


std::vector<chord> makeMeasureVariant(int randomSel, std::vector<chord> startingChord)
{
    std::vector<chord> newVec;
    chordInfo mChordInfo;
    int chordVar = rand() % 3;
    int currentChord;
    bool foundChord;
    int randNum;

    if (randomSel == 0)
    {
        for (int z = 0; z < startingChord.size(); z++)
        {
            newVec.push_back(startingChord[z]);
        }

        std::shuffle(newVec.begin(), newVec.end(), std::random_device());
    }
    else
    {
        for (int z = 0; z < startingChord.size(); z++)
        {
            if (z >= randomSel)
            {
                randNum = (rand() % 100) + 1;
                foundChord = false;
                std::cout << "before make chord\n";

                //to find what chord is next, we'll create a sum array
                int sumArray[10];
                sumArray[0] = mChordInfo.transitionProb[startingChord[z].chordIndex][0];
                for (int x = 1; x < 10; x++)
                {
                    sumArray[x] = sumArray[x - 1] + mChordInfo.transitionProb[startingChord[z].chordIndex][x];
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

                //...then we make a new chord that's a variation of the old one
                chord tempChord = makeChord(mChordInfo, currentChord, startingChord[z].octave[0], 0);
                //and add it to the Bars
                std::cout << "before push tempChord\n";
                newVec.push_back(tempChord);
            }
            else
            {
                std::cout << "before make prev chord\n";
                chord tempChord = startingChord[z];
                std::cout << "before push prev tempChord\n";
                //else we just push back the same chord
                newVec.push_back(tempChord);
            }
        }
    }

    std::cout << "before return newVec\n";
    return newVec;
}

std::vector<int> barOrderMaker(int size)
{
    std::vector<int> order;
    order.push_back(0);
    order.push_back(1);

    int numDifferentBar = 1;

    for (int x = 2; x < size; x++)
    {
        order.push_back((rand() % (numDifferentBar + 1)));
        if (order[x] == numDifferentBar)
        {
            numDifferentBar++;
        }
    }

    return order;
}

std::vector<songClass> geneticAl(int popSize, int barSize)
{
    std::vector<songClass> population;
    std::vector<int> songEval;
    songEval.resize(popSize);

    //setup our MIDI maker
    midiMaker midiM;

    std::cout << "Starting Program and creating population\n";

    //fill population
    for (int x = 0; x < popSize; x++)
    {
        songClass temp(barSize);
        population.push_back(temp);
    }

    std::cout << "Population created\n";

    //we'll have 100 generations
    for (int x = 0; x < 100; x++)
    {
        std::cout << "Starting generation #" << x + 1 << "\n";


        std::cout << "Starting fitness function evaluation\n";

        //run a fitness function
        for (int y = 0; y < popSize; y++)
        {
            //we'll evaluate groups of 4 functions
            songEval[y] = population[y].fitnessFunc(4);
        }

        std::cout << "Selecting best songs\n";

        //select the best songs
        std::vector<songClass> bestSongs;
        for (int y = 0; y < popSize; y++)
        {
            //we need to sort the songs based on how well they did
            for (int i = 0; i < popSize - 1; i++)
            {
                for (int j = 0; j < popSize - i - 1; j++)
                {
                    if (songEval[j] > songEval[j + 1])
                    {
                        int tempInt = songEval[j + 1];
                        songEval[j + 1] = songEval[j];
                        songEval[j] = tempInt;

                        songClass tempSong = population[j + 1];
                        population[j + 1] = population[j];
                        population[j] = tempSong;
                    }
                }
            }

            //then we'll take the top 50%
            for (int z = popSize - 1; z > popSize / 2; z--)
            {
                bestSongs.push_back(population[z]);
            }
        }

        std::cout << "Beginning breeding\n";

        //crossover best songs to create new population
        for (int y = 0; y < popSize; y++)
        {
            int temp1 = rand() % bestSongs.size();
            int temp2 = rand() % bestSongs.size();

            int randStartPos = rand() % (barSize - 2);

            bestSongs[temp1].crossOver(randStartPos, randStartPos + 2, bestSongs[temp2]);

            songClass changedSong = bestSongs[temp1];

            population[y] = changedSong;
        }

        std::cout << "Beginning mutation\n";

        //mutation
        for (int y = 0; y < popSize; y++)
        {
            //1/10 chance to have a random mutation to occur
            if (rand() % 10 == 0)
            {
                int pos = rand() % barSize;
                population[y].mutate(pos);
            }
        }

        std::cout << "Ending generation #" << x + 1 << "\n";
    }


    //we'll do a final analysis of the songs
    for (int y = 0; y < popSize; y++)
    {
        //we'll evaluate groups of 4 functions
        songEval[y] = population[y].fitnessFunc(4);
    }

    //we'll sort the population so the best songs are at the end
    for (int i = 0; i < popSize - 1; i++)
    {
        for (int j = 0; j < popSize - i - 1; j++)
        {
            if (songEval[j] > songEval[j + 1])
            {
                int tempInt = songEval[j + 1];
                songEval[j + 1] = songEval[j];
                songEval[j] = tempInt;

                songClass tempSong = population[j + 1];
                population[j + 1] = population[j];
                population[j] = tempSong;
            }
        }
    }
    
    std::cout << "Returning population\n";

    return population;
}

/*
    for (int x = 0; x < popSize; x++)
    {
        std::vector<chord> newSong = population[x].getSong();
        for (int y = 0; y < newSong.size(); y++)
        {
            midiM.playNote(newSong[y], 100);
        }
        midiM.outputMidi("preAI_song" + std::to_string(x + 1));
        midiM.resetMidi();
    }

    for (int x = 0; x < POPSIZE; x++)
    {
        std::vector<chord> newSong = population[x].getSong();
        for (int y = 0; y < newSong.size(); y++)
        {
            midiM.playNote(newSong[y], 100);
        }
        midiM.outputMidi("postAI_song" + std::to_string(x + 1));
        midiM.resetMidi();
    }
*/