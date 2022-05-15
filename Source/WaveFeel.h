/*
  ==============================================================================

    WaveFeel.h
    Created: 18 Jan 2022 7:27:49am
    Author:  ryand

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class WaveFeel : public LookAndFeel_V4
{
public:
    WaveFeel();
    ~WaveFeel();

    void drawLinearSlider(Graphics&,
        int x, int y, int width, int height,
        float sliderPos,
        float minSliderPos,
        float maxSliderPos,
        const Slider::SliderStyle,
        Slider&) override;

    void drawRotarySlider(Graphics&, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, Slider&) override;

    juce::Slider::SliderLayout getSliderLayout(Slider&) override;
    Label* createSliderTextBox(Slider&) override;
    Font getLabelFont(Label&) override;



    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    Font getTextButtonFont(TextButton&, int buttonHeight) override { return getFont(); }

private:
    Font getFont()
    {
        return Font("Consolas", "Regular", 10.f);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveFeel)
};