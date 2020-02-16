/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2015 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "DistrhoPlugin.hpp"
#include "Effects/Chorus/ChorusEngine.h"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------------------------------------

/**
  Plugin that demonstrates the latency API in DPF.
 */
class TalChorusPlugin : public Plugin
{
public:
    TalChorusPlugin() : Plugin(0, 0, 0) // 1st argument: Number of parameters
    {
        chorusEngine = new ChorusEngine(getSampleRate());
        sampleRateChanged(getSampleRate());
        chorusEngine->setEnablesChorus(true, false);
    }

    ~TalChorusPlugin() override
    {
        delete chorusEngine;
    }

protected:
   /* --------------------------------------------------------------------------------------------------------
    * Information */

   /**
      Get the plugin label.
      This label is a short restricted name consisting of only _, a-z, A-Z and 0-9 characters.
    */
    const char* getLabel() const override
    {
        return "talchorus";
    }

   /**
      Get an extensive comment/description about the plugin.
    */
    const char* getDescription() const override
    {
        return "Juno-like chorus extracted from TAL-NoiseMaker";
    }

   /**
      Get the plugin author/maker.
    */
    const char* getMaker() const override
    {
        return "soerenbnoergaard";
    }

   /**
      Get the plugin homepage.
    */
    const char* getHomePage() const override
    {
        return "https://github.com/soerenbnoergaard/talchorus";
    }

   /**
      Get the plugin license name (a single line of text).
      For commercial plugins this should return some short copyright information.
    */
    const char* getLicense() const override
    {
        return "GPL";
    }

   /**
      Get the plugin version, in hexadecimal.
    */
    uint32_t getVersion() const override
    {
        return d_version(0, 0, 1);
    }

   /**
      Get the plugin unique Id.
      This value is used by LADSPA, DSSI and VST plugin formats.
    */
    int64_t getUniqueId() const override
    {
        /* soerenbnoergaard: I just made something up */
        return d_cconst('d', 'L', 'b', 'y');
    }

   /* --------------------------------------------------------------------------------------------------------
    * Init */

   /**
      Initialize the parameter @a index.
      This function will be called once, shortly after the plugin is created.
    */
    void initParameter(uint32_t index, Parameter& parameter) override
    {
        if (index != 0)
            return;

        /* parameter.hints  = kParameterIsAutomable; */
        /* parameter.name   = "Latency"; */
        /* parameter.symbol = "latency"; */
        /* parameter.unit   = "s"; */
        /* parameter.ranges.def = 1.0f; */
        /* parameter.ranges.min = 0.0f; */
        /* parameter.ranges.max = 5.0f; */
    }

   /* --------------------------------------------------------------------------------------------------------
    * Internal data */

   /**
      Get the current value of a parameter.
      The host may call this function from any context, including realtime processing.
    */
    float getParameterValue(uint32_t index) const override
    {
        if (index != 0)
            return 0.0f;

        return 0;
    }

   /**
      Change a parameter value.
      The host may call this function from any context, including realtime processing.
      When a parameter is marked as automable, you must ensure no non-realtime operations are performed.
      @note This function will only be called for parameter inputs.
    */
    void setParameterValue(uint32_t index, float value) override
    {
        if (index != 0)
            return;
    }

   /* --------------------------------------------------------------------------------------------------------
    * Audio/MIDI Processing */

   /**
      Run/process function for plugins without MIDI input.
      @note Some parameters might be null if there are no audio inputs or outputs.
    */
    void run(const float** inputs, float** outputs, uint32_t frames) override
    {
        const float* const inL  = inputs[0];
        const float* const inR  = inputs[1];
        float* const outL = outputs[0];
        float* const outR = outputs[1];

        float sampleL;
        float sampleR;
        for (uint32_t n = 0; n < frames; n++) {
            sampleL = inL[n];
            sampleR = inR[n];
            chorusEngine->process(&sampleL, &sampleR);
            outL[n] = sampleL;
            outR[n] = sampleR;
        }
    }

   /* --------------------------------------------------------------------------------------------------------
    * Callbacks (optional) */

   /**
      Optional callback to inform the plugin about a sample rate change.
      This function will only be called when the plugin is deactivated.
    */
    void sampleRateChanged(double newSampleRate) override
    {
        chorusEngine->setSampleRate(newSampleRate);
    }

    // -------------------------------------------------------------------------------------------------------

private:

    ChorusEngine *chorusEngine;

   /**
      Set our plugin class as non-copyable and add a leak detector just in case.
    */
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TalChorusPlugin)
};

/* ------------------------------------------------------------------------------------------------------------
 * Plugin entry point, called by DPF to create a new plugin instance. */

Plugin* createPlugin()
{
    return new TalChorusPlugin();
}

// -----------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
