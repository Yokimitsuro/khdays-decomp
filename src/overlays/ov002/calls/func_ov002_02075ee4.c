typedef unsigned int u32;
typedef volatile unsigned int vu32;

typedef struct Ov002ScreenCtx {
    char pad000[0xc];
    void *pOverlay;             /* 0x0c */
    void *pBuffer;              /* 0x10 */
} Ov002ScreenCtx;

extern Ov002ScreenCtx *data_ov002_0207fa18;
extern char data_ov002_0207f444[];

extern void func_02000fb4(int nSlot, void *pWhat);
extern void func_0201e374(int nWhich);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_ov002_02053d94(int nMode);
extern void func_ov002_02056fb8(int nMode, int nArg);
extern void func_ov002_02053cd4(int nMode);
extern int func_ov002_0206b864(void);
extern void *G2_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(u32 nValue, void *pDest, u32 nSize);
extern void func_ov002_02075fd4(int nMode);

/* Tear the screen down and hand it back.
 *
 * The screen's own slot is released and its work buffer freed; a screen that
 * had brought an overlay up closes that too.  Unless something else is already
 * holding the display, both engines get their four backgrounds turned back on
 * with the objects left off, the BG3 map is cleared and the screen pointer is
 * dropped.
 */
void func_ov002_02075ee4(void)
{
    vu32 *pDispCnt;
    vu32 *pSubDispCnt;

    func_02000fb4(1, data_ov002_0207f444);
    func_0201e374(-16);

    if (data_ov002_0207fa18->pBuffer != 0) {
        NNSi_FndFreeFromDefaultHeap(data_ov002_0207fa18->pBuffer);
        data_ov002_0207fa18->pBuffer = 0;
    }

    if (data_ov002_0207fa18->pOverlay != 0) {
        func_ov002_02053d94(0);
        func_ov002_02056fb8(0, 0);
        func_ov002_02053cd4(9);
    }

    if (func_ov002_0206b864() != 0) {
        pDispCnt = (vu32 *)0x04000000;
        *pDispCnt = (*pDispCnt & 0xffffe0ff) | 0xf00;
        pSubDispCnt = (vu32 *)0x04001000;
        *pSubDispCnt = (*pSubDispCnt & 0xffffe0ff) | 0xf00;
    }

    MIi_CpuClearFast(0, G2_GetBG3ScrPtr(), 0x800);
    func_ov002_02075fd4(0);
    data_ov002_0207fa18 = 0;
}
