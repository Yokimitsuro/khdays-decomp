/* Per-frame advance of the object's five gauges.
 *
 * A signed 1-bit flag at bit 1 of the word at self+0x5c gates the shared
 * finalizer func_0203c904(): when it is set, the byte at self+0x60 decides
 * between bailing out immediately and running the finalizer before returning;
 * when it is clear the finalizer runs and the body below continues.
 *
 * The body then bails if bit 1 of the u16 at *(int *)(self+0x88) is set, and
 * otherwise walks slots 0..4.  A slot advances only while its active byte at
 * self+0xad+i is nonzero, the table at *(int *)(self+0x8c)+0x10 gives it a
 * non-null entry, and the signed s16 index at *(int *)(self+0x88)+2+i*2 is
 * non-negative.  `gauge` is then the slot's Q12 level and `max` its ceiling,
 * a u16 read through gauge[2] scaled to Q12.  Each frame the gauge moves by
 * FX_Mul(elapsed, self[i + 0x25]) -- self+0x94+i*4 is the slot's own rate --
 * in the direction chosen by bit 0 of self+0xb2: up towards max-0x1000, or
 * down towards 0.  On reaching its bound, the byte at self+0xa8+i picks
 * between wrapping to the opposite extreme and stopping there with the slot
 * deactivated.
 *
 * The gauge update is deliberately written as a store followed by a fresh
 * read of *gauge rather than through a named local: with a local, mwcc hoists
 * the `max - 0x1000` subtract above the load of *gauge, while the reload form
 * schedules it into the load-use slot exactly as the ROM does.  self[i+0x25]
 * (0x25*4 == 0x94) likewise has to be a typed index rather than a byte-offset
 * cast, or the loop grows a strength-reduced pointer the ROM does not have.
 */

extern void func_0203c904(int *self, int elapsed);

struct DirBit {
    unsigned char toZero : 1;
};

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_0203bb34(int *self, int elapsed)
{
    int flags = self[0x17];

    if ((flags << 30) >> 31) {
        if (*(unsigned char *)((char *)self + 0x60) == 0) {
            return;
        }
        func_0203c904(self, elapsed);
        return;
    }
    func_0203c904(self, elapsed);

    if (*(unsigned short *)(*(int *)((char *)self + 0x88)) & 2) {
        return;
    }

    {
        char *base = (char *)self;
        int i;
        unsigned char *active = (unsigned char *)(base + 0xad);
        int *table = (int *)(*(int *)(base + 0x8c) + 0x10);
        short *slotIndex = (short *)(*(int *)(base + 0x88) + 2);

        for (i = 0; i < 5; i++) {
            int idx;
            int *slot;
            int *gauge;
            int max;
            int delta;

            if (active[i] == 0) {
                continue;
            }
            slot = (int *)table[i];
            if (slot == 0) {
                continue;
            }

            idx = slotIndex[i];
            if (idx < 0) {
                continue;
            }

            gauge = (int *)slot[idx];
            max = (int)(*(unsigned short *)(*(int *)((char *)gauge + 8) + 4)) << 12;
            delta = FX_Mul(elapsed, self[i + 0x25]);

            if (((struct DirBit *)(base + 0xb2))->toZero == 0) {
                *gauge = *gauge + delta;
                if (*gauge < max - 0x1000) {
                    continue;
                }
                if (*(unsigned char *)(base + i + 0xa8) != 0) {
                    *gauge = 0;
                } else {
                    *gauge = max - 0x1000;
                    active[i] = 0;
                }
            } else {
                *gauge = *gauge - delta;
                if (*gauge > 0) {
                    continue;
                }
                if (*(unsigned char *)(base + i + 0xa8) != 0) {
                    *gauge = max - 0x1000;
                } else {
                    *gauge = 0;
                    active[i] = 0;
                }
            }
        }
    }
}
