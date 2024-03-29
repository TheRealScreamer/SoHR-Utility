/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SoHRUtilityAudioProcessorEditor::SoHRUtilityAudioProcessorEditor(SoHRUtilityAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    //==============================Input Gain==================================
    addAndMakeVisible(inputGainKnob);
    inputGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    inputGainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 66, 28);
    inputGainKnob.setDoubleClickReturnValue(true, 0.0);
    inputGainKnob.setRange(-48.0, 48.0, 0.25); // Adjust the range as needed
    inputGainKnob.setValue(0.0); // Set the default value
    inputGainKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple.withAlpha(0.0f)); /*hides the thumb of the knob*/
    inputGainKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::purple.withAlpha(1.0f)); /*color of slider*/
    inputGainKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::ghostwhite.withAlpha(0.25f)); /*color of slider background*/
    inputGainKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::purple.withAlpha(1.0f)); /*color of values under knob*/
    inputGainKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::purple.withAlpha(0.0f)); /*color of the box around text above*/

    inputGainKnob.onValueChange = [this]()
        {
            audioProcessor.setInputGain(inputGainKnob.getValue());
        };

    addAndMakeVisible(inputGainLabel); /*Makes the Trim Knob Label Visible*/
    inputGainLabel.setText("Input", juce::dontSendNotification); /*Generates the text above the knob*/
    inputGainLabel.setJustificationType(juce::Justification::centred); /*Makes the text centered*/
    inputGainLabel.attachToComponent(&inputGainKnob, false); /*Attaches the text to the knob*/
    inputGainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::purple.withAlpha(1.0f)); /*sets text color*/

    //=============================Phase Button==================================
    addAndMakeVisible(phaseInvertBut); /*Makes the Phase Button Visible*/
    phaseInvertBut.setClickingTogglesState(true); /*makes the button clickable*/
    phaseInvertBut.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::white.withAlpha(0.5f)); /*colors the button when off*/
    phaseInvertBut.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::ghostwhite.withAlpha(0.25f)); /*colors the button when on*/
    phaseInvertBut.setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::purple.withAlpha(0.5f)); /*button text on color*/
    phaseInvertBut.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::purple.withAlpha(1.0f)); /*button text off color*/

    phaseInvertBut.onClick = [this]()
        {
            bool newState = phaseInvertBut.getToggleState();
            audioProcessor.setPhaseState(newState);
        };

    //==============================High Pass===================================
    addAndMakeVisible(hiPassFreqKnob);
    hiPassFreqKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    hiPassFreqKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 66, 28);
    hiPassFreqKnob.setDoubleClickReturnValue(true, 0.0);
    hiPassFreqKnob.setRange(-48.0, 48.0, 0.25); // Adjust the range as needed
    hiPassFreqKnob.setValue(0.0); // Set the default value
    hiPassFreqKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple.withAlpha(0.0f)); /*hides the thumb of the knob*/
    hiPassFreqKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::purple.withAlpha(1.0f)); /*color of slider*/
    hiPassFreqKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::ghostwhite.withAlpha(0.25f)); /*color of slider background*/
    hiPassFreqKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::purple.withAlpha(1.0f)); /*color of values under knob*/
    hiPassFreqKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::purple.withAlpha(0.0f)); /*color of the box around text above*/

    addAndMakeVisible(hiPassFreqLabel); /*Makes the Trim Knob Label Visible*/
    hiPassFreqLabel.setText("Hi-Pass Freq", juce::dontSendNotification); /*Generates the text above the knob*/
    hiPassFreqLabel.setJustificationType(juce::Justification::centred); /*Makes the text centered*/
    hiPassFreqLabel.attachToComponent(&hiPassFreqKnob, false); /*Attaches the text to the knob*/
    hiPassFreqLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::purple.withAlpha(1.0f)); /*sets text color*/


    addAndMakeVisible(hiPassGainKnob);
    hiPassGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    hiPassGainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 66, 28);
    hiPassGainKnob.setDoubleClickReturnValue(true, 0.0);
    hiPassGainKnob.setRange(-48.0, 48.0, 0.25); // Adjust the range as needed
    hiPassGainKnob.setValue(0.0); // Set the default value
    hiPassGainKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple.withAlpha(0.0f)); /*hides the thumb of the knob*/
    hiPassGainKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::purple.withAlpha(1.0f)); /*color of slider*/
    hiPassGainKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::ghostwhite.withAlpha(0.25f)); /*color of slider background*/
    hiPassGainKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::purple.withAlpha(1.0f)); /*color of values under knob*/
    hiPassGainKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::purple.withAlpha(0.0f)); /*color of the box around text above*/

    addAndMakeVisible(hiPassGainLabel); /*Makes the Trim Knob Label Visible*/
    hiPassGainLabel.setText("Hi-Pass Gain", juce::dontSendNotification); /*Generates the text above the knob*/
    hiPassGainLabel.setJustificationType(juce::Justification::centred); /*Makes the text centered*/
    hiPassGainLabel.attachToComponent(&hiPassGainKnob, false); /*Attaches the text to the knob*/
    hiPassGainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::purple.withAlpha(1.0f)); /*sets text color*/


    //==============================High Shelf===================================
    addAndMakeVisible(hiShelfFreqKnob);
    hiShelfFreqKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    hiShelfFreqKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 66, 28);
    hiShelfFreqKnob.setDoubleClickReturnValue(true, 0.0);
    hiShelfFreqKnob.setRange(-48.0, 48.0, 0.25); // Adjust the range as needed
    hiShelfFreqKnob.setValue(0.0); // Set the default value
    hiShelfFreqKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple.withAlpha(0.0f)); /*hides the thumb of the knob*/
    hiShelfFreqKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::purple.withAlpha(1.0f)); /*color of slider*/
    hiShelfFreqKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::ghostwhite.withAlpha(0.25f)); /*color of slider background*/
    hiShelfFreqKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::purple.withAlpha(1.0f)); /*color of values under knob*/
    hiShelfFreqKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::purple.withAlpha(0.0f)); /*color of the box around text above*/

    addAndMakeVisible(hiShelfFreqLabel); /*Makes the Trim Knob Label Visible*/
    hiShelfFreqLabel.setText("Hi-Shelf Freq", juce::dontSendNotification); /*Generates the text above the knob*/
    hiShelfFreqLabel.setJustificationType(juce::Justification::centred); /*Makes the text centered*/
    hiShelfFreqLabel.attachToComponent(&hiShelfFreqKnob, false); /*Attaches the text to the knob*/
    hiShelfFreqLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::purple.withAlpha(1.0f)); /*sets text color*/


    addAndMakeVisible(hiShelfGainKnob);
    hiShelfGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    hiShelfGainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 66, 28);
    hiShelfGainKnob.setDoubleClickReturnValue(true, 0.0);
    hiShelfGainKnob.setRange(-48.0, 48.0, 0.25); // Adjust the range as needed
    hiShelfGainKnob.setValue(0.0); // Set the default value
    hiShelfGainKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple.withAlpha(0.0f)); /*hides the thumb of the knob*/
    hiShelfGainKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::purple.withAlpha(1.0f)); /*color of slider*/
    hiShelfGainKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::ghostwhite.withAlpha(0.25f)); /*color of slider background*/
    hiShelfGainKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::purple.withAlpha(1.0f)); /*color of values under knob*/
    hiShelfGainKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::purple.withAlpha(0.0f)); /*color of the box around text above*/

    addAndMakeVisible(hiShelfGainLabel); /*Makes the Trim Knob Label Visible*/
    hiShelfGainLabel.setText("Hi-Shelf Gain", juce::dontSendNotification); /*Generates the text above the knob*/
    hiShelfGainLabel.setJustificationType(juce::Justification::centred); /*Makes the text centered*/
    hiShelfGainLabel.attachToComponent(&hiShelfGainKnob, false); /*Attaches the text to the knob*/
    hiShelfGainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::purple.withAlpha(1.0f)); /*sets text color*/

    //==============================Trim===================================
    addAndMakeVisible(trimKnob); /*Makes the Trim Knob visible*/
    trimKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag); /*changes boring slider to knob*/
    trimKnob.setRange(-48.0, 48.0, 0.25); /*sets the min and max of the knob (Min, Max, Interval Value)*/
    trimKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 66, 28); /*changes position and size of text box    (sets TB below Knob, Type in Box?, Width, Height)*/
    trimKnob.setDoubleClickReturnValue(true, 0.0); /*sets knob back to 0 when double clicked*/
    trimKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple.withAlpha(0.0f)); /*hides the thumb of the knob*/
    trimKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::purple.withAlpha(1.0f)); /*color of slider*/
    trimKnob.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::ghostwhite.withAlpha(0.25f)); /*color of slider background*/
    trimKnob.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::purple.withAlpha(1.0f)); /*color of values under knob*/
    trimKnob.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::purple.withAlpha(0.0f)); /*color of the box around text above*/

    trimKnob.onValueChange = [this]()
        {
            audioProcessor.setTrimGain(trimKnob.getValue());
        };

    addAndMakeVisible(trimKnobLabel); /*Makes the Trim Knob Label Visible*/
    trimKnobLabel.setText("Trim", juce::dontSendNotification); /*Generates the text above the knob*/
    trimKnobLabel.setJustificationType(juce::Justification::centred); /*Makes the text centered*/
    trimKnobLabel.attachToComponent(&trimKnob, false); /*Attaches the text to the knob*/
    trimKnobLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::purple.withAlpha(1.0f)); /*sets text color*/




    setSize(800, 400);/*pixel size of plugin*/
}

SoHRUtilityAudioProcessorEditor::~SoHRUtilityAudioProcessorEditor()
{
}

//==============================================================================
void SoHRUtilityAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
}

void SoHRUtilityAudioProcessorEditor::resized()
{
    float topMargin = getHeight() * 0.15; /*Creates a variable to position knob along the y axis*/
    float leftMargin = getWidth() * 0.02; /*Creates a variable to position knob along x axis*/
    float rightMargin = getWidth() * 1.33;
    float knobSize = getWidth() * 0.5; /*Control overall knob size*/

    //Position trimKnob at top-left
    inputGainKnob.setBounds(leftMargin, topMargin * 0.35, knobSize * 0.3, knobSize * 0.3);

    //Position hi pass freq at bottom-left
    hiPassFreqKnob.setBounds(leftMargin, topMargin * 4.4, knobSize * 0.3, knobSize * 0.3);

    //Position hi pass gain at bottom-left
    hiPassGainKnob.setBounds(leftMargin / .08, topMargin * 4.4, knobSize * 0.3, knobSize * 0.3);

    //Position hi shelf freq at bottom-left
    hiShelfFreqKnob.setBounds(rightMargin * 0.63, topMargin * 4.4, knobSize * 0.3, knobSize * 0.3);

    //Position hi shelf gain at bottom-left
    hiShelfGainKnob.setBounds(rightMargin * 0.45, topMargin * 4.4, knobSize * 0.3, knobSize * 0.3);

    //Position phaseInvertBut at bottom-center
    phaseInvertBut.setBounds(getWidth() * 0.58 - knobSize * 0.25, getHeight() - knobSize * 0.13 - 16, 80, 40);

    //Position Trim at top-right
    trimKnob.setBounds(rightMargin * 0.63, topMargin * 0.35, knobSize * 0.3, knobSize * 0.3);

    //trimKnob.setBounds(leftMargin, topMargin,knobSize,knobSize); /*sets the position of the slider.  (x-axis, y-axis, Width, Height)*/
    //trimKnob.setBounds(0, 0, 100,100);
    //phaseInvertBut.setBounds(trimKnob.getX() + trimKnob.getWidth() * 0.25, trimKnob.getY() + trimKnob.getHeight() + 16, trimKnob.getWidth() * 0.5, trimKnob.getWidth() * 0.25); /*see comment above^^^*/
    //inputGainKnob.setBounds(800, 0, 100, 100);
}
