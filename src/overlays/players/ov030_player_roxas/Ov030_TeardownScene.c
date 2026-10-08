/* Scene teardown: release the context's sub-objects and hand back whatever
 * Ov022_DestroyRoot returns as the next step.
 *
 * data_0204c240 bit 2 -- the boot-mode gate ov002 and ov022 also read -- skips
 * the first two releases entirely, so those two resources only exist in one of
 * the two boot modes.
 */
typedef struct {
    char pad0000[0x910];
    int aSub0910[1];         /* +0x0910 */
    char pad0914[0x2318];
    int aSub2c2c[1];         /* +0x2c2c */
    char pad2c30[0x20];
    void *pBuffer2c50;       /* +0x2c50 */
    int aSub2c54[1];         /* +0x2c54 */
    char pad2c58[0x54];
    void *pObject2cac;       /* +0x2cac */
    int aSub2cb0[1];         /* +0x2cb0 */
} Ov030Context;

extern Ov030Context *NNSi_FndGetCurrentRootHeap(void);
extern void FreeAllResourceTables(int *p);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void VeneerTo_Obj_Destroy(void *obj);
extern void Ov002_FreeResourceTables(int *a, int *b);
extern void Ov030_setupTriple(int *p);
extern void *Ov022_DestroyRoot(Ov030Context *ctx);

extern unsigned char data_0204c240;

void *Ov030_TeardownScene(void) {
    Ov030Context *ctx = NNSi_FndGetCurrentRootHeap();

    if ((data_0204c240 & 4) == 0) {
        FreeAllResourceTables(ctx->aSub2c2c);
        NNSi_FndFreeFromDefaultHeap(ctx->pBuffer2c50);
    }
    if (ctx->pObject2cac != 0) {
        VeneerTo_Obj_Destroy(ctx->pObject2cac);
    }
    Ov002_FreeResourceTables(ctx->aSub2c54, ctx->aSub0910);
    Ov030_setupTriple(ctx->aSub2cb0);
    return Ov022_DestroyRoot(ctx);
}
