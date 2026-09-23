/* Summon tick: the +0x44 timer accumulates the frame rate. At 0x660 (once, +0x70 bit 0) the
 * actor's +0x3dc target is refreshed (020cab14) and, when there is one, the first idle one of the
 * ten +0x4ac helpers (+0x390 clear) is launched (020d2a5c) from the +0x40c part's +0x14 point
 * towards the target's +0x74 position jittered by up to +-1/16 on x and z. Once the +4 item's
 * +0xad byte clears the +0x40 count grows; while a helper is idle and fewer than 12 were summoned
 * pose 0x17 plays and the actor is knocked back in place (mode 7) to repeat; otherwise pose 0x18
 * plays, the +0x3e4 shape gains bit 1, +0x50 takes the track height and +0x54 the rise to route
 * point 0xb, and the node moves on to 020d08ec. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;
struct Items4ac { char pad[0x4ac]; int item[10]; };

extern int func_ov107_020cab14(int obj, int kind);
extern int func_02023eb4(int n);
extern void func_ov254_020d2a5c(int helper, void *from, Vec3 *to);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_ov254_020cd840(int *state, int a);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020d08ec(void);
extern const Vec3 data_02041dc8;

void func_ov254_020d06d0(int *node)
{
    int *state = (int *)node[1];
    Vec3 to;
    int i;
    int idle;
    int j;

    state[0x11] += *(int *)(node[0] + 0x2c);
    if ((*((u8 *)state + 0x70) & 1) == 0 && state[0x11] >= 0x660) {
        *((u8 *)state + 0x70) |= 1;
        *(int *)(*state + 0x3dc) = func_ov107_020cab14(*state, 0);
        if (*(int *)(*state + 0x3dc) != 0) {
            to = *(Vec3 *)(*(int *)(*state + 0x3dc) + 0x74);
            j = func_02023eb4(0x201) - 0x100;
            to.x += j;
            j = func_02023eb4(0x201) - 0x100;
            to.z += j;
            for (i = 0; i < 10; i++) {
                if (*(int *)(((struct Items4ac *)*state)->item[i] + 0x390) == 0) {
                    func_ov254_020d2a5c(((struct Items4ac *)*state)->item[i],
                                        (void *)(*(int *)(*state + 0x40c) + 0x14), &to);
                    break;
                }
            }
        }
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    idle = 0;
    for (i = 0; i < 10; i++) {
        if (*(int *)(((struct Items4ac *)*state)->item[i] + 0x390) == 0) {
            idle = 1;
            break;
        }
    }
    state[0x10]++;
    if (idle && state[0x10] < 0xc) {
        func_ov107_020c9264(*state, 0x17, 0);
        func_ov107_020c0b90(*state, 7, data_02041dc8, 0);
        state[0x11] = 0;
        *((u8 *)state + 0x70) = 0;
        return;
    }
    func_ov107_020c9264(*state, 0x18, 0);
    ((B8 *)(*(int *)(*state + 0x3e4) + 8))->f |= 2;
    state[0x11] = 0;
    *((u8 *)state + 0x70) = 0;
    state[0x14] = *(int *)(state[2] + 4);
    state[0x15] = func_ov254_020cd840(state, 0xb) - state[0x14];
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d08ec);
}
