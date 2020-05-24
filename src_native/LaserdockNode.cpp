#include <vector>

#include <napi.h>

// #include <laserdocklib/LaserdockDeviceManager.h>
// #include <laserdocklib/LaserdockDevice.h>
// #include <laserdocklib/LaserdockSample.h>

#include "LaserdockNode.h"

int nodeForceInit()
{
    LaserdockDeviceManager &lddmanager = LaserdockDeviceManager::getInstance();
    device = lddmanager.get_next_available_device();
    if (!device)
    {
        return -1;
    }
    return 1;
}

Napi::Number nodeInit(const Napi::CallbackInfo &info)
{
    LaserdockDeviceManager &lddmanager = LaserdockDeviceManager::getInstance();

    if (device && device->status() == LaserdockDevice::Status::INITIALIZED)
    {
        return Napi::Number::New(info.Env(), 1);
    }
    return Napi::Number::New(info.Env(), nodeForceInit());
}

Napi::Number nodeEnableOutput(const Napi::CallbackInfo &info)
{
    if (!device)
    {
        return Napi::Number::New(info.Env(), -1);
    }
    if (device->enable_output())
    {
        return Napi::Number::New(info.Env(), 1);
    }
    // The Lasercube can get in a state where `device->status()` still returns initialized, even when the Lasercube is disconnected.
    // the `nodeInit()` code can only be called when the Lasercube is not yet connected,
    // so to workaround we just re-try connecting to the Lasercube if this fails.
    if (nodeForceInit())
    {
        if (device->enable_output())
        {
            return Napi::Number::New(info.Env(), 1);
        }
    }
    return Napi::Number::New(info.Env(), -1);
}

Napi::Number nodeDisableOutput(const Napi::CallbackInfo &info)
{
    if (!device)
    {
        return Napi::Number::New(info.Env(), -1);
    }
    return Napi::Number::New(info.Env(), device->disable_output());
}

Napi::Number nodeSetDacRate(const Napi::CallbackInfo &info)
{
    const uint32_t rate = info[0].As<Napi::Number>().Uint32Value();

    if (!device)
    {
        return Napi::Number::New(info.Env(), -1);
    }
    return Napi::Number::New(info.Env(), device->set_dac_rate(rate));
}

Napi::Number nodeClearRingbuffer(const Napi::CallbackInfo &info)
{
    if (!device)
    {
        return Napi::Number::New(info.Env(), -1);
    }
    return Napi::Number::New(info.Env(), device->clear_ringbuffer());
}

Napi::Number nodeSendSamples(const Napi::CallbackInfo &info)
{
    const Napi::Array samples = info[0].As<Napi::Array>();
    const uint32_t count = info[1].As<Napi::Number>().Uint32Value();

    // Convert plain objects to LaserdockSample
    std::vector<LaserdockSample> convertedSamples(count);
    for (unsigned int i = 0; i < count; i++)
    {
        const Napi::Object sample = samples[i].As<Napi::Object>();
        convertedSamples[i] = {
            (uint16_t)sample["rg"].As<Napi::Number>().Uint32Value(),
            (uint16_t)sample["b"].As<Napi::Number>().Uint32Value(),
            (uint16_t)sample["x"].As<Napi::Number>().Uint32Value(),
            (uint16_t)sample["y"].As<Napi::Number>().Uint32Value(),
        };
    }

    if (!device)
    {
        return Napi::Number::New(info.Env(), -1);
    }
    return Napi::Number::New(info.Env(), device->send_samples(convertedSamples.data(), count));
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports["nodeInit"] = Napi::Function::New(env, nodeInit);
    exports["nodeEnableOutput"] = Napi::Function::New(env, nodeEnableOutput);
    exports["nodeDisableOutput"] = Napi::Function::New(env, nodeDisableOutput);
    exports["nodeSetDacRate"] = Napi::Function::New(env, nodeSetDacRate);
    exports["nodeClearRingbuffer"] = Napi::Function::New(env, nodeClearRingbuffer);
    exports["nodeSendSamples"] = Napi::Function::New(env, nodeSendSamples);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
