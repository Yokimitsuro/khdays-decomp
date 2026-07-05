extern void MTX_RotY33_();
extern void func_01ffa724();
extern void MTX_MultVec33();
extern void VEC_Add();
extern void func_01ff8d18();
extern int func_01ff8e94();
extern int func_0202a818();
extern void func_ov063_020b6434();
extern void func_ov063_020b647c();
extern void func_ov063_020b6844();
extern void func_ov063_020b6968();
extern short data_0203d210[];
extern int data_02041dc8;

struct Vec3 { int x; int y; int z; };

int func_ov063_020b64f4(char *owner, char *ent, int delta)
{
    char *cfg = *(char **)(owner + 0xdb4);
    int ret = 1;
    int vec[6];
    int mtx[9];

    *(int *)(ent + 0x130) += delta;

    switch (*(unsigned char *)(ent + 0x12c)) {
    case 0:
        ret = 0;
        break;
    case 1:
        *(unsigned short *)(ent + 0x15e) += *(unsigned short *)(owner + 0x10);
        if (*(int *)(ent + 0x130) >= *(int *)(ent + 0x134)) {
            *(unsigned char *)(ent + 0x12c) = 3;
            *(int *)(ent + 0x130) = 0;
        }
        break;
    case 3:
    {
        int a;
        vec[0] = 0;
        vec[1] = 0;
        vec[2] = 0x1000;
        *(unsigned short *)(ent + 0x15e) += *(unsigned short *)(owner + 0x10);
        a = *(unsigned short *)(ent + 0x15e) >> 4;
        MTX_RotY33_(mtx, -data_0203d210[a * 2], -data_0203d210[a * 2 + 1]);
        func_01ffa724(0x1800, vec, vec);
        MTX_MultVec33(vec, mtx, vec);
        VEC_Add(vec, cfg + 0x48c, &vec[3]);
        func_ov063_020b6968(&vec[3], owner, ent, &vec[3], &data_02041dc8, 0);
        *(struct Vec3 *)(ent + 0xa4) = *(struct Vec3 *)&vec[3];
        func_01ff8d18(vec, vec);
        if (func_0202a818(ent, delta) != 0 && *(short *)(ent + 2) == 0) {
            if (*(int *)(cfg + 0x6bc) != 0x30)
                func_ov063_020b6434(ent);
            else
                func_ov063_020b647c(ent, 1);
        }
        if (*(int *)(ent + 0x130) >= 0xc000)
            func_ov063_020b6844(owner, ent, ent + 0xa4, vec);
        if (*(int *)(cfg + 0x7b0) >= 0x4b000 || *(int *)(cfg + 0x6bc) != 0x30) {
            *(struct Vec3 *)(ent + 0x13c) = *(struct Vec3 *)&vec[3];
            MTX_MultVec33(ent + 0x148, mtx, vec);
            func_01ff8d18(vec, ent + 0x148);
            func_01ffa724(*(int *)(ent + 0x158), ent + 0x148, ent + 0x148);
            *(unsigned char *)(ent + 0x12c) = 4;
            *(int *)(ent + 0x130) = 0;
        }
        break;
    }
    case 4:
        func_ov063_020b6844(owner, ent, ent + 0xa4, ent + 0x148);
        if (*(unsigned char *)(ent + 0x12c) == 4) {
            func_ov063_020b6968(&vec[3], owner, ent, ent + 0xa4, ent + 0x148, 1);
            *(struct Vec3 *)(ent + 0xa4) = *(struct Vec3 *)&vec[3];
            if (func_0202a818(ent, delta) != 0 && *(short *)(ent + 2) == 0)
                func_ov063_020b647c(ent, 1);
        }
        if (func_01ff8e94(ent + 0x13c, &vec[3]) > *(int *)(ent + 0x154)
            || *(unsigned char *)(ent + 0x12c) != 4)
            func_ov063_020b6434(ent);
        break;
    case 5:
        if (func_0202a818(ent, delta) != 0) {
            ret = 0;
            *(unsigned char *)(ent + 0x12c) = 0;
            *(int *)(ent + 0x130) = 0;
        }
        break;
    }
    return ret;
}
