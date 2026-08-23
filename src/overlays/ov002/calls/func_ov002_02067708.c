/*
 * Ov002_OpenTutorialPage - build the tutorial page and hand back its step.
 *
 * The page object is taken from the scene, cleared and given its text writer.
 * The sub screen's background layers are remembered and switched to the pair
 * this screen needs, the tile map is filled and slot 0x1a claimed. Both text
 * containers are opened, the two entries this page answers to are registered,
 * and the surfaces are built - the wide set for tutorial 0x12, the plain one
 * otherwise. Unless the panel is already showing, the two side nodes are armed.
 *
 * THUMB.
 */

typedef unsigned short u16;
typedef unsigned int u32;

extern int *data_ov002_0207f9fc;
extern char data_ov002_0207eefc[];
extern char data_ov002_0207ef14[];
extern char data_ov002_0207ef28[];
extern char data_ov002_0207ef3c[];

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *pDst, int nValue, int nSize);
extern void func_ov002_0205280c(int pWriter, int pResource);
extern void func_ov002_02053b28(int nSlot, int nX, int nY, short nWidth,
                                short nHeight);
extern void func_ov002_02053cd4(int nSlot);
extern int func_02024ee8(char *pName, u32 nId);
extern void func_ov002_02052a6c(int nKey, int pfnDone, int nArg);
extern void func_ov002_020675d4(void);
extern void func_ov002_0206762c(void);
extern int func_ov002_020575e4(void);
extern int func_ov002_020536bc(int nTag);
extern void func_ov002_020536dc(int hNode, int nArg);
extern void func_02033b78(int nBank, int nCue);
extern void func_ov002_020674f4(void);
extern void func_ov002_0206752c(void);
extern void func_ov002_020678c4(void);

#define REG_DISPCNT_SUB (*(volatile u32 *)0x04001000)

void *func_ov002_02067708(u16 nTutorial)
{
    int hud;

    hud = (int)NNSi_FndGetCurrentRootHeap();
    data_ov002_0207f9fc = (int *)hud;
    MI_CpuFill8((void *)hud, 0, 0x1b0);
    func_ov002_0205280c(hud + 0x19c, (int)data_ov002_0207eefc);
    *(int *)(hud + 0x2c) = (REG_DISPCNT_SUB & 0x1f00) >> 8;
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & 0xffffe0ff) | 0xc00;
    func_ov002_02053b28(0x1a, 0, 0, 0x20, 0x20);
    func_ov002_02053cd4(0x1a);
    *(u16 *)hud = nTutorial;
    *(int *)(hud + 4) = func_02024ee8(data_ov002_0207ef14, 0xe);
    *(int *)(hud + 8) = func_02024ee8(data_ov002_0207ef28, 0xe);
    func_ov002_02052a6c((int)data_ov002_0207ef3c, (int)func_ov002_020674f4, 0);
    func_ov002_02052a6c(0x80000030 |
                        (((*(int *)(hud + 8) + 0x8000) & 0xfffffc) << 7),
                        (int)func_ov002_0206752c, 0);
    *(int *)(hud + 0x30) = *(u16 *)hud == 0x12;
    *(int *)(hud + 0x28) = 2;
    if (*(int *)(hud + 0x30) != 0) {
        func_ov002_0206762c();
    } else {
        func_ov002_020675d4();
    }
    if (func_ov002_020575e4() == 0) {
        func_ov002_020536dc(func_ov002_020536bc(0x18), 1);
        func_ov002_020536dc(func_ov002_020536bc(0x19), 1);
    }
    func_02033b78(0, 2);
    return func_ov002_020678c4;
}
