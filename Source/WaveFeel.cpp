/*
  ==============================================================================

    WaveFeel.cpp
    Created: 18 Jan 2022 7:31:06am
    Author:  ryand

  ==============================================================================
*/

#include "WaveFeel.h"

WaveFeel::WaveFeel()
{
    setColour(TextButton::buttonColourId, Colours::yellow.withAlpha(0.5f));
    setColour(TextButton::buttonOnColourId, Colours::yellow.darker(0.9f));

    setColour(Slider::rotarySliderFillColourId, Colours::yellow);
    setColour(Slider::rotarySliderOutlineColourId, Colours::yellow.withAlpha(0.5f));
}

WaveFeel::~WaveFeel()
{
}

void WaveFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
{
    juce::Rectangle<float> bgFrame(x, y, width, height);
    g.setColour(juce::Colours::whitesmoke);
    g.drawRoundedRectangle(bgFrame, 1.f, 2.f);

    g.setColour(juce::Colours::transparentBlack.withAlpha(0.f));
    g.fillAll();


    juce::Rectangle<float> centerRect(width * 0.03, sliderPos, width * 0.94, height - sliderPos);
    g.setColour(juce::Colours::orange);
    g.fillRoundedRectangle(centerRect, 1.f);
}

void WaveFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    auto radius = jmin<float>(width / 2.1f, height / 2.1f);
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.55f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

    g.setColour(slider.findColour(Slider::textBoxOutlineColourId));

    if (slider.isEnabled())
        g.setColour(slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 1.0f : 0.7f));
    else
        g.setColour(Colour(0x80808080));


    auto lineThickness = jmin(15.0f, jmin(width, height) * 0.45f) * 0.1f;


    g.setColour(findColour(Slider::trackColourId));
    Path outlineArc;
    outlineArc.addArc(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, true);
    g.strokePath(outlineArc, PathStrokeType(lineThickness));

    g.setColour(juce::Colours::orange);
    juce::Path p;
    auto pointerLength = radius * 0.5f;
    auto pointerThickness = 2.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
    g.setColour(findColour(Slider::thumbColourId));
    g.fillPath(p);

    g.setColour(Colours::transparentBlack.withAlpha(0.f));
    g.fillAll();
}

juce::Slider::SliderLayout WaveFeel::getSliderLayout(Slider& slider)
{
    Slider::SliderLayout layout;
    auto bounds = slider.getLocalBounds();

    juce::Rectangle<int> textBox(0, bounds.getHeight() * 0.8f, bounds.getWidth(), bounds.getHeight() * 0.2f);
    Rectangle<int> sliderBox(0, 0, bounds.getWidth(), bounds.getHeight() * 0.8f);

    layout.textBoxBounds = textBox;
    layout.sliderBounds = sliderBox;

    return layout;
}

Label* WaveFeel::createSliderTextBox(Slider& slider)
{
    Label* l = LookAndFeel_V4::createSliderTextBox(slider);
    // make sure editor text is black (so it shows on white background)
    l->setColour(juce::Label::outlineColourId, juce::Colours::transparentWhite.withAlpha(0.0f));
    l->setColour(juce::Slider::textBoxBackgroundColourId, Colours::hotpink.withAlpha(0.f));
    l->setColour(juce::Label::textColourId, Colours::white);

    return l;
}

Font WaveFeel::getLabelFont(Label&)
{
    return getFont();
}

void WaveFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    juce::Rectangle<int> bounds = button.getLocalBounds();

    g.setColour(findColour(TextButton::buttonColourId));
    g.drawRoundedRectangle(bounds.toFloat(), 3.f, 2.f);

    g.setColour(button.findColour(juce::TextButton::buttonColourId).withAlpha(0.1f));
    g.fillAll();

    if (button.isDown())
    {
        g.setColour(button.findColour(juce::TextButton::buttonOnColourId).withAlpha(1.f));
        g.fillRoundedRectangle(bounds.toFloat(), 5.f);
    }
    if (shouldDrawButtonAsHighlighted)
    {
        g.setColour(button.findColour(juce::TextButton::buttonOnColourId).withAlpha(0.5f));
        g.fillRoundedRectangle(bounds.toFloat(), 5.f);
    }
    if (button.getToggleState())
    {
        g.setColour(button.findColour(juce::TextButton::buttonOnColourId).withAlpha(0.8f));
        g.fillRoundedRectangle(bounds.toFloat(), 5.f);
    }

}
