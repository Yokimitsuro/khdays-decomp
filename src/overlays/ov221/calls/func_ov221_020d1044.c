/* Sub-state script of the ov221 enemy: runs while the +0x40c script id is the current sub-state and
 * none is pending. The +0x404 timer accumulates the node's rate; without the +0x408 hold it fires
 * reaction 0x12a at the +0xb0 point in mode 4 at 0x220, 5 at 0x1d38 and 0x12 at 0x1fe0 (bits 0/2/3
 * of +0x400), clears bit 6 of the +0x60 high byte past 0x1e48, and once past 0x600 with the owner
 * grounded (+0x17a bit 0) it lands (bit 7): the +0x410 point takes the +0x180 point lowered by the
 * +0x80 radius, a 5/6 message with that point is broadcast, effect 9 spawns at the origin and
 * +0x41c/+0x420 clear. When the rig is free and either held or grounded, func_ov221_020d0fcc (with
 * the +0x408 hold) finishes the script. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
struct Bits17a { u8 b0 : 1; };
struct hw60 { unsigned short lo : 8, hi : 8; };

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern void func_ov107_020c5af8(char *owner, int id, int mode, void *at);
extern void func_02031384(int to, void *msg, int size);
extern void func_ov107_020c0b90(char *actor, int a, Vec3 v, int b);
extern void func_ov221_020d0fcc(char *self, int hold);
extern const Vec3 data_02041dc8;

void func_ov221_020d1044(char *self, int *node)
{
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;

    if (*(signed char *)(self + 0x40c) == -1) {
        return;
    }
    if (*(signed char *)(self + 0x40c) != *(signed char *)(self + 0x100 + 0xc6)
        || *(signed char *)(self + 0x100 + 0xc7) != -1) {
        return;
    }
    *(int *)(self + 0x404) += *(int *)(*node + 0x2c);
    if (*(int *)(self + 0x408) == 0) {
        if ((*(u8 *)(self + 0x400) & 1) == 0 && *(int *)(self + 0x404) >= 0x220) {
            *(u8 *)(self + 0x400) |= 1;
            func_ov107_020c5af8(self, 0x12a, 4, self + 0xb0);
        }
        if ((*(u8 *)(self + 0x400) & 4) == 0 && *(int *)(self + 0x404) >= 0x1d38) {
            *(u8 *)(self + 0x400) |= 4;
            func_ov107_020c5af8(self, 0x12a, 5, self + 0xb0);
        }
        if ((*(u8 *)(self + 0x400) & 8) == 0 && *(int *)(self + 0x404) >= 0x1fe0) {
            *(u8 *)(self + 0x400) |= 8;
            func_ov107_020c5af8(self, 0x12a, 0x12, self + 0xb0);
        }
        if (*(int *)(self + 0x404) >= 0x1e48) {
            ((struct hw60 *)(self + 0x60))->hi &= ~0x40;
        }
        if (*(int *)(self + 0x404) >= 0x600 && (*(u8 *)(self + 0x400) & 0x80) == 0
            && ((struct Bits17a *)(self + 0x17a))->b0 != 0) {
            *(Vec3 *)(self + 0x410) = *(Vec3 *)(self + 0x180);
            *(int *)(self + 0x414) -= *(int *)(self + 0x80);
            {
            Cmd14 msg;
            u16 *p = (u16 *)&msg;

            p[0] = 0;
            p[1] = 0;
            p[2] = 0;
            p[3] = 0;
            p[4] = 0;
            p[5] = 0;
            p[6] = 0;
            p[0] = *(u16 *)(self + 2);
            ((u8 *)p)[2] = 5;
            ((u8 *)p)[3] = 6;
            PACK(msg, scratchX, *(Fx32 *)(self + 0x410), 5);
            PACK(msg, scratchY, *(Fx32 *)(self + 0x414), 8);
            PACK(msg, scratchZ, *(Fx32 *)(self + 0x418), 11);
            msg.flag = 0;
            func_02031384(1, &msg, 0xe);
            }
            func_ov107_020c0b90(self, 9, data_02041dc8, 1);
            *(int *)(self + 0x41c) = 0;
            *(u8 *)(self + 0x420) = 0;
            *(u8 *)(self + 0x400) |= 0x80;
        }
    }
    if (*(u8 *)(*(int *)(self + 0x384) + 0xad) != 0) {
        return;
    }
    if (*(int *)(self + 0x408) == 0 && ((struct Bits17a *)(self + 0x17a))->b0 == 0) {
        return;
    }
    func_ov221_020d0fcc(self, *(int *)(self + 0x408));
}
