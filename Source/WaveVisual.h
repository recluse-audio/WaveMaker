/*
  ==============================================================================

    WaveVisual.h
    Created: 17 Jan 2022 7:59:23pm
    Author:  ryand

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveVisual  : public juce::Component
{
public:
    WaveVisual(WaveFactory& factory) : waveFactory(factory)
    {

    }

    ~WaveVisual() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        auto w = getLocalBounds().getWidth();
        auto h = getLocalBounds().getHeight();
        auto frameHalf = h / 2;
        

        auto waveBuffer = waveFactory.getBuffer();
        float waveIncrement = (float)w / (float)waveBuffer.getNumSamples();
     
        juce::Rectangle<int> waveFrame = { 0,0, w, h };

        g.fillRoundedRectangle(waveFrame.toFloat(), 5.f);

        g.setColour(Colours::pink);

        juce::Path wavePath;

        wavePath.startNewSubPath(0, frameHalf);

        auto* buffRead = waveBuffer.getReadPointer(0);

        for (int i = 0; i < waveBuffer.getNumSamples() - 1; ++i)
        {
            auto x = i * waveIncrement;
            auto value1 = buffRead[i];

            auto y = frameHalf - (value1 * frameHalf * 0.8f);
            wavePath.lineTo(x, y);
        }
        wavePath.lineTo(w, frameHalf);

        PathStrokeType stroke(3.f, juce::PathStrokeType::curved);
        g.strokePath(wavePath, stroke);

    }


    void resized() override
    {

    }

private:
    WaveFactory& waveFactory;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveVisual)
};
