/* Sweep tick of an ov259 helper for 0xaa0 of its +0x34 timer: a box around it (centre 0.1875 above
 * its +0x74 position, axes from the rest frame and the +0x124 ground normal, extent 7 x the elapsed
 * fraction capped at 0x2b00) collects the entities it touches. Each one not yet struck (bit
 * `1 << id` of the +0x38 mask) that takes the hit (020ca918 kind 7, push 0.375 up) knocks the +0x394
 * owner back at its position (mode 0xb), plays sound 0x172/7 at the +8 point and is marked; entities
 * no longer touched are forgotten. The +0xc velocity then clears. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct BoxQuery {
    Vec3 vCenter;
    Vec3 vAxisX;
    Vec3 vAxisZ;
    Vec3 vAxisY;
    int nExtent;
    int bFlag;
};

extern int FX_Inv(int num, int den);
extern int func_ov107_020c8fd0(int actor, struct BoxQuery *query, int *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov259_020cd3c4(int actor, int id, int variant, void *at);
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;
extern const Vec3 data_02041dc8;

void func_ov259_020d2498(int *node)
{
    int *state = (int *)node[1];
    u16 i;

    state[0xd] += *(int *)(node[0] + 0x2c);
    if (state[0xd] < 0xaa0) {
        struct BoxQuery box;
        Vec3 push;
        int hits[4];
        u8 seen;
        int extent;
        int count;

        seen = 0;
        extent = FX_Inv(state[0xd], 0x800);
        if (extent > 0x2b00) {
            extent = 0x2b00;
        }
        box.vCenter = *(Vec3 *)(*state + 0x74);
        box.vCenter.y += 0x300;
        box.vAxisX = data_02042270;
        box.vAxisZ = data_02042258;
        box.vAxisY = *(Vec3 *)(*state + 0x124);
        box.nExtent = extent * 7;
        box.bFlag = 0;
        push.x = 0;
        push.y = 0x600;
        push.z = 0;
        count = func_ov107_020c8fd0(*state, &box, hits);
        for (i = 0; i < count; i++) {
            u8 bit = 1 << *(u16 *)(hits[i] + 2);

            seen |= bit;
            if ((*((u8 *)state + 0x38) & bit) == 0 &&
                func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x394), 7, &push, 0)) {
                func_ov107_020c0b90(*(int *)(*state + 0x394), 0xb, *(Vec3 *)(hits[i] + 0x74), 0);
                func_ov259_020cd3c4(*(int *)(*state + 0x394), 0x172, 7, (void *)state[2]);
                *((u8 *)state + 0x38) |= bit;
            }
        }
        *((u8 *)state + 0x38) &= seen;
    }
    *(Vec3 *)(state + 3) = data_02041dc8;
}
