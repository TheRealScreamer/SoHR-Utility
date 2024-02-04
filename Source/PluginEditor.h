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
class SoHRUtilityAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    SoHRUtilityAudioProcessorEditor(SoHRUtilityAudioProcessor&);
    ~SoHRUtilityAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    juce::Slider inputGainKnob; /*creates the variable for input gain*/
    juce::Label inputGainLabel; /*creats the variable for the text above knob*/

    juce::Slider trimKnob; /*creates the Trim Knob slider*/
    juce::Label trimKnobLabel; /*creates the variable for the text above knob*/

    juce::TextButton phaseInvertBut{ "Phase" }; /*creates the phase button that says phase*/

    juce::Slider hiPassFreqKnob; /*creates the variable for Highpass Frequency Knob*/
    juce::Label  hiPassFreqLabel; /*creats the variable for the text above knob*/

    juce::Slider hiPassGainKnob; /*creates the slider for hi pass gain control*/
    juce::Label hiPassGainLabel;/*creates text thatll be attacked to knob*/

    juce::Slider hiShelfFreqKnob; /*creates the variable for Highpass Frequency Knob*/
    juce::Label  hiShelfFreqLabel; /*creats the variable for the text above knob*/

    juce::Slider hiShelfGainKnob; /*creates the slider for hi pass gain control*/
    juce::Label hiShelfGainLabel;/*creates text thatll be attacked to knob*/

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SoHRUtilityAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SoHRUtilityAudioProcessorEditor)
};
