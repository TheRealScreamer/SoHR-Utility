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
    trimKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag); /*changes boring slider to knob*/
    trimKnob.setRange(-96.0, 48.0, 0.25); /*sets the min and max of the knob (Min, Max, Interval Value)*/
    trimKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 66, 28); /*changes position and size of text box    (sets TB below Knob, Type in Box?, Width, Height)*/
    trimKnob.setDoubleClickReturnValue(true, 0.0); /*sets knob back to 0 when double clicked*/
    
    addAndMakeVisible(phaseInvertBut); /*Makes the Phase Button Visible*/
    phaseInvertBut.setClickingTogglesState(true); /*makes the button clickable*/

    addAndMakeVisible(trimKnobLabel); /*Makes the Trim Knob Label Visible*/
    trimKnobLabel.setText("Trim", juce::dontSendNotification); /*Generates the text above the knob*/
    trimKnobLabel.setJustificationType(juce::Justification::centred); /*Makes the text centered*/
    trimKnobLabel.attachToComponent(&trimKnob, false); /*Attaches the text to the knob*/

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
    float topMargin = getHeight() * 0.15; /*Creates a variable to position knob along the y axis*/
    float leftMargin = getWidth() * 0.25; /*Creates a variable to position knob along x axis*/
    float knobSize = getWidth() * 0.5; /*Control overall knob size*/

    trimKnob.setBounds(leftMargin, topMargin,knobSize,knobSize); /*sets the position of the slider.  (x-axis, y-axis, Width, Height)*/
    phaseInvertBut.setBounds(trimKnob.getX() + trimKnob.getWidth() * 0.25, trimKnob.getY() + trimKnob.getHeight() + 16, trimKnob.getWidth() * 0.5, trimKnob.getWidth() * 0.25); /*see comment above^^^*/
}
