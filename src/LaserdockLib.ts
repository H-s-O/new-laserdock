import bindings from 'bindings';

const LaserdockLib = bindings('laserdocknode');

export function init(): number {
    return LaserdockLib.nodeInit();
}

export function enableOutput(): number {
    return LaserdockLib.nodeEnableOutput();
}

export function disableOutput(): number {
    return LaserdockLib.nodeDisableOutput();
}

export function clearRingBuffer(): number {
    return LaserdockLib.nodeClearRingbuffer();
}

export function setDacRate(rate: number): number {
    return LaserdockLib.nodeSetDacRate(rate);
}

export function sendSamples(points: any[], numOfPoints: number): number {
    return LaserdockLib.nodeSendSamples(points, numOfPoints);
}

export interface IPoint {
    x: number;
    y: number;
    r: number;
    g: number;
    b: number;
    i?: number;
}