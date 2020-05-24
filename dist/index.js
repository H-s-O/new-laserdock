"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    Object.defineProperty(o, k2, { enumerable: true, get: function() { return m[k]; } });
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (Object.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.Laserdock = void 0;
const core_1 = require("@laser-dac/core");
const laserdockLib = __importStar(require("./LaserdockLib"));
const convert_1 = require("./convert");
class Laserdock extends core_1.Device {
    async start() {
        this.stop();
        const status = laserdockLib.init();
        if (status < 1) {
            return false;
        }
        const output = laserdockLib.enableOutput();
        laserdockLib.clearRingBuffer();
        return !!output;
    }
    stop() {
        laserdockLib.disableOutput();
        if (this.interval) {
            clearTimeout(this.interval);
        }
    }
    convertPoint(p) {
        return {
            x: convert_1.relativeToPosition(p.x),
            y: convert_1.relativeToPosition(1 - p.y),
            rg: convert_1.relativeToRedGreen(p.r, p.g),
            b: convert_1.relativeToBlue(p.b)
        };
    }
    stream(scene, pointsRate, fps) {
        laserdockLib.setDacRate(pointsRate);
        const callback = () => {
            const len = scene.points.length;
            this.interval = setTimeout(callback, (len / pointsRate) * 1000);
            const points = scene.points.map(this.convertPoint);
            laserdockLib.sendSamples(points, len);
        };
        this.interval = setTimeout(callback, 0);
    }
}
exports.Laserdock = Laserdock;
