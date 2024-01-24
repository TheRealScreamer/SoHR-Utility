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
    addAndMakeVisible(trimKnob); /*Makes the Trim Knob visible*/

    setSize (400, 400);/*pixel size of plugin*/
}

SoHRUtilityAudioProcessorEditor::~SoHRUtilityAudioProcessorEditor()
{
}

//==============================================================================
void SoHRUtilityAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SoHRUtilityAudioProcessorEditor::resized()
{
    trimKnob.setBounds(100,200,200,200); /*sets the position of the slider.  (x-axis, y-axis, Width, Height)*/
}
