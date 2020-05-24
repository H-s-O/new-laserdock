#pragma once

#include <napi.h>

#include <laserdocklib/LaserdockDeviceManager.h>
#include <laserdocklib/LaserdockDevice.h>
#include <laserdocklib/LaserdockSample.h>

LaserdockDevice *device;

int          nodeForceInit();
Napi::Number nodeInit(const Napi::CallbackInfo &info);
Napi::Number nodeEnableOutput(const Napi::CallbackInfo &info);
Napi::Number nodeDisableOutput(const Napi::CallbackInfo &info);
Napi::Number nodeSetDacRate(const Napi::CallbackInfo &info);
Napi::Number nodeClearRingbuffer(const Napi::CallbackInfo &info);
Napi::Number nodeSendSamples(const Napi::CallbackInfo &info);
