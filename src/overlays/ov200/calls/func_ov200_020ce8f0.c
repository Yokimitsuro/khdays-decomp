/*
 * func_ov200_020ce8f0 -- x3. AI-state tick: aim toward the target and lead it, store the heading.
 * target = acquire(*state, 0) -> state[2]. dir = normalise(target(+0x74) - state[0x13]) -> state[0xf];
 * state[9] = dir * 0x800 (lead offset). Build the lead point state[0xc] = (*state+0xb0) + state[9];
 * state[0xd] = *(*state+0x78) - *(*state+0x80). Then heading = atan2 of (state[0xc] - (*state+0xb0)),
 * stored at *(*state+0x3ac).
 */
struct vec3 { int x, y, z; };
extern int  func_ov107_020cab14(int obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern void func_01ffa724(int scale, void *in, void *out);
extern void VEC_Add(void *a, void *b, void *c);
extern int  func_020050b4(int x, int z);

void func_ov200_020ce8f0(int *self) {
    int *state = (int *)self[1];
    struct vec3 v;
    int w[3];
    int target = func_ov107_020cab14(*state, 0);

    state[2] = target;
    VEC_Subtract((void *)(target + 0x74), (void *)state[0x13], (void *)(state + 0xf));
    func_01ff8d18((void *)(state + 0xf), (void *)(state + 0xf));
    func_01ffa724(0x800, (void *)(state + 0xf), (void *)(state + 9));
    v = *(struct vec3 *)(*state + 0xb0);
    VEC_Add(&v, (void *)(state + 9), &v);
    *(struct vec3 *)(state + 0xc) = v;
    state[0xd] = *(int *)(*state + 0x78) - *(int *)(*state + 0x80);
    VEC_Subtract((void *)(state + 0xc), (void *)(*state + 0xb0), w);
    *(int *)(*state + 0x3ac) = func_020050b4(w[0], w[2]);
}
