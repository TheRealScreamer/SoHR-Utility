/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SoHRUtilityAudioProcessor::SoHRUtilityAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameters();
}

SoHRUtilityAudioProcessor::~SoHRUtilityAudioProcessor()
{
}

//==============================================================================
const juce::String SoHRUtilityAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SoHRUtilityAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SoHRUtilityAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SoHRUtilityAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SoHRUtilityAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SoHRUtilityAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SoHRUtilityAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SoHRUtilityAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SoHRUtilityAudioProcessor::getProgramName (int index)
{
    return {};
}

void SoHRUtilityAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SoHRUtilityAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SoHRUtilityAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SoHRUtilityAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SoHRUtilityAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Retrieve parameter values
    float inputGain = apvts.getRawParameterValue("InputGain")->load();
    float hiPassGain = apvts.getRawParameterValue("HiPassGain")->load();
    float hiShelfGain = apvts.getRawParameterValue("HiShelfGain")->load();
    float trimGain = apvts.getRawParameterValue("Trim")->load();
    bool phaseInvert = phaseState;

     
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            // Apply processing based on parameters
            float inputSample = channelData[sample];
            inputSample *= juce::Decibels::decibelsToGain(inputGain) * ((!phaseInvert * 2.0) - 1.0);
            channelData[sample] = inputSample;
        }
    }
}

//==============================================================================
bool SoHRUtilityAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SoHRUtilityAudioProcessor::createEditor()
{
    return new SoHRUtilityAudioProcessorEditor (*this);
}

//==============================================================================
void SoHRUtilityAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SoHRUtilityAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
void SoHRUtilityAudioProcessor::addParameters()
{
    // Add parameters with IDs "InputGain", "HiPassGain", "HiShelfGain", and "Trim"
    apvts.createAndAddParameter("InputGain", "Input Gain", "Input Gain", juce::NormalisableRange<float>(-48.0f, 48.0f), 0.0f, nullptr, nullptr);
    apvts.createAndAddParameter("HiPassGain", "High-Pass Gain", "High-Pass Gain", juce::NormalisableRange<float>(-48.0f, 48.0f), 0.0f, nullptr, nullptr);
    apvts.createAndAddParameter("HiShelfGain", "High-Shelf Gain", "High-Shelf Gain", juce::NormalisableRange<float>(-48.0f, 48.0f), 0.0f, nullptr, nullptr);
    apvts.createAndAddParameter("Trim", "Trim", "Trim", juce::NormalisableRange<float>(-48.0f, 48.0f), 0.0f, nullptr, nullptr);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SoHRUtilityAudioProcessor();
}
