/* Side of the ov252 actor that the ground-plane vector `v` points to: 0 when it is within the facing
 * cone (turn below 0x1a87) or shorter than twice the actor's +0x80 radius, else 2 for a turn to one
 * side and 1 for the other (turn from the +0x54 heading, 0203cd20). */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern int func_020050b4(int x, int z);
extern int func_0203cd20(int c);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

u8 func_ov252_020ce42c(int *state, Vec3 v)
{
    int a = func_020050b4(v.x, v.z);
    unsigned int ia = ANG2IDX(state[0x15]);
    unsigned int im = ANG2IDX(a);
    int turn = func_0203cd20(FX_MUL(data_0203d210[im * 2], data_0203d210[ia * 2]) +
                             FX_MUL(data_0203d210[im * 2 + 1], data_0203d210[ia * 2 + 1]));
    int mag = turn < 0 ? -turn : turn;

    if (mag < 0x1a87 || (state = (int *)*state, func_01ff8d18(&v, &v) < state[0x20] * 2)) {
        return 0;
    }
    return turn >= 0 ? 2 : 1;
}
