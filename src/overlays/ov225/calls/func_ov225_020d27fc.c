/* Slam entry of the ov225 enemy. The point 3.04 above the owner (turned by its +0xa0 pose
 * from the +8 point) is sent to the owner as mode 5 and reaction 0x14b mode 0x12 fires there;
 * bits 1 and 7 of the +0x60 high byte and bit 0 of +0x1ae are raised, the +0x5c timer clears
 * and the tick hands over to func_ov225_020d2908. */
struct vec3 { int x, y, z; };
typedef unsigned short u16;

extern void func_0202f384(struct vec3 *out, const void *pose, struct vec3 *in);
extern void VEC_Add(struct vec3 *a, struct vec3 *b, struct vec3 *c);
extern void func_ov107_020c0b90(int owner, int mode, struct vec3 v, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov225_020d2908(int *node);

void func_ov225_020d27fc(int *node)
{
    int *state = (int *)node[1];
    struct vec3 v;
    u16 flags;

    v.x = 0;
    v.y = 0x30a4;
    v.z = 0;
    func_0202f384(&v, (const void *)(*state + 0xa0), &v);
    VEC_Add(&v, (struct vec3 *)state[2], &v);
    func_ov107_020c0b90(*state, 5, v, 0);
    func_ov107_020c5af8(*state, 0x14b, 0x12, &v);
    flags = *(u16 *)(*state + 0x60);
    *(u16 *)(*state + 0x60) = (u16)((flags & ~0xff00) | (((((unsigned int)flags << 0x10) >> 0x18 | 2) << 0x18) >> 0x10));
    *(u16 *)(*state + 0x1ae) |= 1;
    flags = *(u16 *)(*state + 0x60);
    *(u16 *)(*state + 0x60) = (u16)((flags & ~0xff00) | (((((unsigned int)flags << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10));
    state[0x17] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov225_020d2908);
}
