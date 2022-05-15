/*
  ==============================================================================

    TuningTool.h
    Created: 18 Jan 2022 5:52:45pm
    Author:  ryand

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/*
    Tuning selection set by tuningMenu, but this needs to affect the HarmonicComponent and waveFactory
*/
class TuningTool
{
public:
    TuningTool()
    {
        initTunings();
    }
    ~TuningTool() {}

    // don't need to pass index here but it ensures they go to the same spot
    void addToTunings(Array<float> tuning, StringRef name, int index)
    {
        tuningsArray.set(index, tuning);
        nameArray.set(index, name);
    }

    Array<float>& getArrayOfTunings(int index)
    {
        return tuningsArray[index];
    }

    StringRef getName(int index)
    {
        return nameArray[index];
    }

    Array<float>& getArrayOfPitchClass()
    {
        return harmonicToPitchClass;
    }


private:
    Array<Array<float>> tuningsArray; // not ideal to keep these separate but not sure about multi=arrays
    StringArray nameArray;
                                        // 1   2    3    4    5    6    7   ...  Harmonics   The get sketchy up really high
    Array<float> harmonicToPitchClass = { 0.f, 0.f, 7.f, 0.f, 4.f, 7.f, 10.f, 0.f, 2.f, 4.f, 5.f, 7.f, 8.f, 10.f, 11.f, 0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 5.f, 6.f, 7.f };
    void initTunings()
    {
        
    }
};