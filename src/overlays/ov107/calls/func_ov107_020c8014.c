typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

struct Obj {
    u16 flags00;
    u8 pad02[0xae];
    VecFx32 pos_b0;
    u8 pad_bc[0xf0];
    u16 field_1ac;
    u8 pad_1ae[0x16];
    u8 field_1c4;
    u8 field_1c5;
    u8 pad_1c6[0xa];
    int field_1d0;
    u8 pad_1d4[0x44];
    s16 field_218;
    u8 pad_21a[0xd6];
    int field_2f0;
};

struct HitPacket {
    u32 flags00;
    VecFx32 normal;
    u32 field10;
    u32 field14;
    u32 field18;
    u32 field1c;
    u32 field20;
    u32 field24;
    u32 field28;
};

extern int func_ov107_020c518c(void *a, void *b);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
extern void func_01ffa724(int factor, VecFx32 *src, VecFx32 *dst);
extern int func_ov107_020c5cfc(void *obj, int param, struct HitPacket *packet);

int func_ov107_020c8014(struct Obj *a, struct Obj *b)
{
    u16 flagsA;
    u16 flagsB;

    if (func_ov107_020c518c(a, b) != 0) {
        flagsA = a->flags00;
        flagsB = b->flags00;

        if ((flagsA & 0x80) == 0 || (flagsB & 0x80) == 0) {
            if ((flagsA & 0x80) != 0 && (flagsB & 0x40) != 0) {
        if (b->field_2f0 == 0 &&
            b->field_1d0 != 0 &&
            (b->field_1ac & 7) == 0 &&
            (b->field_1c4 & 4) != 0) {
            VecFx32 deltaA;

            VEC_Subtract(&a->pos_b0, &b->pos_b0, &deltaA);
            func_01ff8d18(&deltaA, &deltaA);
            func_01ffa724(0x800, &deltaA, &deltaA);
            struct HitPacket packetA = {0};

            func_01ffa724(-0x1000, &deltaA, &deltaA);
            packetA.flags00 = (u16)(packetA.flags00 & 0xffff0000 | 4 | 0x2000);
            packetA.normal = deltaA;
            packetA.field10 = (u16)packetA.field10;
            packetA.field14 = packetA.field14 & 0xffff0000 | 0xffff;
            packetA.field18 = 0;
            func_ov107_020c5cfc(b, 0, &packetA);
            b->field_1c5 &= ~4;
        }
            } else if ((flagsA & 0x40) != 0 && (flagsB & 0x80) != 0) {
        if (a->field_2f0 == 0 &&
            a->field_1d0 != 0 &&
            (a->field_1ac & 7) == 0 &&
            (a->field_1c4 & 4) != 0) {
            VecFx32 deltaB;

            VEC_Subtract(&b->pos_b0, &a->pos_b0, &deltaB);
            func_01ff8d18(&deltaB, &deltaB);
            func_01ffa724(0x800, &deltaB, &deltaB);
            struct HitPacket packetB = {0};

            func_01ffa724(-0x1000, &deltaB, &deltaB);
            packetB.flags00 = (u16)(packetB.flags00 & 0xffff0000 | 4 | 0x2000);
            packetB.normal = deltaB;
            packetB.field10 = (u16)packetB.field10;
            packetB.field14 = packetB.field14 & 0xffff0000 | 0xffff;
            packetB.field18 = 0;
            func_ov107_020c5cfc(a, 0, &packetB);
            a->field_1c5 &= ~4;
        }
            } else if ((flagsA & 0x40) != 0 && (flagsB & 0x40) != 0) {
        if (a->field_2f0 != 0 ||
            b->field_2f0 != 0 ||
            a->field_1d0 == 0 ||
            (a->field_1ac & 7) != 0 ||
            b->field_1d0 == 0 ||
            (b->field_1ac & 7) != 0) {
        } else if ((a->field_1c4 & 4) != 0 ||
                   (b->field_1c4 & 4) != 0) {
            VecFx32 deltaC;

            VEC_Subtract(&a->pos_b0, &b->pos_b0, &deltaC);
            func_01ff8d18(&deltaC, &deltaC);
            func_01ffa724(0x800, &deltaC, &deltaC);
            struct HitPacket packetC = {0};

            packetC.flags00 = (u16)(packetC.flags00 & 0xffff0000 | 4 | 0x2000);
            packetC.normal = deltaC;
            if ((a->field_1c4 & 4) == 0) {
                packetC.field10 = packetC.field10 & 0xffff0000 |
                                  (u16)(a->field_218 / 10);
            }
            packetC.field10 = (u16)packetC.field10;
            packetC.field14 = packetC.field14 & 0xffff0000 | 0xffff;
            packetC.field18 = 0;
            func_ov107_020c5cfc(a, 0, &packetC);

            {
                struct HitPacket packetD = {0};

                func_01ffa724(-0x1000, &deltaC, &deltaC);
                packetD.flags00 = (u16)(packetD.flags00 & 0xffff0000 | 4 | 0x2000);
                packetD.normal = deltaC;
                if ((b->field_1c4 & 4) == 0) {
                    packetD.field10 = packetD.field10 & 0xffff0000 |
                                      (u16)(b->field_218 / 10);
                }
                packetD.field10 = (u16)packetD.field10;
                packetD.field14 = packetD.field14 & 0xffff0000 | 0xffff;
                packetD.field18 = 0;
                func_ov107_020c5cfc(b, 0, &packetD);
                a->field_1c5 &= ~4;
                b->field_1c5 &= ~4;
            }
        }
            }
        }
        return 1;
    }

    return 0;
}
