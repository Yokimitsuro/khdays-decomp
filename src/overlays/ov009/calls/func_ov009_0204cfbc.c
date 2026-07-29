typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov009InputContext {
    u8 pad_0000[0x959c];
    void *pageA;
    void *pageB;
    u8 pad_95a4[0x95fc - 0x95a4];
    int inputEnabled;
    int pageAEnabled;
    int pageBEnabled;
    u8 pad_9608[0x9610 - 0x9608];
    u16 buttonState;
    u8 pad_9612[0x963e - 0x9612];
    u16 inputSource;
} Ov009InputContext;

extern Ov009InputContext *volatile data_ov009_020563e4[];
extern u16 data_0204c190;

#define OV009_CONTEXT (data_ov009_020563e4[1])

extern u16 func_020362fc(const u16 *source);
extern int func_ov009_0204e860(void *pageA, void *pageB);
extern int func_ov009_0204e8d8(void *pageA, void *pageB);
extern int func_ov009_0204e950(void *pageA, void *pageB);
extern int func_ov009_0204e9c8(void *pageA, void *pageB);
extern int func_ov009_0204ea40(void *pageA, void *pageB);
extern int func_ov009_0204eab8(void *pageA, void *pageB);
extern int func_ov009_0204eb30(void *pageA, void *pageB);
extern int func_ov009_0204eba8(void *pageA, void *pageB);
extern int func_ov009_0204ec20(void *pageA, void *pageB);
extern int func_ov009_0204ec98(void *pageA, void *pageB);
extern int func_ov009_0204ed10(void *pageA, void *pageB);
extern int func_ov009_0204ed88(void *pageA, void *pageB);

void func_ov009_0204cfbc(void)
{
    Ov009InputContext *context = OV009_CONTEXT;
    void *pageA = context->pageAEnabled ? context->pageA : 0;
    void *pageB = context->pageBEnabled ? context->pageB : 0;

    if (context->inputEnabled == 0) {
        return;
    }

    if ((func_020362fc(&context->inputSource) & 0x40) != 0 &&
        func_ov009_0204e860(pageA, pageB) != 0) {
        return;
    }
    if ((func_020362fc(&OV009_CONTEXT->inputSource) & 0x80) != 0 &&
        func_ov009_0204e8d8(pageA, pageB) != 0) {
        return;
    }
    if ((func_020362fc(&OV009_CONTEXT->inputSource) & 0x20) != 0 &&
        func_ov009_0204e950(pageA, pageB) != 0) {
        return;
    }
    if ((func_020362fc(&OV009_CONTEXT->inputSource) & 0x10) != 0 &&
        func_ov009_0204e9c8(pageA, pageB) != 0) {
        return;
    }

    if ((data_0204c190 & 0x0001) != 0 &&
        func_ov009_0204ea40(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0002) != 0 &&
        func_ov009_0204eab8(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0400) != 0 &&
        func_ov009_0204eb30(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0800) != 0 &&
        func_ov009_0204eba8(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0200) != 0 &&
        func_ov009_0204ec20(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0100) != 0 &&
        func_ov009_0204ec98(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0004) != 0 &&
        func_ov009_0204ed10(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0008) != 0 &&
        func_ov009_0204ed88(pageA, pageB) != 0) {
        return;
    }

    OV009_CONTEXT->buttonState =
        (data_0204c190 & 0x2f0f) |
        (func_020362fc(&OV009_CONTEXT->inputSource) & 0x00f0);
}
