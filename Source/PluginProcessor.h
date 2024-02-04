/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class SoHRUtilityAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    SoHRUtilityAudioProcessor();
    ~SoHRUtilityAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    //Getter and setter for inputgain
    float getInputGain() const { return inputGain; }
    void setInputGain(float newValue) { inputGain = newValue; }

    //Getter and setter for phaseState
    bool getPhaseState() const { return phaseState; }
    void  setPhaseState(bool newState) { phaseState = newState; }

    //Getter and setter for trimgain
    float getTrimGain() const { return trimGain; }
    void setTrimGain(float newValue) { trimGain = newValue; }

private:

    float inputGain;

    float phaseState;

    float trimGain;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SoHRUtilityAudioProcessor)
};
