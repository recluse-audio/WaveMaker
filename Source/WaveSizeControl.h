/*
  ==============================================================================

    WaveSizeControl.h
    Created: 18 Jan 2022 3:30:16pm
    Author:  ryand

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WaveFactory.h"
#include "WaveFeel.h"

//==============================================================================
/*
*       Holds a label for text input and a button to call 
*/
class WaveSizeControl  : public juce::Component, Button::Listener
{
public:
    WaveSizeControl(WaveFactory& w) : waveFactory(w)
    {
        setLookAndFeel(&waveFeel);

        size256 = std::make_unique<TextButton>("256");
        size256->addListener(this);
        size256->setClickingTogglesState(true);
        size256->setRadioGroupId(1);
        addAndMakeVisible(size256.get());

        size512 = std::make_unique<TextButton>("512");
        size512->addListener(this);
        size512->setClickingTogglesState(true);
        size512->setRadioGroupId(1);
        addAndMakeVisible(size512.get());

        size1024 = std::make_unique<TextButton>("1024");
        size1024->addListener(this);
        size1024->setClickingTogglesState(true);
        size1024->setRadioGroupId(1);
        addAndMakeVisible(size1024.get());

        size2048 = std::make_unique<TextButton>("2048");
        size2048->addListener(this);
        size2048->setClickingTogglesState(true);
        size2048->setToggleState(true, NotificationType::dontSendNotification);
        size2048->setRadioGroupId(1);
        addAndMakeVisible(size2048.get());

        size4096 = std::make_unique<TextButton>("4096");
        size4096->addListener(this);
        size4096->setClickingTogglesState(true);
        size4096->setRadioGroupId(1);
        addAndMakeVisible(size4096.get());

        label = std::make_unique<Label>("Wave Size In Samples");
        label->setText("Wave Size In Samples", NotificationType::dontSendNotification);
        label->setJustificationType(Justification::centred);
        addAndMakeVisible(label.get());

    }

    ~WaveSizeControl() override
    {
    }

    void paint (juce::Graphics& g) override
    {

    }

    void resized() override
    {
        size256->setBoundsRelative(0.f, 0.2f, 0.2f, 0.75f);
        size512->setBoundsRelative(0.2f, 0.2f, 0.2f, 0.75f);
        size1024->setBoundsRelative(0.4f, 0.2f, 0.2f, 0.75f);
        size2048->setBoundsRelative(0.6f, 0.2f, 0.2f, 0.75f);
        size4096->setBoundsRelative(0.8f, 0.2f, 0.2f, 0.75f);
        label->setBoundsRelative(0.f, 0.f, 1.f, 0.2f);
    }

    void buttonClicked(Button* b) override
    {
        if (b == size256.get())
        {
            tableSize = 256;
            waveFactory.changeTableSize(tableSize);
        }
        if (b == size512.get())
        {
            tableSize = 512;
            waveFactory.changeTableSize(tableSize);
        }
        if (b == size1024.get())
        {
            tableSize = 1024;
            waveFactory.changeTableSize(tableSize);
        }
        if (b == size2048.get())
        {
            tableSize = 2048;
            waveFactory.changeTableSize(tableSize);
        }
        if (b == size4096.get())
        {
            tableSize = 4096;
            waveFactory.changeTableSize(tableSize);
        }
            

    }

private:
    int tableSize = 2048;
    WaveFeel waveFeel;
    WaveFactory& waveFactory;
    std::unique_ptr<TextButton> size256;
    std::unique_ptr<TextButton> size512;
    std::unique_ptr<TextButton> size1024;
    std::unique_ptr<TextButton> size2048;
    std::unique_ptr<TextButton> size4096;
    std::unique_ptr<Label> label;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveSizeControl)
};
