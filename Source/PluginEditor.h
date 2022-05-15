/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "HarmonicComponent.h"
#include "WaveFactory.h"
#include "WaveVisual.h"
#include "AudioBufferWriter.h"
#include "WaveSizeControl.h"
#include "WaveFeel.h"
#include "TuningTool.h"

//==============================================================================
/**
*/
class WaveMakerAudioProcessorEditor  : public juce::AudioProcessorEditor, Button::Listener, Timer
{
public:
    WaveMakerAudioProcessorEditor (WaveMakerAudioProcessor&);
    ~WaveMakerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(Button* b) override;
    void timerCallback() override;

    Array<float> getHarmonicCoefs();
    Array<float> getHarmonicMult();

    void normalizeWave();

    // used in name inputs (label) call back
    void enterName(StringRef name);

private:
    TuningTool tuningTool;
    int numHarmonics = 24;

    WaveFeel waveFeel;

    BufferWriter bufferWriter;
    WaveFactory waveFactory;
    std::unique_ptr<WaveVisual> waveVisual;
    std::unique_ptr<TextButton> makeButton;
    std::unique_ptr<TextButton> normalizeButton;
    std::unique_ptr<TextButton> testButton;

    std::unique_ptr<Label> nameInput;

    juce::OwnedArray<HarmonicComponent> harmonics;
    std::unique_ptr<WaveSizeControl> waveSize; 
    WaveMakerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveMakerAudioProcessorEditor)
};
