typedef unsigned char  u8;

typedef struct Ov000SubSceneContext {
    u8 pad_0000[0x20];
    int baseMode;
    u8 pad_0024[0x4b58];
    u8 textSurface[0x3c];
    u8 variantSource[0x0c];
} Ov000SubSceneContext;

extern Ov000SubSceneContext *volatile data_ov000_0205ac28;
extern void func_02030158(void *surface);
extern int *func_ov000_02056970(void *object, int index);
extern void func_ov000_02053da8(
    void *surface,
    int x,
    int y,
    int depth,
    const int *text
);
extern void func_ov000_02053d18(
    void *surface,
    int x,
    int y,
    int depth,
    const int *text,
    int shadowOffset
);
extern void func_020300f8(void *surface);

void func_ov000_02053928(int mode) {
    Ov000SubSceneContext *context = data_ov000_0205ac28;
    u8 *surfaceBase = (u8 *)context + 0x37c;
    int *text = 0;

    func_02030158(surfaceBase + 0x4800);

    switch (mode) {
    case 2:
    {
        Ov000SubSceneContext *modeContext = data_ov000_0205ac28;

        switch (modeContext->baseMode) {
        case 0:
            text = func_ov000_02056970(
                modeContext->variantSource, 5);
            break;
        case 1:
            text = func_ov000_02056970(
                modeContext->variantSource, 6);
            break;
        case 2:
            text = func_ov000_02056970(
                modeContext->variantSource, 7);
            break;
        }

        func_ov000_02053da8(
            surfaceBase + 0x4800, 0, -1, 2, text);
        text = func_ov000_02056970(
            data_ov000_0205ac28->variantSource, 8);
        func_ov000_02053da8(
            surfaceBase + 0x4800, 0, 0x17, 4, text);
        break;
    }
    case 3:
        text = func_ov000_02056970(
            data_ov000_0205ac28->variantSource, 10);
        func_ov000_02053d18(
            surfaceBase + 0x4800, 0, 4, 2, text, 0);
        text = func_ov000_02056970(
            data_ov000_0205ac28->variantSource, 11);
        func_ov000_02053d18(
            surfaceBase + 0x4800, 0x46, 0x19, 2, text, 2);
        text = func_ov000_02056970(
            data_ov000_0205ac28->variantSource, 12);
        func_ov000_02053d18(
            surfaceBase + 0x4800, 0xaa, 0x19, 2, text, 2);
        break;
    }

    func_020300f8(surfaceBase + 0x4800);
}
