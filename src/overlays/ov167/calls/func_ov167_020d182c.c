/* Hover-hold tick of the ov166 enemy (x3: ov166/167/168). With +0x88 clear the +0x24 height
 * eases towards 2.5 (a thirtieth of the difference per tick) unless the +0x44 target height is
 * unset (INT_MAX), in which case it steps 0x200 towards the target's +0x194. The +0x74
 * orientation looks from the target's +0x74 at the +8 position (world Y up), the +0x48 timer
 * grows by dt, and the direction from the +0x390 joint's +0x14 to the target is kept. Once the
 * timer is non-negative (bit 0 of +0x84 not yet set) the actor sends a zero-vector position
 * message (cmd 8, flag 2) and sets the bit; past 0x3a70 (bit 1 not yet set) the first free
 * +0x3ac sub-item (bit 0 of its +0x60 clear) is launched by 020ce134 along that direction and
 * the bit is set. Losing the +4 item's +0xad byte requests sub-state 2 and releases the slot. */
typedef struct { int x, y, z; } Vec3;
struct vec3 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_0203cd7c(int *out, Vec3 *from, Vec3 *at, const int *up);
extern void func_0202ea48(int *quat, int *mtx);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov107_020c0b90(int obj, int cmd, struct vec3 v, int flag);
extern void func_ov167_020d1d74(int subitem, Vec3 *from, Vec3 *dir);
extern void func_0203c634(int node, int slot, void *cb);
extern int data_02042264;
extern struct vec3 data_02041dc8;

void func_ov167_020d182c(int node)
{
    int target;
    int *state = *(int **)(node + 4);
    int mtx[9];
    Vec3 dir;
    int i;

    target = state[3];
    if (state[0x22] == 0) {
        if (state[0x11] != 0x7fffffff) {
            state[9] += (0x2800 - state[0x11]) / 30;
        } else if (*(int *)(target + 0x194) < state[9]) {
            state[9] -= 0x200;
        } else {
            state[9] += 0x200;
        }
    }
    func_0203cd7c(mtx, (Vec3 *)(target + 0x74), (Vec3 *)state[2], &data_02042264);
    func_0202ea48(state + 0x1d, mtx);
    VEC_Subtract((Vec3 *)(target + 0x74), (Vec3 *)(*(int *)(*state + 0x390) + 0x14), &dir);
    func_01ff8d18(&dir, &dir);
    state[0x12] += *(int *)(*(int *)node + 0x2c);
    if ((*(unsigned char *)((char *)state + 0x84) & 1) == 0 && state[0x12] >= 0) {
        struct vec3 v = data_02041dc8;
        func_ov107_020c0b90(*state, 8, v, 2);
        *(unsigned char *)((char *)state + 0x84) |= 1;
    }
    if ((*(unsigned char *)((char *)state + 0x84) & 2) == 0 && state[0x12] >= 0x3a70) {
        for (i = 0; i < 1; i++) {
            int sub = ((int *)*state)[0xeb + i];
            if ((((struct hw60 *)(sub + 0x60))->lo & 1) == 0) {
                func_ov167_020d1d74(sub, (Vec3 *)(*(int *)(*state + 0x390) + 0x14), &dir);
                break;
            }
        }
        *(unsigned char *)((char *)state + 0x84) |= 2;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)(node + 0x20), 0);
}
