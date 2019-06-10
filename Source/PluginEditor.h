/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MIDIGateAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    MIDIGateAudioProcessorEditor (MIDIGateAudioProcessor&);
    ~MIDIGateAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	void sliderValueChanged(Slider* slider) override; // [3]

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MIDIGateAudioProcessor& processor;

	Slider midiVolume; // [1]

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDIGateAudioProcessorEditor)
};
