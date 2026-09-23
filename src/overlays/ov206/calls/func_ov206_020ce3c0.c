/* Fall tick of the ov206 enemy: the +0x14 point is zeroed (data_02041dc8); until flagged
 * (+0x52) the +0x24 timer accumulates the owner's rate and past 0x666 fires reaction 0x116
 * mode 0xd at the +8 point and sets the flag. Once the +0xc idle byte is clear the owner plays
 * animation 4 (mode 1), +0x20 and the flag clear and the tick hands over to
 * func_ov206_020ce470. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov206_020ce470(int *node);
extern const Vec3 data_02041dc8;

void func_ov206_020ce3c0(int *node)
{
    int *state = (int *)node[1];

    *(Vec3 *)(state + 5) = data_02041dc8;
    if (*(unsigned char *)((char *)state + 0x52) == 0) {
        state[9] += *(int *)(node[0] + 0x2c);
        if (state[9] >= 0x666) {
            func_ov107_020c5af8(*state, 0x116, 0xd, (void *)state[2]);
            *(unsigned char *)((char *)state + 0x52) = 1;
        }
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 4, 1);
    state[8] = 0;
    *(unsigned char *)((char *)state + 0x52) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov206_020ce470);
}
