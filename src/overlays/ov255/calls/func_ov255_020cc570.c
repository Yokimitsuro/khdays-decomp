/* Update handler of the ov255 enemy (+8): the +0x3a4 part and the common update advance by dt
 * (0 while bit 1 of +0x1ac is set); the +0x3bc pose then follows the +0x3b8 part's pose, turned by
 * the rotation from data_02042270 to data_0204227c. */
typedef struct { int w[4]; } Quat;
typedef struct { int w[11]; } Srt;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9ec8(int part, int dt);
extern void func_ov107_020c6980(char *self, int dt);
extern void func_0202ed60(Quat *out, const Vec3 *a, const Vec3 *b);
extern void func_0202ef54(Quat *out, const void *a, const Quat *b);
extern void func_0203c9d0(void *srt, const Quat *q);
extern const Vec3 data_02042270;
extern const Vec3 data_0204227c;

void func_ov255_020cc570(char *self, int dt)
{
    Quat turned;
    Quat turn;

    if (*(unsigned short *)(self + 0x1ac) & 2) {
        dt = 0;
    }
    func_ov107_020c9ec8(*(int *)(self + 0x3a4), dt);
    func_ov107_020c6980(self, dt);
    *(Srt *)(self + 0x3bc) = *(Srt *)(*(int *)(self + 0x3b8) + 4);
    func_0202ed60(&turn, &data_02042270, &data_0204227c);
    func_0202ef54(&turned, self + 0x3bc, &turn);
    func_0203c9d0(self + 0x3bc, &turned);
}
