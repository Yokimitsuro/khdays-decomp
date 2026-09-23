/* Stamp-walk tick: reads the frame of the +0x388 part's animation 0 (0203bec0). Each armed foot
 * (+0x3d0 slot) stamps inside its window (foot 0 frames 15..17, foot 1 frames 33..35): a sphere at
 * the foot part's +4 point (+0x3c0 slot) with the foot's +0x90 radius sweeps the actor list and
 * every entity in it is pushed 0.375 away horizontally (kind 4, on behalf of the +0x384 rider); on
 * acceptance the 14-byte message data_ov236_020d6470 carries its +0x74 point raised by 0.5 and its
 * +0x1b4 byte to the rider's +0x24 hook, and reaction 0x127 mode 0xd fires at that raised point.
 * The +0x7c step flag alternates: at frame 15 it rises and, with foot 0 alive, note 2 of
 * data_ov236_020d6430 goes to the actor's hook and reaction mode 0xb fires at foot 0; at frame 33 it
 * falls and, with foot 1 alive, note 3 goes out and mode 0xc fires at foot 1. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 center; int nRadius; } Sphere;
typedef struct { u16 lo; u16 hi; } Cmd4;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern int func_0203bec0(int part, int channel);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, void *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern const Cmd4 data_ov236_020d6430[];
extern const Cmd14 data_ov236_020d6470;

void func_ov236_020d59d8(int *node)
{
    Cmd4 note1;
    Cmd4 note2;
    int *state = (int *)node[1];
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int hits[4];
    Sphere sphere;
    Vec3 push;
    Vec3 raw;
    int frame;
    int k;
    int n;
    int i;

    frame = func_0203bec0(*(int *)(*state + 0x388), 0);
    for (k = 0; k < 2; k++) {
        if (((short *)*state)[0x1e8 + k] == 0) {
            continue;
        }
        if (!((k == 0 && frame >= 0xf000 && frame <= 0x11000) || (k == 1 && frame >= 0x21000 && frame <= 0x23000))) {
            continue;
        }
        sphere.center = *(Vec3 *)(*(int *)((int *)*state)[0xf0 + k] + 4);
        n = *(int *)(*(int *)((int *)*state)[0xf0 + k] + 0x90);
        sphere.nRadius = n;
        n = func_ov107_020c8eb8(*state, &sphere, hits);
        for (i = 0; i < n; i++) {
            Cmd14 msg;

            VEC_Subtract((void *)(hits[i] + 0x74), &sphere.center, &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x600, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x384), 4, &push, 0) == 0) {
                continue;
            }
            msg = data_ov236_020d6470;
            raw = *(Vec3 *)(hits[i] + 0x74);
            raw.y += 0x800;
            PACK(msg, scratchX, *(Fx32 *)&raw.x, 5);
            PACK(msg, scratchY, *(Fx32 *)&raw.y, 8);
            PACK(msg, scratchZ, *(Fx32 *)&raw.z, 11);
            msg.flag = *(u8 *)(hits[i] + 0x1b4);
            if (*(void (**)(int, Cmd14 *, int))(*(int *)(*state + 0x384) + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*(int *)(*state + 0x384) + 0x24))(*(int *)(*state + 0x384), &msg, 0xe);
            }
            func_ov107_020c5af8(*state, 0x127, 0xd, &raw);
        }
    }
    if (*((u8 *)state + 0x7c) == 0) {
        if (func_0203bec0(*(int *)(*state + 0x388), 0) < 0xf000) {
            return;
        }
        *((u8 *)state + 0x7c) = 1;
        if (*(short *)(*state + 0x3d0) <= 0) {
            return;
        }
        {
            Cmd4 *p = &note1;

            p->hi = data_ov236_020d6430[2].hi;
            p->lo = data_ov236_020d6430[2].lo;
            if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
            }
        }
        func_ov107_020c5af8(*state, 0x127, 0xb, (void *)(**(int **)(*state + 0x3c0) + 4));
    } else if (*((u8 *)state + 0x7c) == 1) {
        if (func_0203bec0(*(int *)(*state + 0x388), 0) < 0x21000) {
            return;
        }
        *((u8 *)state + 0x7c) = 0;
        if (*(short *)(*state + 0x3d2) <= 0) {
            return;
        }
        {
            Cmd4 *p = &note2;

            p->hi = data_ov236_020d6430[3].hi;
            p->lo = data_ov236_020d6430[3].lo;
            if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
            }
        }
        func_ov107_020c5af8(*state, 0x127, 0xc, (void *)(**(int **)(*state + 0x3c4) + 4));
    }
}
