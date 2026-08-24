typedef struct Ov004Context {
    char pad_0000[0x5544];
    int objectHandles[3];
    char pad_5550[0x2c];
    int objectScale;
    int scaleStep;
} Ov004Context;

extern Ov004Context *data_ov004_02051384;
extern void func_020326f0(void *manager, int objectHandle, int value, int scale);

void func_ov004_020504c4(void) {
    data_ov004_02051384->objectScale += data_ov004_02051384->scaleStep;
    if (data_ov004_02051384->scaleStep > 0x14) {
        data_ov004_02051384->scaleStep -= 0x10;
    } else {
        data_ov004_02051384->scaleStep = 0x14;
    }
    if (data_ov004_02051384->objectScale > 0x1000) {
        data_ov004_02051384->objectScale = 0x1000;
    }
    func_020326f0((char *)data_ov004_02051384 + 0xb0c,
                  data_ov004_02051384->objectHandles[1],
                  data_ov004_02051384->objectScale, 0x1000);
}
