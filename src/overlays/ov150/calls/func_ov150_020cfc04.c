/* ov150 actor initializer: install the callback table, seed the camera pose,
 * build the actor's primary subitem, resolve two bone attachments, create the
 * action resource and five node subitems, configure four actions, seed the two
 * pose handles and open the sub-object.
 *
 * This is the twin of ov149 020cdde4: the two ROMs are byte for byte identical
 * apart from the thirty-four relocation-bearing instructions, whose targets map
 * one to one onto ov150's own symbols. The shared template is ov121 020cdde4
 * with this family's numbers: ten callbacks, two bone attachments, five node
 * subitems, action strength 0x2800, camera scale 0x1000, and a trailing
 * func_ov150_020d15f0 whose result is parked at +0x3c8 before the 0x14e
 * notification.
 *
 * CODEGEN NOTE inherited from the ov121 twin -- the `+ 0x14` store into +0x2cc is
 * a SCOPE problem, not a scheduling one. Written at function scope, mwcc reserves
 * r0/r1 for the trailing func_ov107_020c9440(self, 1) argument setup and the
 * store sinks below the two movs. Putting the tail in its own block with its own
 * `int *self` declaration frees r0 and mwcc emits the ROM's
 * `add r0,r0,#0x14 ; str r0,[r6,#0x2cc]`. */
struct Ov150Vec3 {
    int x;
    int y;
    int z;
};

struct Ov150Pose {
    struct Ov150Vec3 position;
    int scale;
};

struct Ov150SubitemSlot {
    void *subitem;
    int pad;
};

struct Ov150Kinds {
    int values[5];
};

extern struct Ov150Kinds data_ov150_020d2558;
extern struct Ov150Vec3 data_02041dc8;
extern const unsigned short data_ov150_020d25cc[];
extern const unsigned short data_ov150_020d25d0[];
extern char data_ov150_020d25d8[];

extern void func_ov150_020cfe74(void);
extern void func_ov150_020cfebc(void);
extern void func_ov150_020cff34(void);
extern void func_ov150_020d030c(void);
extern void func_ov150_020d0190(void);
extern void func_ov150_020d01b8(void);
extern void func_ov150_020d01e0(void);
extern void func_ov150_020d0358(void);
extern void func_ov150_020d04f4(void);
extern void func_ov150_020cff04(void);

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
extern void *func_ov150_020d15f0();
extern void func_0203355c();

void func_ov150_020cfc04(int param)
{
    struct Ov150Kinds kinds;
    struct Ov150Pose pose;
    int i;
    int resource;

    kinds = data_ov150_020d2558;

    *(void **)(param + 0x08) = func_ov150_020cfe74;
    *(void **)(param + 0x0c) = func_ov150_020cfebc;
    *(void **)(param + 0x1c) = func_ov150_020cff34;
    *(void **)(param + 0x30) = func_ov150_020d030c;
    *(void **)(param + 0x28) = func_ov150_020d0190;
    *(void **)(param + 0x2c) = func_ov150_020d01b8;
    *(void **)(param + 0x34) = func_ov150_020d01e0;
    *(void **)(param + 0x1d0) = func_ov150_020d0358;
    *(void **)(param + 0x1e0) = func_ov150_020d04f4;
    *(void **)(param + 0x1dc) = func_ov150_020cff04;

    *(int *)(param + 0x70) = 0x1000;
    *(int *)(param + 0x64) = 0;
    *(int *)(param + 0x68) = 0x1000;
    *(int *)(param + 0x6c) = 0;

    {
        int *self = (int *)param;

        ((void **)self)[0xe1] = func_0203b898(func_ov107_020c9440(self, 0));
        func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
        ((void **)self)[0xe5] = func_0203bee8(self[0xe1], 3, data_ov150_020d25cc);
        ((void **)self)[0xe6] = func_0203bee8(self[0xe1], 1, data_ov150_020d25d0);
        ((char **)self)[0xb3] = (char *)((void **)self)[0xe6] + 0x14;
        ((void **)self)[0xf3] = func_ov107_020c9e50(
            func_ov107_020c9440(self, 1), data_ov150_020d25d8);
        ((void **)self)[0xe4] = func_0203d15c(0x28);

        for (i = 0; i < 5; i++) {
            ((struct Ov150SubitemSlot *)((void **)self)[0xe4])[i].subitem =
                func_0203b898(func_ov107_020c9440(self, kinds.values[i]));
            func_ov107_020c9074(self,
                ((struct Ov150SubitemSlot *)((void **)self)[0xe4])[i].subitem);
            *(int *)((char *)((struct Ov150SubitemSlot *)
                ((void **)self)[0xe4])[i].subitem + 0x5c) |= 2;
        }

        func_ov107_020c92b0(self, 0, 1, 0, 0x2800);
        func_ov107_020c92b0(self, 1, 1, 0, 0x2800);
        func_ov107_020c92b0(self, 2, 1, 0, 0x2800);
        func_ov107_020c92b0(self, 4, 1, 0, 0x2800);

        pose.position = data_02041dc8;
        pose.scale = 0x1000;

        ((void **)self)[0xe2] = func_01fffca8(self + 0x8b, 0x10, 100);
        *((int **)self)[0xe2] = func_ov107_020c319c(&pose);
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            resource = func_ov107_020c319c(&pose);
            *p = resource;
            self[0xe3] = resource;
        }
        ((void **)self)[0xf2] = func_ov150_020d15f0(self);
        func_0203355c(0x14e);
    }
}
