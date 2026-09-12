#pragma thumb on

/* Construct the sub-object embedded at +0x20 of an actor object.
 *
 * Every caller builds it in place -- `func_0202d968(actor + 0x20, ...)` -- and
 * passes the address of the record the sub-object is bound to, which
 * `func_0202bfcc` computes from the actor's index byte. That record address is
 * stored at field +0x00 and the rest of the block is brought to its start
 * state: the sentinel halfword at +0x46 is set to -1, the flag word at +0x04 is
 * cleared and then given bit 4, the three embedded 12-byte vectors at +0x14,
 * +0x20 and +0x2c are zeroed by chain-copying the shared zero vector, ten
 * scattered int fields are cleared, four fields get their fixed defaults, the
 * second halfword at +0x44 gets 0x666, and finally bit 2 is added to the flag
 * word (leaving 0x14) to mark the object constructed.
 *
 * The layout of this object is only partly known -- the cleared fields are
 * spread over a 0x440-byte block at a 0xa8-byte stride -- so it stays word
 * indexing rather than a struct that would mostly be padding.
 */

typedef struct { int x, y, z; } VecFx32;

extern VecFx32 data_02041dc8;                      /* kVecZero */

int func_0202d968(int *self, int record)
{
    self[0] = record;                              /* +0x000 */
    *(short *)((char *)self + 0x46) = -1;
    self[1] = 0;                                   /* +0x004 flags */
    self[1] |= 0x10;
    *(VecFx32 *)(self + 8) = data_02041dc8;        /* +0x020 */
    *(VecFx32 *)(self + 5) = *(VecFx32 *)(self + 8);   /* +0x014 */
    *(VecFx32 *)(self + 0xb) = *(VecFx32 *)(self + 5); /* +0x02c */
    self[0x10f] = 0;                               /* +0x43c */
    self[0x3b] = 0;                                /* +0x0ec */
    self[0x65] = 0;                                /* +0x194 */
    self[0x8f] = 0;                                /* +0x23c */
    self[0xb9] = 0;                                /* +0x2e4 */
    self[0xe3] = 0;                                /* +0x38c */
    self[0x10d] = 0;                               /* +0x434 */
    self[4] = 0;                                   /* +0x010 */
    self[3] = 0;                                   /* +0x00c */
    self[2] = 0;                                   /* +0x008 */
    self[0xe] = 0x80000000;                        /* +0x038 */
    self[0xf] = 0x80;                              /* +0x03c */
    self[0x10] = 0x2000;                           /* +0x040 */
    self[0x10e] = 0x1000;                          /* +0x438 */
    *(unsigned short *)((char *)self + 0x44) = 0x666;
    self[1] |= 4;
    return 1;
}
