/* Brain start of the ov235 enemy: sub-state 0 with none pending, the +0x1c and +0x2c orientations
 * reset to the identity quaternion, the +4/+8/+0xc shortcuts point at the owner's +0x74 point,
 * +0xb0 point and its rig's +0xad busy byte, +0x88 is set, and the three slots get their ticks
 * (1: func_ov235_020cd4d4, 0: func_ov235_020cd1f0, 2: func_ov235_020cd3f8). */
typedef struct { int w[4]; } Quat;

extern void func_0203c634(int *node, int slot, void *cb);
extern const Quat data_020420f8;
extern void func_ov235_020cd4d4(int *node);
extern void func_ov235_020cd1f0(int *node);
extern void func_ov235_020cd3f8(int *node);

void func_ov235_020cd140(int *node)
{
    int *state = (int *)node[1];

    *(unsigned char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    *(Quat *)(state + 7) = data_020420f8;
    *(Quat *)(state + 0xb) = *(Quat *)(state + 7);
    state[1] = *state + 0x74;
    state[2] = *state + 0xb0;
    state[3] = *(int *)(*state + 0x384) + 0xad;
    state[0x22] = 1;
    func_0203c634(node, 1, (void *)func_ov235_020cd4d4);
    func_0203c634(node, 0, (void *)func_ov235_020cd1f0);
    func_0203c634(node, 2, (void *)func_ov235_020cd3f8);
}
