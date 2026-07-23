/* Enter the wind-up state: set 0x06 and then 0x40 in the high byte of the hw60 flag word,
 * raise bit 0 of the flags at +0x1ae, clear bit 0 of the sub-object's byte at +8, aim the
 * effect at the stored target vector, start effect 0x49 on it, clear the counter at
 * state[0xb] and continue in the next step.
 *
 * The target vector is passed BY VALUE: mwcc builds it just below sp, loads its first two
 * words into r2/r3 and leaves the third in the outgoing stack slot, which is exactly the
 * ROM's `sub r3,sp,#8 / stm r3 / ldm r3,{r2,r3}`. Passing a pointer instead loses all of it.
 *
 * One of four byte-identical siblings (ov127/ov128/ov129/ov130). */
typedef struct { int x, y, z; } VecFx32;

extern void func_ov107_020c0b90(int obj, int a, VecFx32 v, int d);
extern void func_ov107_020c5af8(int obj, int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov130_020cd690(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct LowByte { unsigned bits : 8; };

void func_ov130_020cd59c(int *node) {
    int *state = (int *)node[1];

    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    }
    *(unsigned short *)(state[0] + 0x1ae) |= 1;
    ((struct LowByte *)(*(int *)(state[0] + 0x388) + 8))->bits &= ~1;
    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    }
    func_ov107_020c0b90(state[0], 0, *(VecFx32 *)state[5], 0);
    func_ov107_020c5af8(state[0], 0, 0x49, state[5]);
    state[0xb] = 0;
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov130_020cd690);
}
