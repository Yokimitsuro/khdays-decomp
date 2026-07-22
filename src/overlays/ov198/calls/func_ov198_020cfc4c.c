struct vec { int x, y, z; };

extern void func_0203bc78();
extern int func_02016320();
extern void VEC_Subtract();
extern int func_01ff8d18();
extern void func_0203b9fc();
extern void func_0202f188();
extern struct vec data_02042264;
extern struct vec data_02041dc8;

void func_ov198_020cfc4c(int self, int a, int b, int c)
{
    int o = *(int *)(self + 0x84);
    int buf[12];
    struct vec tmp;
    struct vec dir;
    int n;

    func_0203bc78(self, a, b, c);

    if (func_02016320(*(int *)(self + 0x88) + 0x20, buf, 0,
                      *(unsigned int *)(o + 0x3d0)) != 0) {
        tmp = *(struct vec *)&buf[9];

        if (*(int *)(o + 0x3e4) == 0) {
            VEC_Subtract(&tmp, o + 0x3a4, o + 0x3b0);
        }

        *(struct vec *)(o + 0x3a4) = tmp;
        *(int *)(o + 0x3e4) = 0;
    }

    if (*(unsigned char *)(self + 0xad) == 0) {
        int k = *(short *)(*(int *)(self + 0x88) + 2);

        if (k != 0 && k != 1) {
            goto skip;
        }

        if (*(int *)(o + 0x3e8) != 0) {
            if (*(int *)(o + 0x394) != 0) {
                VEC_Subtract(*(int *)(o + 0x394) + 400, o + 0xb0, &dir);

                if (func_01ff8d18(&dir, &dir) <= 0x4800) {
                    *(int *)(o + 0x3bc) = *(int *)(o + 0x3bc) > 0 ? 0x244d : -0x244d;
                } else {
                    *(int *)(o + 0x3bc) = *(int *)(o + 0x3bc) > 0 ? 0x10c1 : -0x10c1;
                }
            }

            func_0203b9fc(self, 0, k, 0);

            n = *(int *)(o + 0x3bc);
            n *= -1;

            *(int *)(o + 0x3bc) = n;

            func_0202f188(o + 0x3c0, &data_02042264, n);
        }

skip:
        ;

        {
            struct vec z = data_02041dc8;

            *(struct vec *)(o + 0x3a4) = z;
            *(struct vec *)(o + 0x3b0) = z;
        }

        *(int *)(o + 0x3e4) = 1;
    }
}
