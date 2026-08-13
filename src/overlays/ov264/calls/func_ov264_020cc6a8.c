typedef unsigned char u8;
typedef signed char s8;

typedef struct { int x, y, z; } VecFx32;
typedef struct { int w[11]; } Srt;

extern void func_0203c960(Srt *srt);
extern void func_0203ca30(Srt *srt, const VecFx32 *t);
extern void func_0203ca9c(Srt *srt, int scale);
extern void *func_ov107_020c09a0(void *owner, void *slot, u8 flags, void *xform,
                                 int a5, int a6);
extern void *func_ov107_020c0794(void *owner, void *slot, int kind, int a4,
                                 const Srt *srt);
extern void func_ov107_020c0b14(void *self, int a2);
extern void *func_ov107_020cb040(void *self, int id, int a3, int a4, void *xform);
extern void func_ov264_020cc64c(void *self);
extern void func_ov264_020cea48(void *node, const VecFx32 *pos);
extern void func_ov107_020c7500(void *self, void *cmd, void *arg3);

void func_ov264_020cc6a8(char *self, u8 *cmd, void *arg3)
{
    int rawZ;
    int rawY;
    int rawX;
    Srt srt;
    VecFx32 pos;

    if (cmd[2] == 5) {
        ((char *)&rawX)[3] = cmd[5];
        ((char *)&rawX)[2] = cmd[6];
        ((char *)&rawX)[1] = cmd[7];
        pos.x = rawX >> 8;
        ((char *)&rawY)[3] = cmd[8];
        ((char *)&rawY)[2] = cmd[9];
        ((char *)&rawY)[1] = cmd[10];
        pos.y = rawY >> 8;
        ((char *)&rawZ)[3] = cmd[11];
        ((char *)&rawZ)[2] = cmd[12];
        ((char *)&rawZ)[1] = cmd[13];
        pos.z = rawZ >> 8;
        func_0203c960(&srt);
        func_0203ca30(&srt, &pos);
        switch (cmd[3]) {
        case 0:
            *(void **)(self + (cmd[3] << 3) + 0x444) =
                func_ov107_020c09a0(*(void **)(self + 0x3c),
                                    *(void **)(self + (cmd[3] << 3) + 0x440),
                                    0x17, self + 0x3f4, 3, 0);
            break;
        case 1:
            func_0203ca9c(&srt, 0x1000);
            *(void **)(self + (cmd[3] << 3) + 0x444) =
                func_ov107_020c0794(*(void **)(self + 0x3c),
                                    *(void **)(self + (cmd[3] << 3) + 0x440),
                                    5, 0, &srt);
            break;
        case 3:
            func_0203ca9c(&srt, 0x1000);
            *(void **)(self + (cmd[3] << 3) + 0x444) =
                func_ov107_020c0794(*(void **)(self + 0x3c),
                                    *(void **)(self + (cmd[3] << 3) + 0x440),
                                    0x15, 0, &srt);
            func_ov107_020c0b14(self, 1);
            break;
        case 2:
        case 4:
            *(void **)(self + (cmd[3] << 3) + 0x444) =
                func_ov107_020c09a0(*(void **)(self + 0x3c),
                                    *(void **)(self + (cmd[3] << 3) + 0x440),
                                    (u8)(((cmd[3] == 2) ? 0 : 4) | 1),
                                    self + 0x3c8, 0, 1);
            if (cmd[3] == 2) {
                *(void **)(self + 0x43c) =
                    func_ov107_020cb040(self, 0x15d, 5, 1, self + 0x3c8);
            }
            break;
        case 5:
            break;
        case 6:
            func_ov264_020cc64c(self);
            break;
        case 7:
            func_ov264_020cea48(*(void **)(self + 0x3c0), &pos);
            break;
        }
    }
    func_ov107_020c7500(self, cmd, arg3);
}
