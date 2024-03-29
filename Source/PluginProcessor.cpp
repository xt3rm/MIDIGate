/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MIDIGateAudioProcessor::MIDIGateAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	)
#endif
{
}

MIDIGateAudioProcessor::~MIDIGateAudioProcessor()
{
}

//==============================================================================
const String MIDIGateAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool MIDIGateAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool MIDIGateAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool MIDIGateAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double MIDIGateAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int MIDIGateAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int MIDIGateAudioProcessor::getCurrentProgram()
{
	return 0;
}

void MIDIGateAudioProcessor::setCurrentProgram(int index)
{
}

const String MIDIGateAudioProcessor::getProgramName(int index)
{
	return {};
}

void MIDIGateAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void MIDIGateAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
}

void MIDIGateAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MIDIGateAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void MIDIGateAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	//   ScopedNoDenormals noDenormals;
	//   auto totalNumInputChannels  = getTotalNumInputChannels();
	//   auto totalNumOutputChannels = getTotalNumOutputChannels();

	//   // In case we have more outputs than inputs, this code clears any output
	//   // channels that didn't contain input data, (because these aren't
	//   // guaranteed to be empty - they may contain garbage).
	//   // This is here to avoid people getting screaming feedback
	//   // when they first compile a plugin, but obviously you don't need to keep
	//   // this code if your algorithm always overwrites all the output channels.
	//   for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
	//       buffer.clear (i, 0, buffer.getNumSamples());

	//   // This is the place where you'd normally do the guts of your plugin's
	//   // audio processing...
	//   // Make sure to reset the state if your inner loop is processing
	//   // the samples and the outer loop is handling the channels.
	//   // Alternatively, you can process the samples with the channels
	//   // interleaved by keeping the same state.
	//   for (int channel = 0; channel < totalNumInputChannels; ++channel)
	//   {
	//       auto* channelData = buffer.getWritePointer (channel);

	//       // ..do something to the data...
	//   }
	   //buffer.clear();

	   // the audio buffer in a midi effect will have zero channels!
	jassert(buffer.getNumChannels() == 0);

	MidiBuffer processedMidi;
	int time;
	MidiMessage m;
	float pValue = 0.f;
	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
	{
		if (m.isNoteOn())
		{
			uint8 newVel = (uint8)noteOnVel;
			notes.add(m.getNoteNumber());
			m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), 0.f);
			processedMidi.addEvent(m, time);
		}
		else if (m.isNoteOff())
		{
			notes.removeValue(m.getNoteNumber());
		}
		else if (m.isAftertouch())
		{
		}
		else if (m.isPitchWheel())
		{
				
			
			
		}
		else if (m.isControllerOfType(1)) 
		{
			pValue = m.getControllerValue();
			uint8 newVel = (uint8)pValue;
			
			int currentNote = 0;
			while (currentNote < notes.size() - 1) {
				processedMidi.addEvent(MidiMessage::noteOn(m.getChannel(), notes[currentNote], newVel), time);

				currentNote++;
			}
		}

		//
	}
	midiMessages.swapWith(processedMidi);
}

//==============================================================================
bool MIDIGateAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MIDIGateAudioProcessor::createEditor()
{
	return new MIDIGateAudioProcessorEditor(*this);
}

//==============================================================================
void MIDIGateAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void MIDIGateAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new MIDIGateAudioProcessor();
}
