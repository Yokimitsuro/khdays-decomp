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
struct Ov141Vec3 {
    int x;
    int y;
    int z;
};

struct Ov141Pose {
    struct Ov141Vec3 position;
    int scale;
};

struct Ov141SubitemSlot {
    void *subitem;
    int pad;
};

struct Ov141KindTable {
    int kind[5];
};

extern struct Ov141KindTable data_ov141_020ce9bc;
extern struct Ov141Vec3 data_02041dc8;
extern const char data_ov141_020cea4c[];
extern const char data_ov141_020cea50[];
extern char data_ov141_020cea58[];

extern void func_ov141_020cc238(void);
extern void func_ov141_020cc280(void);
extern void func_ov141_020cc2f8(void);
extern void func_ov141_020cc6d0(void);
extern void func_ov141_020cc554(void);
extern void func_ov141_020cc57c(void);
extern void func_ov141_020cc5a4(void);
extern void func_ov141_020cc71c(void);
extern void func_ov141_020cc8b0(void);
extern void func_ov141_020cc2c8(void);

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
extern void *func_ov141_020cd9ac();
extern void func_0203355c();

void func_ov141_020cbfc4(int param)
{
    struct Ov141KindTable kinds;
    struct Ov141Pose pose;
    int i;
    int resource;

    kinds = data_ov141_020ce9bc;

    *(void **)(param + 0x08) = func_ov141_020cc238;
    *(void **)(param + 0x0c) = func_ov141_020cc280;
    *(void **)(param + 0x1c) = func_ov141_020cc2f8;
    *(void **)(param + 0x30) = func_ov141_020cc6d0;
    *(void **)(param + 0x28) = func_ov141_020cc554;
    *(void **)(param + 0x2c) = func_ov141_020cc57c;
    *(void **)(param + 0x34) = func_ov141_020cc5a4;
    *(void **)(param + 0x1d0) = func_ov141_020cc71c;
    *(void **)(param + 0x1e0) = func_ov141_020cc8b0;
    *(void **)(param + 0x1dc) = func_ov141_020cc2c8;

    *(int *)(param + 0x70) = 0x800;
    *(int *)(param + 0x64) = 0;
    *(int *)(param + 0x68) = 0x800;
    *(int *)(param + 0x6c) = 0;

    {
        int *self = (int *)param;

        ((void **)self)[0xe1] = func_0203b898(func_ov107_020c9440(self, 0));
        func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
        ((void **)self)[0xe5] = func_0203bee8(self[0xe1], 3, data_ov141_020cea4c);
        ((void **)self)[0xe6] = func_0203bee8(self[0xe1], 1, data_ov141_020cea50);
        ((char **)self)[0xb3] = (char *)((void **)self)[0xe6] + 0x14;
        ((void **)self)[0xf3] = func_ov107_020c9e50(
            func_ov107_020c9440(self, 1), data_ov141_020cea58);
        ((void **)self)[0xe4] = func_0203d15c(0x28);

        for (i = 0; i < 5; i++) {
            ((struct Ov141SubitemSlot *)((void **)self)[0xe4])[i].subitem =
                func_0203b898(func_ov107_020c9440(self, kinds.kind[i]));
            func_ov107_020c9074(self,
                ((struct Ov141SubitemSlot *)((void **)self)[0xe4])[i].subitem);
            *(int *)((char *)((struct Ov141SubitemSlot *)
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
        ((void **)self)[0xf2] = func_ov141_020cd9ac(self);
        func_0203355c(0x11e);
    }
}
