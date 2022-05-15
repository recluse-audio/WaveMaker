/*
  ==============================================================================

    Menu.cpp
    Created: 18 Jan 2022 5:18:30pm
    Author:  ryand

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TuningsMenu.h"

//==============================================================================
TuningMenu::TuningMenu()
{
    menuButton = std::make_unique<TextButton>("");
    menuButton->addListener(this);
    addAndMakeVisible(menuButton.get());
}

TuningMenu::~TuningMenu()
{
    menu.clear();
}

void TuningMenu::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::transparentBlack.withAlpha(0.f));
    g.fillAll();
}

void TuningMenu::resized()
{
    menuButton->setBoundsRelative(0.f, 0.0f, 0.4f, 0.2f);

}

void TuningMenu::buttonClicked(Button* b)
{
    if (b == menuButton.get())
    {
        if (b == menuButton.get())
        {
            prepareMenu();
            auto menuArea = Rectangle<int>(getScreenX(), getScreenY() - getParentHeight(), getParentWidth(), getParentHeight());
            int selection = menu.showMenu(PopupMenu::Options().withTargetScreenArea(menuArea));

            runMenuSelection(selection);
        }
        repaint();
    }
}

void TuningMenu::prepareMenu()
{
    menu.clear();
    
    menu.addSectionHeader("TUNINGS");

}

void TuningMenu::runMenuSelection(int selection)
{
    if (selection == 0)
    {
        menu.dismissAllActiveMenus();
    }
    else
    {
        switch (selection)
        {
        case 0:
            break;
        case 1:
            break;
        }
    }
}


