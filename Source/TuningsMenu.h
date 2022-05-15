/*
  ==============================================================================

    TuningMenu.h
    Created: 18 Jan 2022 5:18:30pm
    Author:  ryand

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "TuningTool.h"


//==============================================================================
/*
*       A base class for Juce_Recluse menus
*/
class TuningMenu  : public juce::Component, Button::Listener
{
public:
    TuningMenu();
    ~TuningMenu() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked(Button* b) override;

    void prepareMenu();
    void runMenuSelection(int selection); // override this to make the class work

private:
    PopupMenu menu;
    std::unique_ptr<TextButton> menuButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TuningMenu)
};
