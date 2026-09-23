/* Burst of the ov248 enemy: effects 9 and 3 (flag 1), 4 (flag 2) and 5 spawn at
 * the owner's +0x494 contact point, reaction 0x146 mode 0xa fires at the +0xc position, the +0x4c
 * timer and the +0x61/+0x62 flags reset and the tick hands over to func_ov248_020cf450. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov248_020cf450(int *node);

void func_ov248_020cf33c(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c0b90(*state, 9, *(Vec3 *)(*state + 0x494), 1);
    func_ov107_020c0b90(*state, 3, *(Vec3 *)(*state + 0x494), 1);
    func_ov107_020c0b90(*state, 4, *(Vec3 *)(*state + 0x494), 2);
    func_ov107_020c0b90(*state, 5, *(Vec3 *)(*state + 0x494), 0);
    func_ov107_020c5af8(*state, 0x146, 0xa, (void *)state[3]);
    state[0x13] = 0;
    *((unsigned char *)state + 0x61) = 0;
    *((unsigned char *)state + 0x62) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov248_020cf450);
}
