/* Effect message hook of the ov271 enemy. A "spawned" message (kind 5) picks
 * by byte 3: slot 0 spawns pair 0 (kind 5) at the packed position (bytes 5..0xd, big-endian
 * signed 24-bit); slot 7 does the same with the transform scaled 1.5 and kind 0x15 into pair 2,
 * or pair 3 while pair 2's effect is still alive (0203c6e0); slots 1/3 enable the first (1) or the
 * two other (3) +0x390 parts (func_ov271_020d237c) and start reaction 0x161 mode 7 on the +0xa0 pose
 * into +0x3b0, slots 2/4 disable them again; slots 5/6 start modes 4/5 (looping) into +0x3b4/
 * +0x3b8. The base hook always runs. */
typedef unsigned char u8;

typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;
struct Pair { int res; int handle; };

extern void func_0203c960(SrtTransform *t);
extern void func_0203ca30(SrtTransform *t, const Vec3 *pos);
extern void func_0203ca9c(SrtTransform *t, int scale);
extern int func_ov107_020c0794(int model, int res, int kind, int zero, SrtTransform *t);
extern int func_0203c6e0(int model, int handle);
extern void func_ov271_020d237c(int part, int on);
extern int func_ov107_020cb040(char *self, int id, int mode, int flag, void *pose);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

void func_ov271_020cffe8(char *self, u8 *msg, int arg)
{
    SrtTransform transform;
    Vec3 translation;
    union {
        int words[3];
        u8 bytes[12];
    } packedA;
    union {
        int words[3];
        u8 bytes[12];
    } packedB;
    int i;

    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            func_0203c960(&transform);
            packedA.bytes[3] = msg[5];
            packedA.bytes[2] = msg[6];
            packedA.bytes[1] = msg[7];
            translation.x = packedA.words[0] >> 8;
            packedA.bytes[7] = msg[8];
            packedA.bytes[6] = msg[9];
            packedA.bytes[5] = msg[0xa];
            translation.y = packedA.words[1] >> 8;
            packedA.bytes[11] = msg[0xb];
            packedA.bytes[10] = msg[0xc];
            packedA.bytes[9] = msg[0xd];
            translation.z = packedA.words[2] >> 8;
            func_0203ca30(&transform, &translation);
            (*(struct Pair **)(self + 0x3a4))[0].handle =
                func_ov107_020c0794(*(int *)(self + 0x3c), (*(struct Pair **)(self + 0x3a4))[0].res, 5, 0, &transform);
            break;
        case 7:
            func_0203c960(&transform);
            func_0203ca9c(&transform, 0x1800);
            packedB.bytes[3] = msg[5];
            packedB.bytes[2] = msg[6];
            packedB.bytes[1] = msg[7];
            translation.x = packedB.words[0] >> 8;
            packedB.bytes[7] = msg[8];
            packedB.bytes[6] = msg[9];
            packedB.bytes[5] = msg[0xa];
            translation.y = packedB.words[1] >> 8;
            packedB.bytes[11] = msg[0xb];
            packedB.bytes[10] = msg[0xc];
            packedB.bytes[9] = msg[0xd];
            translation.z = packedB.words[2] >> 8;
            func_0203ca30(&transform, &translation);
            if (func_0203c6e0(*(int *)(self + 0x3c), (*(struct Pair **)(self + 0x3a4))[2].handle) == 0) {
                (*(struct Pair **)(self + 0x3a4))[2].handle =
                    func_ov107_020c0794(*(int *)(self + 0x3c), (*(struct Pair **)(self + 0x3a4))[2].res, 0x15, 0, &transform);
            } else {
                (*(struct Pair **)(self + 0x3a4))[3].handle =
                    func_ov107_020c0794(*(int *)(self + 0x3c), (*(struct Pair **)(self + 0x3a4))[3].res, 0x15, 0, &transform);
            }
            break;
        case 1:
            func_ov271_020d237c(*(int *)(self + 0x390), 1);
            *(int *)(self + 0x3b0) = func_ov107_020cb040(self, 0x161, 7, 0, self + 0xa0);
            break;
        case 2:
            func_ov271_020d237c(*(int *)(self + 0x390), 0);
            break;
        case 3:
            for (i = 1; i < 3; i++) {
                func_ov271_020d237c(((int *)(self + 0x390))[i], 1);
            }
            *(int *)(self + 0x3b0) = func_ov107_020cb040(self, 0x161, 7, 0, self + 0xa0);
            break;
        case 4:
            for (i = 1; i < 3; i++) {
                func_ov271_020d237c(((int *)(self + 0x390))[i], 0);
            }
            break;
        case 5:
            *(int *)(self + 0x3b4) = func_ov107_020cb040(self, 0x161, 4, 1, self + 0xa0);
            break;
        case 6:
            *(int *)(self + 0x3b8) = func_ov107_020cb040(self, 0x161, 5, 1, self + 0xa0);
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
