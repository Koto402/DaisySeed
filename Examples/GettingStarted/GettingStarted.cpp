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

UiCurator* UiPtr = UiCurator::GetInstance();
DaisyPod hw;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	/* Handle IO */
	UiPtr->ProcessIo();

	for (size_t i = 0; i < size; i++)
	{
		#ifdef MONO
			//Mono processes the left input and copies it to the left and right output
//			UiPtr->ProcessAudio(in[0][i], out[0][i]);
			out[1][i] = out[0][i];
		#else
			//Stereo processing
			UiPtr->ProcessAudio(in[0][i], out[0][i]);
			UiPtr->ProcessAudio(in[1][i], out[1][i]);
		#endif
	}
}

//Declare audio effects and apply them to a set of pages
Delay<float, 48000>* myDelay = new Delay<float, 48000>;
//Delay<float, 96000>* myLongerDelay = new Delay<float, 96000>;

Page* p1 = new Page(myDelay);

//Page p1(myDelay);
//Page p2(myLongerDelay);

int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(4); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	hw.StartAdc();
//	hw.StartAudio(AudioCallback);

	UiPtr->SetHwRef(&hw);

	UiPtr->AddPage(p1);
//	UiPtr->AddPage(p2);

	
	while(1) 
	{
		/* Run forever */ 
		UiPtr->ProcessIo();
	}
}
