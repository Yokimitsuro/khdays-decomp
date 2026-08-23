/*
 * Ov002_OpenCaptionSurfaces - open the caption screen's surfaces and start the
 * loads that fill them.
 *
 * Each surface's configuration takes the tile block, the screen block and the
 * palette the allocator hands out, and is then opened over its own slot of the
 * scene. The wide layout adds a third surface, marks its own ready flag, hands
 * the current message to the animation block unless it is the placeholder, and
 * kicks the tally load.
 *
 * The main caption surface is opened last, cleared to blank, and its own load
 * is kicked; both of its ready flags go up on the way out.
 *
 * THUMB.
 */

typedef struct {
    char pad000[0x1c];
    int nCharBase;
    char pad020[4];
    int nScreenBase;
    char pad028[4];
    int nPalette;
    char pad030[0x34];
    int nPriority;
    char pad068[4];
    int nCharBase2;
    char pad070[4];
    int nScreenBase2;
    char pad078[4];
    int nPalette2;
} Ov002SurfaceCfg;

typedef struct {
    char pad000[0x14];
    int nCharBase;
    char pad018[4];
    int nScreenBase;
    char pad020[4];
    int nPalette;
} Ov002TallyCfg;

typedef struct {
    char pad000[0x8c];
    int bReadyA;
    int bReadyB;
    int bReadyC;
    char pad098[0x28];
    char surfTop[0x3c];
    char surfMain[0x3c];
    char surfTally[0x88];
    char animBlock[0x14];
} Ov002TextScene;

extern int data_ov002_0207f62c;
extern Ov002SurfaceCfg data_ov002_0207ebf4;
extern Ov002TallyCfg data_ov002_0207ec74;
extern const char data_ov002_0207ec00[];
extern const char data_ov002_0207ec78[];
extern const char data_ov002_0207ec50[];
extern const char data_ov002_0207ece4[];
extern const char data_ov002_0207ed00[];

extern void func_0202ff8c(void *pSurface, const void *pConfig);
extern void func_02030178(void *pSurface, int nValue);
extern int func_020235d0(int a, int b);

extern int func_ov002_0206568c(void);
extern int func_ov002_02053bb8(int nId);
extern int func_ov002_0205740c(void);
extern int func_ov002_020575d0(void);
extern void func_ov002_02052a6c(const char *pName, void *pDone, int nFlags);
extern void func_ov002_020620ec(void *pNode);
extern void func_ov002_02061fec(void *pNode);
extern void func_ov069_020b876c(void *pAnim);

void func_ov002_0206250c(void)
{
    Ov002TextScene *s;

    s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);

    data_ov002_0207ebf4.nCharBase = func_ov002_0206568c();
    data_ov002_0207ebf4.nScreenBase = func_ov002_02053bb8(0x1a);
    data_ov002_0207ebf4.nPalette = func_ov002_0205740c();
    func_0202ff8c(s->surfTop, data_ov002_0207ec00);

    data_ov002_0207ebf4.nCharBase2 = func_ov002_0206568c() + 0x1e;
    data_ov002_0207ebf4.nScreenBase2 = func_ov002_02053bb8(0x1a);
    data_ov002_0207ebf4.nPalette2 = func_ov002_0205740c();

    if (func_ov002_020575d0() != 0) {
        data_ov002_0207ebf4.nPriority = 0xa;
        data_ov002_0207ec74.nCharBase = func_ov002_0206568c() + 0x32;
        data_ov002_0207ec74.nScreenBase = func_ov002_02053bb8(0x1a);
        data_ov002_0207ec74.nPalette = func_ov002_0205740c();
        func_0202ff8c(s->surfTally, data_ov002_0207ec78);
        s->bReadyC = 1;
        if (func_020235d0(0, 9) != 0x165) {
            func_ov069_020b876c(s->animBlock);
        }
        func_ov002_02052a6c(data_ov002_0207ece4, func_ov002_020620ec, 0);
    }

    func_0202ff8c(s->surfMain, data_ov002_0207ec50);
    func_02030178(s->surfMain, 2);
    func_ov002_02052a6c(data_ov002_0207ed00, func_ov002_02061fec, 0);
    s->bReadyA = 1;
    s->bReadyB = 1;
}
