extern int func_02001030(void);
extern int func_ov105_020bf9c0(void);
extern void func_ov105_020bf928(void);

struct CardXferOwner {
    char _pad[0x49c];
    int nField49c;
};
extern struct CardXferOwner *data_ov006_020565e4;

void func_ov006_0204dbb4(void) {
    switch (func_02001030()) {
    case 0:
        return;
    case 1:
        if (func_ov105_020bf9c0() != 0) {
            data_ov006_020565e4->nField49c = 0;
        }
        return;
    case 3:
        return;
    default:
        func_ov105_020bf928();
    }
}
