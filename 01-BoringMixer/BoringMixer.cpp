#include "SC_PlugIn.h"

static InterfaceTable *ft;

struct BoringMixer : public Unit {
};

static void BoringMixer_next(BoringMixer *unit, int inNumSamples);
static void BoringMixer_Ctor(BoringMixer* unit);

void BoringMixer_Ctor(BoringMixer* unit) {
    SETCALC(BoringMixer_next);
}

void BoringMixer_next(BoringMixer* unit, int inNumSamples) {

    float *left = IN(0);
    float *right = IN(1);
    float *out = OUT(0);

    for (int i = 0; i < inNumSamples; i++) {
        out[i] = (left[i] + right[i]) * 0.5;
    }
}

PluginLoad(BoringMixerUGens) {
    ft = inTable;
    DefineSimpleUnit(BoringMixer);
}