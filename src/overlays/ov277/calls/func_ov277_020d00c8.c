/* Summon tick of the ov244 enemy (x2 with ov277). Every 0x455 of the +0x20 timer (fed by the
 * owner's rate) the next of the two children listed at the owner's +0x400 (index at +0x12) is
 * woken, unless its +0x60 low byte has bit 0 set: its +0x1cc hook runs (child, 0) and it is placed (c5c54)
 * at the +0x3c8 bone's +0x14 point on the +0xc floor height, pushed 2.0 along the angle
 * index x pi. Once the +0x1c timer reaches 0x2aaa, animation 3 plays and the tick hands over to
 * func_ov277_020d0290. */
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

extern void func_ov107_020c5c54(int child, Vec3 *pos);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern void func_ov277_020d0290(int *node);

void func_ov277_020d00c8(int *node)
{
    int *state = (int *)node[1];
    Vec3 pos;
    int child;

    state[8] += *(int *)(*node + 0x2c);
    if (state[8] > 0x455) {
        state[8] = 0;
        if (*(short *)((char *)state + 0x12) < 2) {
            child = ((int *)*(int *)(*state + 0x400))[*(short *)((char *)state + 0x12)];
            if ((((struct hw60 *)(child + 0x60))->lo & 1) == 0) {
                if (*(void (**)(int, int))(child + 0x1cc) != 0) {
                    (*(void (**)(int, int))(child + 0x1cc))(child, 0);
                }
                pos = *(Vec3 *)(*(int *)(*state + 0x3c8) + 0x14);
                pos.y = *(int *)(state[3] + 4);
                pos.x += data_0203d210[ANG2IDX(*(short *)((char *)state + 0x12) * 0x6488 / 2) * 2] * 2;
                pos.z += data_0203d210[ANG2IDX(*(short *)((char *)state + 0x12) * 0x6488 / 2) * 2 + 1] * 2;
                func_ov107_020c5c54(((int *)*(int *)(*state + 0x400))[*(short *)((char *)state + 0x12)], &pos);
            }
        }
        (*(short *)((char *)state + 0x12))++;
    }
    state[7] += *(int *)(*node + 0x2c);
    if (state[7] < 0x2aaa) {
        return;
    }
    func_ov107_020c9264(*state, 3, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov277_020d0290);
}
