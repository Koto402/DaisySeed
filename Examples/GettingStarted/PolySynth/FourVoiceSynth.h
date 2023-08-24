#include <daisy_pod.h>
#include <daisysp.h>
#include "../SynthVoice/SynthVoice.h"

using namespace daisy;
using namespace daisysp;

#define NUM_VOICES (4)
constexpr float voicesAverageFraction = 1.0f / NUM_VOICES;

class FourVoiceSynth
{
	public:
		FourVoiceSynth(int sampleRate, int midiChannel) 
        {
			//Set private attributes
			this->sampleRate_ = sampleRate;
			this->midiChannel_ = midiChannel;

			//Init Oscillators
			for (int i = 0; i < NUM_VOICES; i++)
            {
                this->voices[i].oscillator = new Oscillator();
                this->voices[i].oscillator->Init(this->sampleRate_);
                this->voices[i].oscillator->SetAmp(0.0);

                this->voices[i].envelope = new Adsr();
                this->voices[i].envelope->Init(sampleRate_);
                this->voices[i].envelope->SetTime(ADSR_SEG_ATTACK, 2.0);
                this->voices[i].envelope->SetTime(ADSR_SEG_DECAY, .1);
                this->voices[i].envelope->SetTime(ADSR_SEG_RELEASE, .01);
                this->voices[i].envelope->SetSustainLevel(.25);
            }
        }
		
        ~FourVoiceSynth() 
        {
            for (int i = 0; i < NUM_VOICES; i++)
            {
                delete this->voices[i].oscillator;
                delete this->voices[i].envelope;
            }
        }

		float Process()
		{
            float sum = 0.0f;
            for (int i = 0; i < NUM_VOICES; i++)
            {
				float amplitude = this->voices[i].envelope->Process(this->voices[i].envelopeTrigGate);
				this->voices[i].oscillator->SetAmp(amplitude);
                sum += this->voices[i].oscillator->Process();
            }
			return SoftClip(voicesAverageFraction * sum);
		}

		void HandleNoteOn(NoteOnEvent event)
		{
			float pitch = powf(2,(event.note-69.0f)/12.0f)*440.0f;
			this->amplitude_ = (1/127.0) * event.velocity * maxAmplitude_;

			this->voices[currentVoice].oscillator->SetFreq(pitch);
			this->voices[currentVoice].envelope->SetSustainLevel(this->amplitude_);
			this->voices[currentVoice].envelopeTrigGate = true;
			this->noteOnCount++;
			
			this->currentVoice++;
			if (this->currentVoice > (NUM_VOICES - 1))
			{
				//loop back to first voice
				this->currentVoice = 0;
			}
		}

		void HandleNoteOff(NoteOffEvent event)
		{
			this->voices[this->currentRelease].envelopeTrigGate = false;
			this->currentRelease++;
			
			if(this->currentRelease >= NUM_VOICES)
			{
				this->currentRelease = 0;
			}

			this->noteOnCount--;
			if(this->noteOnCount <= 0)
			{
				this->noteOnCount = 0;
			}
        }

		void HandleControlChange(ControlChangeEvent event)
		{
			float normalizedValue = event.value / 127.0f;
			switch(event.control_number)
			{
				case 72:
					if(event.value < Oscillator::WAVE_LAST)
					{
						for(size_t i = 0; i < NUM_VOICES; i++)
						{
							this->voices[i].oscillator->SetWaveform(event.value);
						}
					}
					break;

				case 74:
					for(size_t i = 0; i < NUM_VOICES; i++)
					{
						this->voices[i].envelope->SetAttackTime(normalizedValue * maxAttackS_);
					}
					break;
				case 75:
					for(size_t i = 0; i < NUM_VOICES; i++)
					{
						this->voices[i].envelope->SetSustainLevel(normalizedValue * amplitude_);
					}
					break;
				case 76:
					for(size_t i = 0; i < NUM_VOICES; i++)
					{
						this->voices[i].envelope->SetDecayTime(normalizedValue * maxDecayS_);	
					}
					break;
				case 77:
					for(size_t i = 0; i < NUM_VOICES; i++)
					{
						this->voices[i].envelope->SetReleaseTime(normalizedValue * maxReleaseS_);
					}
					break;
				default:
					break;
			}
		}

		int GetMidiChannel() 
		{
			return this->midiChannel_;
		}
		
		void SetMidiChannel(int midiChannel) 
		{
			this->midiChannel_ =  midiChannel;
		}

	private:
		float maxAttackS_  = 8.0;
		float maxDecayS_   = 8.0;
		float maxReleaseS_ = 8.0;

		int noteOnCount = 0;

		size_t currentVoice = 0;
		size_t currentRelease = 0;
		SynthVoiceSingleOsc_t voices[4];
        
        float amplitude_ = 0.15;
		float maxAmplitude_ = 0.15;
	
		int sampleRate_ = 48000;
		int	midiChannel_ = 0;
};