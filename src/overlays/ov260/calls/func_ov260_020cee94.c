/* Big stomp tick of the ov260 actor: the +0x70 timer accumulates the frame rate and the cue fires once
 * at 0x198 (020cd04c 3). For 0x550 a box at the +0x54 impact point (rest axes, extent growing to 4.0,
 * flagged) is swept for hits (020cd2a0 kind 4); once the +0x74 clock passes 0x330 up to three idle
 * shards of the fifteen at +0x434 are thrown from the impact point, fanned 4pi/15 apart, 2.0-4.0 out
 * (020d23d0). After the stomp, once the partner holds no queued move, the next move is 2 and the node
 * ends. Codegen: a signed `thrown` with the post-stomp part in an `else` (no `return` after the
 * loop) keeps the two loop tests apart (`cmp i,#15; popge; cmp thrown,#3; blt`); a `return` after the
 * loop lets mwcc merge them into `cmp; cmplt`. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
struct Ov260Shards { char pad[0x434]; int shards[15]; };
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
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern int func_02023eb4(int n);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov260_020d23d0(int shard, Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov260_020cee94(int *node)
{
    int *state = (int *)node[1];
    struct BoxQuery box;
    Mtx33 rot;
    Vec3 v;

    state[0x1c] += *(int *)(node[0] + 0x2c);
    if ((*((u8 *)state + 0x7b) & 1) == 0 && state[0x1c] >= 0x198) {
        *((u8 *)state + 0x7b) |= 1;
        func_ov260_020cd04c(*state, 3);
    }
    if (state[0x1c] <= 0x550) {
        int i;
        int thrown;

        box.vCenter = *(Vec3 *)(state + 0x15);
        box.nExtent = (state[0x1c] << 14) / 0x550;
        box.vAxisX = data_02042270;
        box.vAxisZ = data_02042258;
        box.vAxisY = data_02042264;
        box.bFlag = 1;
        func_ov260_020cd2a0(state, 4, 0, &box, 0);
        state[0x1d] += *(int *)(node[0] + 0x2c);
        if (state[0x1d] < 0x330) {
            return;
        }
        for (i = 0, thrown = 0; i < 15 && thrown < 3; i++) {
            if (*(int *)(((struct Ov260Shards *)*state)->shards[i] + 0x388) == 0) {
                int idx = ANG2IDX(i * 0xc910 / 15) * 2;

                MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
                v.z = func_02023eb4(0x2000) + 0x2000;
                v.x = 0;
                v.y = 0;
                MTX_MultVec33(&v, &rot, &v);
                VEC_Add(&v, &box.vCenter, &v);
                func_ov260_020d23d0(((struct Ov260Shards *)*state)->shards[i], &v);
                thrown++;
            }
        }
    } else {
        if (*(u8 *)(state[1] + 0xad) != 0) {
            return;
        }
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
