#include <daisy_pod.h>
#include <daisysp.h>


using namespace daisy;
using namespace daisysp;


class MonoSynth
{
	public:
		MonoSynth(int sampleRate, int midiChannel) 
        {
			//Set private attributes
			this->sampleRate_ = sampleRate;
			this->midiChannel_ = midiChannel;
			
			//Init Oscillators
			this->osc1 = new Oscillator();
			this->osc1->Init(sampleRate_);
            this->osc1->SetAmp(0.0);

			this->osc2 = new Oscillator();
            this->osc2->Init(sampleRate_);
			this->osc2->SetAmp(0.0);

			//Init Adsr
			this->envelope.Init(sampleRate_);
            //Set envelope parameters
            envelope.SetTime(ADSR_SEG_ATTACK, 2.0);
            envelope.SetTime(ADSR_SEG_DECAY, .1);
            envelope.SetTime(ADSR_SEG_RELEASE, .01);

            envelope.SetSustainLevel(.25);


        }
        ~MonoSynth() 
        {
            delete this->osc1;
            delete this->osc2;
        }

		float Process()
		{
			return this->envelope.Process(this->trigGate_) * 0.5f * (this->osc1->Process() + this->osc2->Process());
		}

		void HandleNoteOn(NoteOnEvent event)
		{
			float pitch = powf(2,(event.note-69.0f)/12.0f)*440.0f;
			this->amplitude_ = (1/127.0) * event.velocity * maxAmplitude_;

			this->osc1Pitch_ = pitch;
			this->osc2Pitch_ = pitch;

			this->osc1->SetFreq(osc1Pitch_);
			this->osc1->SetAmp(amplitude_);

			this->osc2->SetFreq(osc2Pitch_ + osc2PitchOffset);
			this->osc2->SetAmp(amplitude_);

			this->trigGate_ = true;
			this->noteOnCount++;
		}

		void HandleNoteOff(NoteOffEvent event)
		{
			this->noteOnCount--;
			if(noteOnCount <= 0)
			{
				this->trigGate_ = false;				
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
						this->osc1->SetWaveform(event.value);
						this->osc2->SetWaveform(event.value);
					}
					break;
				case 73:
					//calculate pitch offset in range |-1, 1| * max pitch;
					this->osc2PitchOffset = (normalizedValue - 0.5f) * 2.0f * maxPitchOffset_;
					this->osc2->SetFreq(osc2Pitch_ + osc2PitchOffset);
					break;
				case 74:
					this->envelope.SetAttackTime(normalizedValue * maxAttackS_);
					break;
				case 75:
					this->envelope.SetSustainLevel(normalizedValue * amplitude_);
					break;
				case 76:
					this->envelope.SetDecayTime(normalizedValue * maxDecayS_);							
					break;
				case 77:
					this->envelope.SetReleaseTime(normalizedValue * maxReleaseS_);		
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
		Adsr envelope;
		bool trigGate_ = true;
		float maxAttackS_  = 8.0;
		float maxDecayS_   = 8.0;
		float maxReleaseS_ = 8.0;

		int noteOnCount = 0;

		Oscillator* osc1;
		Oscillator* osc2;	
		float osc1Pitch_= 440.0;
		float osc2Pitch_ = 440.0;
		float osc2PitchOffset = 0.0;
		float maxPitchOffset_ = 10.0;
		float amplitude_ = 0.15;
		float maxAmplitude_ = 0.15;
	
		int sampleRate_ = 48000;
		int	midiChannel_ = 0;
};