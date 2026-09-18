/* Message handler of the ov048 enemy (x4: ov048/067/086/103). 0x21 tells the slot callback 0x2f
 * and hands over to the hover step. 0x22 arms the attack: the rig's mode (+0x2f84: 2, 3 or 4)
 * picks the pattern index and duration (0x6000 / 0x15000 / 0x27000), the target is refreshed,
 * 0x33 (mode 4) or 0x32 is told, the animation is set to 0x9000, bit 29 is raised, the rig's
 * counter cleared and its speed set to 0x800 (0xc00 in hard mode, scaled by 1.2 in mode 4),
 * the fall speed to 0x180 (0x240 in hard mode), the node turns to face the target unless locked,
 * and the attack step takes over. 0x23/0x24 tell 0x31/0x30 and hand over to the landing step. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_02023c40(void);                                                /* game mode: 1 = hard */
extern void func_ov022_020a2954(char *self);
extern void func_01fff774(void *animation, int track, int frame);              /* Anim_SetFrameWrapped */
extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern int func_01ff8d18(const Vec3 *v, Vec3 *unit);
extern int FX_Atan2(int x, int z);
extern char *data_ov048_020b4b80;
extern void func_ov048_020b43a8(void);
extern void func_ov048_020b458c(void);
extern void func_ov048_020b4848(void);

void *func_ov048_020b360c(char *self, int msg)
{
    char *rig = data_ov048_020b4b80 + 0x2c + 0x2c00;
    void *next = 0;
    Vec3 d;
    u16 a;
    unsigned int *node;

    switch (msg - 0x21) {
    case 0:
        next = (void *)&func_ov048_020b43a8;
        (*(void (**)(char *, int))(self + 0x664))(self, 0x2f);
        break;
    case 1:
        next = (void *)&func_ov048_020b458c;
        switch (*(int *)(rig + 0x358)) {
        case 2:
            *(int *)(rig + 0x360) = 0;
            *(int *)(rig + 0x36c) = 0x6000;
            break;
        case 3:
            *(int *)(rig + 0x360) = 1;
            *(int *)(rig + 0x36c) = 0x15000;
            break;
        case 4:
            *(int *)(rig + 0x360) = 2;
            *(int *)(rig + 0x36c) = 0x27000;
            break;
        }
        func_ov022_020a2954(self);
        if (*(int *)(rig + 0x358) == 4) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x33);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x32);
        }
        func_01fff774(*(char **)(self + 0x20) + 4, 0, 0x9000);
        *(int *)(self + 0x7b0) = 0x9000;
        *(unsigned long long *)self |= 0x20000000;
        *(int *)(rig + 0x364) = 0;
        *(int *)(rig + 0x368) = func_02023c40() == 1 ? 0xc00 : 0x800;
        if (*(int *)(rig + 0x358) == 4) {
            *(int *)(rig + 0x368) = (int)(((long long)*(int *)(rig + 0x368) * 0x1333 + 0x800) >> 12);
        }
        *(int *)(self + 0x4b0) = func_02023c40() == 1 ? 0x240 : 0x180;
        if (func_ov022_020ad114(self) != 0) {
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
    case 3:
        next = (void *)&func_ov048_020b4848;
        if (msg == 0x24) {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x30);
        } else {
            (*(void (**)(char *, int))(self + 0x664))(self, 0x31);
        }
        break;
    }
    return next;
}
