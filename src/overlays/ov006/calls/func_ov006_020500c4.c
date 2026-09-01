typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*MissionState)(void);

typedef struct {
    void *sceneObject;
    u8 inputHeaderAndPadding[0x1c];
    u32 sessionReady;
    u32 parametersReady;
    u32 singleRowMode;
    u32 menuState;
    u8 menuMetadata[8];
    u32 cursorIndex;
    u8 selectionAndRows[0x24];
    u8 resourceRegion[0x10];
} MissionMenuContext;

extern u16 data_ov006_020561d0[];
extern MissionMenuContext *data_ov006_02056660;
extern u8 data_ov006_0205652c[];
extern u8 data_ov006_02056508[];

extern MissionMenuContext *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int func_02023588(u32 id);
extern int func_02036298(void *header, short *limits);
extern void *func_02023930(void *descriptor, void *parameter);
extern void func_ov006_020559dc(int subState);
extern void func_ov006_0204faf0(int enabled);
extern int func_ov006_0204f674(void);
extern int func_02030640(void);
extern int func_02030670(void);
extern int func_02030694(void);
extern int func_ov006_0204fa88(void);
extern int func_ov006_02055b30(u32 mode);
extern void func_ov006_0204d57c(void *subObject);
extern void func_ov006_0204d554(void *subObject, const void *config);
extern void func_ov006_02050e1c(void);
extern void func_ov006_020502e4(void);

MissionState func_ov006_020500c4(int immediate)
{
    short limits[2];

    {
        char *source = (char *)data_ov006_020561d0;
        u16 upper = *(u16 *)(source + 12);
        u16 lower = *(u16 *)(source + 10);
        *(volatile u16 *)&limits[1] = upper;
        *(volatile u16 *)&limits[0] = lower;
    }
    MissionMenuContext *context = NNSi_FndGetCurrentRootHeap();
    data_ov006_02056660 = context;
    MI_CpuFill8(context, 0, sizeof(MissionMenuContext));
    data_ov006_02056660->cursorIndex = 0;
    data_ov006_02056660->singleRowMode =
        func_02023588(0x200d) != 0;
    data_ov006_02056660->menuState = 0;
    func_02036298(
        &data_ov006_02056660->inputHeaderAndPadding, limits);

    MissionState nextState;
    if (immediate != 0) {
        data_ov006_02056660->sceneObject =
            func_02023930(data_ov006_0205652c, (void *)1);
        func_ov006_020559dc(0xd);
        func_ov006_0204faf0(1);
        data_ov006_02056660->sessionReady = 1;
        data_ov006_02056660->singleRowMode = func_ov006_0204f674();
        nextState = func_ov006_02050e1c;
    } else if (data_ov006_02056660->singleRowMode != 0 ||
               (func_02030640() != 0 && func_02030670() != 0)) {
        data_ov006_02056660->sceneObject =
            func_02023930(data_ov006_0205652c, (void *)1);
        func_ov006_0204faf0(0);
        data_ov006_02056660->sessionReady = func_02030694();
        func_ov006_02055b30(func_ov006_0204fa88());
        func_ov006_020559dc(4);
        nextState = func_ov006_02050e1c;
    } else {
        data_ov006_02056660->sceneObject =
            func_02023930(data_ov006_0205652c, (void *)0);
        func_ov006_0204faf0(0);
        func_ov006_020559dc(0);
        nextState = func_ov006_020502e4;
    }

    func_ov006_0204d57c(&data_ov006_02056660->resourceRegion);
    func_ov006_0204d554(
        &data_ov006_02056660->resourceRegion, data_ov006_02056508);
    return nextState;
}
