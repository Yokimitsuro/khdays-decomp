extern int MI_CpuFill8();
extern int INITi_CpuClear32_0x01ff86fc();
extern int NNS_FndRemoveListObject();
extern int *NNS_FndGetNextListObject();
extern int func_020236ac();

void func_ov005_020504c0(char *r4) {
    int *r5;
    int *r6;

    MI_CpuFill8(r4 + 0x2c, 0, 0xa0);
    INITi_CpuClear32_0x01ff86fc(0, r4 + 0xcc, 0x18);
    *(int *)(r4 + 0) = 0;
    *(int *)(r4 + 4) = 0;
    *(short *)(r4 + 0x70) = 1;

    r5 = NNS_FndGetNextListObject(r4 + 8, 0);
    if (r5 != 0) {
        do {
            r6 = NNS_FndGetNextListObject(r4 + 8, r5);
            NNS_FndRemoveListObject(r4 + 8, r5);
            if (r5 != 0) {
                func_020236ac(r5);
            }
            r5 = r6;
        } while (r6 != 0);
    }

    r5 = NNS_FndGetNextListObject(r4 + 0x14, 0);
    if (r5 != 0) {
        do {
            r6 = NNS_FndGetNextListObject(r4 + 0x14, r5);
            NNS_FndRemoveListObject(r4 + 0x14, r5);
            if (r5 != 0) {
                func_020236ac(r5);
            }
            r5 = r6;
        } while (r6 != 0);
    }

    r5 = NNS_FndGetNextListObject(r4 + 0x20, 0);
    if (r5 != 0) {
        do {
            r6 = NNS_FndGetNextListObject(r4 + 0x20, r5);
            NNS_FndRemoveListObject(r4 + 0x20, r5);
            if (r5 != 0) {
                func_020236ac(r5);
            }
            r5 = r6;
        } while (r6 != 0);
    }
}
