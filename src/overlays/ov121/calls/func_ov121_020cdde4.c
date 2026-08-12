/* ov121 actor initializer: install the callback table, seed the camera pose,
 * build the actor's primary subitem, resolve four bone attachments, create the
 * action resource and three node subitems, configure four actions and seed the
 * two pose handles.
 *
 * The four bone names resolved through func_0203bee8 are Bone_R_fing,
 * Bip01_R_Foot, Bip01_L_Foot and Bip01; each returns a 0x30-byte attachment
 * record.  Field 0x2cc keeps the body of the Bip01 record (its +0x14 block),
 * which is the only place in ov121 that writes it.
 *
 * Shared with ov120 and ov122: the same function with fourteen overlay-local
 * symbols substituted, the eight callbacks it installs and the six data
 * records it seeds from.
 *
 * CODEGEN NOTE -- the +0x14 store is a SCOPE problem, not a scheduling one.
 * Written at function scope, mwcc reserves r0/r1 for the trailing
 * func_ov107_020c9440(self, 1) argument setup, so the offset lands in r2 and
 * the store sinks below the two movs.  Putting the whole tail in its own block
 * with its own `int *self` declaration (the idiom the matched ov281 homolog
 * uses) frees r0, and mwcc emits the ROM's `add r0,r0,#0x14 ; str r0,[r6,#0x2cc]`
 * with the argument movs after it.  Twenty-five source forms of the store
 * itself -- temporaries, post-increment, assignment expressions, volatile,
 * register hints, inline helper, declaration-order permutations -- are all
 * bit-identical and none of them move it. */
struct Ov120Vec3 {
    int x;
    int y;
    int z;
};

struct Ov120Pose {
    struct Ov120Vec3 position;
    int scale;
};

struct Ov120SubitemSlot {
    void *subitem;
    int pad;
};

struct Ov120Bone {
    unsigned char pad[0x14];
};

extern struct Ov120Vec3 data_ov121_020cfd04;
extern struct Ov120Vec3 data_02041dc8;
extern const unsigned short data_ov121_020cfd4c[];
extern const unsigned short data_ov121_020cfd58[];
extern const unsigned short data_ov121_020cfd68[];
extern const unsigned short data_ov121_020cfd78[];
extern char data_ov121_020cfd80[];

extern void func_ov121_020ce058(void);
extern void func_ov121_020ce0a0(void);
extern void func_ov121_020ce0c4(void);
extern void func_ov121_020ce32c(void);
extern void func_ov121_020ce294(void);
extern void func_ov121_020ce388(void);
extern void func_ov121_020ce5c0(void);
extern void func_ov121_020ce264(void);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern struct Ov120Bone *func_0203bee8();
extern void *func_ov107_020c9e50();
extern void *func_0203d15c();
extern void func_ov107_020c9074();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern int func_ov107_020c319c();
extern void func_0203355c();

void func_ov121_020cdde4(int param)
{
    struct Ov120Vec3 kinds;
    struct Ov120Pose pose;
    int i;
    int resource;

    kinds = data_ov121_020cfd04;

    *(void **)(param + 0x08) = func_ov121_020ce058;
    *(void **)(param + 0x0c) = func_ov121_020ce0a0;
    *(void **)(param + 0x1c) = func_ov121_020ce0c4;
    *(void **)(param + 0x30) = func_ov121_020ce32c;
    *(void **)(param + 0x34) = func_ov121_020ce294;
    *(void **)(param + 0x1d0) = func_ov121_020ce388;
    *(void **)(param + 0x1e0) = func_ov121_020ce5c0;
    *(void **)(param + 0x1dc) = func_ov121_020ce264;

    *(int *)(param + 0x70) = 0x800;
    *(int *)(param + 0x64) = 0;
    *(int *)(param + 0x68) = 0x800;
    *(int *)(param + 0x6c) = 0;

    {
        int *self = (int *)param;

        ((void **)self)[0xe1] = func_0203b898(func_ov107_020c9440(self, 0));
        func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
        ((void **)self)[0xe4] = func_0203bee8(self[0xe1], 1, data_ov121_020cfd4c);
        ((void **)self)[0xe5] = func_0203bee8(self[0xe1], 1, data_ov121_020cfd58);
        ((void **)self)[0xe6] = func_0203bee8(self[0xe1], 1, data_ov121_020cfd68);
        ((void **)self)[0xe7] = func_0203bee8(self[0xe1], 1, data_ov121_020cfd78);
        ((char **)self)[0xb3] = (char *)((void **)self)[0xe7] + 0x14;
        ((void **)self)[0xe8] = func_ov107_020c9e50(
            func_ov107_020c9440(self, 1), data_ov121_020cfd80);
        ((void **)self)[0xe9] = func_0203d15c(0x18);

        for (i = 0; i < 3; i++) {
            ((struct Ov120SubitemSlot *)((void **)self)[0xe9])[i].subitem =
                func_0203b898(func_ov107_020c9440(self, ((int *)&kinds)[i]));
            func_ov107_020c9074(self,
                ((struct Ov120SubitemSlot *)((void **)self)[0xe9])[i].subitem);
            *(int *)((char *)((struct Ov120SubitemSlot *)
                ((void **)self)[0xe9])[i].subitem + 0x5c) |= 2;
        }

        func_ov107_020c92b0(self, 0, 1, 0, 0x1800);
        func_ov107_020c92b0(self, 1, 1, 0, 0x1800);
        func_ov107_020c92b0(self, 2, 1, 0, 0x1800);
        func_ov107_020c92b0(self, 4, 1, 0, 0x1800);

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
        func_0203355c(0x11a);
    }
}
