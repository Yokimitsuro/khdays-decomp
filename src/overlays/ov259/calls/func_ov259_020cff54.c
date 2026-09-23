/* Sequence tick of the ov259 actor: the +0x68 timer accumulates the frame rate; with more than one
 * target in range (020cdc20) the aim is refreshed (020cdcac) and the +0x14 velocity doubles. The
 * +0x98 step fires the rig's four sweeps (020d1700 on the +0x384 body) at 0xb28 / 0x1298 / 0x18f8
 * / 0x1ed0, the last one lifted 1.25 (data_ov259_020d2f78), queueing +0x420 = 4 each time (the last
 * also +0x94 = 200 and +0x424); step 4 moves the node on to 020d02b8. Otherwise +0x94 grades the
 * target count against the actor's +0x80 range (100 / 10 / 2), and the six +0xac flags pulse the
 * cue (020cd2c8, alternating 0 / 1) at 0x550, 0xaa0, 0xff0, 0x1430, 0x17e8 and 0x1ed0. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern int func_ov259_020cdc20(int *node);
extern void func_ov259_020cdcac(int *node);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov259_020d1700(int body, int a, int b, Vec3 lift);
extern void func_ov259_020cd2c8(int actor, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020d02b8(void);
extern const Vec3 data_02041dc8;
extern const Vec3 data_ov259_020d2f78;

void func_ov259_020cff54(int *node)
{
    int *state = (int *)node[1];
    int n;

    state[0x1a] += *(int *)(node[0] + 0x2c);
    n = func_ov259_020cdc20(node);
    if (n > 1) {
        func_ov259_020cdcac(node);
        func_01ffa724(0x2000, (Vec3 *)(state + 5), (Vec3 *)(state + 5));
    }
    switch (state[0x26]) {
    case 0:
        if (state[0x1a] > 0xb28) {
            func_ov259_020d1700(*(int *)(*state + 0x384), 0xb28 - 0x660, 0x770, data_02041dc8);
            *(int *)(*state + 0x420) = 4;
            state[0x26]++;
        }
        break;
    case 1:
        if (state[0x1a] > 0x1298) {
            func_ov259_020d1700(*(int *)(*state + 0x384), 0x3b8, 0x660, data_02041dc8);
            *(int *)(*state + 0x420) = 4;
            state[0x26]++;
        }
        break;
    case 2:
        if (state[0x1a] > 0x18f8) {
            func_ov259_020d1700(*(int *)(*state + 0x384), 0x3b8, 0x5d8, data_02041dc8);
            *(int *)(*state + 0x420) = 4;
            state[0x26]++;
        }
        break;
    case 3:
        if (state[0x1a] > 0x1ed0) {
            func_ov259_020d1700(*(int *)(*state + 0x384), 0x3b8, 0xe58, data_ov259_020d2f78);
            *(int *)(*state + 0x420) = 4;
            state[0x25] = 200;
            *(int *)(*state + 0x424) = 1;
            state[0x26]++;
        }
        break;
    case 4:
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020d02b8);
        return;
    }
    if (n < *(int *)(*state + 0x80) * 4) {
        state[0x25] = 100;
    } else if (n < *(int *)(*state + 0x80) * 6) {
        state[0x25] = 10;
    } else {
        state[0x25] = 2;
    }
    if ((*((u8 *)state + 0xac) & 1) == 0 && state[0x1a] >= 0x550) {
        *((u8 *)state + 0xac) |= 1;
        func_ov259_020cd2c8(*state, 0);
    }
    if ((*((u8 *)state + 0xac) & 2) == 0 && state[0x1a] >= 0xaa0) {
        *((u8 *)state + 0xac) |= 2;
        func_ov259_020cd2c8(*state, 1);
    }
    if ((*((u8 *)state + 0xac) & 4) == 0 && state[0x1a] >= 0xff0) {
        *((u8 *)state + 0xac) |= 4;
        func_ov259_020cd2c8(*state, 0);
    }
    if ((*((u8 *)state + 0xac) & 8) == 0 && state[0x1a] >= 0x1430) {
        *((u8 *)state + 0xac) |= 8;
        func_ov259_020cd2c8(*state, 1);
    }
    if ((*((u8 *)state + 0xac) & 0x10) == 0 && state[0x1a] >= 0x17e8) {
        *((u8 *)state + 0xac) |= 0x10;
        func_ov259_020cd2c8(*state, 0);
    }
    if ((*((u8 *)state + 0xac) & 0x20) == 0 && state[0x1a] >= 0x1ed0) {
        *((u8 *)state + 0xac) |= 0x20;
        func_ov259_020cd2c8(*state, 1);
    }
}
