extern int *NNSi_FndGetCurrentRootHeap(void);
extern int *Msg_OpenContainerAndReadHeader(void *res, int b, int *c);
extern void Ov007_ReleaseAndFreeField2644(int *out, int arg);
extern int GameState_GetField(int a, int b);
extern void *Ov007_GetVarRecordByIndex(int *s, int idx);
extern void Ov007_SetupSubDisplay(void);
extern int *Archive_LoadFile(int arg, int b);
extern void Res_LoadSpriteSet(int *a, int *b, int c, int d, int e);
extern void GFXi_EnqueueCommand(int a, int b, int c, int d);
extern void Gfx_EnqueueTableCmdAt14(int a, int b, int c, int d);
extern void Gfx_EnqueueTableCmdAtC(int a, int b, int c, int d);
extern void ObjNode_InitFromDesc(int *a, unsigned int *b);
extern int VeneerTo_SlotTable_AddEntry(int *a, int b, int c);
extern void Slot_SetPosition(int *a, int b, unsigned int *c);
extern void Slot_SetMode2Bit(int *a, int b, int c);
extern void Font_LoadUTF16(int *a, void *b);
extern void TileTextRenderer_Init(int *a, int b, int *c, unsigned short *d);
extern void GX_LoadBGPltt(void *a, int b, int c);
extern void Ov007_FadeInStep(void);

extern int data_ov007_0204d420;
extern int gOv007UiMnlMPath;
extern int gOv007UiMnlMnlTextPath;
extern int gOv007TextFontEu10AllPath;
extern int data_ov007_0204d3ac;

/* ov007 scene init: grab the root heap, publish it, spawn the framebuffer/dual-screen
 * objects, pick the sub-display layout from the handler code (7..13 -> 1..7), build the
 * OAM/BG resources, configure the scroll box + palette, and return the per-frame update
 * handler (0204cf18). */
void *Ov007_SceneInit(int param_1, int param_2, int param_3, int param_4) {
    int *heap = NNSi_FndGetCurrentRootHeap();
    int idx;
    struct {
        unsigned int box[2];
        unsigned short blk[8];
        unsigned int l24[4];
    } fr;

    data_ov007_0204d420 = (int)heap;
    heap[0x16b0] = param_1;
    heap[0] = (int)Msg_OpenContainerAndReadHeader(&gOv007UiMnlMPath, 0xf, heap + 0x1400);
    Ov007_ReleaseAndFreeField2644(heap + 2, (int)&gOv007UiMnlMnlTextPath);

    heap[0x16ae] = GameState_GetField(0, 9);
    switch (heap[0x16ae]) {
    case 7:  idx = 1; break;
    case 8:  idx = 2; break;
    case 9:  idx = 3; break;
    case 10: idx = 4; break;
    case 11: idx = 5; break;
    case 12: idx = 6; break;
    case 13: idx = 7; break;
    default: idx = 0; break;
    }
    heap[0x1d] = (int)Ov007_GetVarRecordByIndex(heap + 2, idx);
    heap[0x1e] = 0;
    heap[0x16af] = 0;
    Ov007_SetupSubDisplay();
    heap[1] = (int)Archive_LoadFile(
        (int)(((((unsigned)heap[0] + 0x8000) & 0xfffffc) << 7) | 0x80000000), 0xe);
    Res_LoadSpriteSet(heap + 5, (int *)heap[1], heap[0x16af], heap[0x16af], heap[0x16af]);
    GFXi_EnqueueCommand(0x11, 0x2000, *(int *)(heap[7] + 0xc), *(int *)(heap[7] + 8));
    Gfx_EnqueueTableCmdAt14(1, heap[6], 0, *(int *)(heap[6] + 0x10));
    {
        int iVar9 = *(int *)(heap[5] + 8);
        Gfx_EnqueueTableCmdAtC(1, heap[5], 0, iVar9);

        fr.l24[0] = ((((unsigned)heap[0] + 0x8000) & 0xfffffc) << 7) | 0x80000001;
        fr.l24[1] = 1;
        fr.l24[2] = 0;
        fr.l24[3] = 0;
        ObjNode_InitFromDesc(heap + 0x41f, fr.l24);
        heap[0x16ad] = VeneerTo_SlotTable_AddEntry(heap + 0x41f, 0, 0);

        fr.box[0] = 0x80000;
        fr.box[1] = 0xbc000;
        Slot_SetPosition(heap + 0x41f, heap[0x16ad], fr.box);
        Slot_SetMode2Bit(heap + 0x41f, heap[0x16ad], 0);
        Font_LoadUTF16(heap + 9, &gOv007TextFontEu10AllPath);

        {
            unsigned short flag = 0;
            fr.blk[0] = flag;
            if (heap[0x16af] == 0) {
                flag = 0xc;
            }
            fr.blk[1] = flag;
        }
        fr.blk[2] = 0x20;
        fr.blk[3] = 9;
        fr.blk[4] = 1;
        fr.blk[5] = 0;
        fr.blk[6] = 0;
        fr.blk[7] = 0;
        TileTextRenderer_Init(heap + 0xc, 2, heap + 9, fr.blk);
        GX_LoadBGPltt(&data_ov007_0204d3ac, 0, 6);
        heap[8] = 0;
    }
    return (void *)Ov007_FadeInStep;
}
