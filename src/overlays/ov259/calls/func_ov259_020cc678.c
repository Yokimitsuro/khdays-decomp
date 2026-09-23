/* Message hook of the ov259 enemy. A kind-5 message spawns, by byte 3, into the +0x430 item/handle
 * pair table: slots 0/6/10/11 effect 7 at the packed position (bytes 5..0xd, three big-endian signed
 * 24-bit values), slots 9/12 effect 0x17 scaled 3.0 there (byte 4 as flag), slot 14 effect 0x15 into
 * pair 2 at the packed position oriented by the +0x384 body's +0x124 axis; slots 1 and 4 switch the
 * body's glow (020d1764 on / off) and anchor effect 0xf on the +0xa0 pose, slots 2/3 effect 0x15 there;
 * slots 5 and 7 anchor effects 1 / 7 on the +0x410 bone, slot 8 a looping effect 7 on the +0xa0 pose;
 * slot 15 raises the owner flag (020c0b14), and slots 16/17 hide / show the +0x390 wing rig (+0x42c).
 * The base hook always runs. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { int w[11]; } SrtTransform;
typedef union { int words[3]; u8 bytes[12]; } Packed;
struct Pair { int res; int handle; };
struct Ov259 { char pad[0x430]; struct Pair pairs[13]; };

extern void func_0202f188(Quat *q, const Vec3 *axis, int angle);
extern void func_0202ed60(Quat *out, const Vec3 *forward, const Vec3 *direction);
extern void func_0202ef54(Quat *out, const Quat *a, const Quat *b);
extern void func_0203c9d0(SrtTransform *t, const Quat *q);
extern void func_0203c960(SrtTransform *t);
extern void func_0203ca30(SrtTransform *t, const Vec3 *pos);
extern void func_0203ca9c(SrtTransform *t, int scale);
extern void func_0203ca50(void *pose, int x, int y, int z);
extern int func_ov107_020c0794(int model, int res, int kind, u8 flag, void *at);
extern int func_ov107_020c09a0(int model, int res, int kind, void *at, u8 flag, int loop);
extern void func_ov107_020c0b14(char *self, int on);
extern void func_ov259_020d1764(int body, int on);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);
extern const Vec3 data_02042264;

void func_ov259_020cc678(char *self, u8 *msg, int arg)
{
    SrtTransform t;
    Vec3 v;
    Quat spin;
    Quat q;
    Packed packedA;
    Packed packedB;
    Packed packedC;

    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
        case 6:
        case 10:
        case 11:
            packedA.bytes[3] = msg[5];
            packedA.bytes[2] = msg[6];
            packedA.bytes[1] = msg[7];
            v.x = packedA.words[0] >> 8;
            packedA.bytes[7] = msg[8];
            packedA.bytes[6] = msg[9];
            packedA.bytes[5] = msg[0xa];
            v.y = packedA.words[1] >> 8;
            packedA.bytes[11] = msg[0xb];
            packedA.bytes[10] = msg[0xc];
            packedA.bytes[9] = msg[0xd];
            v.z = packedA.words[2] >> 8;
            func_0203c960(&t);
            func_0203ca30(&t, &v);
            ((struct Ov259 *)self)->pairs[msg[3]].handle =
                func_ov107_020c0794(*(int *)(self + 0x3c), ((struct Ov259 *)self)->pairs[msg[3]].res, 7, 0, &t);
            break;
        case 1:
            func_ov259_020d1764(*(int *)(self + 0x384), 1);
            ((struct Ov259 *)self)->pairs[msg[3]].handle =
                func_ov107_020c0794(*(int *)(self + 0x3c), ((struct Ov259 *)self)->pairs[msg[3]].res, 0xf, msg[4], self + 0xa0);
            break;
        case 4:
            func_ov259_020d1764(*(int *)(self + 0x384), 0);
            ((struct Ov259 *)self)->pairs[msg[3]].handle =
                func_ov107_020c0794(*(int *)(self + 0x3c), ((struct Ov259 *)self)->pairs[msg[3]].res, 0xf, msg[4], self + 0xa0);
            break;
        case 9:
        case 12:
            func_0203c960(&t);
            func_0203ca9c(&t, 0x3000);
            packedB.bytes[3] = msg[5];
            packedB.bytes[2] = msg[6];
            packedB.bytes[1] = msg[7];
            v.x = packedB.words[0] >> 8;
            packedB.bytes[7] = msg[8];
            packedB.bytes[6] = msg[9];
            packedB.bytes[5] = msg[0xa];
            v.y = packedB.words[1] >> 8;
            packedB.bytes[11] = msg[0xb];
            packedB.bytes[10] = msg[0xc];
            packedB.bytes[9] = msg[0xd];
            v.z = packedB.words[2] >> 8;
            func_0203ca30(&t, &v);
            ((struct Ov259 *)self)->pairs[msg[3]].handle =
                func_ov107_020c0794(*(int *)(self + 0x3c), ((struct Ov259 *)self)->pairs[msg[3]].res, 0x17, msg[4], &t);
            break;
        case 2:
        case 3:
            ((struct Ov259 *)self)->pairs[msg[3]].handle =
                func_ov107_020c0794(*(int *)(self + 0x3c), ((struct Ov259 *)self)->pairs[msg[3]].res, 0x15, msg[4], self + 0xa0);
            break;
        case 14:
            packedC.bytes[3] = msg[5];
            packedC.bytes[2] = msg[6];
            packedC.bytes[1] = msg[7];
            v.x = packedC.words[0] >> 8;
            packedC.bytes[7] = msg[8];
            packedC.bytes[6] = msg[9];
            packedC.bytes[5] = msg[0xa];
            v.y = packedC.words[1] >> 8;
            packedC.bytes[11] = msg[0xb];
            packedC.bytes[10] = msg[0xc];
            packedC.bytes[9] = msg[0xd];
            v.z = packedC.words[2] >> 8;
            func_0203c960(&t);
            func_0203ca30(&t, &v);
            func_0202f188(&spin, &data_02042264, 0);
            func_0202ed60(&q, &data_02042264, (Vec3 *)(*(int *)(self + 0x384) + 0x124));
            func_0202ef54(&q, &q, &spin);
            func_0203c9d0(&t, &q);
            ((struct Ov259 *)self)->pairs[2].handle =
                func_ov107_020c0794(*(int *)(self + 0x3c), ((struct Ov259 *)self)->pairs[2].res, 0x15, msg[4], &t);
            break;
        case 5:
            ((struct Ov259 *)self)->pairs[msg[3]].handle =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov259 *)self)->pairs[msg[3]].res, 1,
                                    (void *)(*(int *)(self + 0x410) + 4), 0, 0);
            break;
        case 7:
            ((struct Ov259 *)self)->pairs[msg[3]].handle =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov259 *)self)->pairs[msg[3]].res, 7,
                                    (void *)(*(int *)(self + 0x410) + 4), 0, 0);
            break;
        case 8:
            ((struct Ov259 *)self)->pairs[msg[3]].handle =
                func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov259 *)self)->pairs[msg[3]].res, 7,
                                    self + 0xa0, 0, 1);
            break;
        case 15:
            func_ov107_020c0b14(self, 1);
            break;
        case 16:
            func_0203ca50((void *)(*(int *)(self + 0x390) + 4), 0, 0, 0);
            *(int *)(self + 0x42c) = 0;
            break;
        case 17:
            func_0203ca50((void *)(*(int *)(self + 0x390) + 4), 0x1000, 0x1000, 0x1000);
            *(int *)(self + 0x42c) = 1;
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
