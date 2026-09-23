/* Physics tick of the ov146 actor: with no current move the +0xc velocity rests; the velocity is
 * mirrored to the actor's +0xf0 and then damped for the frame in 0x88-sized slices, by 0.08 per slice
 * on the ground (+0x17a bit 0) and 0.02 in the air. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 b0 : 1; } Bit0;

extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern const Vec3 data_02041dc8;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov146_020ceaf0(int *node)
{
    int *state = (int *)node[1];
    int remaining;

    if (*(signed char *)(*state + 0x1c6) == -1) {
        *(Vec3 *)(state + 3) = data_02041dc8;
    }
    *(Vec3 *)(*state + 0xf0) = *(Vec3 *)(state + 3);
    for (remaining = *(int *)(node[0] + 0x2c); remaining > 0; remaining -= 0x88) {
        if (((Bit0 *)(*state + 0x17a))->b0) {
            func_01ffa724(0x1000 - FX_MUL(FX_Inv(remaining <= 0x88 ? remaining : 0x88, 0x88), 0x148),
                          (Vec3 *)(state + 3), (Vec3 *)(state + 3));
        } else {
            func_01ffa724(0x1000 - FX_MUL(FX_Inv(remaining <= 0x88 ? remaining : 0x88, 0x88), 0x52),
                          (Vec3 *)(state + 3), (Vec3 *)(state + 3));
        }
    }
}
