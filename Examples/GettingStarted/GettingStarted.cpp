#include "daisy_pod.h"
#include "daisysp.h"
#include "Effect/Delay.h"
#include "Effect/AbstractEffect.h"
#include "Ui/Page/Page.h"
#include "util/util.h"

using namespace daisy;
using namespace daisysp;

DaisyPod hw;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	hw.ProcessAllControls();
	for (size_t i = 0; i < size; i++)
	{
		out[0][i] = in[0][i];
		out[1][i] = in[1][i];
	}
}

int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(4); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	
	AbstractEffect* delay = new Delay();
	hw.StartAdc();
	hw.StartAudio(AudioCallback);
	while(1) {}
}
