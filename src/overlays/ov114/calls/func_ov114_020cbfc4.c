/* Constructor of the ov114 enemy: installs the handlers (+8 tick, +0xc draw, +0x1c/+0x20
 * message pair, +0x30 hit callback, +0x1d0 on-hit, +0x1e0 release, +0x1dc finish, +0x34 tick),
 * seeds the +0x64 pose (scale 0x800, y 0x800) and bit 4 of +0x1ae, builds the primary item from
 * pool entry 0 (subscribed, its +4 placement lifted by 0x100), the two sub-items of the
 * overlay's kind pair in a fresh 16-byte slot table (+0x394, attached, bit 1 on their +0x5c),
 * configures action 2 (mode 2, rate 0x1000) and creates two placements from the actor's +0x64
 * pose: +0x388 on the +0x22c list and +0x38c on the +0x144 list; sound 0x112 is loaded. */
typedef unsigned short u16;

struct Ov114Kinds {
    int a;
    int b;
};

struct Ov114SubitemSlot {
    void *subitem;
    int pad;
};

extern struct Ov114Kinds data_ov114_020cdfb4;
extern void func_ov114_020cc184(void);
extern void func_ov114_020cc1c4(void);
extern void func_ov114_020cc284(void);
extern void func_ov114_020cc220(void);
extern void func_ov114_020cc444(void);
extern void func_ov114_020cc490(void);
extern void func_ov114_020cc68c(void);
extern void func_ov114_020cc398(void);
extern void func_ov114_020cc3c8(void);
extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203ca14();
extern void func_0203bfb4();
extern void *func_0203d15c();
extern void func_ov107_020c9074();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern int func_ov107_020c319c();
extern void func_0203355c();

void func_ov114_020cbfc4(int param)
{
    struct Ov114Kinds kinds;
    int i;

    kinds = data_ov114_020cdfb4;
    *(void **)(param + 0x08) = func_ov114_020cc184;
    *(void **)(param + 0x0c) = func_ov114_020cc1c4;
    *(void **)(param + 0x1c) = func_ov114_020cc284;
    *(void **)(param + 0x20) = func_ov114_020cc220;
    *(void **)(param + 0x30) = func_ov114_020cc444;
    *(void **)(param + 0x1d0) = func_ov114_020cc490;
    *(void **)(param + 0x1e0) = func_ov114_020cc68c;
    *(void **)(param + 0x1dc) = func_ov114_020cc398;
    *(void **)(param + 0x34) = func_ov114_020cc3c8;
    *(int *)(param + 0x70) = 0x800;
    *(int *)(param + 0x64) = 0;
    *(int *)(param + 0x68) = 0x800;
    *(int *)(param + 0x6c) = 0;
    *(u16 *)(param + 0x100 + 0xae) |= 0x10;
    {
        int *self = (int *)param;
        ((void **)self)[0xe1] = func_0203b898(func_ov107_020c9440(self, 0));
        func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
        func_0203ca14((char *)((void **)self)[0xe1] + 4, 0, 0x100, 0);
        ((void **)self)[0xe5] = func_0203d15c(0x10);
        for (i = 0; i < 2; i++) {
            ((struct Ov114SubitemSlot *)((void **)self)[0xe5])[i].subitem =
                func_0203b898(func_ov107_020c9440(self, ((int *)&kinds)[i]));
            func_ov107_020c9074(self,
                ((struct Ov114SubitemSlot *)((void **)self)[0xe5])[i].subitem);
            *(int *)((char *)((struct Ov114SubitemSlot *)
                ((void **)self)[0xe5])[i].subitem + 0x5c) |= 2;
        }
        func_ov107_020c92b0(self, 2, 2, 0, 0x1000);
        ((void **)self)[0xe2] = func_01fffca8(self + 0x8b, 0x10, 100);
        *((int **)self)[0xe2] = func_ov107_020c319c(self + 0x19);
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            self[0xe3] = *p = func_ov107_020c319c(self + 0x19);
        }
        func_0203355c(0x112);
    }
}
