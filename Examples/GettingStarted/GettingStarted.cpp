#include <daisy_pod.h>
#include <daisysp.h>

#include "Filters/moogladder.h"
#include "Effect/Delay.h"
#include "Effect/LowpassFilter.h"
#include "Effect/HighpassFilter.h"
#include "Effect/AbstractEffect.h"

#include "Ui/Page/Page.h"
#include "Ui/UiCurator/UiCurator.h"
#include <math.h>

using namespace daisy;
using namespace daisysp;



#define MONO
//#define PASSTHROUGH

DaisyPod hw;

Oscillator wave;
Oscillator wave2;
LowpassFilter filt(20000, 0.707, 48000);
static bool retrig_gate = false;
Adsr waveEnvelope;


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
			float waves = 0.5 * wave.Process() + 0.5 * wave2.Process(); 
			filt.ProcessMono(waveEnvelope.Process(false) * waves, out[0][i]);
			out[1][i] = out[0][i];
			retrig_gate = false;
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


int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(16); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	hw.StartAdc();
	hw.StartAudio(AudioCallback);
	hw.midi.StartReceive();

	

	wave.Init(48000);
	wave.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
	wave.SetAmp(0);
	wave.SetFreq(440.0);

	wave2.Init(48000);
	float wave2_frequency = 440.0;	
	wave2.SetWaveform(Oscillator::WAVE_POLYBLEP_SAW);
	wave2.SetAmp(0);
	wave2.SetFreq(wave2_frequency);

	waveEnvelope.Init(48000);




	while(1) 
	{
		hw.midi.Listen();
		while(hw.midi.HasEvents())
		{
			MidiEvent event = hw.midi.PopEvent();
			static float wave2PitchOffset = 0.0;
			switch(event.type)
			{
				case NoteOn:
				{
					NoteOnEvent noteOn = event.AsNoteOn();
					wave.Reset();
					wave.SetFreq(powf(2,(noteOn.note-69)/12.0)*440.0);
					wave.SetAmp((1/127.0)*noteOn.velocity);

					wave2.Reset();
					wave2_frequency = (powf(2,(noteOn.note-69)/12.0)*440.0) + wave2PitchOffset; 
					wave2.SetFreq(wave2_frequency);
					wave2.SetAmp((1/127.0)*noteOn.velocity);
					waveEnvelope.Retrigger(true);
					break;
				}
				case NoteOff:
				{
					wave.SetAmp(0);
					wave2.SetAmp(0);
					break;
				}
				case ControlChange:
				{
					ControlChangeEvent ccEvent = event.AsControlChange();
					float normalized_value = ccEvent.value / 127.0;
					switch(ccEvent.control_number)
					{
						case 70:
						{
							filt.SetCutoffFreq(normalized_value * 8000);
							break;
						}
						case 71:
						{
							filt.SetQ(normalized_value * 5.8 + 0.2);
							break;
						}
						case 72:
						{
							if(ccEvent.value < Oscillator::WAVE_LAST)
							{
								wave.SetWaveform(ccEvent.value);
								wave2.SetWaveform(ccEvent.value);
							}
							break;
						}
						case 73:
						{ 
        					float centeredValue = normalized_value - 0.5;
        					float scaledValue = centeredValue * 2;

							wave2PitchOffset = scaledValue * 20;
							wave2.SetFreq(wave2_frequency+wave2PitchOffset);
							break;
						}
						case 74:
						{
							waveEnvelope.SetAttackTime(normalized_value*24.0);
							break;
						}
						case 75:
						{
							waveEnvelope.SetSustainLevel(normalized_value*1.0);
							break;
						}
						case 76:
						{
							waveEnvelope.SetDecayTime(normalized_value*4.0);							
							break;
						}
						case 77:
						{
							waveEnvelope.SetReleaseTime(normalized_value*4.0);		
							break;
						}
						default:
						{
							break;
						}
					}


					break;
				}

				default:
				{
					break;
				}
			}
		}

		/* Run forever */ 
	}
}
