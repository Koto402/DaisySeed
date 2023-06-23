#include <daisy_pod.h>
#include <daisysp.h>

#include "Effect/LowpassFilter.h"
#include "Effect/HighpassFilter.h"

#include "SynthVoice/SynthVoice.H"


using namespace daisy;
using namespace daisysp;




#define MONO
//#define PASSTHROUGH

DaisyPod hw;
SynthVoice voice1(48000,0);
SynthVoice voice2(48000,1);
SynthVoice voice3(48000,2);
SynthVoice voice4(48000,3);
SynthVoice* synthVoices[] = {&voice1,&voice2,&voice3,&voice4};
LowpassFilter filt(20000, 0.707, 48000);
Oscillator test;

const float frac = 1.0/sqrt(ARRAY_DIM(synthVoices));

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	/* Handle IO */
	hw.ProcessAllControls();
	for (size_t i = 0; i < size; i++)
	{
		#ifdef MONO
		#ifdef PASSTHROUGH /*left signal only */
			out[0][i] = in[0][i];
			out[1][i] = out[0][i];
		#else
			//Mono processes the left input and copies it to the left and right output
			float voicesOutput = 0;
			for (size_t i = 0; i < ARRAY_DIM(synthVoices); i++)
			{
				voicesOutput += synthVoices[i]->Process();
			}
			filt.ProcessMono(SoftClip(voicesOutput*frac), out[1][i]);
			out[0][i] = out[1][i];
		#endif
		#else
		#ifdef PASSTHROUGH
			out[0][i] = in[0][i];
			out[1][i] = in[1][i];
		#else
			myLowpassL.ProcessMono(in[0][i], out[0][i]);
			myLowpassR.ProcessMono(in[1][i], out[1][i]);				
		#endif
		#endif
	}
}

void handleMidi()
{
	MidiEvent midiEvent = hw.midi.PopEvent();
	switch(midiEvent.type)
	{
		case NoteOn:
			for (size_t i = 0; i < ARRAY_DIM(synthVoices); i++)
			{
				if(midiEvent.channel == synthVoices[i]->GetMidiChannel())
				{
					synthVoices[i]->HandleNoteOn(midiEvent.AsNoteOn());
				}
			}
			break;

		case NoteOff:
			for (size_t i = 0; i < ARRAY_DIM(synthVoices); i++)
			{
				if(midiEvent.channel == synthVoices[i]->GetMidiChannel())
				{
					synthVoices[i]->HandleNoteOff(midiEvent.AsNoteOff());
				}
			}
			break;

		case ControlChange:
		{
			ControlChangeEvent ccEvent = midiEvent.AsControlChange();
			for (size_t i = 0; i < ARRAY_DIM(synthVoices); i++)
			{
				if(midiEvent.channel == synthVoices[i]->GetMidiChannel())
				{
					synthVoices[i]->HandleControlChange(ccEvent);
				}
			}
			switch(ccEvent.control_number)
			{
				case 70:
					filt.SetCutoffFreq(1/127.0 * ccEvent.value * 8000.0 );
					break;
				case 71:
					filt.SetQ((1/127.0 * ccEvent.value * 5.8) + 0.2);
					break;
				default:
					break;
			}
			break;
		}
		default:
			break;
	}
}

int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(16); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	hw.StartAdc();
	
	hw.midi.StartReceive();
	hw.StartAudio(AudioCallback);

	while(1) 
	{
		hw.midi.Listen();
		while(hw.midi.HasEvents())
		{
			handleMidi();
		}
	}
}