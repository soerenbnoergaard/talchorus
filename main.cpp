class MutePlugin : public Plugin
{
public:
    /**
      Plugin class constructor.
      */
    MutePlugin()
        : Plugin(0, 0, 0) // 0 parameters, 0 programs and 0 states
    {
    }
protected:
    /* ----------------------------------------------------------------------------------------
     * Information */
    /**
      Get the plugin label.
      This label is a short restricted name consisting of only _, a-z, A-Z and 0-9 characters.
      */
    const char* getLabel() const override
    {
        return "Mute";
    }
    /**
      Get the plugin author/maker.
      */
    const char* getMaker() const override
    {
        return "DPF";
    }
    /**
      Get the plugin license name (a single line of text).
      For commercial plugins this should return some short copyright information.
      */
    const char* getLicense() const override
    {
        return "MIT";
    }
    /**
      Get the plugin version, in hexadecimal.
      */
    uint32_t getVersion() const override
    {
        return d_version(1, 0, 0);
    }
    /**
      Get the plugin unique Id.
      This value is used by LADSPA, DSSI and VST plugin formats.
      */
    int64_t getUniqueId() const override
    {
        return d_cconst('M', 'u', 't', 'e');
    }
    /* ----------------------------------------------------------------------------------------
     * This example has no parameters, so skip parameter stuff */
    void  initParameter(uint32_t, Parameter&) override {}
    float getParameterValue(uint32_t) const   override { return 0.0f; }
    void  setParameterValue(uint32_t, float)  override {}
    /* ----------------------------------------------------------------------------------------
     * Audio/MIDI Processing */
    /**
      Run/process function for plugins without MIDI input.
NOTE: Some parameters might be null if there are no audio inputs or outputs.
*/
    void run(const float**, float** outputs, uint32_t frames) override
    {
        // get the left and right audio outputs
        float* const outL = outputs[0];
        float* const outR = outputs[1];
        // mute audio
        std::memset(outL, 0, sizeof(float)*frames);
        std::memset(outR, 0, sizeof(float)*frames);
    }
};
