/* func_ov008_02087b98 -- Ov008_ClosePanel: tear the panel context down.  Rebuilds
 * the sprite cells, closes the panel screen, releases the +0xc5fc object, ends
 * the card transfer binding, frees the param table and the digit cells, the
 * text cache (+0xc130), the four render surfaces (+0xc19c/+0xc1d8/+0xc214/
 * +0xc160) and the three glyph sets (+0xc13c/+0xc148/+0xc154), both widget
 * groups (+0x7530/+0x2ab0) and their scratch buffer (+0x2aa8), the shared
 * buffer (+4), then both sub-panels' displays and buffers, and clears the
 * context pointer.
 */
typedef unsigned char u8;

extern char *data_ov008_02090fac;

extern void func_ov008_02083400(void);                       /* Ov008_RebuildSpriteCells */
extern void func_ov008_02082214(void);                       /* close the panel screen */
extern void func_ov008_0208e650(void *pObject);              /* ov008_InvokeMethod8 */
extern void func_02033500(int nArg);                         /* FSi_BindCardTransfer */
extern void func_ov008_0208b1bc(void);                       /* Ov008_FreeParamTable */
extern void func_ov008_02084324(void);                       /* free the digit cells */
extern void func_ov008_02055c74(void *pCache);
extern void func_0202ffbc(void *pSurface);                   /* FreeAllListNodeSubBuffers */
extern void func_0202ff7c(void *pGlyphs);                    /* FreeFieldAt8 */
extern void func_ov008_02054364(void *pGroup);               /* Ov008_Set_4364 */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_ov008_020559a8(void *pPanel);
extern void func_ov008_0205550c(void *pPanel);               /* Ov008_ReleaseThreeBuffers */

void func_ov008_02087b98(void)
{
    char *ctx = data_ov008_02090fac;

    func_ov008_02083400();
    func_ov008_02082214();
    func_ov008_0208e650(ctx + 0xc5fc);
    func_02033500(0);
    func_ov008_0208b1bc();
    func_ov008_02084324();
    func_ov008_02055c74(ctx + 0xc130);
    func_0202ffbc(ctx + 0xc19c);
    func_0202ffbc(ctx + 0xc1d8);
    func_0202ffbc(ctx + 0xc214);
    func_0202ffbc(ctx + 0xc160);
    func_0202ff7c(ctx + 0xc13c);
    func_0202ff7c(ctx + 0xc148);
    func_0202ff7c(ctx + 0xc154);
    func_ov008_02054364(ctx + 0x7530);
    func_ov008_02054364(ctx + 0x2ab0);
    if (*(void **)(ctx + 0x2aa8) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(ctx + 0x2aa8));
        *(void **)(ctx + 0x2aa8) = 0;
    }
    if (*(void **)(ctx + 4) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(ctx + 4));
        *(void **)(ctx + 4) = 0;
    }
    func_ov008_020559a8(ctx + 0x5c);
    func_ov008_020559a8(ctx + 0x10);
    func_ov008_0205550c(ctx + 0x5c);
    func_ov008_0205550c(ctx + 0x10);
    data_ov008_02090fac = 0;
}
