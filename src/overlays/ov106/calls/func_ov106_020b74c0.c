/* Start the ov106 scene from its launch record: the scene block is taken and cleared (0x8eb4 bytes),
 * field 0x14 opens on data_ov106_020b8af0, the record's caption string is copied to +0x8e50 and its
 * +0x44 value kept in +0x8e90, the +0x8b38 camera starts in mode 0xb, the data_ov106_020b8ab4 task runs
 * 020b7b08, the frame counter is sampled into +0x8e3c/+0x8e28, the 2.0 x 2.0 view rectangles are set,
 * the view is built (020b77b4), both selections clear to -1 and the shared 0x44-byte state is reset.
 * Returns the next state (020b75c0). */
typedef struct { int v[10]; } ViewRects;

extern char *data_ov106_020b8b60;
extern char data_ov106_020b8af0[];
extern char data_ov106_020b8ab4[];
extern char data_0204c41c[];
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int val, int size);
extern void func_02020aa8(int nId, void *nFlags);
extern void OS_SPrintf(char *buf, const char *fmt);
extern void func_0202e8ec(void *p, int a);
extern void func_0202ea14(void *pCamera, int nMode);
extern void func_0202ea1c(void *p, int a);
extern void func_02000f48(int priority, const char *name, void (*callback)(void));
extern int func_0201e428(void);
extern void func_02011134(ViewRects *p);
extern void func_ov106_020b77b4(void);
extern void func_ov106_020b7b08(void);
extern void func_ov106_020b75c0(void);

void *func_ov106_020b74c0(char *record)
{
    ViewRects rects;

    data_ov106_020b8b60 = NNSi_FndGetCurrentRootHeap();
    MI_CpuFill8(data_ov106_020b8b60, 0, 0x8eb4);
    func_02020aa8(0x14, data_ov106_020b8af0);
    OS_SPrintf(data_ov106_020b8b60 + 0x8e50, record);
    *(int *)(data_ov106_020b8b60 + 0x8e90) = *(int *)(record + 0x44);
    *(int *)(data_ov106_020b8b60 + 0x8e4c) = 0xb;
    func_0202e8ec(data_ov106_020b8b60 + 0x8b38, 0);
    func_0202ea14(data_ov106_020b8b60 + 0x8b38, *(int *)(data_ov106_020b8b60 + 0x8e4c));
    func_0202ea1c(data_ov106_020b8b60 + 0x8b38, 0);
    func_02000f48(1, data_ov106_020b8ab4, func_ov106_020b7b08);
    *(int *)(data_ov106_020b8b60 + 0x8e3c) = func_0201e428();
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
    func_02011134(&rects);
    func_ov106_020b77b4();
    *(int *)(data_ov106_020b8b60 + 0x8eac) = -1;
    *(int *)(data_ov106_020b8b60 + 0x8eb0) = -1;
    MI_CpuFill8(data_0204c41c, 0, 0x44);
    return func_ov106_020b75c0;
}
