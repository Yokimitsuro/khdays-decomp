/* func_ov027_02082ba4 -- Ov027_DrawSignInPanel: draw the sign-in panel of the event scene.
 * PROVENANCE: byte-identical twin of ov023's Ov023_DrawSignInPanel (func_ov023_02083334), same
 * code and callees, verified byte-exact in this overlay.
 * Copies the panel's screen data (+0x8) into its screen buffer (+0xc: the two size halfwords
 * followed by the cells at +0xc) with 02013484, taking the column (3 - the local peer's slot,
 * 020bf240) * 2 as the source x and the buffer's own width / height as the destination size,
 * then queues the buffer for the BG at 0x19 (GFXi_EnqueueCommand with the byte count at +8). */
typedef unsigned short u16;

typedef struct Ov023PanelScreen {
    u16  nWidth;              /* 0x00 */
    u16  nHeight;             /* 0x02 */
    int  nField04;            /* 0x04 */
    int  nBytes;              /* 0x08 */
    u16  aCell[1];            /* 0x0c */
} Ov023PanelScreen;

typedef struct Ov023Panel {
    int  nField00;            /* 0x00 */
    int  nField04;            /* 0x04 */
    void *pScreenData;        /* 0x08 */
    Ov023PanelScreen *pScreen; /* 0x0c */
} Ov023Panel;

extern int  WM_EndKeySharing_0x020bf240(void);                      /* the local peer's slot */
extern void func_02013484(void *pScreenDst, void *pScreenData, int nSrcX, int nSrcY, int nDstX, int nDstY, unsigned int nDstW, unsigned int nDstH, int nWidth, int nHeight);
extern void GFXi_EnqueueCommand(int nCmd, int nDest, void *pSrc, int nSize);

void func_ov027_02082ba4(Ov023Panel *pPanel)
{
    Ov023PanelScreen *pScreen;
    void *pData;

    pScreen = pPanel->pScreen;
    pData = pPanel->pScreenData;
    func_02013484(pScreen->aCell, pData, (3 - WM_EndKeySharing_0x020bf240()) * 2, 0, 0, 0, pScreen->nWidth, pScreen->nHeight, 2, 2);
    GFXi_EnqueueCommand(0x19, 0, pPanel->pScreen->aCell, pPanel->pScreen->nBytes);
}
