/*
 * Point the node at its stored heading, then advance to the default pose if both sub-nodes are
 * idle (x-family).
 *
 * Hand the heading vector cached at state[10..0xc] to BuildHeadingRotation (020d43a4) with the
 * apply flag set, then gate: if either the sub-node at state[1]+0xad or the one reached through
 * *state+0x388 is still busy, wait. Otherwise fire event 4, seed the default pose (020d4234), and
 * advance with a callback.
 *
 * ★ THIS IS THE ORIGINAL `ldm`-args-coalescing example (it was the deferred-ties entry's own
 * citation), and the STRUCT-BY-VALUE crack matched it on the first compile: the vector at
 * state[10..0xc] is passed as `*(struct Vec3 *)(state + 10)`, which mwcc loads with one
 * `ldm r1,{r1,r2,r3}` -- exactly the ROM. Three separate `int` args would have been three `ldr`s.
 * The tie is retired.
 */
struct Vec3 { int x, y, z; };

extern void func_ov197_020ccb24(int *state, struct Vec3 v, int flag);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov197_020cc9b4(int a, int b);
extern void func_0203c634(int self, int idx, int cb);
extern int func_ov197_020cd65c;

void func_ov197_020cd5e4(int self) {
    int *state = *(int **)(self + 4);

    func_ov197_020ccb24(state, *(struct Vec3 *)(state + 10), 1);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (*(unsigned char *)(*(int *)(*state + 0x388) + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 4, 0);
    func_ov197_020cc9b4(*state, 2);
    func_0203c634(self, *(signed char *)(self + 0x20), (int)&func_ov197_020cd65c);
}
