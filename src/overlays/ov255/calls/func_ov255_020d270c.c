/* Decay callback of the ov255 shake entries: every entry (0x38 bytes) of the context's +0x90
 * table (+0x8c entries) with a positive strength eases its offset and strength towards zero by
 * 1/(15/k) and 1/(10/k) per call (k = the owner's +0x3c8 byte) and is cleared once the strength
 * falls under 1/16. */
struct Shake { int offset; int strength; char pad[0x30]; };
struct ShakeSet { char pad[0x8c]; int count; struct Shake *items; };

extern int func_02020400(int num, int den);

void func_ov255_020d270c(int a, int b, int *ctx)
{
    int i;
    int off;

    i = 0;
    if (((struct ShakeSet *)ctx[1])->count > 0) {
        off = 0;
        do {
            struct Shake *e = (struct Shake *)((char *)((struct ShakeSet *)ctx[1])->items + off);

            if (e->strength > 0) {
                e->offset += func_02020400(-e->offset, func_02020400(0xf, *(unsigned char *)(ctx[0] + 0x3c8)));
                e->strength += func_02020400(-e->strength, func_02020400(0xa, *(unsigned char *)(ctx[0] + 0x3c8)));
                if (e->strength < 0x100) {
                    e->strength = 0;
                    e->offset = 0;
                }
            }
            off += 0x38;
        } while (++i < ((struct ShakeSet *)ctx[1])->count);
    }
}
