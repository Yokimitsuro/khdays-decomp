/* Initialize the refresh-window subsystem and register its named task. */
typedef unsigned char u8;

typedef struct Ov002RefreshWindowState {
    unsigned int uFlags;
    int nScale;
    int fxMetric;
    u8 gap000c[0x34];
    int nLatch;
    u8 bStatus;
} Ov002RefreshWindowState;

extern Ov002RefreshWindowState *data_ov002_0207f600;
extern int data_ov002_0207e850;

extern int func_0201e438(void);
extern void func_ov002_02051528(int nX, int nY, int nWidth,
                                int nHeight, int nMode);
extern void func_ov002_02051854(void);
extern void func_02000f48(int nPriority, void *pName,
                          void (*pCallback)(void));

void func_ov002_020518e0(void)
{
    data_ov002_0207f600->fxMetric = func_0201e438() << 12;
    data_ov002_0207f600->nScale = 0x100;
    data_ov002_0207f600->uFlags |= 1;
    data_ov002_0207f600->uFlags &= ~0x10;
    data_ov002_0207f600->nLatch = 0;
    data_ov002_0207f600->bStatus = 0;
    func_ov002_02051528(0, 0, 0x100, 0xc0, 0);
    func_02000f48(1, &data_ov002_0207e850, func_ov002_02051854);
}
