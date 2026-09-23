/* Shockwave tick of an ov260 part: the +0x40 timer accumulates the frame rate; for 0x440 a box at
 * the +0x34 point (rest axes, extent growing to 3.0 over the run, flagged) is swept for hits
 * (020d0e14); after that the next move is 0 and the node ends. */
typedef struct { int x, y, z; } Vec3;
struct BoxQuery {
    Vec3 vCenter;
    Vec3 vAxisX;
    Vec3 vAxisZ;
    Vec3 vAxisY;
    int nExtent;
    int bFlag;
};

extern int func_ov260_020d0e14(int *state, void *sphere, void *cyl);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;

void func_ov260_020d16e4(int *node)
{
    int *state = (int *)node[1];
    struct BoxQuery box;

    state[0x10] += *(int *)(node[0] + 0x2c);
    if (state[0x10] <= 0x440) {
        box.vCenter = *(Vec3 *)(state + 0xd);
        box.nExtent = (state[0x10] * 3 << 12) / 0x440;
        box.vAxisX = data_02042270;
        box.vAxisZ = data_02042258;
        box.vAxisY = data_02042264;
        box.bFlag = 1;
        func_ov260_020d0e14(state, 0, &box);
        return;
    }
    *(signed char *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
