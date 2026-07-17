/*
 * NONMATCHING -- 164/160, ONE instruction over: the final two vec3 copies. The ROM fuses the
 * `*state` load with the state+0xc advance into a post-increment `ldr r0,[r4],#0xc` (r4 then serves
 * as both copy1 src and copy2 dst); mwcc emits `ldr r0,[r4] ; add r3,r4,#0xc` (separate) no matter
 * the spelling -- tried `state += 3`, a fresh walking pointer `p=state; owner=*p; p+=3`, and a
 * single `sv=state+3` base. mwcc will not choose post-increment addressing here. Everything else
 * (ease/apply, the timer, the abs+rand reroll) is byte-exact. Attack only the copy pair.
 *
 * func_ov200_020cec8c -- x3 (ov200/201/271). AI-state tick: ease the pose, tick a reroll timer, and
 * publish the pose.
 * Ease the working pose state[0x21..] toward its target by state[0x18] (0202f55c) and apply it to the
 * owner (0203c9d0, *state+0xa0). If the timer state[0x20] is positive, decrement by owner_delta. If
 * the owner flag bit2 at *state+0x1c4 is set, reroll the timer: lo + RandNextScaled(abs(hi-lo)+1),
 * lo/hi at *state+0x224/+0x228. Publish state[3..5] to the owner (*state+0xf0), then reset state[3..5]
 * to the const vec data_02041dc8.
 */
struct vec3 { int x, y, z; };
extern void func_0202f55c(void *a, int s, void *b, void *m);
extern void func_0203c9d0(void *a, void *b);
extern int  func_02023eb4(int mul);
extern struct vec3 data_02041dc8;

void func_ov200_020cec8c(int *self) {
    int *state = (int *)self[1];

    func_0202f55c((void *)(state + 0x21), state[0x18], (void *)(state + 0x21), (void *)(state + 0x25));
    func_0203c9d0((void *)(*state + 0xa0), (void *)(state + 0x21));
    if (state[0x20] > 0) {
        state[0x20] -= *(int *)(*self + 0x2c);
    }
    if (*(unsigned char *)(*state + 0x1c4) & 4) {
        int lo = *(int *)(*state + 0x224);
        int d = *(int *)(*state + 0x228) - lo;
        state[0x20] = lo + func_02023eb4((d < 0 ? -d : d) + 1);
    }
    {
        int *p = state;
        int owner = *p;
        p += 3;
        *(struct vec3 *)(owner + 0xf0) = *(struct vec3 *)p;
        *(struct vec3 *)p = data_02041dc8;
    }
}
