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

extern MissionMenuContext *data_ov006_02056660;
extern u16 data_0204c190;

extern u32 func_ov006_0204fa1c(void);
extern int func_ov006_0204fa58(void);
extern int func_ov006_02055924(void);
extern int func_ov006_02055b0c(int selection);
extern void func_ov006_02055fe8(int cursorIndex);
extern void func_ov006_02056000(u8 sessionReady);
extern int func_ov006_02055a54(u32 state, int animate, int completionValue);
extern void func_ov006_02051970(int entryCount);
extern void func_ov006_0204f9b0(MissionLabel labels[4]);
extern void func_ov006_0204fd68(void);
extern void func_ov006_02056030(void);
extern void func_ov006_02056098(void);
extern void func_ov006_0205606c(void *text, int x, int y, u8 style,
                                int layer, int align, int visible);
extern void *func_ov006_0204d58c(void *resource, int index);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void FS_UnloadOverlayImage_0x020362ec(void *image);
extern void func_02033b78(u32 soundId, u32 variant);
extern void CARDi_GetRomAccessor_0x020505b0(void);
extern void func_ov006_0205187c(void);

MissionState func_ov006_02050360(void)
{
    int action = 0;
    MissionState nextState = (MissionState)action;
    u8 visibleOptionCount = (u8)func_ov006_0204fa1c();
    u16 buttonBits;
    MissionLabel optionLabels[4];
    u8 optionIndex;

    FS_UnloadOverlayImage_0x020362ec(data_ov006_02056660->inputHeader);
    buttonBits = data_0204c190;
    if ((buttonBits & 1) != 0) {
        action = 1;
    }
    if ((buttonBits & 2) != 0) {
        action = 2;
    }

    if (func_ov006_02055924() != 0) {
        func_ov006_02051970(visibleOptionCount + 1);
        if ((action & 1) != 0) {
            MissionMenuContext *context = data_ov006_02056660;
            if (context->selection.cursorIndex == 0) {
                context->sessionReady = 1;
            } else {
                context->sessionReady = 0;
            }
            func_ov006_02056000(data_ov006_02056660->sessionReady);
            func_02033b78(0, 1);
            nextState = CARDi_GetRomAccessor_0x020505b0;
        }
        if ((action & 2) != 0) {
            func_02033b78(0, 3);
            func_ov006_02055a54(8, 1, 0);
            func_ov006_0204fd68();
            nextState = func_ov006_0205187c;
        }
    }

    func_ov006_02056030();
    func_ov006_0205606c(
        func_ov006_0204d58c(&data_ov006_02056660->resource, 0x3c),
        0xfa, 2, 1, 1, 1, 1);
    func_ov006_0205606c(
        func_ov006_0204d58c(&data_ov006_02056660->resource, 0x3d),
        0x80, 0x60, 1, 1, 3, 1);

    MI_CpuFill8(optionLabels, 0, sizeof(optionLabels));
    func_ov006_0204f9b0(optionLabels);
    for (optionIndex = 0; optionIndex < 4; optionIndex++) {
        func_ov006_0205606c(
            optionLabels[optionIndex], 0x57, optionIndex * 0x18 + 0x23,
            optionIndex < visibleOptionCount ? 1 : 3, 1, 0, 0);
    }

    func_ov006_02055fe8((u8)data_ov006_02056660->selection.cursorIndex);
    func_ov006_02055b0c(func_ov006_0204fa58());
    func_ov006_0205606c(
        func_ov006_0204d58c(&data_ov006_02056660->resource, 0x3e),
        0x80, 0x98, 1, 1, 3, 0);
    func_ov006_0205606c(
        func_ov006_0204d58c(&data_ov006_02056660->resource, 0x3f),
        10, 0xb4, 1, 1, 0, 0);
    func_ov006_02056098();
    return nextState;
}