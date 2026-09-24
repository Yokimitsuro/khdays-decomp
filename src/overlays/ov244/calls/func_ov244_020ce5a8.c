/* Ov244_TickChargeUp -- charge-up tick of an ov244 part: keeps the part at its anchor's +0x14
 * position raised to the target's height + 0x200, accumulates the owner's rate on the +4 timer and
 * steps the +0x10 phase at 0x2800, 0x3214 and 0x3547, spawning effect 0x113 (variants 0xb and
 * 0xc) at the part on the last two steps. Once the part is idle (+0xad clear) its channels 0, 2,
 * 4 and 1 are started (mode 1), it is reset (0203c7ac) and the tick hands over to
 * func_ov244_020ce72c. */
typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

extern void func_0203ca30(void *pSrt, VecFx32 *pPos);
extern void func_02033d0c(int nEffect, int nVariant, VecFx32 *pPos, int nFlags);
extern void func_0203b9fc(int obj, int channel, int a, int b);
extern void func_0203c7ac(int obj, int n);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov244_020ce72c(int *node);

void func_ov244_020ce5a8(int *node)
{
    int *state = (int *)node[1];
    VecFx32 pos;

    pos = *(VecFx32 *)(*(char **)(state[3] + 0x3c8) + 0x14);
    pos.y = *(int *)(state[3] + 0xb4) + 0x200;
    func_0203ca30((void *)(state[0] + 4), &pos);
    state[1] += *(int *)(*node + 0x2c);
    if (*(unsigned char *)(state + 4) == 0 && state[1] >= 0x2800) {
        (*(unsigned char *)(state + 4))++;
    } else if (*(unsigned char *)(state + 4) == 1 && state[1] >= 0x3214) {
        (*(unsigned char *)(state + 4))++;
        func_02033d0c(0x113, 0xb, &pos, 0);
    } else if (*(unsigned char *)(state + 4) == 2 && state[1] >= 0x3547) {
        (*(unsigned char *)(state + 4))++;
        func_02033d0c(0x113, 0xc, &pos, 0);
    }
    if (*(unsigned char *)(state[0] + 0xad) == 0) {
        func_0203b9fc(state[0], 0, 1, 0);
        func_0203b9fc(state[0], 2, 1, 0);
        func_0203b9fc(state[0], 4, 1, 0);
        func_0203b9fc(state[0], 1, 1, 0);
        func_0203c7ac(state[0], 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov244_020ce72c);
        return;
    }
}
