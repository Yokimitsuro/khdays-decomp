/* Shed entry of the ov252 actor: when no armour piece is picked the next move is 4; otherwise pose
 * 0x13 plays, the part takes motion 0xc, the owner plays effect 4 at the origin, +0x60 clears and the
 * node moves on to 020d0480. */
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;
struct Ov252Pieces { char pad[0x4f4]; int shapes[4]; };

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov252_020d0480(void);
extern const Vec3 data_02041dc8;

void func_ov252_020d03b0(int *node)
{
    int *state = (int *)node[1];
    int i;

    for (i = 3; i >= 0; i--) {
        if (((B8 *)(((struct Ov252Pieces *)*state)->shapes[i] + 8))->f & 1) {
            break;
        }
    }
    if (i >= 4) {
        *(unsigned char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    } else {
        func_ov107_020c9264(*state, 0x13, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x574), 0xc, 0);
        func_ov107_020c0b90(*state, 4, data_02041dc8, 0);
        state[0x18] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d0480);
    }
}
