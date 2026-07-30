/*
 * Obj_InitChannelsAndRun - lazily (re)initialise an object's three attachment
 * channels, then dispatch its per-frame processor.
 *
 * When the object's dirty bit (flags & 0x10) is set, clear the three 8-byte
 * channel slots at +0x3c/+0x44/+0x4c and, for each channel whose source pointer
 * (obj[2]/obj[4]/obj[6]) is non-null, bind it via func_02027978; then clear the
 * dirty bit. Finally run func_01ffb8fc over the object, using the shared work
 * buffer at data_020475d0 when one is already installed, otherwise a local
 * 0x188-byte scratch frame that is published to data_020475d0 for the duration
 * of the call and cleared afterwards. A u16 status flag (data_027e0654) is reset
 * to 0 on the way out.
 */

extern void INITi_CpuClear32_0x01ff86fc(int value, void *dest, int size);
extern void func_02027978(unsigned int *bits, void *node);
extern void func_01ffb8fc(void *buf, unsigned int *ctx);
extern unsigned int *data_020475d0;
extern unsigned short data_027e0654;

void func_020279e0(unsigned int *param_1)
{
    unsigned int scratch[98];

    if ((*param_1 & 0x10) == 0x10) {
        INITi_CpuClear32_0x01ff86fc(0, param_1 + 0xf, 8);
        INITi_CpuClear32_0x01ff86fc(0, param_1 + 0x11, 8);
        INITi_CpuClear32_0x01ff86fc(0, param_1 + 0x13, 8);
        if (param_1[2] != 0)
            func_02027978(param_1 + 0xf, (void *)param_1[2]);
        if (param_1[4] != 0)
            func_02027978(param_1 + 0x11, (void *)param_1[4]);
        if (param_1[6] != 0)
            func_02027978(param_1 + 0x13, (void *)param_1[6]);
        *param_1 &= ~0x10;
    }
    if (data_020475d0 != 0) {
        func_01ffb8fc(data_020475d0, param_1);
    } else {
        data_020475d0 = scratch;
        func_01ffb8fc(scratch, param_1);
        data_020475d0 = 0;
    }
    data_027e0654 = 0;
}
