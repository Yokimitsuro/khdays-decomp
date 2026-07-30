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

extern Ov009InputContext *volatile data_ov008_02090f04[];
extern u16 data_0204c190;

#define OV009_CONTEXT (data_ov008_02090f04[1])

extern u16 func_020362fc(const u16 *source);
extern int func_ov008_02051500(void *pageA, void *pageB);
extern int func_ov008_02051578(void *pageA, void *pageB);
extern int func_ov008_020515f0(void *pageA, void *pageB);
extern int func_ov008_02051668(void *pageA, void *pageB);
extern int func_ov008_020516e0(void *pageA, void *pageB);
extern int func_ov008_02051758(void *pageA, void *pageB);
extern int func_ov008_020517d0(void *pageA, void *pageB);
extern int func_ov008_02051848(void *pageA, void *pageB);
extern int func_ov008_020518c0(void *pageA, void *pageB);
extern int func_ov008_02051938(void *pageA, void *pageB);
extern int func_ov008_020519b0(void *pageA, void *pageB);
extern int func_ov008_02051a28(void *pageA, void *pageB);

void func_ov008_0204f2a8(void)
{
    Ov009InputContext *context = OV009_CONTEXT;
    void *pageA = context->pageAEnabled ? context->pageA : 0;
    void *pageB = context->pageBEnabled ? context->pageB : 0;

    if (context->inputEnabled == 0) {
        return;
    }

    if ((func_020362fc(&context->inputSource) & 0x40) != 0 &&
        func_ov008_02051500(pageA, pageB) != 0) {
        return;
    }
    if ((func_020362fc(&OV009_CONTEXT->inputSource) & 0x80) != 0 &&
        func_ov008_02051578(pageA, pageB) != 0) {
        return;
    }
    if ((func_020362fc(&OV009_CONTEXT->inputSource) & 0x20) != 0 &&
        func_ov008_020515f0(pageA, pageB) != 0) {
        return;
    }
    if ((func_020362fc(&OV009_CONTEXT->inputSource) & 0x10) != 0 &&
        func_ov008_02051668(pageA, pageB) != 0) {
        return;
    }

    if ((data_0204c190 & 0x0001) != 0 &&
        func_ov008_020516e0(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0002) != 0 &&
        func_ov008_02051758(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0400) != 0 &&
        func_ov008_020517d0(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0800) != 0 &&
        func_ov008_02051848(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0200) != 0 &&
        func_ov008_020518c0(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0100) != 0 &&
        func_ov008_02051938(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0004) != 0 &&
        func_ov008_020519b0(pageA, pageB) != 0) {
        return;
    }
    if ((data_0204c190 & 0x0008) != 0 &&
        func_ov008_02051a28(pageA, pageB) != 0) {
        return;
    }

    OV009_CONTEXT->buttonState =
        (data_0204c190 & 0x2f0f) |
        (func_020362fc(&OV009_CONTEXT->inputSource) & 0x00f0);
}
