#include "SC_PlugIn.hpp"

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;

// declare struct to hold unit generator state
struct MySaw : public SCUnit{

// Constructor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.
public:
    MySaw() {
        // 1. set the calculation function.
        if (isAudioRateIn(0)) {
            // if the frequency argument is audio rate
            set_calc_function<MySaw,&MySaw::next_a>();
        } else {    
        // if thene frequency argument is control rate (or a scalar).
            set_calc_function<MySaw,&MySaw::next_k>();
        }   

        // 2. initialize the unit generator state variables.
        // initialize a constant for multiplying the frequency
        mFreqMul = 2.0 * sampleDur();
        // get initial phase of oscillator
        mPhase = in0(1);

        // 3. calculate one sample of output.
        if (isAudioRateIn(0)) {
            next_a(1);
        } else {
            next_k(1);
        }
     
    }

private:
    double mPhase; // phase of the oscillator, from -1 to 1.
    float mFreqMul; // a constant for multiplying frequency

    //////////////////////////////////////////////////////////////////

    // The calculation function executes once per control period
    // which is typically 64 samples.

    // calculation function for an audio rate frequency argument
    void next_a(int inNumSamples)
    {
        // get the pointer to the output buffer
        float *outBuf = out(0);

        // get the pointer to the input buffer
        const float *freq = in(0);

        // get phase and freqmul constant from struct and store it in a
        // local variable.
        // The optimizer will cause them to be loaded it into a register.
        float freqmul = mFreqMul;
        double phase = mPhase;

        // perform a loop for the number of samples in the control period.
        // If this unit is audio rate then inNumSamples will be 64 or whatever
        // the block size is. If this unit is control rate then inNumSamples will
        // be 1.
        for (int i=0; i < inNumSamples; ++i)
        {
            // out must be written last for in place operation
            float z = phase;
            phase += freq[i] * freqmul;

            // these if statements wrap the phase a +1 or -1.
            if (phase >= 1.f) phase -= 2.f;
            else if (phase <= -1.f) phase += 2.f;

            // write the output
            outBuf[i] = z;
        }

        // store the phase back to the struct
        mPhase = phase;
    }

    //////////////////////////////////////////////////////////////////

    // calculation function for a control rate frequency argument
    void next_k(int inNumSamples)
    {
        // get the pointer to the output buffer
        float *outBuf = out(0);

        // freq is control rate, so calculate it once.
        float freq = in0(0) * mFreqMul;

        // get phase from struct and store it in a local variable.
        // The optimizer will cause it to be loaded it into a register.
        double phase = mPhase;

        // since the frequency is not changing then we can simplify the loops
        // by separating the cases of positive or negative frequencies.
        // This will make them run faster because there is less code inside the loop.
        if (freq >= 0.f) {
            // positive frequencies
            for (int i=0; i < inNumSamples; ++i)
            {
                outBuf[i] = phase;
                phase += freq;
                if (phase >= 1.f) phase -= 2.f;
            }
        } else {
            // negative frequencies
            for (int i=0; i < inNumSamples; ++i)
            {
                outBuf[i] = phase;
                phase += freq;
                if (phase <= -1.f) phase += 2.f;
            }
        }

        // store the phase back to the struct
        mPhase = phase;
    }
};

// the entry point is called by the host when the plug-in is loaded
PluginLoad(MySawUGens)
{
    // InterfaceTable *inTable implicitly given as argument to the load function
    ft = inTable; // store pointer to InterfaceTable

    // registerUnit takes the place of the Define*Unit functions. It automatically checks for the presence of a
    // destructor function.
    // starting from version 3.11 it also allows to disable buffer aliasing
    registerUnit<MySaw>(ft, "MySaw", false);
}
