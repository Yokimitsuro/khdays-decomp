/*
 * Builds the map panel's touch page and hands back its poll loop.
 *
 * The slot context is taken from the heap, published to the overlay's own slot
 * and cleared, and its stroke list is initialised. Eight touch regions are then
 * registered, each with a resource id, a rectangle in panel coordinates and the
 * handler that runs while it is held: five narrow buttons along the bottom, a
 * wider one beside them, the drawing grid itself at forty across and a hundred
 * and sixty-eight down, and the palette strip on the left.
 *
 * The two regions whose sixth argument is not the empty id carry a second one,
 * used while the region is held rather than tapped.
 *
 * Finally the owning player is recorded, the page's resource is opened, the
 * panel is told to come up, and the poll loop is returned as the page's first
 * state.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002SlotContext {
    int hResource;
    int nSlot;
    char list[0x10];
    int aActive[4];
    int bFlag;
} Ov002SlotContext;

extern Ov002SlotContext *data_ov002_0207f99c;
extern int data_ov002_0207eeb0;

extern Ov002SlotContext *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *pDest, u8 nValue, u32 nSize);
extern void NNS_FndInitList(void *pList, u16 nOffset);
extern void func_ov002_020657f4(int nId, int nX, int nY, int nWidth, int nHeight,
                                int nHeldId, void *pHandler);
extern int func_02030788(void);
extern int func_02023930(int *pResource, int nArg);
extern void func_ov002_0206700c(void);

extern void func_ov002_02065f40(void);
extern void func_ov002_02065fd4(void);
extern void func_ov002_02065ff8(void);
extern void func_ov002_0206601c(void);
extern void func_ov002_02066048(void);
extern void func_ov002_02066074(void);
extern void func_ov002_020660b0(void);
extern void func_ov002_020661f0(void);
extern void func_ov002_02065e54(void);

void *func_ov002_02065cc8(void)
{
    Ov002SlotContext *pCtx;

    pCtx = NNSi_FndGetCurrentRootHeap();
    data_ov002_0207f99c = pCtx;
    MI_CpuFill8(pCtx, 0, 0x2c);
    NNS_FndInitList(pCtx->list, 0x14);

    func_ov002_020657f4(0x4b3, 0, 0x60, 0x10, 0x30, 0xffff, func_ov002_02065f40);
    func_ov002_020657f4(0x44c, 0x30, 0x90, 0x10, 0x10, 0xffff, func_ov002_02065fd4);
    func_ov002_020657f4(0x44d, 0x40, 0x90, 0x10, 0x10, 0xffff, func_ov002_02065ff8);
    func_ov002_020657f4(0x44e, 0x60, 0x90, 0x10, 0x10, 0xffff, func_ov002_0206601c);
    func_ov002_020657f4(0x44f, 0x70, 0x90, 0x10, 0x10, 0xffff, func_ov002_02066048);
    func_ov002_020657f4(0x450, 0x90, 0x90, 0x40, 0x10, 0x464, func_ov002_02066074);
    func_ov002_020657f4(0x474, 0x28, 0xa8, 0xb0, 0x18, 0xffff, func_ov002_020660b0);
    func_ov002_020657f4(0x492, 0x18, 0xa0, 0x10, 0x17, 0x493, func_ov002_020661f0);

    pCtx->nSlot = func_02030788();
    pCtx->hResource = func_02023930(&data_ov002_0207eeb0, 0);
    func_ov002_0206700c();
    return func_ov002_02065e54;
}
