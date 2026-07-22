/* Scene entry: the context IS the current root heap block, so publish it and
 * zero all 0x18 bytes -- which is exactly the two NNS_FndList headers it then
 * initialises, both with a link offset of 0x14. Returns the next scene step. */
typedef struct {
    char aPrimary[0xc];     /* +0x00 NNS_FndList */
    char aSecondary[0xc];   /* +0x0c NNS_FndList */
} Ov002ListPairContext;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, unsigned char value, unsigned int size);
extern void NNS_FndInitList(void *list, unsigned short offset);
extern void func_ov002_02052a5c(void);

extern Ov002ListPairContext *data_ov002_0207f608;

void *func_ov002_02052998(void) {
    Ov002ListPairContext *ctx = NNSi_FndGetCurrentRootHeap();

    data_ov002_0207f608 = ctx;
    MI_CpuFill8(ctx, 0, 0x18);
    NNS_FndInitList(ctx->aPrimary, 0x14);
    NNS_FndInitList(ctx->aSecondary, 0x14);
    return (void *)&func_ov002_02052a5c;
}
