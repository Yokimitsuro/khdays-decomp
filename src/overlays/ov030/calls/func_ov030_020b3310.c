/* Scene teardown: release the context's sub-objects and hand back whatever
 * func_ov022_0209fab4 returns as the next step.
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
extern void func_0202a440(int *p);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void WM_EndKeySharing_0x02023ad0(void *obj);
extern void func_ov002_02051fc8(int *a, int *b);
extern void func_ov030_020b4c34(int *p);
extern void *func_ov022_0209fab4(Ov030Context *ctx);

extern unsigned char data_0204c240;

void *func_ov030_020b3310(void) {
    Ov030Context *ctx = NNSi_FndGetCurrentRootHeap();

    if ((data_0204c240 & 4) == 0) {
        func_0202a440(ctx->aSub2c2c);
        NNSi_FndFreeFromDefaultHeap(ctx->pBuffer2c50);
    }
    if (ctx->pObject2cac != 0) {
        WM_EndKeySharing_0x02023ad0(ctx->pObject2cac);
    }
    func_ov002_02051fc8(ctx->aSub2c54, ctx->aSub0910);
    func_ov030_020b4c34(ctx->aSub2cb0);
    return func_ov022_0209fab4(ctx);
}
