// This is an alternate way to write the BoringMixer plugin using a newer C++ header (introduced in 2010).

// Using SC_PlugIn.hpp instead of SC_PlugIn.h. SC_PlugIn.hpp includes SC_PlugIn.h. C++ and old-fashioned ugens can
// coexist in the same file.
#include "SC_PlugIn.hpp"

static InterfaceTable *ft;

// Inherits from SCUnit, not Unit.
// Also note that the constructor, destructor, and calc functions are methods of the SCUnit.
struct BoringMixer2 : public SCUnit {
public:
    // Constructor function
    BoringMixer2() {
        // New way of setting calc function.
        set_calc_function<BoringMixer2, &BoringMixer2::next>();
        next(1);
    }

    // If you want a destructor, you would declare "~BoringMixer2() { ... }" here.

private:
    // You can declare state variables here.

    // Calc function
    void next(int inNumSamples) {
        // Note, there is no "unit" variable here, so you can't use a lot of the traditional helper macros. That's why
        // the C++ header offers replacements.

        // in and out are methods of SCUnit that replace IN and OUT.
        // ins are const float*, not float*.
        const float* left = in(0);
        const float* right = in(1);
        float* outbuf = out(0);

        for (int i = 0; i < inNumSamples; i++) {
            outbuf[i] = (left[i] + right[i]) * 0.5;
        }
    }
};

PluginLoad(BoringMixer2UGens) {
    ft = inTable;
    // registerUnit takes the place of the Define*Unit functions. It automatically checks for the presence of a
    // destructor function.
    // However, it does not seem to be possible to disable buffer aliasing with the C++ header.
    registerUnit<BoringMixer2>(ft, "BoringMixer2");
}
