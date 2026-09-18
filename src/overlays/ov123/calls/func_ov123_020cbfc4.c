/* Constructor of the ov123 enemy (and its byte-identical twin): raises bit 8 of the +0 flags,
 * installs the twelve handlers (+8 tick, +0xc veneer, +0x1c message, +0x28/+0x2c/+0x30/+0x34/
 * +0x38 callbacks, +0x10 draw, +0x1e0 release, +0x1d0 on-hit, +0x1dc finish), seeds the +0x64
 * pose (scale 0x800, y 0x800) and bit 4 of the +0x1ae flags, builds the primary item from pool
 * entry 0 (subscribed), resolves the named bone (+0x390), the two sub-items of the +0xe298 pool
 * pair (+0x398, attached, bit 1 on their +0x5c), configures actions 0/1/2/4 with the +0xe2a0
 * offset and the 0x3000/0x1800/0x1800/0x1800 rates, then creates two capsule placements from
 * one request (position (0, 0x800, 0), world Y axis, radius and height 0x800): +0x38c on the
 * +0x144 list, +0x388 on the +0x22c list; +0x394 is built by cd4cc and sound 0x115 is loaded. */
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

extern const int data_ov123_020ce298[2];
extern struct Ov153Vec3 data_ov123_020ce2a0;
extern const struct Ov153Vec3 data_02042264;
extern void func_ov123_020cc38c(void);
extern const char data_ov123_020ce30c[];

extern void func_ov123_020cc254(void);
extern void WM_EndKeySharing_0x020cc294(void);   /* the game's tail-call veneer to the ov107 draw hook, named after the byte-identical SDK thunk */
extern void func_ov123_020cc2a0(void);
extern void func_ov123_020cc524(void);
extern void func_ov123_020cc33c(void);
extern void func_ov123_020cc364(void);
extern void func_ov123_020cc3dc(void);
extern void func_ov123_020cc420(void);
extern void func_ov123_020cc518(void);
extern void func_ov123_020cc6e8(void);
extern void func_ov123_020cc570(void);
extern void *func_ov123_020cd4cc(int *self);

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

void func_ov123_020cbfc4(int param)
{
    struct Ov153Vec3 offset;
    struct Ov153Capsule req;
    int kinds[2];
    int i;
    int resource;

    kinds[0] = data_ov123_020ce298[0];
    kinds[1] = data_ov123_020ce298[1];
    offset = data_ov123_020ce2a0;

    *(u16 *)param |= 0x100;
    *(void **)(param + 0x08) = func_ov123_020cc254;
    *(void **)(param + 0x0c) = WM_EndKeySharing_0x020cc294;
    *(void **)(param + 0x1c) = func_ov123_020cc2a0;
    *(void **)(param + 0x30) = func_ov123_020cc524;
    *(void **)(param + 0x28) = func_ov123_020cc33c;
    *(void **)(param + 0x2c) = func_ov123_020cc364;
    *(void **)(param + 0x10) = func_ov123_020cc3dc;
    *(void **)(param + 0x34) = func_ov123_020cc420;
    *(void **)(param + 0x38) = func_ov123_020cc518;
    *(void **)(param + 0x1e0) = func_ov123_020cc6e8;
    *(void **)(param + 0x1d0) = func_ov123_020cc570;
    *(void **)(param + 0x1dc) = func_ov123_020cc38c;

    *(int *)(param + 0x70) = 0x800;
    *(int *)(param + 0x64) = 0;
    *(int *)(param + 0x68) = 0x800;
    *(int *)(param + 0x6c) = 0;
    *(u16 *)(param + 0x100 + 0xae) |= 0x10;

    {
        int *self = (int *)param;

        ((void **)self)[0xe1] = func_0203b898(func_ov107_020c9440(self, 0));
        func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
        ((void **)self)[0xe4] = func_0203bee8(self[0xe1], 1, data_ov123_020ce30c);
        ((void **)self)[0xe6] = func_0203d15c(0x10);

        for (i = 0; i < 2; i++) {
            ((struct Ov153SubitemSlot *)((void **)self)[0xe6])[i].subitem =
                func_0203b898(func_ov107_020c9440(self, kinds[i]));
            func_ov107_020c9074(self,
                ((struct Ov153SubitemSlot *)((void **)self)[0xe6])[i].subitem);
            *(int *)((char *)((struct Ov153SubitemSlot *)
                ((void **)self)[0xe6])[i].subitem + 0x5c) |= 2;
        }

        func_ov107_020c92b0(self, 0, 1, &offset, 0x3000);
        func_ov107_020c92b0(self, 1, 1, &offset, 0x1800);
        func_ov107_020c92b0(self, 2, 1, &offset, 0x1800);
        func_ov107_020c92b0(self, 4, 1, &offset, 0x1800);

        req.vPos.x = 0;
        req.vPos.z = 0;
        req.vPos.y = 0x800;
        req.vUp = data_02042264;
        req.nRadius = 0x800;
        req.nHeight = 0x800;
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            resource = func_ov107_020c3210(&req);
            *p = resource;
            self[0xe3] = resource;
        }
        ((void **)self)[0xe2] = func_01fffca8(self + 0x8b, 0x10, 100);
        *((int **)self)[0xe2] = func_ov107_020c3210(&req);
        ((void **)self)[0xe5] = func_ov123_020cd4cc(self);
        func_0203355c(0x115);
    }
}
