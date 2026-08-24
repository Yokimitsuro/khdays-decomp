/* Ov002_UploadSlotIconPalette - push one slot's icon palette to the panel.
 *
 * The mode picks which palette bank the icon comes from: icons below thirteen
 * live in the first bank, the rest in the second with their index rebased. Each
 * icon owns thirty-two bytes one entry into the bank, and each slot owns
 * thirty-two bytes two entries into the destination. While the panel is not held
 * the copy goes through the graphics queue; while it is held it is written
 * straight into the saved background palette, if one was kept. Every mode but
 * three also clears the slot's retire timer, the byte array at +0x65 that the
 * cancel path arms at fifteen and the frame tick counts down.
 *
 * ARM. Returns early when the mode has no palette bound.
 *
 * The bank pointer is written out per arm rather than kept in a local. mwcc
 * commons the three reads back into one predicated reload, which is what the
 * original emits; assigning it to a local first gives that value a different
 * register and sinks the +0xc load to the bottom of its block.
 */
typedef unsigned char u8;

typedef struct {
    int nId;                            /* +0x00 */
    int nIcon;                          /* +0x04 */
    int nField0008;                     /* +0x08 */
    int nField000c;                     /* +0x0c */
} Ov002PanelSlot;

typedef struct {
    u8 pad0000[0x65];
    u8 abSlotRetireTimer[4];            /* +0x65 */
    u8 pad0069[0x130 - 0x69];
    Ov002PanelSlot aSlots[4];           /* +0x130 */
    u8 pad0170[0x1b0 - 0x170];
    int nHeld;                          /* +0x1b0 */
    u8 pad01b4[0x1fc - 0x1b4];
    char *apHelpPltA[4];                /* +0x1fc */
    char *apHelpPltB[4];                /* +0x20c */
    char *hSavedBg2Plt;                 /* +0x21c */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f614;

extern void GFXi_EnqueueCommand(int nKind, int nDest, int nSource, int nSize);
extern void MIi_CpuCopy16(int nSource, int nDest, int nSize);

void func_ov002_02057260(int nSlot, int nMode)
{
    Ov002PanelContext *pCtx;
    int nIcon;
    int nSource;
    int nDest;
    int nBank;

    pCtx = data_ov002_0207f614;
    nIcon = pCtx->aSlots[nSlot].nIcon;
    if (pCtx->apHelpPltA[nMode] == 0) {
        return;
    }
    if (nIcon >= 13) {
        nIcon -= 13;
        nBank = *(int *)(pCtx->apHelpPltB[nMode] + 0xc);
    } else {
        nBank = *(int *)(pCtx->apHelpPltA[nMode] + 0xc);
    }
    nSource = nIcon * 32 + 32;
    nDest = nSlot * 32 + 64;
    if (pCtx->nHeld != 0) {
        if (pCtx->hSavedBg2Plt != 0) {
            MIi_CpuCopy16(nBank + nSource, (int)pCtx->hSavedBg2Plt + nDest, 0x20);
        }
    } else {
        GFXi_EnqueueCommand(0xf, nDest, nBank + nSource, 0x1e);
    }
    if (nMode != 3) {
        pCtx->abSlotRetireTimer[nSlot] = 0;
    }
}
