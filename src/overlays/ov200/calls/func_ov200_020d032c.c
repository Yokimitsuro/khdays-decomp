/* Beam state builder of the ov200 enemy (x3: ov200/ov201/ov271). Spawns the 0x54-byte beam
 * state (kind 0x64, ov200 057c) under the +0x3c list, keeps the owner at +0 and builds the
 * three beam nodes from the kinds of data_ov200_020d1844 (registered on the owner, bit 1 of
 * +0x5c raised) into +4/+8/+0xc; +0x10 takes the +0x3a4 target's +8, an 8-byte child (kind
 * 0x64, ov200 1768) at +0x30 takes the owner's +0x3a8; +0x14 keeps the beam kind, which
 * selects the two anchors +0x48/+0x4c: the +0x3a0 and +0x39c nodes' +0x14 for kind 0, the
 * +0x39c one twice for kind 1 and the +0x3a0 one twice for kind 2. */
typedef struct { int w[3]; } KindTable;

extern int func_0203c5c0(int list, int a, int size, void *cb, int flag, int *out);
extern int func_ov107_020c9440(int owner, int kind);
extern int func_0203b898(int res);
extern void func_ov107_020c9074(int owner, int obj);
extern const KindTable data_ov200_020d1844;
extern void func_ov200_020d057c(void);
extern void func_ov200_020d1768(void);

int *func_ov200_020d032c(int owner, int nKind)
{
    int *state;
    KindTable kinds;
    unsigned int i;
    int node;

    kinds = data_ov200_020d1844;
    func_0203c5c0(*(int *)(owner + 0x3c), 0x64, 0x54, (void *)func_ov200_020d057c, 0, (int *)&state);
    state[0] = owner;
    for (i = 0; i < 3; i++) {
        node = func_0203b898(func_ov107_020c9440(owner, kinds.w[i]));
        *(int *)(node + 0x5c) |= 2;
        func_ov107_020c9074(owner, node);
        switch (i) {
        case 0:
            state[1] = node;
            break;
        case 1:
            state[2] = node;
            break;
        case 2:
            state[3] = node;
            break;
        }
    }
    state[4] = *(int *)(*(int *)(state[0] + 0x3a4) + 8);
    func_0203c5c0(*(int *)(owner + 0x3c), 0x64, 8, (void *)func_ov200_020d1768, 0, state + 0xc);
    *(int *)state[0xc] = *(int *)(state[0] + 0x3a8);
    state[5] = nKind;
    switch (state[5]) {
    case 0:
        state[0x12] = *(int *)(state[0] + 0x3a0) + 0x14;
        state[0x13] = *(int *)(state[0] + 0x39c) + 0x14;
        break;
    case 2:
        state[0x13] = *(int *)(state[0] + 0x3a0) + 0x14;
        state[0x12] = state[0x13];
        break;
    case 1:
        state[0x13] = *(int *)(state[0] + 0x39c) + 0x14;
        state[0x12] = state[0x13];
        break;
    }
    return state;
}
