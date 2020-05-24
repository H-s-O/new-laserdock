"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.sendSamples = exports.setDacRate = exports.clearRingBuffer = exports.disableOutput = exports.enableOutput = exports.init = void 0;
const bindings_1 = __importDefault(require("bindings"));
const LaserdockLib = bindings_1.default('laserdocknode');
function init() {
    return LaserdockLib.nodeInit();
}
exports.init = init;
function enableOutput() {
    return LaserdockLib.nodeEnableOutput();
}
exports.enableOutput = enableOutput;
function disableOutput() {
    return LaserdockLib.nodeDisableOutput();
}
exports.disableOutput = disableOutput;
function clearRingBuffer() {
    return LaserdockLib.nodeClearRingbuffer();
}
exports.clearRingBuffer = clearRingBuffer;
function setDacRate(rate) {
    return LaserdockLib.nodeSetDacRate(rate);
}
exports.setDacRate = setDacRate;
function sendSamples(points, numOfPoints) {
    return LaserdockLib.nodeSendSamples(points, numOfPoints);
}
exports.sendSamples = sendSamples;
