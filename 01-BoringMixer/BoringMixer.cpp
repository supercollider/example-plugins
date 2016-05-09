#include "SC_PlugIn.h"

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;

// declare struct to hold unit generator state
struct BoringMixer : public Unit {
    // this is blank because this particular ugen is stateless.
    // in more advanced examples we'll have stuff here.
};

// in some older plugins these function declarations are wrapped in 'extern "C" { ... }'
// no need to do that these days.
static void BoringMixer_next(BoringMixer* unit, int inNumSamples);
static void BoringMixer_Ctor(BoringMixer* unit);

// the constructor function is called when a Synth containing this ugen is played.
// it MUST be named PluginName_Ctor.
// in later examples, this function will initialize state variables.
void BoringMixer_Ctor(BoringMixer* unit) {
    // set a calculation function.
    // in later examples, we will have multiple calculation functions depending on input and output rates.
    SETCALC(BoringMixer_next);
    // calculate one sample of output.
    // this allows plugging into other ugens with initial-rate inputs 
    BoringMixer_next(unit, 1);
}

// the calculation function can have any name, but this is conventional.
// this function is called every control period (64 samples is typical)
void BoringMixer_next(BoringMixer* unit, int inNumSamples) {

    // IN and OUT are helper macros that return audio-rate input and output buffers.
    // in SC source code, these buffers are often called "wire bufs" since they are how ugens communicate.
    float *left = IN(0); // first input
    float *right = IN(1); // second input
    float *out = OUT(0); // first output

    // loop through samples
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
    DefineSimpleUnit(BoringMixer);
}
