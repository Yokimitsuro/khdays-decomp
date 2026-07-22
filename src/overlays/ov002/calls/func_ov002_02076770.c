/* Report the element's kind byte and its index within its own pool. The index is
 * the byte distance from the pool base divided by the element stride, both of
 * which live on the pool descriptor at +8.
 *
 * The division goes through func_02020400 BY ADDRESS: writing `/` emits a call
 * to _s32_div_f, which is not a symbol this project can link. */
extern int func_02020400(int numerator, int denominator);

typedef struct {
    char pad0000[0x4e];
    unsigned short wStride;     /* +0x4e */
    char pad0050[4];
    char *pBase;                /* +0x54 */
} Ov002PoolDesc;

typedef struct {
    char pad0000[8];
    Ov002PoolDesc *pPool;       /* +8 */
    char pad000c[5];
    unsigned char bKind;        /* +0x11 */
} Ov002PoolElement;

void func_ov002_02076770(Ov002PoolElement *self, unsigned char *outKind,
                         short *outIndex) {
    Ov002PoolDesc *pool;

    *outKind = self->bKind;

    pool = self->pPool;
    *outIndex = (short)func_02020400((int)((char *)self - pool->pBase),
                                     pool->wStride);
}
