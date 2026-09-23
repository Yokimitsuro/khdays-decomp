/* Lunge sequence tick of the ov259 actor: the +0x68 timer accumulates the frame rate; with no
 * target in range (020cdc20) the x / z velocity stops, and the aim is refreshed (020cdcac). The +0x98
 * step fires the body sweeps (020d1700, +0x420 = 5): at 0x550 and 0xaa0 flat, at 0x1100 lifted 0.375
 * after facing the +8 track (+0x78 / +0x7c heading), at 0x17e8 dropped 0.375 while an idle +0x388
 * helper (+0x388 clear) is launched along the heading (020d26e0). Past step 3, once the +4 item's
 * +0xad byte clears, the actor faces the track again and, by the target count against its +0x80
 * range, goes to move 0x12 (over 12x) or 0x10 (over 5x) or plays pose 0x15 with a lifted sweep
 * (+0x420 = 6, +0x424) and restarts via 020d0b6c. The six +0xac flags pulse the cue (020cd2c8 0, 1,
 * 0, 1, 2, 3) at 0x550, 0x7f8, 0xaa0, 0xff0, 0x1298 and 0x1a90. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;

extern int func_ov259_020cdc20(int *node);
extern void func_ov259_020cdcac(int *node);
extern void func_ov259_020d1700(int body, int a, int b, Vec3 lift);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int y);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0202f384(Vec3 *out, const Quat *q, const Vec3 *in);
extern void func_ov259_020d26e0(int helper, int climb, Vec3 *dir, int heading);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd524(int *node, int pose, int mode);
extern void func_ov259_020cd2c8(int actor, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020d0b6c(void);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;
extern const Vec3 data_02042258;
extern const Vec3 data_ov259_020d2f60;
extern const Vec3 data_ov259_020d2f6c;
extern const Vec3 data_ov259_020d2f84;

void func_ov259_020d06b0(int *node)
{
    int *state = (int *)node[1];
    int n;

    state[0x1a] += *(int *)(node[0] + 0x2c);
    n = func_ov259_020cdc20(node);
    func_ov259_020cdcac(node);
    if (n <= 0) {
        state[5] = 0;
        state[7] = 0;
    }
    switch (state[0x26]) {
    case 0:
        if (state[0x1a] > 0x550) {
            func_ov259_020d1700(*(int *)(*state + 0x384), 0x330, 0x550, data_02041dc8);
            *(int *)(*state + 0x420) = 5;
            state[0x26]++;
        }
        break;
    case 1:
        if (state[0x1a] > 0xaa0) {
            func_ov259_020d1700(*(int *)(*state + 0x384), 0x2a8, 0x660, data_02041dc8);
            *(int *)(*state + 0x420) = 5;
            state[0x26]++;
        }
        break;
    case 2:
        if (state[0x1a] > 0x1100) {
            Vec3 d;

            VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(*state + 0x74), &d);
            func_01ff8d18(&d, &d);
            state[0x1e] = state[0x1f] = func_020050b4(d.x, d.z);
            func_ov259_020d1700(*(int *)(*state + 0x384), 0x198, 0x6e8, data_ov259_020d2f6c);
            *(int *)(*state + 0x420) = 5;
            state[0x26]++;
        }
        break;
    case 3:
        if (state[0x1a] > 0x17e8) {
            Vec3 lift = data_ov259_020d2f84;
            int helper = *(int *)(*state + 0x388);

            if (*(int *)(helper + 0x388) == 0) {
                Vec3 dir;
                Quat q;

                func_0202f188(&q, &data_02042264, state[0x1e]);
                func_0202f384(&dir, &q, &data_02042258);
                func_ov259_020d26e0(helper, state[4], &dir, state[0x1e]);
            }
            func_ov259_020d1700(*(int *)(*state + 0x384), 0x198, 0x440, lift);
            *(int *)(*state + 0x420) = 5;
            state[0x26]++;
        }
        break;
    default:
        if (*(u8 *)(state[1] + 0xad) == 0) {
            Vec3 lift = data_ov259_020d2f60;
            Vec3 d;

            VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(*state + 0x74), &d);
            func_01ff8d18(&d, &d);
            state[0x1e] = state[0x1f] = func_020050b4(d.x, d.z);
            if (n > *(int *)(*state + 0x80) * 12) {
                *(signed char *)(*state + 0x1c7) = 0x12;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            if (n > *(int *)(*state + 0x80) * 5) {
                *(signed char *)(*state + 0x1c7) = 0x10;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
            func_ov107_020c9264(*state, 0x15, 0);
            func_ov259_020cd524(node, 0x15, 0);
            func_ov259_020d1700(*(int *)(*state + 0x384), 0x2a8, 0x7f8, lift);
            *(int *)(*state + 0x420) = 6;
            *(int *)(*state + 0x424) = 1;
            *((u8 *)state + 0xac) = 0;
            state[0x1a] = 0;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020d0b6c);
            return;
        }
        break;
    }
    if ((*((u8 *)state + 0xac) & 1) == 0 && state[0x1a] >= 0x550) {
        *((u8 *)state + 0xac) |= 1;
        func_ov259_020cd2c8(*state, 0);
    }
    if ((*((u8 *)state + 0xac) & 2) == 0 && state[0x1a] >= 0x7f8) {
        *((u8 *)state + 0xac) |= 2;
        func_ov259_020cd2c8(*state, 1);
    }
    if ((*((u8 *)state + 0xac) & 4) == 0 && state[0x1a] >= 0xaa0) {
        *((u8 *)state + 0xac) |= 4;
        func_ov259_020cd2c8(*state, 0);
    }
    if ((*((u8 *)state + 0xac) & 8) == 0 && state[0x1a] >= 0xff0) {
        *((u8 *)state + 0xac) |= 8;
        func_ov259_020cd2c8(*state, 1);
    }
    if ((*((u8 *)state + 0xac) & 0x10) == 0 && state[0x1a] >= 0x1298) {
        *((u8 *)state + 0xac) |= 0x10;
        func_ov259_020cd2c8(*state, 2);
    }
    if ((*((u8 *)state + 0xac) & 0x20) == 0 && state[0x1a] >= 0x1a90) {
        *((u8 *)state + 0xac) |= 0x20;
        func_ov259_020cd2c8(*state, 3);
    }
}
