/* Message handler of the ov032 enemy (and its byte-identical twins). While the +0x2644 item
 * has no owner, messages 3/0xf (and 0xe for a bit-36 actor) are forced to 0x21 unless bit 8 of
 * +0x464 holds. 0x21 raises bit 1 of the +0x2c30 flags, clears bit 32, tells the slot callback
 * 0x1b (bit 2 of +0x24) or 0x1c and hands over to the charge tick. 0x25 arms a 0x1d000 timer
 * and animation frame, tells 0x2f, asks the +0x668 handler whether the shot fires (bit 49,
 * animation restart, bit 1 of +0x464 on the local session) and then shares 0x22's body: the
 * hover step, 0x2f told only for 0x22 itself, the +0x4b0 fall speed (0x480 in 60 Hz frames,
 * else 0x300), the +0x2e7c/+0x2e80 pair cleared and, for 0x22 with a target, the node turned
 * to face it unless locked. 0x23 tells 0x31 and hands over to the fire attempt; 0x24 sets the
 * +0x64 halfword to 0x1800, tells 0x30 (+0x2e78 set) or 0x32 and hands over to the shot. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

struct ActorBits {
    unsigned char bUnk0 : 1;
    unsigned char bFired : 1;
};

extern int func_02023c40(void);                                                /* frame-rate flag, 1 when running 60Hz */
extern void func_01fff774(void *animation, int track, int frame);              /* Anim_SetFrameWrapped */
extern void func_0202af1c(int *p);
extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */
extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Atan2(int x, int z);
extern void func_ov032_020b413c(void);
extern void func_ov032_020b4f24(void);
extern void func_ov032_020b552c(void);
extern void func_ov032_020b51a8(void);

void *func_ov032_020b3698(char *self, int msg)
{
    void *next = 0;
    int force = 0;
    Vec3 d;
    u16 a;
    unsigned int *node;

    if (*(unsigned char *)(*(char **)(self + 0x2000 + 0x644) + 0x18) == 0) {
        if (msg == 3 || msg == 0xf ||
            (msg == 0xe && (*(unsigned long long *)(self + 0x464) & 0x1000000000ULL) != 0)) {
            force = 1;
        }
    }
    if (force != 0 && (*(unsigned long long *)(self + 0x464) & 0x100) == 0) {
        msg = 0x21;
    }
    switch (msg - 0x21) {
    case 0:
        *(unsigned char *)(self + 0x2000 + 0xc30) |= 2;
        *(unsigned long long *)self &= ~0x100000000ULL;
        next = (void *)&func_ov032_020b413c;
        if ((*(int *)(self + 0x24) & 4) != 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x1b);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x1c);
        }
        break;
    case 4:
        *(int *)(self + 0x7b0) = 0x1d000;
        *(int *)(self + 0x4cc) = 0x1d000;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        func_01fff774(*(char **)(self + 0x20) + 4, 0, 0x1d000);
        ((struct ActorBits *)(self + 0x694))->bFired = (*(int (**)(char *))(self + 0x668))(self);
        if (((struct ActorBits *)(self + 0x694))->bFired) {
            *(unsigned long long *)self |= 0x2000000000000ULL;
            if ((**(int **)(self + 0x20) & 0x20) == 0) {
                func_0202af1c(*(int **)(self + 0x20) + 1);
            }
            if (func_02030788() == 0) {
                *(unsigned long long *)(self + 0x464) |= 2ULL;
            }
        }
        /* fall through */
    case 1:
        next = (void *)&func_ov032_020b4f24;
        if (msg == 0x22) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        }
        *(int *)(self + 0x4b0) = func_02023c40() == 1 ? 0x480 : 0x300;
        *(int *)(self + 0x2000 + 0xe7c) = 0;
        *(int *)(self + 0x2000 + 0xe80) = 0;
        if (func_ov022_020ad114(self) != 0 && msg != 0x25) {
            VEC_Subtract(func_ov022_020ad0c0(self), (Vec3 *)(self + 0x8c + 0x400), &d);
            if (VEC_Mag(&d) != 0) {
                func_01ff8d18(&d, &d);
            }
            a = (u16)FX_Atan2(-d.x, -d.z);
            node = *(unsigned int **)(self + 0x20);
            if ((*node & 0x20) == 0) {
                *(u16 *)((char *)node + 0x80) = a + 0x8000;
                *(u16 *)((char *)node + 4) |= 0x20;
            }
        }
        break;
    case 2:
        next = (void *)&func_ov032_020b552c;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x31);
        break;
    case 3:
        *(u16 *)(self + 0x64) = 0x1800;
        next = (void *)&func_ov032_020b51a8;
        if (*(int *)(self + 0x2000 + 0xe78) != 0) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x32);
        }
        break;
    }
    return next;
}
