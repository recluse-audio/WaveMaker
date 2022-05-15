/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveMakerAudioProcessorEditor::WaveMakerAudioProcessorEditor (WaveMakerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    startTimerHz(30);

    setLookAndFeel(&waveFeel);

    testButton = std::make_unique<TextButton>("Test");
    testButton->addListener(this);
    testButton->setClickingTogglesState(true);
    addAndMakeVisible(testButton.get());
    

    makeButton = std::make_unique<TextButton>("Make Wave");
    makeButton->addListener(this);
    addAndMakeVisible(makeButton.get());

    normalizeButton = std::make_unique<TextButton>("Normalize");
    normalizeButton->addListener(this);
    normalizeButton->setClickingTogglesState(true);
    addAndMakeVisible(normalizeButton.get());

    waveSize = std::make_unique<WaveSizeControl>(waveFactory);
    addAndMakeVisible(waveSize.get());
    //waveFactory.numHarmonicsChanged(numHarmonics);

    for (int i = 0; i < numHarmonics; i++)
    {
        auto harmonic = new HarmonicComponent(i);
        addAndMakeVisible(*harmonic);
        harmonics.add(harmonic);
    }

    waveVisual = std::make_unique<WaveVisual>(waveFactory);
    addAndMakeVisible(waveVisual.get());

    nameInput = std::make_unique<Label>();
    nameInput->setText("Enter Name", NotificationType::dontSendNotification);
    nameInput->setEditable(true);
    nameInput->onTextChange = [this] { enterName(nameInput->getText()); };
    addChildComponent(nameInput.get());

    setSize(1000, 500);
}

WaveMakerAudioProcessorEditor::~WaveMakerAudioProcessorEditor()
{
}

//==============================================================================
void WaveMakerAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto color = Colour().fromFloatRGBA(0.1f, 0.05f, 0.35f, 1.f);
    g.fillAll(color);
}

void WaveMakerAudioProcessorEditor::resized()
{
    waveVisual->setBoundsRelative(0.25f, 0.f, 0.75f, 0.475f);

    for (int i = 0; i < numHarmonics; i++)
    {
        float width = 0.725f / (float)numHarmonics;
        float xPos = width * i;
        harmonics[i]->setBoundsRelative(xPos + 0.25, 0.5f, width, 0.5f);
    }

    testButton->setBoundsRelative(0.f, 0.f, 0.1f, 0.1f);

    makeButton->setBoundsRelative(0.f, 0.3f, 0.1f, 0.1f);
    nameInput->setBoundsRelative(0.1f, 0.3f, 0.15f, 0.1f);

    normalizeButton->setBoundsRelative(0.f, 0.5f, 0.1f, 0.1f);

    
    waveSize->setBoundsRelative(0.f, 0.7f, 0.225f, 0.075f);
}

void WaveMakerAudioProcessorEditor::buttonClicked(Button* b)
{
    if (b == testButton.get())
    {
        if (testButton->getToggleState())
        {
            audioProcessor.passWaveform(waveFactory.getBuffer());
        }
        audioProcessor.testWave(testButton->getToggleState());
    }

    if (b == makeButton.get())
    {
        /*for (int i = 0; i < numHarmonics; i++)
        {
            float harm = i + 1;
            harmonics[i]->setCoef(1.f / harm);
            harmonics[i]->setMultiple(harm);
        }*/
        nameInput->setVisible(true);
        
    }

    if (b == normalizeButton.get())
    {
        waveFactory.setNormalized(normalizeButton->getToggleState());
    }
}

void WaveMakerAudioProcessorEditor::timerCallback()
{
    repaint();
    waveFactory.createWave(getHarmonicMult(), getHarmonicCoefs());
    //waveVisual->repaint();
    //waveVisual->updateWaveBuffer(waveFactory->getBuffer());
}

Array<float> WaveMakerAudioProcessorEditor::getHarmonicCoefs()
{
    Array<float> floatArray;
        
    for (int i = 0; i < numHarmonics; i++)
    {
        floatArray.add(harmonics[i]->getHarmonicGain());
    }

    return floatArray;
}

Array<float> WaveMakerAudioProcessorEditor::getHarmonicMult()
{
    Array<float> floatArray;

    for (int i = 0; i < numHarmonics; i++)
    {
        floatArray.add(harmonics[i]->getHarmonicRatio());
    }

    return floatArray;
}

void WaveMakerAudioProcessorEditor::normalizeWave()
{
    
}

void WaveMakerAudioProcessorEditor::enterName(StringRef name)
{
    String filePath = "C:/Users/ryand/Desktop";
    bufferWriter.writeBufferToDisk(waveFactory.getBuffer(), filePath, name);
    nameInput->setVisible(false);
}
