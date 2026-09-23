/* Dismount landing tick: the +0x78 clock accumulates the frame rate and the +0x7c phase steps at
 * 0x3aaa / 0x3bbb / 0x4666 / 0x4777 / 0x5222; each step fires reaction 0x166 at the rear rider's
 * +0x3c4 shape (mode 5, while the +0x3d2 counter is up) or the front one's +0x3c0 shape (mode 4,
 * +0x3d0), the last step both. Once the +0x20 flag byte clears the actor plays pose 0x10, a lost
 * front / rear rider is announced with the 4-byte notes at data_ov278_020d63e4 + 0x10 / + 4
 * through the actor's +0x24 hook, the +0x14 timer clears and the node moves to 020d57a4. */
typedef unsigned char u8;
typedef unsigned short u16;

struct Ov278Actor {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov278Actor *self, void *msg, int size);
};

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern u16 data_ov278_020d63e4[];
extern void func_ov278_020d5758(void);

void func_ov278_020d5494(int *node)
{
    int *state = (int *)node[1];
    u16 noteFront[2];
    u16 noteRear[2];
    u16 *pp;

    state[0x1e] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x7c) == 0 && state[0x1e] >= 0x3aaa) {
        *((u8 *)state + 0x7c) = 1;
        if (*(short *)(*state + 0x300 + 0xd2) > 0) {
            func_ov107_020c5af8(*state, 0x166, 5, (void *)(**(int **)(*state + 0x3c4) + 4));
        }
    }
    if (*((u8 *)state + 0x7c) == 1 && state[0x1e] >= 0x3bbb) {
        *((u8 *)state + 0x7c) = 2;
        if (*(short *)(*state + 0x300 + 0xd0) > 0) {
            func_ov107_020c5af8(*state, 0x166, 4, (void *)(**(int **)(*state + 0x3c0) + 4));
        }
    }
    if (*((u8 *)state + 0x7c) == 2 && state[0x1e] >= 0x4666) {
        *((u8 *)state + 0x7c) = 3;
        if (*(short *)(*state + 0x300 + 0xd2) > 0) {
            func_ov107_020c5af8(*state, 0x166, 5, (void *)(**(int **)(*state + 0x3c4) + 4));
        }
    }
    if (*((u8 *)state + 0x7c) == 3 && state[0x1e] >= 0x4777) {
        *((u8 *)state + 0x7c) = 4;
        if (*(short *)(*state + 0x300 + 0xd0) > 0) {
            func_ov107_020c5af8(*state, 0x166, 4, (void *)(**(int **)(*state + 0x3c0) + 4));
        }
    }
    if (*((u8 *)state + 0x7c) == 4 && state[0x1e] >= 0x5222) {
        *((u8 *)state + 0x7c) = 5;
        if (*(short *)(*state + 0x300 + 0xd0) > 0) {
            func_ov107_020c5af8(*state, 0x166, 4, (void *)(**(int **)(*state + 0x3c0) + 4));
        }
        if (*(short *)(*state + 0x300 + 0xd2) > 0) {
            func_ov107_020c5af8(*state, 0x166, 5, (void *)(**(int **)(*state + 0x3c4) + 4));
        }
    }
    if (*(u8 *)state[8] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x10, 0);
    if (*(short *)(*state + 0x300 + 0xd0) == 0) {
        pp = noteFront;
        pp[1] = data_ov278_020d63e4[9];
        pp[0] = data_ov278_020d63e4[8];
        if (((struct Ov278Actor *)*state)->pfnMessage != 0) {
            ((struct Ov278Actor *)*state)->pfnMessage((struct Ov278Actor *)*state, pp, 4);
        }
    }
    if (*(short *)(*state + 0x300 + 0xd2) == 0) {
        pp = noteRear;
        pp[1] = data_ov278_020d63e4[3];
        pp[0] = data_ov278_020d63e4[2];
        if (((struct Ov278Actor *)*state)->pfnMessage != 0) {
            ((struct Ov278Actor *)*state)->pfnMessage((struct Ov278Actor *)*state, pp, 4);
        }
    }
    state[5] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov278_020d5758);
}
