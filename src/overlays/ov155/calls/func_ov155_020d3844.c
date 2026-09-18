/* Big constructor of the ov153 enemy (x3: ov153/154/155): raises bit 8 of the +0 flags, installs
 * the eleven handlers (+8 tick, +0xc/+0x10 draw pair, +0x1c message, +0x28/+0x2c/+0x30/+0x34
 * hit callbacks, +0x1d0 on-hit, +0x1dc finish, +0x1e0 release), seeds the +0x64 pose (scale
 * 0x1400, y 0x1400) and bit 4 of the +0x1ae flags, builds the primary item from pool entry 0,
 * resolves the "headcon" bone (+0x38c), the two sub-items of kinds 1/2 (+0x394, attached, bit 1
 * on their +0x5c), configures actions 0/1/2/4 with the (0, 0xa00, 0) offset and the
 * 0x3e66/0x1f33/0x1f33/0x1f33 rates, then creates two capsule placements from one request
 * (position (0, 0xa00, 0), world Y axis, radius and height 0xa00): +0x390 on the +0x144 list,
 * +0x388 on the +0x22c list; +0x398 is built by func_ov155_020d3dd4 and sound 0x13c is loaded. */
typedef unsigned short u16;

struct Ov153Vec3 {
    int x;
    int y;
    int z;
};

struct Ov153Capsule {
    struct Ov153Vec3 vPos;
    struct Ov153Vec3 vUp;
    int nRadius;
    int nHeight;
};

struct Ov153SubitemSlot {
    void *subitem;
    int pad;
};

extern const int data_ov155_020d588c[2];
extern struct Ov153Vec3 data_ov155_020d5894;
extern const struct Ov153Vec3 data_02042264;
extern const char data_ov155_020d590c[];

extern void func_ov155_020d3ad0(void);
extern void WM_EndKeySharing_0x020d3b10(void);   /* the game's tail-call veneer to the ov107 draw hook, named after the byte-identical SDK thunk */
extern void func_ov155_020d3b6c(void);
extern void func_ov155_020d4b70(void);
extern void func_ov155_020d3c08(void);
extern void func_ov155_020d3c30(void);
extern void func_ov155_020d3c58(void);
extern void func_ov155_020d3c9c(void);
extern void func_ov155_020d4cf0(void);
extern void func_ov155_020d4bbc(void);
extern void func_ov155_020d3b1c(void);
extern void *func_ov155_020d3dd4(int *self);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern void *func_0203bee8();
extern void *func_0203d15c();
extern void func_ov107_020c9074();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern int func_ov107_020c3210(struct Ov153Capsule *req);
extern void func_0203355c();

void func_ov155_020d3844(int param)
{
    struct Ov153Capsule req;
    struct Ov153Vec3 offset;
    int kinds[2];
    int i;
    int resource;

    kinds[0] = data_ov155_020d588c[0];
    kinds[1] = data_ov155_020d588c[1];
    offset = data_ov155_020d5894;

    *(u16 *)param |= 0x100;
    *(void **)(param + 0x08) = func_ov155_020d3ad0;
    *(void **)(param + 0x0c) = WM_EndKeySharing_0x020d3b10;
    *(void **)(param + 0x1c) = func_ov155_020d3b6c;
    *(void **)(param + 0x30) = func_ov155_020d4b70;
    *(void **)(param + 0x28) = func_ov155_020d3c08;
    *(void **)(param + 0x2c) = func_ov155_020d3c30;
    *(void **)(param + 0x10) = func_ov155_020d3c58;
    *(void **)(param + 0x34) = func_ov155_020d3c9c;
    *(void **)(param + 0x1e0) = func_ov155_020d4cf0;
    *(void **)(param + 0x1d0) = func_ov155_020d4bbc;
    *(void **)(param + 0x1dc) = func_ov155_020d3b1c;

    *(int *)(param + 0x70) = 0x1400;
    *(int *)(param + 0x64) = 0;
    *(int *)(param + 0x68) = 0x1400;
    *(int *)(param + 0x6c) = 0;
    *(u16 *)(param + 0x100 + 0xae) |= 0x10;

    {
        int *self = (int *)param;

        ((void **)self)[0xe1] = func_0203b898(func_ov107_020c9440(self, 0));
        func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
        ((void **)self)[0xe3] = func_0203bee8(self[0xe1], 1, data_ov155_020d590c);
        ((void **)self)[0xe5] = func_0203d15c(0x10);

        for (i = 0; i < 2; i++) {
            ((struct Ov153SubitemSlot *)((void **)self)[0xe5])[i].subitem =
                func_0203b898(func_ov107_020c9440(self, kinds[i]));
            func_ov107_020c9074(self,
                ((struct Ov153SubitemSlot *)((void **)self)[0xe5])[i].subitem);
            *(int *)((char *)((struct Ov153SubitemSlot *)
                ((void **)self)[0xe5])[i].subitem + 0x5c) |= 2;
        }

        func_ov107_020c92b0(self, 0, 1, &offset, 0x3e66);
        func_ov107_020c92b0(self, 1, 1, &offset, 0x1f33);
        func_ov107_020c92b0(self, 2, 1, &offset, 0x1f33);
        func_ov107_020c92b0(self, 4, 1, &offset, 0x1f33);

        req.vUp = data_02042264;
        req.nRadius = 0xa00;
        req.nHeight = 0xa00;
        req.vPos.y = 0xa00;
        req.vPos.x = 0;
        req.vPos.z = 0;
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            resource = func_ov107_020c3210(&req);
            *p = resource;
            self[0xe4] = resource;
        }
        ((void **)self)[0xe2] = func_01fffca8(self + 0x8b, 0x10, 100);
        *((int **)self)[0xe2] = func_ov107_020c3210(&req);
        ((void **)self)[0xe6] = func_ov155_020d3dd4(self);
        func_0203355c(0x13c);
    }
}
