/* Constructor of the ov194 enemy (x3: ov194/195/196): installs the handlers (+8 tick, +0xc
 * draw, +0x1c message, +0x30/+0x34 hit callbacks, +0x1d0 on-hit, +0x1e0 release, +0x1dc
 * finish), seeds the +0x64 pose (scale 0x1400, y 0x1400), builds the primary item from pool
 * entry 0 (subscribed), resolves its "Bone_head" (+0x394, mode 1) and "tag_00" (+0x398, mode
 * 3) joints, keeps the "move" motion handle (+0x3d0), the three sub-items of kinds 2/3/4 in a
 * fresh 24-byte slot table (+0x3d4, attached, bit 1 on their +0x5c), configures actions 0/1/2/4
 * (modes 1/1/1/1, rate 0x2851), resolves the "B" (+0x39c) and "guru0" (+0x3a0) joints of the
 * first sub-item, and creates two placements from a zero position with scale 0x10cc: +0x38c on
 * the +0x22c list and +0x390 on the +0x144 list, whose +0x20 block is kept in +0x2cc; sound
 * 0x134 is loaded. (The ov120 initializer shape: the +0x2cc store needs the tail in its own
 * block with its own `int *self` -- see func_ov120_020cbfc4.) */
struct Ov194Vec3 {
    int x;
    int y;
    int z;
};

struct Ov194Pose {
    struct Ov194Vec3 position;
    int scale;
};

struct Ov194SubitemSlot {
    void *subitem;
    int pad;
};

extern struct Ov194Vec3 data_ov196_020d67cc;
extern struct Ov194Vec3 data_02041dc8;
extern const char data_ov196_020d686c[];
extern const char data_ov196_020d6878[];
extern const char data_ov196_020d6880[];
extern const char data_ov196_020d6888[];
extern const char data_ov196_020d688c[];

extern void func_ov196_020d3ac4(void);
extern void func_ov196_020d3b0c(void);
extern void func_ov196_020d3b98(void);
extern void func_ov196_020d3e1c(void);
extern void func_ov196_020d3d20(void);
extern void func_ov196_020d3e78(void);
extern void func_ov196_020d40d4(void);
extern void func_ov196_020d3b68(void);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern char *func_0203bee8();
extern void *func_ov107_020c9e50();
extern void *func_0203d15c();
extern void func_ov107_020c9074();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern int func_ov107_020c319c();
extern void func_0203355c();

void func_ov196_020d3844(int param)
{
    struct Ov194Vec3 kinds;
    struct Ov194Pose pose;
    int i;

    kinds = data_ov196_020d67cc;

    *(void **)(param + 0x08) = func_ov196_020d3ac4;
    *(void **)(param + 0x0c) = func_ov196_020d3b0c;
    *(void **)(param + 0x1c) = func_ov196_020d3b98;
    *(void **)(param + 0x30) = func_ov196_020d3e1c;
    *(void **)(param + 0x34) = func_ov196_020d3d20;
    *(void **)(param + 0x1d0) = func_ov196_020d3e78;
    *(void **)(param + 0x1e0) = func_ov196_020d40d4;
    *(void **)(param + 0x1dc) = func_ov196_020d3b68;

    *(int *)(param + 0x70) = 0x1400;
    *(int *)(param + 0x64) = 0;
    *(int *)(param + 0x68) = 0x1400;
    *(int *)(param + 0x6c) = 0;

    {
        int *self = (int *)param;

        ((void **)self)[0xe1] = func_0203b898(func_ov107_020c9440(self, 0));
        func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
        ((void **)self)[0xe5] = func_0203bee8(self[0xe1], 1, data_ov196_020d686c);
        ((void **)self)[0xe6] = func_0203bee8(self[0xe1], 3, data_ov196_020d6878);
        ((void **)self)[0xf4] = func_ov107_020c9e50(func_ov107_020c9440(self, 1), data_ov196_020d6880);
        ((void **)self)[0xf5] = func_0203d15c(0x18);

        for (i = 0; i < 3; i++) {
            ((struct Ov194SubitemSlot *)((void **)self)[0xf5])[i].subitem =
                func_0203b898(func_ov107_020c9440(self, ((int *)&kinds)[i]));
            func_ov107_020c9074(self,
                ((struct Ov194SubitemSlot *)((void **)self)[0xf5])[i].subitem);
            *(int *)((char *)((struct Ov194SubitemSlot *)
                ((void **)self)[0xf5])[i].subitem + 0x5c) |= 2;
        }

        func_ov107_020c92b0(self, 0, 1, 0, 0x2851);
        func_ov107_020c92b0(self, 1, 1, 0, 0x2851);
        func_ov107_020c92b0(self, 2, 1, 0, 0x2851);
        func_ov107_020c92b0(self, 4, 1, 0, 0x2851);

        ((void **)self)[0xe7] = func_0203bee8(((struct Ov194SubitemSlot *)((void **)self)[0xf5])[0].subitem, 1, data_ov196_020d6888);
        ((void **)self)[0xe8] = func_0203bee8(((struct Ov194SubitemSlot *)((void **)self)[0xf5])[0].subitem, 1, data_ov196_020d688c);

        pose.position = data_02041dc8;
        pose.scale = 0x10cc;

        ((void **)self)[0xe3] = func_01fffca8(self + 0x8b, 0x10, 100);
        *((int **)self)[0xe3] = func_ov107_020c319c(&pose);
    }
    {
        int *self = (int *)param;
        int *p = func_01fffca8(self + 0x51, 4, 100);
        int resource = func_ov107_020c319c(&pose);
        *p = resource;
        self[0xe4] = resource;
        ((char **)self)[0xb3] = (char *)resource + 0x20;
        func_0203355c(0x134);
    }
}
