/* Ov011_UpdateTitleFrame -- per-frame title update: step the layout animator, scroll both panes,
 * update their sprite groups, advance the background scroll, drop each pane's pending sprite in
 * once its anchor is on screen, float every visible sprite of both managers upwards (hiding the
 * ones that leave the top), and flush both sprite managers.
 *
 * The scene pointer is the file-defined shared-bss global: through the extern Ov011Globals the
 * reload of pScene is not hoisted above the pos.y store. The second pass counts panes with k and
 * slots with i (the other way round the allocator rotates four registers). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct UiLayoutPos {
    int x;
    int y;
} UiLayoutPos;

typedef struct Ov011Pane {
    void *pBuffer;
    u8    pad_00004[0x10908 - 4];
    int   aSlot[4];
    u8    pad_10918[0x1091a - 0x10918];
    u16   wScrollPhase;
    u8    pad_1091c[0x10940 - 0x1091c];
} Ov011Pane;

typedef struct Ov011SpriteManager {
    u8 data[0x4a38];
} Ov011SpriteManager;

typedef struct Ov011Scene {
    int                nA;
    int                nMode;
    u8                 pad_00008[4];
    u32                nArchiveBase;
    u8                 pad_00010[4];
    Ov011Pane          aPane[2];
    u8                 pad_21294[0x23aac - 0x21294];
    int                nBgScroll;
    int                nPrevBgScroll;
    u8                 pad_23ab4[0x23ad0 - 0x23ab4];
    Ov011SpriteManager aManager[2];
} Ov011Scene;

/* khdays: shared-bss */
u32 data_ov011_0205e960 = 0;
Ov011Scene *data_ov011_0205e964 = 0;

extern void         func_ov011_0205cad8(void);
extern void         func_ov011_0205bb58(int nPane, int nUnused);
extern void         func_ov011_0205cff0(int nPane);
extern UiLayoutPos *func_020325a0(Ov011SpriteManager *pManager, int nSlot);
extern void         func_0203257c(Ov011SpriteManager *pManager, int nSlot, UiLayoutPos *pPos);
extern void         func_02032710(Ov011SpriteManager *pManager, int nSlot, int bVisible);
extern int          func_02032748(Ov011SpriteManager *pManager, int nSlot);
extern void         func_0203256c(Ov011SpriteManager *pManager);

void func_ov011_0205c3a0(void)
{
    int i;
    int k;
    UiLayoutPos pos;

    func_ov011_0205cad8();
    func_ov011_0205bb58(0, 1);
    func_ov011_0205bb58(1, 1);
    func_ov011_0205cff0(0);
    func_ov011_0205cff0(1);
    data_ov011_0205e964->nPrevBgScroll = data_ov011_0205e964->nBgScroll;
    data_ov011_0205e964->nBgScroll += 0x94;

    for (i = 0; i < 2; i++) {
        if (data_ov011_0205e964->aPane[i].wScrollPhase != 0) {
            pos = *func_020325a0(&data_ov011_0205e964->aManager[i],
                                 data_ov011_0205e964->aPane[i].aSlot[1]);
            if ((pos.y >> 12) <= 0x80) {
                pos.y += 0x40000;
                func_0203257c(&data_ov011_0205e964->aManager[i],
                              data_ov011_0205e964->aPane[i].aSlot[2], &pos);
                func_02032710(&data_ov011_0205e964->aManager[i],
                              data_ov011_0205e964->aPane[i].aSlot[2], 1);
                data_ov011_0205e964->aPane[i].wScrollPhase = 0;
            }
        }
    }

    for (k = 0; k < 2; k++) {
        for (i = 0; i < 4; i++) {
            int nSlot = data_ov011_0205e964->aPane[k].aSlot[i];
            Ov011SpriteManager *pManager = &data_ov011_0205e964->aManager[k];

            if (func_02032748(pManager, nSlot)) {
                pos = *func_020325a0(pManager, nSlot);
                pos.y -= 0x17ae;
                func_0203257c(pManager, nSlot, &pos);
                func_02032710(pManager, nSlot, pos.y > -0x40000);
            }
        }
    }
    func_0203256c(&data_ov011_0205e964->aManager[0]);
    func_0203256c(&data_ov011_0205e964->aManager[1]);
}
