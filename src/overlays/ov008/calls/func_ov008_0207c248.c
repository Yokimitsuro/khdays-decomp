typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*MissionState)(void);

typedef struct {
    u32 cursorIndex;
    u32 repeatFrames;
} MissionMenuSelectionState;

typedef struct {
    void *resourceBase;
    u32 resourceValue;
    void *resourceData;
} MissionResourceRecord;

typedef struct {
    void *sceneObject;
    u16 inputHeader[13];
    u8 pad_1e[2];
    u32 sessionReady;
    u32 parametersReady;
    u32 singleRowMode;
    u32 menuState;
    u8 menuMetadata[8];
    MissionMenuSelectionState selection;
    u8 rows[0x20];
    MissionResourceRecord resource;
    u8 tail[4];
} MissionMenuContext;

typedef u16 MissionLabel[11];

extern MissionMenuContext *data_ov008_02090fa0;
extern u16 data_0204c190;

extern u32 func_ov008_0207b778(void);
extern int func_ov008_0207b7b4(void);
extern int func_ov008_02081694(void);
extern int func_ov008_0208187c(int selection);
extern void func_ov008_02081d58(int cursorIndex);
extern void func_ov008_02081d70(u8 sessionReady);
extern int func_ov008_020817c4(u32 state, int animate, int completionValue);
extern void func_ov008_0207d6c4(int entryCount);
extern void func_ov008_0207b70c(MissionLabel labels[4]);
extern void func_ov008_0207bb4c(void);
extern void func_ov008_02081da0(void);
extern void func_ov008_02081e08(void);
extern void func_ov008_02081ddc(void *text, int x, int y, u8 style,
                                int layer, int align, int visible);
extern void *func_ov008_02055c84(void *resource, int index);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void FS_UnloadOverlayImage_0x020362ec(void *image);
extern void func_02033b78(u32 soundId, u32 variant);
extern void CARDi_GetRomAccessor_0x0207c498(void);
extern void func_ov008_0207d5d0(void);

MissionState func_ov008_0207c248(void)
{
    int action = 0;
    MissionState nextState = (MissionState)action;
    u8 visibleOptionCount = (u8)func_ov008_0207b778();
    u16 buttonBits;
    MissionLabel optionLabels[4];
    u8 optionIndex;

    FS_UnloadOverlayImage_0x020362ec(data_ov008_02090fa0->inputHeader);
    buttonBits = data_0204c190;
    if ((buttonBits & 1) != 0) {
        action = 1;
    }
    if ((buttonBits & 2) != 0) {
        action = 2;
    }

    if (func_ov008_02081694() != 0) {
        func_ov008_0207d6c4(visibleOptionCount + 1);
        if ((action & 1) != 0) {
            MissionMenuContext *context = data_ov008_02090fa0;
            if (context->selection.cursorIndex == 0) {
                context->sessionReady = 1;
            } else {
                context->sessionReady = 0;
            }
            func_ov008_02081d70(data_ov008_02090fa0->sessionReady);
            func_02033b78(0, 1);
            nextState = CARDi_GetRomAccessor_0x0207c498;
        }
        if ((action & 2) != 0) {
            func_02033b78(0, 3);
            func_ov008_020817c4(8, 1, 0);
            func_ov008_0207bb4c();
            nextState = func_ov008_0207d5d0;
        }
    }

    func_ov008_02081da0();
    func_ov008_02081ddc(
        func_ov008_02055c84(&data_ov008_02090fa0->resource, 0x3c),
        0xfa, 2, 1, 1, 1, 1);
    func_ov008_02081ddc(
        func_ov008_02055c84(&data_ov008_02090fa0->resource, 0x3d),
        0x80, 0x60, 1, 1, 3, 1);

    MI_CpuFill8(optionLabels, 0, sizeof(optionLabels));
    func_ov008_0207b70c(optionLabels);
    for (optionIndex = 0; optionIndex < 4; optionIndex++) {
        func_ov008_02081ddc(
            optionLabels[optionIndex], 0x57, optionIndex * 0x18 + 0x23,
            optionIndex < visibleOptionCount ? 1 : 3, 1, 0, 0);
    }

    func_ov008_02081d58((u8)data_ov008_02090fa0->selection.cursorIndex);
    func_ov008_0208187c(func_ov008_0207b7b4());
    func_ov008_02081ddc(
        func_ov008_02055c84(&data_ov008_02090fa0->resource, 0x3e),
        0x80, 0x98, 1, 1, 3, 0);
    func_ov008_02081ddc(
        func_ov008_02055c84(&data_ov008_02090fa0->resource, 0x3f),
        10, 0xb4, 1, 1, 0, 0);
    func_ov008_02081e08();
    return nextState;
}