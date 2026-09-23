/* Physics tick of the ov238 actor: with a target (+0x390) its pose is the rotation from up to its
 * +0x124 normal combined with the +0x24 spin about the +0x40 axis; landed in move 2 the ground normal is
 * copied to +0x30. Its +0xf0 velocity takes the +0xc velocity, which then rests. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
typedef struct { u8 b0 : 1; } Bit0;

extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0202ef54(Quat *out, const Quat *a, const Quat *b);
extern void func_0203c9d0(void *srt, const Quat *rot);
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

void func_ov238_020d2b84(int *node)
{
    int *state = (int *)node[1];
    Quat tilt;
    Quat spin;

    if (*(int *)(*state + 0x390) != 0) {
        func_0202f188(&spin, (Vec3 *)(state + 0x10), state[9]);
        func_0202ed60(&tilt, &data_02042264, (Vec3 *)(*state + 0x124));
        func_0202ef54(&tilt, &tilt, &spin);
        func_0203c9d0((void *)(*state + 0xa0), &tilt);
    }
    if (*(signed char *)(*state + 0x1c6) == 2 && ((Bit0 *)(*state + 0x17a))->b0) {
        *(Vec3 *)(state + 0xc) = *(Vec3 *)(*state + 0x124);
    }
    {
        Vec3 *vel = (Vec3 *)(state + 3);

        *(Vec3 *)(*state + 0xf0) = *vel;
        *vel = data_02041dc8;
    }
}
