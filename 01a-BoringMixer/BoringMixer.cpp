#include "SC_PlugIn.h"

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;

// declare struct to hold unit generator state
struct BoringMixer : public Unit {
    // in later examples, we will declare state variables here.
};

// older plugins wrap these function declarations in 'extern "C" { ... }'
// no need to do that these days.
static void BoringMixer_next(BoringMixer* unit, int inNumSamples);
static void BoringMixer_Ctor(BoringMixer* unit);

// the constructor function is called when a Synth containing this ugen is played.
// it MUST be named "PluginName_Ctor", and the argument must be "unit."
void BoringMixer_Ctor(BoringMixer* unit) {
    // in later examples, we will initialize state variables here.

    // set a calculation function. for now, we only have one calculation function.
    SETCALC(BoringMixer_next);
    // calculate one sample of output.
    // this allows plugging into other ugens with initial-rate inputs
    BoringMixer_next(unit, 1);
}

// the calculation function can have any name, but this is conventional. the first argument must be "unit."
// this function is called every control period (64 samples is typical)
// Don't change the names of the arguments, or the helper macros won't work.
void BoringMixer_next(BoringMixer* unit, int inNumSamples) {

    // IN and OUT are helper macros that return audio-rate input and output buffers. These are known as "wire buffers."
    // In old ugens you'll see ZIN and ZOUT, which are not recommended.

    // scsynth saves memory by aliasing wire buffers. In this case, "out" and "left" are the same. You should either
    // be mindful of this behavior or turn it off in the PluginLoad section.
    float *left = IN(0); // first input
    float *right = IN(1); // second input
    float *out = OUT(0); // first output

    // Loop through samples and do the computation.
    for (int i = 0; i < inNumSamples; i++) {
        out[i] = (left[i] + right[i]) * 0.5;
    }
}

// the entry point is called by the host when the plug-in is loaded
PluginLoad(BoringMixerUGens) {
    // InterfaceTable *inTable implicitly given as argument to the load function
    ft = inTable; // store pointer to InterfaceTable
    // DefineSimpleUnit is one of four macros defining different kinds of ugens.
    // In later examples involving memory allocation, we'll see DefineDtorUnit.
    // You can disable aliasing by using DefineSimpleCantAliasUnit and DefineDtorCantAliasUnit.
    DefineSimpleUnit(BoringMixer);
}
