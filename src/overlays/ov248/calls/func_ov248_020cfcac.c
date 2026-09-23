/* Volley tick of the ov248 actor: before the first shot the move ends (brain slot +0x20 cleared) once
 * 020cd524 reports the target out of reach. The +0x4c delay runs down at the frame rate; when it
 * expires the first idle projectile of the owner's +0x3c0 set (bit 0 of its +0x60 low byte clear) is
 * launched from the +0xc origin, 2.0 + 3/8 x shot ahead along the +0x40 heading (jittered by up to
 * 1.5 on x and z after the first shot). Eight shots, 0.19 apart, then brain slot +0x20 runs 020cfe84. */
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned short lo : 8; unsigned short hi : 8; } Flags60;
struct Ov248Owner { char pad[0x3c0]; int shots[8]; };

extern int func_ov248_020cd524(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_02023eb4(int bound);
extern void func_ov248_020d0264(int shot, Vec3 at, Vec3 dir);
extern void func_ov248_020cfe84(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov248_020cfcac(int *node)
{
    int *state = (int *)node[1];
    Vec3 pos;
    Vec3 dir;
    int i;

    if (state[0x12] == 0 && func_ov248_020cd524(node) < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if ((state[0x13] -= *(int *)(node[0] + 0x2c)) > 0) {
        return;
    }
    for (i = 0; i < 8; i++) {
        if (!(((Flags60 *)(((struct Ov248Owner *)*state)->shots[i] + 0x60))->lo & 1)) {
            {
                int idx = ANG2IDX(state[0x10]) * 2;

                dir.x = data_0203d210[idx];
                dir.y = 0;
                dir.z = data_0203d210[idx + 1];
            }
            func_01ffa724(state[0x12] * 0x18000 / 8 + 0x2000, &dir, &pos);
            VEC_Add(&pos, (Vec3 *)state[3], &pos);
            if (state[0x12] != 0) {
                int jit = func_02023eb4(0x3001) - 0x1800;

                pos.x += jit;
                pos.z += func_02023eb4(0x3001) - 0x1800;
            }
            func_ov248_020d0264(((struct Ov248Owner *)*state)->shots[i], pos, dir);
            break;
        }
    }
    if (++state[0x12] < 8) {
        state[0x13] = 0x300;
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov248_020cfe84);
}
