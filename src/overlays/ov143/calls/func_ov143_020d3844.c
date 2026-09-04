/* ov141 actor initializer: install the callback table, seed the camera pose,
 * build the actor's rig, resolve two bone attachments, create the action
 * resource and five node subitems, configure four actions, seed the two pose
 * handles and open the actor's own sub-object.
 *
 * The two bones resolved through func_0203bee8 are "7" (kind 3) and "root"
 * (kind 1); each returns a 0x30-byte attachment record. Field 0x2cc keeps the
 * body of the "root" record (its +0x14 block).
 *
 * The tail lives in its own block with its own `int *self` declaration. That is
 * not cosmetic: at function scope mwcc reserves r0/r1 for the trailing
 * func_ov107_020c9440(self, 1) argument setup, the +0x14 offset lands in r2 and
 * the store sinks below the two movs. The block frees r0 and the original's
 * `add r0,r0,#0x14 ; str r0,[r6,#0x2cc]` comes back.
 */
struct Ov143Vec3 {
    int x;
    int y;
    int z;
};

struct Ov143Pose {
    struct Ov143Vec3 position;
    int scale;
};

struct Ov143SubitemSlot {
    void *subitem;
    int pad;
};

struct Ov143KindTable {
    int kind[5];
};

extern struct Ov143KindTable data_ov143_020d623c;
extern struct Ov143Vec3 data_02041dc8;
extern const char data_ov143_020d62cc[];
extern const char data_ov143_020d62d0[];
extern char data_ov143_020d62d8[];

extern void func_ov143_020d3ab8(void);
extern void func_ov143_020d3b00(void);
extern void func_ov143_020d3b78(void);
extern void func_ov143_020d3f50(void);
extern void func_ov143_020d3dd4(void);
extern void func_ov143_020d3dfc(void);
extern void func_ov143_020d3e24(void);
extern void func_ov143_020d3f9c(void);
extern void func_ov143_020d4130(void);
extern void func_ov143_020d3b48(void);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern void *func_0203bee8();
extern void *func_ov107_020c9e50();
extern void *func_0203d15c();
extern void func_ov107_020c9074();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern int func_ov107_020c319c();
extern void *func_ov143_020d522c();
extern void func_0203355c();

void func_ov143_020d3844(int param)
{
    struct Ov143KindTable kinds;
    struct Ov143Pose pose;
    int i;
    int resource;

    kinds = data_ov143_020d623c;

    *(void **)(param + 0x08) = func_ov143_020d3ab8;
    *(void **)(param + 0x0c) = func_ov143_020d3b00;
    *(void **)(param + 0x1c) = func_ov143_020d3b78;
    *(void **)(param + 0x30) = func_ov143_020d3f50;
    *(void **)(param + 0x28) = func_ov143_020d3dd4;
    *(void **)(param + 0x2c) = func_ov143_020d3dfc;
    *(void **)(param + 0x34) = func_ov143_020d3e24;
    *(void **)(param + 0x1d0) = func_ov143_020d3f9c;
    *(void **)(param + 0x1e0) = func_ov143_020d4130;
    *(void **)(param + 0x1dc) = func_ov143_020d3b48;

    *(int *)(param + 0x70) = 0x800;
    *(int *)(param + 0x64) = 0;
    *(int *)(param + 0x68) = 0x800;
    *(int *)(param + 0x6c) = 0;

    {
        int *self = (int *)param;

        ((void **)self)[0xe1] = func_0203b898(func_ov107_020c9440(self, 0));
        func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
        ((void **)self)[0xe5] = func_0203bee8(self[0xe1], 3, data_ov143_020d62cc);
        ((void **)self)[0xe6] = func_0203bee8(self[0xe1], 1, data_ov143_020d62d0);
        ((char **)self)[0xb3] = (char *)((void **)self)[0xe6] + 0x14;
        ((void **)self)[0xf3] = func_ov107_020c9e50(
            func_ov107_020c9440(self, 1), data_ov143_020d62d8);
        ((void **)self)[0xe4] = func_0203d15c(0x28);

        for (i = 0; i < 5; i++) {
            ((struct Ov143SubitemSlot *)((void **)self)[0xe4])[i].subitem =
                func_0203b898(func_ov107_020c9440(self, kinds.kind[i]));
            func_ov107_020c9074(self,
                ((struct Ov143SubitemSlot *)((void **)self)[0xe4])[i].subitem);
            *(int *)((char *)((struct Ov143SubitemSlot *)
                ((void **)self)[0xe4])[i].subitem + 0x5c) |= 2;
        }

        func_ov107_020c92b0(self, 0, 1, 0, 0x1f33);
        func_ov107_020c92b0(self, 1, 1, 0, 0x1f33);
        func_ov107_020c92b0(self, 2, 1, 0, 0x1f33);
        func_ov107_020c92b0(self, 4, 1, 0, 0x1f33);

        pose.position = data_02041dc8;
        pose.scale = 0x800;

        ((void **)self)[0xe2] = func_01fffca8(self + 0x8b, 0x10, 100);
        *((int **)self)[0xe2] = func_ov107_020c319c(&pose);
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            resource = func_ov107_020c319c(&pose);
            *p = resource;
            self[0xe3] = resource;
        }
        ((void **)self)[0xf2] = func_ov143_020d522c(self);
        func_0203355c(0x11e);
    }
}
