/*
 * Ov002_ConstructGameplayScene - master constructor for the ov002 gameplay scene. Builds the
 * gameplay session on the root heap (published to data_ov002_0207fa00), brings up every
 * subsystem, seeds the per-mission scene-transition entry, and returns the initial state handler.
 *
 * Flow:
 *  - grabs the root heap and records it; enables the lazy class unless either archive
 *    (func_02023588 0x18bd / 0x18c9) is already resident;
 *  - initialises the session header fields at heap+0x8b4c..heap+0x8dc2 (handles/flags/-1
 *    sentinels), the card-present flag at heap+0x8b54, and the local-player bit at heap+0x8dc2;
 *  - clears the big work area at heap+0x859c (0x5a4 bytes) and copies the mission descriptor
 *    from `params` (or the default data_0204c240 when null) into the session record at heap+0x8ba8;
 *  - if hard mode is active it scales the three reward figures at data_0204c254+0x10 by 100;
 *  - formats the mission id string (OS_SPrintf) and loads its archive, then runs the whole init
 *    chain (party/enemy/HUD/camera/panel/etc. - the func_ov002_* calls) and the sub-object
 *    allocators (Ov002_AllocSceneState, Ov002_EnsureSceneManager(0x792b), ...);
 *  - allocates the 0x40-entry u16 table at heap+0x8dac from func_020235d0 (unless flag 4 is set);
 *  - when the global mode byte data_0204c240 is 0, maps the mission id to the next-scene id in
 *    data_0204c23c (the scene-transition table);
 *  - returns func_ov002_02067d9c when a link session is active (func_02030670), else
 *    func_ov002_02067f78 - the scene's first tick handler.
 *
 * THUMB, returns the handler pointer. Notes on matching the original codegen: the card flag is a
 * merged store (one int temp, not a store per branch); the hard-mode reward loop keeps the
 * data_0204c254 base pointer live from its +0xe test through the +0x10 scale (counter declared
 * before the pointer so it lands in the low scratch register); and the transition switch emits its
 * case bodies in source order, so the cases are listed 5,6,4,0x6c,0x6f,0x514,0x72,0x515 to match.
 */

typedef unsigned char  u8;
typedef unsigned short u16;

extern int   data_ov002_0207fa00;
extern short data_0204c23c;
extern u8    data_0204c240;
extern u8    data_0204c248;
extern u8    data_0204c254;
extern int   data_0204c4d8;
extern int   data_ov002_0207efb0;
extern int   data_ov002_0207efbc;
extern int   data_ov002_0207efc0;
extern int   data_ov002_0207f134;

extern int  NNSi_FndGetCurrentRootHeap(void);
extern int  func_02023588(int archiveId);
extern void func_ov002_0206e718(int enabled);
extern int  func_02023bf0(void);
extern void func_02020aa8(int a, void *b);
extern int  func_02030670(void);
extern int  CARDi_GetRomAccessor_0x020315f4(void);
extern int  func_02030788(void);
extern void func_ov002_02069240(void);
extern void MI_CpuFill8(void *dest, int data, int size);
extern void func_020350c8(void);
extern void func_020235e8(int a, int b, int c);
extern void OS_SPrintf(char *buf, void *fmt, int arg);
extern int  func_02024ee8(char *buf, int a);
extern void func_ov002_020693cc(int a);
extern void func_ov002_020697cc(void);
extern void func_ov002_0206a230(void);
extern void func_ov002_020697e8(void);
extern void func_ov002_02069c24(void);
extern void func_ov002_0206a2b8(void);
extern void func_ov002_0206a2e8(void);
extern void func_ov002_0206a080(void);
extern void func_ov002_0206a0f4(void);
extern void func_ov002_0206a29c(void);
extern void func_ov002_0206a2cc(void);
extern void func_ov002_02069798(void);
extern void func_ov002_0207185c(void);
extern void func_ov002_020734e8(int a);
extern void func_0202b73c(void);
extern void func_ov002_02076924(void);
extern void func_ov002_0206eabc(void);
extern void func_ov002_0206f444(int a);
extern void func_ov002_0206fb5c(void);
extern void func_ov002_0206da28(void);
extern void func_ov002_020636dc(void);
extern void func_ov002_02069b70(void);
extern void func_ov002_020763c8(void);
extern void func_ov002_020765f8(int active);
extern int  func_ov002_02078e18(int sceneId);
extern void func_ov002_0206b910(void *a, void *b);
extern void func_ov002_0206da54(int a, int b);
extern int  func_02023c40(void);
extern void func_ov002_02069c04(void);
extern void func_02035c28(void);
extern int  NNSi_FndAllocFromDefaultExpHeap(int size);
extern short func_020235d0(int a, int b);
extern void func_ov002_0206e640(void);
extern void *func_ov002_02067d9c(void);
extern void *func_ov002_02067f78(void);

void *func_ov002_020679d4(void *param_1)
{
    char *heap;
    char *rec;
    char *src;
    char buf[0x14];
    int i;

    heap = (char *)NNSi_FndGetCurrentRootHeap();
    rec = heap + 0x8ba8;
    data_ov002_0207fa00 = (int)heap;
    if (func_02023588(0x18bd) == 0 && func_02023588(0x18c9) == 0) {
        func_ov002_0206e718(1);
    }
    *(int *)heap = func_02023bf0();
    func_02020aa8(2, &data_ov002_0207f134);
    *(int *)(heap + 0x8b58) = -1;
    *(int *)(heap + 0x8b4c) = -1;
    *(u16 *)(heap + 0x8da0) = 0;
    if (func_02030670() != 0 && *(int *)(CARDi_GetRomAccessor_0x020315f4() + 4) >= 3) {
        i = 1;
    } else {
        i = 0;
    }
    *(int *)(heap + 0x8b54) = i;
    *(int *)(heap + 0x8b60) = -1;
    *(int *)(heap + 0x8b64) = 0;
    *(u8 *)(heap + 0x8b68) = 0;
    *(u8 *)(heap + 0x8dc2) = 1 << func_02030788();
    *(u16 *)(heap + 0x8dc0) = 0xffff;
    *(u8 *)(heap + 0x8d9c) = 0;
    *(u8 *)(heap + 0x8da4) = 0;
    func_ov002_02069240();
    MI_CpuFill8(heap + 0x859c, 0, 0x5a4);
    src = param_1 ? (char *)param_1 : (char *)&data_0204c240;
    *(u16 *)rec = *(u16 *)(src + 2);
    *(u16 *)(rec + 2) = *(u16 *)(src + 4);
    func_020350c8();
    func_020235e8(0x82 << 6, 5, 0);
    *(int *)(rec + 0x14) = *(u8 *)(src + 1);
    if ((data_0204c240 & 2) != 0 && (data_0204c240 & 4) == 0) {
        int k;
        char *q = (char *)&data_0204c254;
        if (*(u16 *)(q + 0xe) == 0) {
            for (k = 0; k < 3; k++) {
                *(int *)(q + 0x10) = *(int *)(q + 0x10) * 0x64;
                q += 4;
            }
        }
    }
    OS_SPrintf(buf, &data_ov002_0207efb0, *(short *)rec);
    *(int *)(heap + 4) = func_02024ee8(buf, 2);
    func_ov002_020693cc(*(int *)(rec + 0x14));
    func_ov002_020697cc();
    func_ov002_0206a230();
    func_ov002_020697e8();
    func_ov002_02069c24();
    func_ov002_0206a2b8();
    func_ov002_0206a2e8();
    func_ov002_0206a080();
    func_ov002_0206a0f4();
    func_ov002_0206a29c();
    func_ov002_0206a2cc();
    func_ov002_02069798();
    func_ov002_0207185c();
    func_ov002_020734e8(*(short *)rec);
    func_0202b73c();
    func_ov002_02076924();
    func_ov002_0206eabc();
    func_ov002_0206f444(*(int *)((char *)&data_0204c4d8 + 0x14));
    func_ov002_0206fb5c();
    func_ov002_0206da28();
    func_ov002_020636dc();
    func_ov002_02069b70();
    func_ov002_020763c8();
    func_ov002_020765f8(1);
    func_ov002_02078e18(0x792b);
    func_ov002_0206b910(&data_ov002_0207efbc, &data_ov002_0207efc0);
    func_ov002_0206da54(0, *(int *)(heap + 4));
    MI_CpuFill8(heap + 0x8d84, 0, 0x18);
    if ((data_0204c240 & 0xc) == 4 && *(u8 *)((char *)&data_0204c248 + 2) != 0) {
        int v = (func_02023c40() == 1) ? 0x14 : 0x1e;
        *(short *)(heap + 0x8d98) = (short)((v << 0xc) >> 0xc);
    } else {
        *(short *)(heap + 0x8d98) = -1;
    }
    *(u8 *)(heap + 0x8b40) = 0;
    *(int *)(heap + 0x8b44) = 0;
    *(int *)(heap + 0x8b48) = 0;
    *(u8 *)(heap + 0x8b41) = 0xff;
    *(u16 *)(heap + 0x8b6a) = 0;
    *(int *)(heap + 0x8b78) = 0;
    *(u16 *)(heap + 0x8b6c) = 0;
    *(u16 *)(heap + 0x8b6e) = 0;
    *(u16 *)(heap + 0x8b70) = 0;
    *(u16 *)(heap + 0x8b72) = 0;
    *(u16 *)(heap + 0x8b74) = 0;
    *(int *)(heap + 0x8db0) = 0;
    *(u16 *)(heap + 0x8db4) = 0xffff;
    *(u8 *)(heap + 0x8db6) = 0;
    *(int *)(heap + 0x8dbc) = 0;
    MI_CpuFill8(heap + 0x8db7, 0, 4);
    *(u8 *)(heap + 0x8d9e) = 0;
    func_ov002_02069c04();
    if ((data_0204c240 & 4) == 0) {
        func_02035c28();
    }
    if ((data_0204c240 & 4) == 0) {
        *(int *)(heap + 0x8dac) = NNSi_FndAllocFromDefaultExpHeap(0x80);
        for (i = 0; i < 0x40; i++) {
            *(short *)(*(int *)(heap + 0x8dac) + i * 2) = func_020235d0(0x1400 + i * 0x10, 0x10);
        }
    } else {
        *(int *)(heap + 0x8dac) = 0;
    }
    func_ov002_0206e640();
    func_020235e8(0x20dd, 3, 0xffff);
    if (data_0204c240 == 0) {
        short sv = *(short *)rec;
        switch (sv) {
        case 5:     data_0204c23c = 4;    break;
        case 6:     data_0204c23c = 5;    break;
        case 4:     data_0204c23c = 6;    break;
        case 0x6c:  data_0204c23c = 0x25; break;
        case 0x6f:  data_0204c23c = 0x4a; break;
        case 0x514: data_0204c23c = 0x5b; break;
        case 0x72:  data_0204c23c = 0x5c; break;
        case 0x515: data_0204c23c = 0x5d; break;
        default:
            if (sv >= 1 && sv <= 6) data_0204c23c = sv;
            break;
        }
    }
    if (func_02030670() != 0) {
        return (void *)func_ov002_02067d9c;
    }
    return (void *)func_ov002_02067f78;
}
