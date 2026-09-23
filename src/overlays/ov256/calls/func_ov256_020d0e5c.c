/* Shockwave tick: the part's +0x5c bit 1 clears and the +0x18 timer accumulates the frame rate.
 * Until 1/6, while the owner (+4) is active (+0x50 == 1), two volumes at the +0xc point sweep the
 * actor list on its behalf: a 58.0-high, 0.19-thick vertical segment (kind 5) and a flat 5.0 x 0.19
 * x 5.0 box (kind 1); every entity whose +2 id bit is clear in the +0x1c mask and that accepts the
 * zero push gets its bit set. Once the part's rig is idle (+0xad), the owner's +0x4b0 slot clears
 * and the node is released (0203c640). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;
typedef struct { Vec3 center; Vec3 axisX; Vec3 axisY; Vec3 axisZ; int nExtentX; int nExtentY; int nExtentZ; } Box;

extern const Vec3 data_02042264;
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;
extern const Vec3 data_02041dc8;
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern int func_ov107_020c8df0(int owner, Box *box, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, const Vec3 *push, int z);
extern void func_0203c640(int *node);

void func_ov256_020d0e5c(int *node)
{
    int *state = (int *)node[1];
    int hits[4];
    Segment seg;
    Box box;
    Vec3 up;
    int i;
    int n;

    *(int *)(*state + 0x5c) &= ~2;
    state[6] += *(int *)(node[0] + 0x2c);
    if (state[6] < 0x2a8 && *(int *)(state[1] + 0x50) == 1) {
        seg.p0 = *(Vec3 *)(state + 3);
        up = data_02042264;
        seg.dir = up;
        seg.nRadius = 0x300;
        seg.nLength = 0x3a000;
        box.center = *(Vec3 *)(state + 3);
        box.axisX = data_02042270;
        box.axisY = up;
        box.axisZ = data_02042258;
        box.nExtentY = 0x300;
        box.nExtentX = 0x2800;
        box.nExtentZ = 0x2800;
        n = func_ov107_020c8f44(state[1], &seg, hits);
        for (i = 0; i < n; i++) {
            u8 bit = 1 << *(u16 *)(hits[i] + 2);

            if ((*((u8 *)state + 0x1c) & bit) != 0) {
                continue;
            }
            if (func_ov107_020ca918(hits[i], state[1], state[1], 5, &data_02041dc8, 0) != 0) {
                *((u8 *)state + 0x1c) |= bit;
            }
        }
        n = func_ov107_020c8df0(state[1], &box, hits);
        for (i = 0; i < n; i++) {
            u8 bit = 1 << *(u16 *)(hits[i] + 2);

            if ((*((u8 *)state + 0x1c) & bit) != 0) {
                continue;
            }
            if (func_ov107_020ca918(hits[i], state[1], state[1], 1, &data_02041dc8, 0) != 0) {
                *((u8 *)state + 0x1c) |= bit;
            }
        }
    }
    if (*(u8 *)(*state + 0xad) != 0) {
        return;
    }
    *(int *)(state[1] + 0x4b0) = 0;
    func_0203c640(node);
}
