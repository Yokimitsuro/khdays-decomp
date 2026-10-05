/* Start the ov106 scene from its launch record: the scene block is taken and cleared (0x8eb4 bytes),
 * field 0x14 opens on data_ov106_020b8af0, the record's caption string is copied to +0x8e50 and its
 * +0x44 value kept in +0x8e90, the +0x8b38 camera starts in mode 0xb, the gOv106Dual3DUpdateName task runs
 * 020b7b08, the frame counter is sampled into +0x8e3c/+0x8e28, the 2.0 x 2.0 view rectangles are set,
 * the view is built (020b77b4), both selections clear to -1 and the shared 0x44-byte state is reset.
 * Returns the next state (020b75c0). */
typedef struct { int v[10]; } ViewRects;

extern char *data_ov106_020b8b60;
extern char data_ov106_020b8af0[];
extern char gOv106Dual3DUpdateName[];
extern char data_0204c41c[];
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int val, int size);
extern void StoreGlobalArrayEntry(int nId, void *nFlags);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void Gfx_ResetDisplayAndVram(void *p, int a);
extern void Obj_SetWord8(void *pCamera, int nMode);
extern void Obj_SetWord4(void *p, int a);
extern void RegisterNamedTask(int priority, const char *name, void (*callback)(void));
extern int GetMasterBrightnessMain(void);
extern void NNS_GfdSetFrmTexVramState(ViewRects *p);
extern void Ov106_SetupView(void);
extern void Ov106_FrameTask(void);
extern void Ov106_WaitPendingText(void);

void *Ov106_StartScene(char *record)
{
    ViewRects rects;

    data_ov106_020b8b60 = NNSi_FndGetCurrentRootHeap();
    MI_CpuFill8(data_ov106_020b8b60, 0, 0x8eb4);
    StoreGlobalArrayEntry(0x14, data_ov106_020b8af0);
    OS_SPrintf(data_ov106_020b8b60 + 0x8e50, record);
    *(int *)(data_ov106_020b8b60 + 0x8e90) = *(int *)(record + 0x44);
    *(int *)(data_ov106_020b8b60 + 0x8e4c) = 0xb;
    Gfx_ResetDisplayAndVram(data_ov106_020b8b60 + 0x8b38, 0);
    Obj_SetWord8(data_ov106_020b8b60 + 0x8b38, *(int *)(data_ov106_020b8b60 + 0x8e4c));
    Obj_SetWord4(data_ov106_020b8b60 + 0x8b38, 0);
    RegisterNamedTask(1, gOv106Dual3DUpdateName, Ov106_FrameTask);
    *(int *)(data_ov106_020b8b60 + 0x8e3c) = GetMasterBrightnessMain();
    *(int *)(data_ov106_020b8b60 + 0x8e28) = *(int *)(data_ov106_020b8b60 + 0x8e3c);
    rects.v[0] = 0;
    rects.v[1] = 0x20000;
    rects.v[2] = 0;
    rects.v[3] = 0x20000;
    rects.v[4] = 0;
    rects.v[5] = 0;
    rects.v[6] = 0;
    rects.v[7] = 0x20000;
    rects.v[8] = 0;
    rects.v[9] = 0x20000;
    NNS_GfdSetFrmTexVramState(&rects);
    Ov106_SetupView();
    *(int *)(data_ov106_020b8b60 + 0x8eac) = -1;
    *(int *)(data_ov106_020b8b60 + 0x8eb0) = -1;
    MI_CpuFill8(data_0204c41c, 0, 0x44);
    return Ov106_WaitPendingText;
}
