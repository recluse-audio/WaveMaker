/*
  ==============================================================================

    HarmonicComponent.h
    Created: 17 Jan 2022 7:26:59pm
    Author:  ryand

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveFactory.h"
#include "WaveFeel.h"
#include "TuningTool.h"


//==============================================================================
/*
*/
class HarmonicComponent  : public juce::Component
{
public:
    HarmonicComponent(int index) 
    {
        setLookAndFeel(&waveFeel);

        harmGain = std::make_unique<Slider>();
        harmGain->setSliderStyle(Slider::SliderStyle::LinearBarVertical);
        harmGain->setTextBoxIsEditable(true);
        harmGain->setRange(0.0, 1.0, 0.001);
        addAndMakeVisible(harmGain.get());

      
        if (index != 0)
        {
            isFundamental = false;
            harmInt = std::make_unique<Slider>();
            harmInt->setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
            harmInt->setTextBoxIsEditable(true);
            harmInt->setRange(1.0, 20.0, 1.0);
            harmInt->setValue((double)index + 1.0);
            addAndMakeVisible(harmInt.get());

            harmFine = std::make_unique<Slider>();
            harmFine->setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
            harmFine->setTextBoxIsEditable(true);
            harmFine->setRange(-1.0, 1.0, 0.01);
            addAndMakeVisible(harmFine.get());
        }
        else
        {
            isFundamental = true;
        }

        
        

    }

    ~HarmonicComponent() override
    {
    }

    void paint (juce::Graphics& g) override
    {

    }

    void resized() override
    {
        harmGain->setBoundsRelative(0.f, 0.f, 1.f, 0.4f);
        if (!isFundamental)
        {
            harmInt->setBoundsRelative(0.f, 0.4f, 1.f, 0.3f);
            harmFine->setBoundsRelative(0.f, 0.7f, 1.f, 0.3f);
        }
        
    }

    // the gain for a given harmonic (or partial)
    float getHarmonicGain()
    {
        return harmGain->getValue();
    }

    // integer multiple + a fine tune
    float getHarmonicRatio()
    {
        float harmRatio = 1.f;

        if (!isFundamental)
        {
            auto mult = harmInt->getValue() + harmFine->getValue();
            harmRatio = jlimit(1.0, 64.0, mult);
        }
        
        return harmRatio;
    }

    // multiple of fundamental
    float getHarmInt()
    {
        if (isFundamental)
        {
            return 1.f;
        }

        return harmInt->getValue();
    }

    void setCoef(float harmVal)
    {
        harmGain->setValue(harmVal, NotificationType::dontSendNotification);
    }

    void setMultiple(float multVal)
    {
        if(!isFundamental)
            harmInt->setValue(multVal, NotificationType::dontSendNotification);
    }
private:
    float value = 0.f;
    bool isFundamental = false;
    std::unique_ptr<Slider> harmGain;
    std::unique_ptr<Slider> harmInt;
    std::unique_ptr<Slider> harmFine;

    WaveFeel waveFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarmonicComponent)
};
