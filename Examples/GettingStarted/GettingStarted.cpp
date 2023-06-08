#include <daisy_pod.h>
#include <daisysp.h>

#include "Filters/moogladder.h"
#include "Effect/Delay.h"
#include "Effect/AbstractEffect.h"

#include "Ui/Page/Page.h"
#include "Ui/UiCurator/UiCurator.h"

using namespace daisy;
using namespace daisysp;


Delay<float, 48000>* delay = new Delay<float, 48000>;
MoogLadder filt;

DaisyPod hw;
UiCurator* UiPtr = UiCurator::GetInstance();

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	static float knob_val_1 = 0;
	static float knob_val_2 = 0;
	/* Handle IO */
	UiPtr->ProcessIo();
	
	knob_val_1 = hw.GetKnobValue(hw.KNOB_1);	
 	knob_val_2 = hw.GetKnobValue(hw.KNOB_2);

	delay->SetDryLevel(knob_val_1);
	delay->SetDelay(knob_val_2*48000);
	//delay->SetFeedback(knob_val_2);
	//filt.SetFreq(knob_val_2 * 3000);

	if(hw.button1.RisingEdge())
	{
		delay->ClearDDL();
	}


	for (size_t i = 0; i < size; i++)
	{
		delay->ProcessMono(in[0][i], out[0][i]);
		//out[0][i] = filt.Process(out[0][i]);
		
		//out[0][i] = filt.Process(in[0][i]);
		
		out[1][i] = out[0][i];
	}
}

int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(4); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	UiPtr->UpdateLeds();
	hw.StartAdc();
	hw.StartAudio(AudioCallback);
	// git test //
	while(1) {/* Run forever */ }
}
