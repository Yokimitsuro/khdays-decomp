/* func_ov201_020d28cc -- AI think tick: step the actor's spline, push it to the render node,
 * count the wait timer down, and re-roll it when the actor is flagged for a random wait.
 *
 * The tail hands the actor's current position to the render node at owner+0xf0 and then resets
 * the state's own copy from the shared zero vector. It advances `state` itself by 0xc bytes with
 * a BYTE cast rather than using a second pointer: that is what produces the ROM's post-indexed
 * `ldr r0, [r4], #0xc`. Writing `state + 3`, or a separate cursor local, splits it into a load
 * plus an add. Same idiom as func_ov247_020d281c.
 * Byte-identical twin of func_ov200_020cec8c. */
struct vec3 { int x, y, z; };
extern void func_0202f55c(void *a, int s, void *b, void *m);
extern void func_0203c9d0(void *a, void *b);
extern int  func_02023eb4(int mul);
extern struct vec3 data_02041dc8;

void func_ov201_020d28cc(int *self) {
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
        int owner = *state;
        state = (int *)((char *)state + 0xc);
        *(struct vec3 *)(owner + 0xf0) = *(struct vec3 *)state;
        *(struct vec3 *)state = data_02041dc8;
    }
}
