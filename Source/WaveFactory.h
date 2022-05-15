/*
  ==============================================================================

    WaveFactory.h
    Created: 17 Jan 2022 7:55:55pm
    Author:  ryand

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"

class WaveFactory
{
public:
    WaveFactory() 
    {
        waveBuffer.setSize(1, tableSize);
    }

    ~WaveFactory(){}

    void createWave(Array<float>& multiples, Array<float>& coefs)
    {
        jassert(multiples.size() == coefs.size());
        waveBuffer.clear();

        auto* buffWrite = waveBuffer.getWritePointer(0);
      
        for (int i = 0; i < multiples.size(); i++) //
        {
            auto angleDelta = MathConstants<double>::twoPi / (double)(tableSize - 1) * multiples[i];
            auto currentAngle = 0.0;

            float harmonicAmp = coefs[i];

            for (int j = 0; j < tableSize; j++)
            {
                auto sample = std::sin(currentAngle);
                buffWrite[j] += (float)sample * harmonicAmp; //harmonicWeights[harmonic];
                currentAngle += angleDelta;
            }
        }
        if (shouldNormalize)
            normalizeBuffer();
    }

    void updateHarmonic(float val, int index)
    {
        
      //  harmonics.set(index, val);

  
    }

    AudioBuffer<float>& getBuffer()
    {
        return waveBuffer;
    }

    void normalizeBuffer()
    {
        auto mag = waveBuffer.getMagnitude(0, tableSize);
      
        if (mag > 1.f)
        {
            auto dif =  1.f / mag;
            
            waveBuffer.applyGain(0, 0, tableSize, dif);
        }
    }

    void setNormalized(bool norm)
    {
        shouldNormalize = norm;
    }

    void changeTableSize(int tSize)
    {
        tableSize = tSize;
        waveBuffer.setSize(1, tableSize); // create wavetables is called by the main timer so no need to call here
    }
private:
    int tableSize = 2048;
    AudioBuffer<float> waveBuffer;
    bool shouldNormalize = false;
  //  Array<float> harmonics;

};