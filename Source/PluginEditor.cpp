/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SoHRUtilityAudioProcessorEditor::SoHRUtilityAudioProcessorEditor (SoHRUtilityAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(trimKnob);
    setSize (400, 400);
}

SoHRUtilityAudioProcessorEditor::~SoHRUtilityAudioProcessorEditor()
{
}

//==============================================================================
void SoHRUtilityAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Sound of Hope Recordings", getLocalBounds(), juce::Justification::centred, 1);
}

void SoHRUtilityAudioProcessorEditor::resized()
{
    trimKnob.setBounds(getLocalBounds());
}
