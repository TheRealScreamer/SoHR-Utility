/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SoHRUtilityAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SoHRUtilityAudioProcessorEditor (SoHRUtilityAudioProcessor&);
    ~SoHRUtilityAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Slider trimKnob; /*creates the Trim Knob slider*/
    juce::TextButton phaseInvertBut{"Phase"}; /*creates the phase button that says phase*/
    juce::Label trimKnobLabel; /*creates the variable for the text above knob*/
    juce::Slider inputGainKnob; /*creates the variable for input gain*/
    juce::Label inputGainLabel;

    SoHRUtilityAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoHRUtilityAudioProcessorEditor)
};
