/* Slam landing of the ov225 enemy. The point 3.04 above the owner (turned by its +0xa0 pose
 * from the +8 point) is taken and the +0x14 leap clears. With a +0x10 target still held the
 * +0x5c timer clears and the aim tick (ov225 2908) runs again; otherwise the point is sent to
 * the owner as mode 5, reaction 0x14b mode 0x12 fires there, sub-state 2 is requested and the
 * action ends. */
typedef unsigned char u8;
struct vec3 { int x, y, z; };

extern void func_0202f384(struct vec3 *out, const void *pose, struct vec3 *in);
extern void VEC_Add(struct vec3 *a, struct vec3 *b, struct vec3 *c);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c0b90(int owner, int mode, struct vec3 v, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern const struct vec3 data_02041dc8;
extern void func_ov225_020d2908(int *node);

void func_ov225_020d2a80(int *node)
{
    int *state = (int *)node[1];
    struct vec3 v;

    v.x = 0;
    v.y = 0x30a4;
    v.z = 0;
    func_0202f384(&v, (const void *)(*state + 0xa0), &v);
    VEC_Add(&v, (struct vec3 *)state[2], &v);
    *(struct vec3 *)(state + 5) = data_02041dc8;
    if (state[4] != 0) {
        state[0x17] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov225_020d2908);
        return;
    }
    func_ov107_020c0b90(*state, 5, v, 0);
    func_ov107_020c5af8(*state, 0x14b, 0x12, &v);
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
