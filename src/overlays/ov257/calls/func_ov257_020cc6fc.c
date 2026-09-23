/* Message handler of the ov257 enemy (+0x1c). Kind-5 messages drive its effects, kept as
 * resource/handle pairs in the +0x400 table: 0 starts the wing effect on the +0x3d8 part
 * (func_ov257_020d24dc, pair 4), 1 the trail between pairs 2 and 3 on the +0x3d4 part
 * (func_ov257_020d2784), 2 stops the trail, 3/4/5 play pairs 0, 1 and 5 (kind 0x17) and 6 pair
 * 7 (kind 5) at the message point, 8 starts the partner effect (func_ov257_020d2b38, pair 9) and
 * attaches pair 6 to the +0x3d4 part, 9 and 0xa play pairs 10 and 11 (kind 5), 0xb starts pair 8
 * at the message point (func_ov257_020d2d1c, unpacked from its three 24-bit coordinates), 0xc
 * starts reaction +0x408 mode 0xd on the +0xa0 pose (+0x40c) and 0xd ends it. Every message then
 * goes to the common handler. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
struct Pair { int res; int handle; };

extern int func_ov257_020d24dc(char *self, int res, void *at);
extern int func_ov257_020d2784(char *self, int res, int res2, void *at);
extern void func_0203c650(int model, int handle);
extern int func_ov107_020c08cc(int model, int res, int kind, int arg, int scale, void *pos);
extern int func_ov107_020c09a0(int model, int res, int kind, void *at, int a, int b);
extern int func_ov257_020d2d1c(char *self, int res, Vec3 *at);
extern int func_ov257_020d2b38(char *self);
extern int func_ov107_020cb040(char *self, int id, int mode, int flag, void *pose);
extern void func_ov107_020cb100(int handle);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

#define PAIRS (*(struct Pair **)(self + 0x400))

void func_ov257_020cc6fc(char *self, u8 *msg, int arg)
{
    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            PAIRS[4].handle = func_ov257_020d24dc(self, PAIRS[4].res, (void *)(*(int *)(self + 0x3d8) + 4));
            break;
        case 1:
            PAIRS[2].handle = func_ov257_020d2784(self, PAIRS[2].res, PAIRS[3].res, (void *)(*(int *)(self + 0x3d4) + 4));
            break;
        case 2:
            if (PAIRS[2].handle != 0) {
                func_0203c650(*(int *)(self + 0x3c), PAIRS[2].handle);
                PAIRS[2].handle = 0;
            }
            break;
        case 3:
            PAIRS[0].handle = func_ov107_020c08cc(*(int *)(self + 0x3c), PAIRS[0].res, 0x17, 0, 0x1000, msg + 5);
            break;
        case 4:
            PAIRS[1].handle = func_ov107_020c08cc(*(int *)(self + 0x3c), PAIRS[1].res, 0x17, 0, 0x1000, msg + 5);
            break;
        case 5:
            PAIRS[5].handle = func_ov107_020c08cc(*(int *)(self + 0x3c), PAIRS[5].res, 0x17, 0, 0x1000, msg + 5);
            break;
        case 6:
            PAIRS[7].handle = func_ov107_020c08cc(*(int *)(self + 0x3c), PAIRS[7].res, 5, 0, 0x1000, msg + 5);
            break;
        case 8:
            PAIRS[9].handle = func_ov257_020d2b38(self);
            PAIRS[6].handle = func_ov107_020c09a0(*(int *)(self + 0x3c), PAIRS[6].res, 4, (void *)(*(int *)(self + 0x3d4) + 4), 0, 0);
            break;
        case 9:
            PAIRS[10].handle = func_ov107_020c08cc(*(int *)(self + 0x3c), PAIRS[10].res, 5, 0, 0x1000, msg + 5);
            break;
        case 10:
            PAIRS[11].handle = func_ov107_020c08cc(*(int *)(self + 0x3c), PAIRS[11].res, 5, 0, 0x1000, msg + 5);
            break;
        case 11: {
            Vec3 pos;
            int rawZ;
            int rawY;
            int rawX;

            ((char *)&rawX)[3] = msg[5];
            ((char *)&rawX)[2] = msg[6];
            ((char *)&rawX)[1] = msg[7];
            pos.x = rawX >> 8;
            ((char *)&rawY)[3] = msg[8];
            ((char *)&rawY)[2] = msg[9];
            ((char *)&rawY)[1] = msg[10];
            pos.y = rawY >> 8;
            ((char *)&rawZ)[3] = msg[11];
            ((char *)&rawZ)[2] = msg[12];
            ((char *)&rawZ)[1] = msg[13];
            pos.z = rawZ >> 8;
            PAIRS[8].handle = func_ov257_020d2d1c(self, PAIRS[8].res, &pos);
            break;
        }
        case 12:
            *(int *)(self + 0x40c) = func_ov107_020cb040(self, (short)*(int *)(self + 0x408), 0xd, 0, self + 0xa0);
            break;
        case 13:
            func_ov107_020cb100(*(int *)(self + 0x40c));
            *(int *)(self + 0x40c) = 0;
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
