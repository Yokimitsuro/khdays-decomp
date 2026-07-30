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

extern Ov009InputContext *volatile data_ov025_020b5744[];
extern u16 data_0204c190;

#define OV009_CONTEXT (data_ov025_020b5744[1])

extern u16 func_020362fc(const u16 *source);
extern int func_ov025_020852b0(void *pageA, void *pageB);
extern int func_ov025_02085328(void *pageA, void *pageB);
extern int func_ov025_020853a0(void *pageA, void *pageB);
extern int func_ov025_02085418(void *pageA, void *pageB);
extern int func_ov025_02085490(void *pageA, void *pageB);
extern int func_ov025_02085508(void *pageA, void *pageB);
extern int func_ov025_02085580(void *pageA, void *pageB);
extern int func_ov025_020855f8(void *pageA, void *pageB);
extern int func_ov025_02085670(void *pageA, void *pageB);
extern int func_ov025_020856e8(void *pageA, void *pageB);
extern int func_ov025_02085760(void *pageA, void *pageB);
extern int func_ov025_020857d8(void *pageA, void *pageB);

void func_ov025_020830d0(void)
{
    Ov009InputContext *context = OV009_CONTEXT;
    void *pageA = context->pageAEnabled ? context->pageA : 0;
    void *pageB = context->pageBEnabled ? context->pageB : 0;

    if (context->inputEnabled == 0) {
        return;
    }

    if ((func_020362fc(&context->inputSource) & 0x40) != 0 &&
        func_ov025_020852b0(pageA, pageB) != 0) {
        return;
    }
    if ((func_020362fc(&OV009_CONTEXT->inputSource) & 0x80) != 0 &&
        func_ov025_02085328(pageA, pageB) != 0) {
        return;
    }
    if ((func_020362fc(&OV009_CONTEXT->inputSource) & 0x20) != 0 &&
        func_ov025_020853a0(pageA, pageB) != 0) {
        return;
    }
    if ((func_020362fc(&OV009_CONTEXT->inputSource) & 0x10) != 0 &&
        func_ov025_02085418(pageA, pageB) != 0) {
        return;
    }

    if ((data_0204c190 & 0x0001) != 0 &&
        func_ov025_02085490(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0002) != 0 &&
        func_ov025_02085508(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0400) != 0 &&
        func_ov025_02085580(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0800) != 0 &&
        func_ov025_020855f8(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0200) != 0 &&
        func_ov025_02085670(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0100) != 0 &&
        func_ov025_020856e8(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0004) != 0 &&
        func_ov025_02085760(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0008) != 0 &&
        func_ov025_020857d8(pageA, pageB) != 0) {
        return;
    }

    OV009_CONTEXT->buttonState =
        (data_0204c190 & 0x2f0f) |
        (func_020362fc(&OV009_CONTEXT->inputSource) & 0x00f0);
}
