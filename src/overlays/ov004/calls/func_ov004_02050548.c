extern void G2x_SetBlendBrightnessExt_(unsigned int reg, int firstMask,
                                       int secondMask, int eva, int evb,
                                       int brightness);

void func_ov004_02050548(int brightness, int plane) {
    if (plane == 0) {
        return;
    }

    if (brightness < -16) {
        brightness = -16;
    } else if (brightness > 16) {
        brightness = 16;
    }

    switch (plane) {
    case 1:
        G2x_SetBlendBrightnessExt_(0x04000050, 2, 0x3f, 0, -16, brightness);
        return;
    case 2:
        G2x_SetBlendBrightnessExt_(0x04000050, 4, 0x3f, 0, -16, brightness);
        return;
    case 3:
        G2x_SetBlendBrightnessExt_(0x04000050, 8, 0x3f, 0, -16, brightness);
        return;
    default:
        G2x_SetBlendBrightnessExt_(0x04000050, 0x3f, 0x3f, 0, -16, brightness);
        return;
    }
}
