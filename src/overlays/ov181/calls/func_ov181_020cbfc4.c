/* Constructor of the ov181 enemy (x4: ov181/182/183/184): installs the handlers (+8 tick, +0xc
 * draw, +0x20/+0x1c message pair, +0x30 hit callback, +0x1e0 release, +0x1d0 on-hit, +0x1dc
 * finish), seeds the +0x64 pose (scale 0xe00, y 0xe00) and bit 4 of +0x1ae, builds the primary
 * item from pool entry 0 (its +4 placement lifted by 0x80, subscribed), keeps the "B_Move"
 * motion handle (+0x390), the three sub-items of kinds 2/3/4 in a fresh 24-byte slot table
 * (+0x398, attached, bit 1 on their +0x5c), configures action 2 (mode 2, rate 0x3000) and
 * creates two placements from the actor's +0x64 pose: +0x388 on the +0x22c list and +0x38c on
 * the +0x144 list; sound 0x131 is loaded. */
typedef unsigned short u16;

struct Ov181Vec3 {
    int x;
    int y;
    int z;
};

struct Ov181SubitemSlot {
    void *subitem;
    int pad;
};

extern struct Ov181Vec3 data_ov181_020ce9f8;
extern const char data_ov181_020cea4c[];

extern void func_ov181_020cc190(void);
extern void func_ov181_020cc1d8(void);
extern void func_ov181_020cc278(void);
extern void func_ov181_020cc2dc(void);
extern void func_ov181_020cc400(void);
extern void func_ov181_020cc69c(void);
extern void func_ov181_020cc44c(void);
extern void func_ov181_020cc248(void);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203ca14();
extern void func_0203bfb4();
extern void *func_ov107_020c9e50();
extern void *func_0203d15c();
extern void func_ov107_020c9074();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern int func_ov107_020c319c();
extern void func_0203355c();

void func_ov181_020cbfc4(int param)
{
    struct Ov181Vec3 kinds;
    int i;

    kinds = data_ov181_020ce9f8;

    *(void **)(param + 0x08) = func_ov181_020cc190;
    *(void **)(param + 0x0c) = func_ov181_020cc1d8;
    *(void **)(param + 0x20) = func_ov181_020cc278;
    *(void **)(param + 0x1c) = func_ov181_020cc2dc;
    *(void **)(param + 0x30) = func_ov181_020cc400;
    *(void **)(param + 0x1e0) = func_ov181_020cc69c;
    *(void **)(param + 0x1d0) = func_ov181_020cc44c;
    *(void **)(param + 0x1dc) = func_ov181_020cc248;

    *(int *)(param + 0x70) = 0xe00;
    *(int *)(param + 0x64) = 0;
    *(int *)(param + 0x68) = 0xe00;
    *(int *)(param + 0x6c) = 0;
    *(u16 *)(param + 0x100 + 0xae) |= 0x10;

    {
        int *self = (int *)param;

        ((void **)self)[0xe1] = func_0203b898(func_ov107_020c9440(self, 0));
        func_0203ca14((char *)((void **)self)[0xe1] + 4, 0, 0x80, 0);
        func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
        ((void **)self)[0xe4] = func_ov107_020c9e50(func_ov107_020c9440(self, 1), data_ov181_020cea4c);
        ((void **)self)[0xe6] = func_0203d15c(0x18);

        for (i = 0; i < 3; i++) {
            ((struct Ov181SubitemSlot *)((void **)self)[0xe6])[i].subitem =
                func_0203b898(func_ov107_020c9440(self, ((int *)&kinds)[i]));
            func_ov107_020c9074(self,
                ((struct Ov181SubitemSlot *)((void **)self)[0xe6])[i].subitem);
            *(int *)((char *)((struct Ov181SubitemSlot *)
                ((void **)self)[0xe6])[i].subitem + 0x5c) |= 2;
        }

        func_ov107_020c92b0(self, 2, 2, 0, 0x3000);

        ((void **)self)[0xe2] = func_01fffca8(self + 0x8b, 0x10, 100);
        *((int **)self)[0xe2] = func_ov107_020c319c(self + 0x19);
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            self[0xe3] = *p = func_ov107_020c319c(self + 0x19);
        }
        func_0203355c(0x131);
    }
}
