#include <daisy_pod.h>
#include <daisysp.h>

#include "Filters/moogladder.h"
#include "Effect/Delay.h"
#include "Effect/AbstractEffect.h"

#include "Ui/Page/Page.h"
#include "Ui/UiCurator/UiCurator.h"

using namespace daisy;
using namespace daisysp;

#define MONO


MoogLadder filt;
UiCurator* UiPtr = UiCurator::GetInstance();

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	/* Handle IO */
	UiPtr->ProcessIo();

	//delay->SetFeedback(knob_val_2);
	//filt.SetFreq(knob_val_2 * 3000);

	for (size_t i = 0; i < size; i++)
	{
		UiPtr->ProcessAudio(in[0][i], out[0][i]);

		#ifdef MONO
			out[1][i] = out[0][i];
		#else
			UiPtr->ProcessAudio(in[0][i], out[0][i]);
		#endif
		
		//out[0][i] = filt.Process(out[0][i]);
		//out[0][i] = filt.Process(in[0][i]);
		
	}
}
Delay<float, 48000>* myDelay = new Delay<float, 48000>;
Delay<float, 48000>* myDelay2 = new Delay<float, 48000>;
//AbstractEffect* myLongerDelay = new Delay<float, 192000>;

int main(void)
{
	UiPtr->InitHw(AudioCallback);
	UiPtr->AddFx(myDelay);
	UiPtr->AddFx(myDelay2);
	while(1) {/* Run forever */ }
}
