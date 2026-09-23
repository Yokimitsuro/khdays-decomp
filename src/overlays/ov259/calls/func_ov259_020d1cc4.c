/* Flight step of an ov259 helper: its hit capsule (the +0x390 record's base block) is re-aimed from
 * its +0x74 position along its +0xa0 facing, widened by 0.25, and swept for the +0x394 owner
 * (020c8f44). Each entity not yet struck (bit `1 << id` of the +0x38 mask) is pushed away at 0.25
 * plus the helper's +0x18 drive (straight down at -2.0 while latched, +0x39c; x0.5625 when the owner
 * is in move 4); if it takes the hit (020ca918, the owner's move as kind) the owner plays sound
 * 0x172/5 (charged, +0x424) or 4 at the +8 point and is knocked back at the entity (mode 6 for
 * moves 3-7, else 0), and the entity is marked. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;

extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern int func_ov107_020c8f44(int owner, Capsule *seg, int *hits);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov259_020cd3c4(int actor, int id, int variant, void *at);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern const Vec3 data_02042258;

void func_ov259_020d1cc4(int *node)
{
    int *state = (int *)node[1];
    Capsule seg;
    Vec3 axis;
    int hits[4];
    Vec3 push;
    Vec3 away;
    int count;
    long i;

    seg = *(Capsule *)(*(int *)(*state + 0x390) + 0x78);
    seg.pos = *(Vec3 *)(*state + 0x74);
    func_0202f384(&axis, (void *)(*state + 0xa0), &data_02042258);
    seg.axis = axis;
    seg.radius += 0x400;
    count = func_ov107_020c8f44(*(int *)(*state + 0x394), &seg, hits);
    for (i = 0; i < count; i++) {
        u8 bit = 1 << *(u16 *)(hits[i] + 2);

        if (*((u8 *)state + 0x38) & bit) {
            continue;
        }
        VEC_Subtract((Vec3 *)(hits[i] + 0x74), (Vec3 *)(*state + 0x74), &push);
        func_01ff8d18(&push, &away);
        func_01ffa724(0x400, &push, &push);
        VEC_Add(&push, (Vec3 *)(state + 6), &push);
        if (*(int *)(*state + 0x39c) != 0) {
            push.y = -0x2000;
        }
        if (*(int *)(*(int *)(*state + 0x394) + 0x420) == 4) {
            func_01ffa724(0x900, &push, &push);
        }
        if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x394),
                                (u8)*(int *)(*(int *)(*state + 0x394) + 0x420), &push, 0)) {
            int owner = *(int *)(*state + 0x394);
            int mode;

            switch (*(int *)(owner + 0x420)) {
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                mode = 6;
                break;
            case 0:
            default:
                mode = 0;
                break;
            }
            if (*(int *)(owner + 0x424) != 0) {
                func_ov259_020cd3c4(owner, 0x172, 5, (void *)state[2]);
            } else {
                func_ov259_020cd3c4(owner, 0x172, 4, (void *)state[2]);
            }
            func_01ffa724(seg.radius, &away, &away);
            VEC_Add(&away, &push, &away);
            func_ov107_020c0b90(*(int *)(*state + 0x394), mode, *(Vec3 *)(hits[i] + 0x74), 0);
            *((u8 *)state + 0x38) |= bit;
        }
    }
}
