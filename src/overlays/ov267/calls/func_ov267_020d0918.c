/* Message hook of the ov267 enemy, receiving side of func_ov212_020cd2a0. A
 * kind-0 message (ignored while +0x50 is 1) hands each of the sixteen +0x38c items the grab flag
 * at 0x24 (bit 1 of its +0x5c); every free item takes the 0x26 height into +0x54 and its 9-byte
 * slot from 0x28: the packed position (three big-endian signed 24-bit values) into +0x40 and the
 * packed tip, whose unit direction from the position orients the item's +0x30 pose (0202ed60
 * against data_02042258). A kind-5 message builds a transform at the packed position (bytes
 * 5..0xd) and, by byte 3, spawns into the +0x60c pair table: slots 0/1 effect 0x17 scaled 1.2
 * (flag 1/3), slots 3/8 effect 5 and slot 7 effect 0x15 with byte 4 as flag; slots 2/4 anchor
 * effect 0x15 on the +0x54c pose (looping in slot 2), slot 5 effect 5 there, slots 6/9 effect 5 on
 * the +0x520 pose. The base hook always runs. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { int w[11]; } SrtTransform;
typedef union { int words[3]; u8 bytes[12]; } Packed;
struct Pair { int res; int handle; };
struct b2 { int b0 : 1, b1 : 1; };
struct Items { char pad[0x38c]; char *items[16]; };
struct Ov267 { char pad[0x60c]; struct Pair pairs[10]; };

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *forward, const Vec3 *direction);
extern void func_0203c9d0(void *pose, const Quat *q);
extern void func_0203c960(SrtTransform *t);
extern void func_0203ca30(SrtTransform *t, const Vec3 *pos);
extern void func_0203ca9c(SrtTransform *t, int scale);
extern int func_ov107_020c0794(int model, int res, int kind, u8 flag, SrtTransform *t);
extern int func_ov107_020c09a0(int model, int res, int kind, void *at, u8 flag, int loop);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);
extern const Vec3 data_02042258;

void func_ov267_020d0918(char *self, u8 *msg, int arg)
{
    Vec3 w;
    Quat q;
    SrtTransform t;
    Vec3 v;
    Packed packedA;
    Packed packedB;
    Packed packedC;
    Packed packedD;
    int i;
    char *item;
    u8 *slot;

    if (msg[2] == 0) {
        if (*(int *)(self + 0x50) != 1) {
            slot = msg;
            for (i = 0; i < 16; i++) {
                item = ((struct Items *)self)->items[i];
                ((struct b2 *)(item + 0x5c))->b1 = msg[0x24];
                if (((struct b2 *)(item + 0x5c))->b1 == 0) {
                    *(int *)(item + 0x54) = *(short *)(msg + 0x26);
                    packedA.bytes[3] = slot[0x28];
                    packedA.bytes[2] = slot[0x29];
                    packedA.bytes[1] = slot[0x2a];
                    *(int *)(item + 0x40) = packedA.words[0] >> 8;
                    packedA.bytes[7] = slot[0x2b];
                    packedA.bytes[6] = slot[0x2c];
                    packedA.bytes[5] = slot[0x2d];
                    *(int *)(item + 0x44) = packedA.words[1] >> 8;
                    packedA.bytes[11] = slot[0x2e];
                    packedA.bytes[10] = slot[0x2f];
                    packedA.bytes[9] = slot[0x30];
                    *(int *)(item + 0x48) = packedA.words[2] >> 8;
                    packedB.bytes[3] = slot[0x31];
                    packedB.bytes[2] = slot[0x32];
                    packedB.bytes[1] = slot[0x33];
                    w.x = packedB.words[0] >> 8;
                    packedB.bytes[7] = slot[0x34];
                    packedB.bytes[6] = slot[0x35];
                    packedB.bytes[5] = slot[0x36];
                    w.y = packedB.words[1] >> 8;
                    packedB.bytes[11] = slot[0x37];
                    packedB.bytes[10] = slot[0x38];
                    packedB.bytes[9] = slot[0x39];
                    w.z = packedB.words[2] >> 8;
                    VEC_Subtract(&w, (Vec3 *)(item + 0x40), &w);
                    func_01ff8d18(&w, &w);
                    func_0202ed60(&q, &data_02042258, &w);
                    func_0203c9d0(item + 0x30, &q);
                    packedC.bytes[3] = slot[0x28];
                    packedC.bytes[2] = slot[0x29];
                    packedC.bytes[1] = slot[0x2a];
                    *(int *)(item + 0x40) = packedC.words[0] >> 8;
                    packedC.bytes[7] = slot[0x2b];
                    packedC.bytes[6] = slot[0x2c];
                    packedC.bytes[5] = slot[0x2d];
                    *(int *)(item + 0x44) = packedC.words[1] >> 8;
                    packedC.bytes[11] = slot[0x2e];
                    packedC.bytes[10] = slot[0x2f];
                    packedC.bytes[9] = slot[0x30];
                    *(int *)(item + 0x48) = packedC.words[2] >> 8;
                }
                slot += 9;
            }
        }
    } else if (msg[2] == 5) {
        packedD.bytes[3] = msg[5];
        packedD.bytes[2] = msg[6];
        packedD.bytes[1] = msg[7];
        v.x = packedD.words[0] >> 8;
        packedD.bytes[7] = msg[8];
        packedD.bytes[6] = msg[9];
        packedD.bytes[5] = msg[0xa];
        v.y = packedD.words[1] >> 8;
        packedD.bytes[11] = msg[0xb];
        packedD.bytes[10] = msg[0xc];
        packedD.bytes[9] = msg[0xd];
        v.z = packedD.words[2] >> 8;
        func_0203c960(&t);
        func_0203ca30(&t, &v);
        switch (msg[3]) {
        case 0:
        case 1:
            func_0203ca9c(&t, 0x1333);
            ((struct Ov267 *)self)->pairs[msg[3]].handle =
                func_ov107_020c0794(*(int *)(self + 0x3c), ((struct Ov267 *)self)->pairs[msg[3]].res, 0x17,
                                    msg[3] == 0 ? 1 : 3, &t);
            break;
        case 3:
        case 8:
            ((struct Ov267 *)self)->pairs[msg[3]].handle =
                func_ov107_020c0794(*(int *)(self + 0x3c), ((struct Ov267 *)self)->pairs[msg[3]].res, 5, msg[4], &t);
            break;
        case 7:
            ((struct Ov267 *)self)->pairs[msg[3]].handle =
                func_ov107_020c0794(*(int *)(self + 0x3c), ((struct Ov267 *)self)->pairs[msg[3]].res, 0x15, msg[4], &t);
            break;
        case 2:
        case 4:
            ((struct Ov267 *)self)->pairs[msg[3]].handle =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov267 *)self)->pairs[msg[3]].res, 0x15,
                                    self + 0x54c, msg[4], msg[3] == 2 ? 1 : 0);
            break;
        case 5:
            ((struct Ov267 *)self)->pairs[msg[3]].handle =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov267 *)self)->pairs[msg[3]].res, 5,
                                    self + 0x54c, msg[4], 0);
            break;
        case 6:
            ((struct Ov267 *)self)->pairs[msg[3]].handle =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov267 *)self)->pairs[msg[3]].res, 5,
                                    self + 0x520, msg[4], 0);
            break;
        case 9:
            ((struct Ov267 *)self)->pairs[msg[3]].handle =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov267 *)self)->pairs[msg[3]].res, 5,
                                    self + 0x520, msg[4], 0);
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
