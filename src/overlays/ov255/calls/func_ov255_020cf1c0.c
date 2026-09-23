/* Ground-strike enter tick of an ov255 state: the owner's +0x24 hook receives note 1 of
 * data_ov255_020d2b20 and the nearest target (020cab14) becomes +0x5c. With one, a ray is cast
 * from 10.0 above its +0x190 point 30.0 straight down through the world's +0x7c collision; on a
 * plain surface (no +8 flag) the ray is clipped to the plane (+0xc), the hit point is sent to the
 * hook in the 14-byte message of data_ov255_020d2b6e and reaction +0x3f8 mode 0x2b fires there.
 * Animation 0x10 plays, the +0x50 timer and +0x65 clear and the tick hands over to
 * func_ov255_020cf3c4. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 lo; u16 hi; } Cmd4;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

/* the note table seen as a word-aligned record: its note 1 follows a 4-byte word */
extern const struct { int w0; Cmd4 n1; } data_ov255_020d2b20;
extern const Cmd14 data_ov255_020d2b6e;
extern int func_ov107_020cab14(int obj, int kind);
extern int *func_01fff920(void *collision, Vec3 *origin, Vec3 *dir);
extern void func_01ffd144(int plane, Vec3 *in, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov255_020cf3c4(int *node);

void func_ov255_020cf1c0(int *node)
{
    int *state = (int *)node[1];
    Cmd4 note = data_ov255_020d2b20.n1;
    Vec3 p;
    Vec3 ray;
    Cmd14 msg;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;

    if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
        (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, &note, 4);
    }
    state[0x17] = func_ov107_020cab14(*state, 0);
    if (state[0x17] != 0) {
        int world = *(int *)(*state + 4);
        int *wall;

        p = *(Vec3 *)(state[0x17] + 0x190);
        p.y += 0xa000;
        ray.x = 0;
        ray.z = 0;
        ray.y = -0x1e000;
        wall = func_01fff920(*(void **)(world + 0x7c), &p, &ray);
        if (wall != 0 && wall[2] == 0) {
            msg = data_ov255_020d2b6e;
            func_01ffd144(wall[3], &ray, &ray);
            VEC_Add(&p, &ray, &p);
            PACK(msg, scratchX, *(Fx32 *)&p.x, 5);
            PACK(msg, scratchY, *(Fx32 *)&p.y, 8);
            PACK(msg, scratchZ, *(Fx32 *)&p.z, 11);
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
            }
            func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x3f8), 0x2b, &p);
        }
    }
    func_ov107_020c9264(*state, 0x10, 0);
    state[0x14] = 0;
    *((u8 *)state + 0x65) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov255_020cf3c4);
}
