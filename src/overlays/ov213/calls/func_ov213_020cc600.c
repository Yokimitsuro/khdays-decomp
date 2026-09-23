/* Message handler of the ov213 enemy (x2 with ov273). A kind-0 message copies its +0x24 flag into
 * bit 1 of the +0x388 tail rig's +0x5c and re-inits it. Kind-5 messages drive the +0x430 effect
 * table: 0 plays pair 0 (kind 0x17, the message's scale byte and point); 1 attaches it at +0x3f8
 * and, when the +4 target is armed (+0x40 bits 0-1), spawns slot effect 0x122/4 at the message's
 * unpacked 24-bit point, plus pair 1 when the scale byte is 1; 2 plays pair 4 (scale 2.0) and
 * raises the ground flag (020c0b14); 3 attaches pairs 5 / 6 at the +0x3f0 / +0x3f4 bones; 4 drops
 * each idle +0x3e4 child (sub-state 0) to the ground below the point at the message's per-child
 * angle and distance around the actor and runs its +0x1cc hook; 5 attaches pair 7 at the body
 * rig's +0x30; 6 plays pair 2 at the unpacked point; 7 / 9 / 8 register effect 0x122 (modes
 * 0xc / 5 / 0xa) on the +0xa0 pose into +0x424 / +0x428 / +0x42c. The base handler always runs. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[11]; } Srt;
struct Pair { int res; int handle; };
struct Bit0 { int b0 : 1; };
struct Bits5c { unsigned int b0 : 1; unsigned int b1 : 1; };
struct Bits40 { int b0 : 1; int b1 : 1; };

extern void func_0203c7ac(int item, int a);
extern int func_ov107_020c08cc(int model, int res, int kind, int arg, int scale, void *pos);
extern int func_ov107_020c09a0(int model, int res, int kind, void *at, int a, int b);
extern int func_02033d0c(int slot, int id, Vec3 *pos, u16 flags);
extern void func_ov107_020c0b14(char *self, int a);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_01fff920(int grid, Vec3 *pos, Vec3 *ray);
extern void VEC_Add(const void *a, const void *b, void *out);
extern void func_0203ca30(void *srt, Vec3 *pos);
extern void func_0203c960(Srt *srt);
extern int func_ov107_020cb040(char *self, int id, int mode, int flag, void *pose);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);
extern const short data_0203d210[];
extern const Vec3 data_02042240;

#define PAIRS (*(struct Pair **)(self + 0x430))
#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov213_020cc600(char *self, u8 *msg, int arg)
{
    Vec3 pos;
    Srt srt;
    Vec3 at;
    Vec3 ray;
    int atZ;
    int atY;
    int atX;
    int rawZ;
    int rawY;
    int rawX;
    int actor;
    int hit;
    int i;

    if (msg[2] == 0) {
        ((struct Bits5c *)(*(int *)(self + 0x388) + 0x5c))->b1 = ((struct Bit0 *)(msg + 0x24))->b0;
        func_0203c7ac(*(int *)(self + 0x388), 0);
    } else if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            PAIRS[0].handle = func_ov107_020c08cc(*(int *)(self + 0x3c), PAIRS[0].res, 0x17, msg[4], 0x1000, msg + 5);
            break;
        case 1:
            PAIRS[0].handle = func_ov107_020c09a0(*(int *)(self + 0x3c), PAIRS[0].res, 0x17, self + 0x3f8, msg[4], 0);
            if (*(int *)(self + 4) != 0 && ((struct Bits40 *)(*(int *)(self + 4) + 0x40))->b0 &&
                ((struct Bits40 *)(*(int *)(self + 4) + 0x40))->b1) {
                ((char *)&atX)[3] = msg[5];
                ((char *)&atX)[2] = msg[6];
                ((char *)&atX)[1] = msg[7];
                at.x = atX >> 8;
                ((char *)&atY)[3] = msg[8];
                ((char *)&atY)[2] = msg[9];
                ((char *)&atY)[1] = msg[10];
                at.y = atY >> 8;
                ((char *)&atZ)[3] = msg[11];
                ((char *)&atZ)[2] = msg[12];
                ((char *)&atZ)[1] = msg[13];
                at.z = atZ >> 8;
                func_02033d0c(0x122, 4, &at, 0);
            }
            if (msg[4] == 1) {
                PAIRS[1].handle = func_ov107_020c09a0(*(int *)(self + 0x3c), PAIRS[1].res, 0x17, self + 0x3f8, 0, 0);
            }
            break;
        case 2:
            PAIRS[4].handle = func_ov107_020c08cc(*(int *)(self + 0x3c), PAIRS[4].res, 0x17, 0, 0x2000, msg + 5);
            func_ov107_020c0b14(self, 1);
            break;
        case 3:
            PAIRS[5].handle = func_ov107_020c09a0(*(int *)(self + 0x3c), PAIRS[5].res, 0x17, (void *)(*(int *)(self + 0x3f0) + 4), 0, 0);
            PAIRS[6].handle = func_ov107_020c09a0(*(int *)(self + 0x3c), PAIRS[6].res, 0x17, (void *)(*(int *)(self + 0x3f4) + 4), 0, 0);
            break;
        case 4: {
            actor = *(int *)(self + 4);
            for (i = 0; i < 8; i++) {
                if (*(signed char *)((*(int **)(self + 0x3e4))[i] + 0x1c6) != 0) {
                    continue;
                }
                pos.x = *(int *)(self + 0xb0) + FX_Mul(data_0203d210[ANG2IDX(((int *)(msg + 4))[i]) * 2], ((int *)(msg + 0x24))[i]);
                pos.y = *(int *)(self + 0xb4) + 0x8000;
                pos.z = *(int *)(self + 0xb8) + FX_Mul(data_0203d210[ANG2IDX(((int *)(msg + 4))[i]) * 2 + 1], ((int *)(msg + 0x24))[i]);
                func_01ffa724(0x10000, &data_02042240, &ray);
                hit = func_01fff920(*(int *)(actor + 0x7c), &pos, &ray);
                if (hit == 0 || *(int *)(hit + 8) != 0) {
                    continue;
                }
                ray.y = (int)(((long long)*(int *)(hit + 0xc) * ray.y) >> 27);
                VEC_Add(&pos, &ray, &pos);
                pos.y += 0x100;
                func_0203ca30((void *)((*(int **)(self + 0x3e4))[i] + 0xa0), &pos);
                if (*(void (**)(int, int))((*(int **)(self + 0x3e4))[i] + 0x1cc) != 0) {
                    (*(void (**)(int, int))((*(int **)(self + 0x3e4))[i] + 0x1cc))((*(int **)(self + 0x3e4))[i], 0);
                }
            }
            break;
        }
        case 5:
            PAIRS[7].handle = func_ov107_020c09a0(*(int *)(self + 0x3c), PAIRS[7].res, 0x17, (void *)(*(int *)(self + 0x384) + 0x30), 0, 0);
            break;
        case 6: {
            func_0203c960(&srt);
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
            func_0203ca30(&srt, &pos);
            PAIRS[2].handle = func_ov107_020c08cc(*(int *)(self + 0x3c), PAIRS[2].res, 0x17, 0, 0x1000, msg + 5);
            break;
        }
        case 7:
            *(int *)(self + 0x424) = func_ov107_020cb040(self, 0x122, 0xc, 0, self + 0xa0);
            break;
        case 9:
            *(int *)(self + 0x428) = func_ov107_020cb040(self, 0x122, 5, 0, self + 0xa0);
            break;
        case 8:
            *(int *)(self + 0x42c) = func_ov107_020cb040(self, 0x122, 0xa, 0, self + 0xa0);
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
