/*
  ==============================================================================

    MidiProcessor.h

    Negative Harmony generation illustration in the Key of C:
        _____________________________________________________________________
        |  | | | |  |  | | | | | |  |  | | | |  |  | | | | | |  |  | | | |  |
        |  | | | |  |  | | | | | |  |  | | | |  |  | | | | | |  |  | | | |  |
        |  | | | |  |  | | | | | |  |  | | | |  |  | | | | | |  |  | | | |  |
        |  |_| |_|  |  |_| |_| |_|  |  |_| |_|  |  |_| |_| |_|  |  |_| |_|  |
        |   |   ||  |   |   |   |   |   |   ||  |   |   |   |   |   |   ||  |
        |   |   ||  |   |   |   |   |   |   ||  |   |   |   |   |   |   ||  |
        |___|___||__|___|___|___|___|___|___||__|___|___|___|___|___|___||__|
                 |              |     |      |        |   | |           |
    Mirror at    |              |     C<---- |------->G   | Bb<---------|-------->A
    Axis between |              Bb<----------|----------->A             |
                 |                           |                          |
    Tonic/      C/G                         C/G                        C/G
    Dominant
  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>

class MidiProcessor final : AudioProcessorValueTreeState::Listener
{
public:
    explicit MidiProcessor(AudioProcessorValueTreeState& vts);
    ~MidiProcessor() override;

    void processMidiMsgsBlock(MidiBuffer& midi_messages);

    int getNegHarmNn(uint8 nn, uint8 key);

private:
    void parameterChanged(const String& parameter_id, float new_value) override;

    MidiBuffer p_midi_buffer_;

    AudioProcessorValueTreeState& apvts_;

    std::atomic<float>* is_on_;
    std::atomic<float>* cur_key_;
    std::atomic<float>* min_nn_;
    std::atomic<float>* max_nn_;

    bool state_changed_;
};
