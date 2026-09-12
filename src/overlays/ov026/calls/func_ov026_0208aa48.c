/* func_ov026_0208aa48 -- Ov008_ClosePanel: tear the panel context down.  Rebuilds
 * the sprite cells, closes the panel screen, releases the +0xc5fc object, ends
 * the card transfer binding, frees the param table and the digit cells, the
 * text cache (+0xc130), the four render surfaces (+0xc19c/+0xc1d8/+0xc214/
 * +0xc160) and the three glyph sets (+0xc13c/+0xc148/+0xc154), both widget
 * groups (+0x7530/+0x2ab0) and their scratch buffer (+0x2aa8), the shared
 * buffer (+4), then both sub-panels' displays and buffers, and clears the
 * context pointer.
 */
typedef unsigned char u8;

extern char *data_ov026_02091368;

extern void func_ov026_020862b0(void);                       /* Ov008_RebuildSpriteCells */
extern void func_ov026_020850c4(void);                       /* close the panel screen */
extern void func_ov026_02090eb8(void *pObject);              /* ov008_InvokeMethod8 */
extern void func_02033500(int nArg);                         /* FSi_BindCardTransfer */
extern void func_ov026_0208e06c(void);                       /* Ov008_FreeParamTable */
extern void func_ov026_020871d4(void);                       /* free the digit cells */
extern void func_ov026_02084d64(void *pCache);
extern void func_0202ffbc(void *pSurface);                   /* FreeAllListNodeSubBuffers */
extern void func_0202ff7c(void *pGlyphs);                    /* FreeFieldAt8 */
extern void func_ov026_02083eb8(void *pGroup);               /* Ov008_Set_4364 */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_ov026_02083694(void *pPanel);
extern void func_ov026_02083234(void *pPanel);               /* Ov008_ReleaseThreeBuffers */

void func_ov026_0208aa48(void)
{
    char *ctx = data_ov026_02091368;

    func_ov026_020862b0();
    func_ov026_020850c4();
    func_ov026_02090eb8(ctx + 0xc5fc);
    func_02033500(0);
    func_ov026_0208e06c();
    func_ov026_020871d4();
    func_ov026_02084d64(ctx + 0xc130);
    func_0202ffbc(ctx + 0xc19c);
    func_0202ffbc(ctx + 0xc1d8);
    func_0202ffbc(ctx + 0xc214);
    func_0202ffbc(ctx + 0xc160);
    func_0202ff7c(ctx + 0xc13c);
    func_0202ff7c(ctx + 0xc148);
    func_0202ff7c(ctx + 0xc154);
    func_ov026_02083eb8(ctx + 0x7530);
    func_ov026_02083eb8(ctx + 0x2ab0);
    if (*(void **)(ctx + 0x2aa8) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(ctx + 0x2aa8));
        *(void **)(ctx + 0x2aa8) = 0;
    }
    if (*(void **)(ctx + 4) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(ctx + 4));
        *(void **)(ctx + 4) = 0;
    }
    func_ov026_02083694(ctx + 0x5c);
    func_ov026_02083694(ctx + 0x10);
    func_ov026_02083234(ctx + 0x5c);
    func_ov026_02083234(ctx + 0x10);
    data_ov026_02091368 = 0;
}
