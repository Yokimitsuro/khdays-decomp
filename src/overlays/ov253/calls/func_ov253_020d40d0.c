/* func_ov253_020d40d0 -- burst entry: the overlay's 14-byte message (data_ov253_020d4a08)
 * carrying the +4 position as three 24-bit coordinates goes through the actor's +0x24 hook;
 * bit 1 of the +0x60 high byte is raised and bits 2-4, 7 cleared, bits 0-1 of +0x1ae clear, the
 * +0x20 timer is armed with 0.5, the +8 velocity takes half the +0x14 direction, +0x44 and
 * +0x24 clear and the node moves to 020d425c. Codegen: the position is packed through Fx32
 * wrapper copies (ov269_3930 idiom). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern const PosMsg data_ov253_020d4a08;
extern void func_ov253_020d425c(void);

void func_ov253_020d40d0(int *node) {
    int *state = (int *)node[1];
    PosMsg msg;
    FxVec vContact;
    FxVec *src;

    msg = data_ov253_020d4a08;
    src = (FxVec *)state[1];
    vContact.x = src->x;
    ((u8 *)&msg)[5] = (u8)(((u32)vContact.x.value >> 0x10 & 0x7f) | ((u32)vContact.x.value >> 0x18 & 0x80));
    ((u8 *)&msg)[6] = (u8)((u32)vContact.x.value >> 8);
    ((u8 *)&msg)[7] = (u8)vContact.x.value;
    vContact.y = src->y;
    ((u8 *)&msg)[8] = (u8)(((u32)vContact.y.value >> 0x10 & 0x7f) | ((u32)vContact.y.value >> 0x18 & 0x80));
    ((u8 *)&msg)[9] = (u8)((u32)vContact.y.value >> 8);
    ((u8 *)&msg)[10] = (u8)vContact.y.value;
    vContact.z = src->z;
    ((u8 *)&msg)[11] = (u8)(((u32)vContact.z.value >> 0x10 & 0x7f) | ((u32)vContact.z.value >> 0x18 & 0x80));
    ((u8 *)&msg)[12] = (u8)((u32)vContact.z.value >> 8);
    ((u8 *)&msg)[13] = (u8)vContact.z.value;
    if (*(void **)(*state + 0x24) != 0) {
        (*(void (**)(int, PosMsg *, int))(*state + 0x24))(*state, &msg, 0xe);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 2) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x9c) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x100 + 0xae) &= ~3;
    state[8] = 0x800;
    func_01ffa724(state[8], (Vec3 *)(state + 5), (Vec3 *)(state + 2));
    state[0x11] = 0;
    state[9] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020d425c);
}
