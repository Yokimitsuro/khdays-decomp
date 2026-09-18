/* Hover step of the ov045 enemy (x4: ov045/064/083/100): on the local player both 64-bit flag
 * words at +0x464 and +0x46c get bit 16; a zero motion sample is folded into the position at
 * +0x498 (in the air bit 7 of +0x24 is dropped, bit 46 raised and the vertical speed cleared);
 * the effect spawner runs with the heading at +0x2aba, the actor's hook decides bit 1 of +0x694
 * (becoming active raises bit 49, shows the node and, for the local player, sets bit 1 of
 * +0x464), a hit (bit 1 of +0x18) latches the rig's +0x2f08 marker, and an active enemy with a
 * busy emitter and no marker either hands over to state 0x21 once (busy effect context, latched
 * at +0x2f04) or ends the hover: bit 49 dropped, node hidden, animation set 0xf000 before its
 * end, bit 29 raised; otherwise it stops, raises bit 2 and lands (state 0 with the slot
 * callback when grounded, else state 2). */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

extern int func_02030788(void);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov083_020b9364(char *self, int dt);
extern void func_0202af1c(void *node);                                          /* SceneNode_Enable */
extern void func_0202af2c(void *node);                                          /* SceneNode_Disable */
extern int func_ov022_02095524(char *emitter);
extern int func_ov022_02095554(char *context);
extern int func_0202aef8(void *animation, int track);                         /* Anim_GetLengthQ12 */
extern void func_01fff774(void *animation, int track, int frame);              /* Anim_SetFrameWrapped */
extern void *func_ov022_020a35f4(char *self, int state);
extern char *data_ov083_020b9b00;

void *func_ov083_020b8d18(char *self)
{
    Vec3 sample;
    Vec3 step;
    void *next = 0;
    char *rig = data_ov083_020b9b00 + 0xdf0 + 0x2000;
    int r;
    unsigned int *node;
    int len;

    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(unsigned long long *)(self + 0x46c) |= 0x10000;
    }
    sample.z = 0;
    sample.y = 0;
    sample.x = 0;
    if ((*(int *)(self + 0x24) & 4) == 0) {
        *(int *)(self + 0x24) &= ~0x80;
        *(unsigned long long *)self |= 0x400000000000ULL;
        *(int *)(self + 0x58) = 0;
    }
    step = sample;
    step.y = 0;
    VEC_Add((Vec3 *)(self + 0x98 + 0x400), &step, (Vec3 *)(self + 0x98 + 0x400));
    func_ov083_020b9364(self, *(short *)(self + 0x2aba));
    r = (*(int (**)(char *))(self + 0x668))(self);
    ((Flags *)(self + 0x694))->b1 = (unsigned char)r;
    if (((Flags *)(self + 0x694))->b1) {
        *(unsigned long long *)self |= 0x2000000000000ULL;
        node = *(unsigned int **)(self + 0x20);
        if ((*node & 0x20) == 0) {
            func_0202af1c(node + 1);
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x464) |= 2;
        }
    }
    if ((*(u16 *)(self + 0x18) & 2) == 2) {
        *(int *)(rig + 0x118) = 1;
    }
    if (((Flags *)(self + 0x694))->b1) {
        if (func_ov022_02095524(self + 0x2f8 + 0x2000) != 0 && *(int *)(rig + 0x118) == 0) {
            if (func_ov022_02095554(self + 0x2f8 + 0x2000) != 0 && *(int *)(rig + 0x114) == 0) {
                *(int *)(rig + 0x114) = 1;
                next = func_ov022_020a35f4(self, 0x21);
            } else {
                len = func_0202aef8(*(char **)(self + 0x20) + 4, 0) - 0xf000;
                *(unsigned long long *)self &= ~0x2000000000000ULL;
                node = *(unsigned int **)(self + 0x20);
                if ((*node & 0x20) == 0) {
                    func_0202af2c(node + 1);
                }
                func_01fff774(*(char **)(self + 0x20) + 4, 0, len);
                *(int *)(self + 0x7b0) = len;
                *(unsigned long long *)self |= 0x20000000;
            }
        } else {
            *(int *)(self + 0x4a0) = 0;
            *(int *)(self + 0x49c) = 0;
            *(int *)(self + 0x498) = 0;
            *(int *)(self + 0x6a0) = 0;
            *(int *)(self + 0x69c) = 0;
            *(int *)(self + 0x698) = 0;
            *(unsigned long long *)self |= 4;
            if ((*(int *)(self + 0x24) & 4) != 0) {
                (*(void (**)(char *, int))(self + 0x664))(self, 0);
                next = func_ov022_020a35f4(self, 0);
            } else {
                next = func_ov022_020a35f4(self, 2);
            }
        }
    }
    return next;
}
