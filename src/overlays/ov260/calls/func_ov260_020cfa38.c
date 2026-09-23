/* Stomp tick of the ov260 actor: the +0x70 timer accumulates the frame rate and the cue fires once at
 * 0x110 (020cd04c 3). For 0x550 a box at the +0x54 impact point (rest axes, extent growing to 3.0,
 * flagged) is swept for hits (020cd2a0 kind 4). Then, once (+0x7b bit 1), the +0x78 stomp count drops
 * and while stomps remain the partner's queued move clears and the node goes back to the hop
 * (020cf17c); otherwise, once the partner holds no queued move, the next move is 2 and the node ends. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
struct BoxQuery {
    Vec3 vCenter;
    Vec3 vAxisX;
    Vec3 vAxisZ;
    Vec3 vAxisY;
    int nExtent;
    int bFlag;
};

extern void func_ov260_020cd04c(int actor, int flag);
extern void func_ov260_020cd2a0(int *state, int kind, void *sphere, void *cyl, void *seg);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020cf17c(void);
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;

void func_ov260_020cfa38(int *node)
{
    int *state = (int *)node[1];
    struct BoxQuery box;

    state[0x1c] += *(int *)(node[0] + 0x2c);
    if ((*((u8 *)state + 0x7b) & 1) == 0 && state[0x1c] >= 0x110) {
        *((u8 *)state + 0x7b) |= 1;
        func_ov260_020cd04c(*state, 3);
    }
    if (state[0x1c] <= 0x550) {
        box.vCenter = *(Vec3 *)(state + 0x15);
        box.nExtent = (state[0x1c] * 3 << 12) / 0x550;
        box.vAxisX = data_02042270;
        box.vAxisZ = data_02042258;
        box.vAxisY = data_02042264;
        box.bFlag = 1;
        func_ov260_020cd2a0(state, 4, 0, &box, 0);
    } else if ((*((u8 *)state + 0x7b) & 2) == 0) {
        *((u8 *)state + 0x7b) |= 2;
        *((signed char *)state + 0x78) -= 1;
        if (*((signed char *)state + 0x78) > 0) {
            *(u8 *)(state[1] + 0xad) = 0;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020cf17c);
            return;
        }
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
