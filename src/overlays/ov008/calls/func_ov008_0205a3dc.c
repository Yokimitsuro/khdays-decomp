typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern int  MI_CpuFill8(void *dest, int data, int size);
extern int  func_02023c40(void);
extern void func_02023c60(void *obj);
extern void func_ov008_0205a1d4(int *obj);
extern void func_02023cc0(void *obj);
extern void func_020110f4(void *p);
extern void GFXi_SaveStateTo(void *p);
extern int  OS_SPrintf(void *buf, const char *fmt, ...);
extern void func_0202a634(void *seq, void *fmtbuf, int c, int d);
extern void func_0202accc(void *seq, int b, void *track, int d);
extern void func_02014e18(int a, int b, int c, int d, int e);
extern void func_ov008_0205a138(int obj, int sceneId, int c);
extern void func_ov008_0205a1fc(int obj, int *param2);
extern void func_ov008_0205a0bc(void);
typedef struct { int f0; unsigned char pad[0x30]; } SceneParam;
extern SceneParam data_ov008_0208e9c4[];
extern char data_ov008_02090298[];
extern char data_ov008_020902ac[];
extern char data_ov008_020902c0[];
extern int  data_0204c678;

/* Ov008_Menu_InitSceneObject: initialize the menu scene object and resources. */
void func_ov008_0205a3dc(int *param_1, int *param_2)
{
    int sceneId;
    int val;
    unsigned short h;
    u32 auStack[32];

    MI_CpuFill8(param_1, 0, 0x528);
    switch (func_02023c40()) {
    case 0: param_1[0x6c] = 0x1000; break;
    case 1: param_1[0x6c] = 0xaaa; break;
    case 2: param_1[0x6c] = 0x2000; break;
    }
    func_02023c60(param_1);
    param_1[6] = 0x785;
    param_1[9] = 0x785;
    param_1[10] = 0x2800;
    param_1[0x149] = *param_2;
    func_ov008_0205a1d4(param_1);
    func_02023cc0(param_1);
    func_020110f4(param_1 + 0x13d);
    GFXi_SaveStateTo(param_1 + 0x147);

    sceneId = *param_2;
    val = (int)data_ov008_0208e9c4;
    val = *(int *)(val + sceneId * 0x34);
    switch (*(int *)param_2) {
    case 0:
        OS_SPrintf(auStack, data_ov008_02090298, val, val);
        break;
    case 5:
    case 0x10:
    case 0x11:
    case 0x12:
        OS_SPrintf(auStack, data_ov008_020902ac, val, val);
        break;
    default:
        OS_SPrintf(auStack, data_ov008_020902c0, val, val);
        break;
    }

    func_0202a634((void *)(param_1 + 0xe), auStack, 1, 0xe);
    func_0202accc((void *)(param_1 + 0xe), 0, (void *)(param_1 + 0x46), 0);

    sceneId = *param_2;
    switch (sceneId) {
    case 1:    h = 0xf8e4; break;
    case 0xe:  h = 0x71c; break;
    case 5:    h = 0x71c; break;
    case 0xb:  h = 0x71c; break;
    case 0x13: h = 0x71c; break;
    default:   h = 0; break;
    }
    *(u16 *)((char *)param_1 + 0xb4) = h;
    *(u16 *)((char *)param_1 + 0x38) |= 0x20;
    param_1[0x21] = (int)param_1;
    func_02014e18((int)(param_1 + 0x16), (int)&func_ov008_0205a0bc, 0, 6, 3);
    func_ov008_0205a138((int)param_1, *param_2, *(u8 *)((char *)&data_0204c678 + 4));
    func_ov008_0205a1fc((int)param_1, (int *)param_2);
}
