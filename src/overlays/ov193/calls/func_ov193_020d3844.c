/* Big constructor of the ov193 enemy (x3: ov193/192/193): raises bit 8 of the +0 flags, installs
 * the eleven handlers (+8 tick, +0xc/+0x10 draw pair, +0x1c message, +0x28/+0x2c/+0x30/+0x34
 * hit callbacks, +0x1d0 on-hit, +0x1dc finish, +0x1e0 release), seeds the +0x64 pose
 * (scale 0xc00, y 0xc00) and bit 4 of the +0x1ae flags, builds the primary item from pool entry
 * 0, resolves the "head02" and "headcon" bones (+0x398/+0x39c), the four sub-items of kinds
 * 1/2/3/6 (+0x3a0, attached, bit 1 on their +0x5c), configures actions 0/1/2/4 with the (0, 0x400,
 * 0) offset and the 0xd99/0x6cc/0x2ecc/0x2ecc rates, then creates four placements: two on the
 * +0x144 list (+0x394 at the origin, scale 0xc00; +0x390 at y 0xc00, scale 0xc00) and two on the
 * +0x22c list (+0x38c at the origin, scale 0xa00; +0x388 at y 0x800, scale 0x800, bit 1 on its
 * +8 flags), fills the +0x3a4 table with four func_ov193_020d5a58 records and loads sound 0x133. */
typedef unsigned short u16;

struct Ov193Vec3 {
    int x;
    int y;
    int z;
};

struct Ov193Pose {
    struct Ov193Vec3 position;
    int scale;
};

struct Ov193Kinds {
    int a;
    int b;
    int c;
    int d;
};

struct Ov193SubitemSlot {
    void *subitem;
    int pad;
};

struct bf {
    unsigned b : 8;
};

extern struct Ov193Kinds data_ov193_020d69a0;
extern struct Ov193Vec3 data_ov193_020d6994;
extern const struct Ov193Vec3 data_02041dc8;
extern const char data_ov193_020d6a2c[];
extern const char data_ov193_020d6a34[];

extern void func_ov193_020d3bb4(void);
extern void WM_EndKeySharing_0x020d3e60(void);
extern void func_ov193_020d3e6c(void);
extern void func_ov193_020d3c4c(void);
extern void func_ov193_020d3de8(void);
extern void func_ov193_020d3e24(void);
extern void func_ov193_020d3ffc(void);
extern void func_ov193_020d3eb0(void);
extern void func_ov193_020d4048(void);
extern void func_ov193_020d3bfc(void);
extern void func_ov193_020d4268(void);
extern void *func_ov193_020d5a58(int *self);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern void *func_0203bee8();
extern void *func_0203d15c();
extern void func_ov107_020c9074();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern int func_ov107_020c319c();
extern void func_0203355c();

void func_ov193_020d3844(int param)
{
    struct Ov193Kinds kinds;
    struct Ov193Pose pose;
    struct Ov193Vec3 offset;
    int i;
    int resource;

    kinds = data_ov193_020d69a0;
    offset = data_ov193_020d6994;

    *(u16 *)param |= 0x100;
    *(void **)(param + 0x08) = func_ov193_020d3bb4;
    *(void **)(param + 0x1c) = func_ov193_020d3c4c;
    *(void **)(param + 0x30) = func_ov193_020d3ffc;
    *(void **)(param + 0x28) = func_ov193_020d3de8;
    *(void **)(param + 0x2c) = func_ov193_020d3e24;
    *(void **)(param + 0x0c) = WM_EndKeySharing_0x020d3e60;
    *(void **)(param + 0x10) = func_ov193_020d3e6c;
    *(void **)(param + 0x34) = func_ov193_020d3eb0;
    *(void **)(param + 0x1e0) = func_ov193_020d4268;
    *(void **)(param + 0x1d0) = func_ov193_020d4048;
    *(void **)(param + 0x1dc) = func_ov193_020d3bfc;

    *(int *)(param + 0x70) = 0xc00;
    *(int *)(param + 0x64) = 0;
    *(int *)(param + 0x68) = 0xc00;
    *(int *)(param + 0x6c) = 0;
    *(u16 *)(param + 0x100 + 0xae) |= 0x10;

    {
        int *self = (int *)param;

        ((void **)self)[0xe1] = func_0203b898(func_ov107_020c9440(self, 0));
        func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
        ((void **)self)[0xe6] = func_0203bee8(self[0xe1], 1, data_ov193_020d6a2c);
        ((void **)self)[0xe7] = func_0203bee8(self[0xe1], 1, data_ov193_020d6a34);
        ((void **)self)[0xe8] = func_0203d15c(0x20);

        for (i = 0; i < 4; i++) {
            ((struct Ov193SubitemSlot *)((void **)self)[0xe8])[i].subitem =
                func_0203b898(func_ov107_020c9440(self, ((int *)&kinds)[i]));
            func_ov107_020c9074(self,
                ((struct Ov193SubitemSlot *)((void **)self)[0xe8])[i].subitem);
            *(int *)((char *)((struct Ov193SubitemSlot *)
                ((void **)self)[0xe8])[i].subitem + 0x5c) |= 2;
        }

        func_ov107_020c92b0(self, 0, 1, &offset, 0x5d99);
        func_ov107_020c92b0(self, 1, 1, &offset, 0x2ecc);
        func_ov107_020c92b0(self, 2, 1, &offset, 0x2ecc);
        func_ov107_020c92b0(self, 4, 1, &offset, 0x2ecc);

        pose.position = data_02041dc8;
        pose.scale = 0xc00;
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            resource = func_ov107_020c319c(&pose);
            *p = resource;
            self[0xe5] = resource;
        }

        pose.position = data_02041dc8;
        pose.scale = 0xa00;
        {
            int **placementSlot = &((int **)self)[0xe3];
            int *placement;
            placement = func_01fffca8(self + 0x8b, 0x10, 100);
            *placementSlot = placement;
            **placementSlot = func_ov107_020c319c(&pose);
        }

        pose.scale = 0xc00;
        pose.position.x = 0;
        pose.position.y = 0xc00;
        pose.position.z = 0;
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            resource = func_ov107_020c319c(&pose);
            *p = resource;
            self[0xe4] = resource;
        }

        pose.scale = 0x800;
        pose.position.x = 0;
        pose.position.y = 0x800;
        pose.position.z = 0;
        ((void **)self)[0xe2] = func_01fffca8(self + 0x8b, 0x10, 100);
        *((int **)self)[0xe2] = func_ov107_020c319c(&pose);
        ((struct bf *)(((char **)self)[0xe2] + 8))->b |= 2;

        ((void **)self)[0xe9] = func_0203d15c(0x10);
        for (i = 0; i < 4; i++) {
            ((void **)((void **)self)[0xe9])[i] = func_ov193_020d5a58(self);
        }
        func_0203355c(0x133);
    }
}
