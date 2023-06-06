#include <daisy_pod.h>
#include "daisysp.h"
#include "Effect/Delay.h"
#include "Effect/AbstractEffect.h"
#include "Ui/Page/Page.h"
#include "util/util.h"
#include "Filters/moogladder.h"

using namespace daisy;
using namespace daisysp;

DaisyPod hw;

Color::PresetColor PresetColors[] = 
{
	Color::PresetColor::RED,
	Color::PresetColor::BLUE,
	Color::PresetColor::GREEN,
};

static Color* ColorObjects[ARRAY_DIM(PresetColors)];

static void InitColors()
{
	for (int i = 0; i < ARRAY_DIM(ColorObjects); i++)
	{
		ColorObjects[i] = new Color();
		ColorObjects[i]->Init(PresetColors[i]);
	}
}

Delay<float, 48000>* delay = new Delay<float, 48000>;
MoogLadder filt;
Page *DelayPage;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	static float knob_val_1 = 0;
	static float knob_val_2 = 0;

	/* Handle IO */
	DelayPage->ProcessIo();
	
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
	InitColors();
	DelayPage = new Page(&hw, ColorObjects[2], delay);
	/* Start Logging on serial port */
	//hw.seed.StartLog(true);
	//hw.seed.PrintLine("Log Started");

	/* Init dsp plugins */
	filt.Init(48000);
	delay->SetDelay(3000);
	delay->SetFeedback(1);
	/* Init user interface */


	//Color green = *ColorObjects[2];
	DelayPage->UpdateLeds();
	//hw.led1.SetColor(green);
	//hw.UpdateLeds();

	/* Start handling audio */
	hw.StartAdc();
	hw.StartAudio(AudioCallback);
	
	while(1) {/* Run forever */ }
}
