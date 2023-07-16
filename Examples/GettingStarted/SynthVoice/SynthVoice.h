#include <daisy_pod.h>
#include <daisysp.h>


using namespace daisy;
using namespace daisysp;

typedef struct SynthVoiceDualOsc
{
	Oscillator* oscillator1;
	Oscillator* oscillator2;
	Adsr* envelope;
	bool envelopeTrigGate = false;
} SynthVoiceDualOsc_t;



typedef struct SynthVoiceSingleOsc
{
	Oscillator* oscillator;
	Adsr* envelope;
	bool envelopeTrigGate = false;
} SynthVoiceSingleOsc_t;