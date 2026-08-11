/* ov281 actor initializer: install callbacks, build actor bounds, resolve twelve bone
 * handles, configure four actions, create their subitems and seed two pose handles.
 *
 * The per-overlay fixed-point values are load-bearing: 0x14cc for the pose, 0x2998 for
 * action zero and 0x1b4c for the remaining actions.  Unlike the nearby ov188/ov190
 * homologs, these values require literal-pool loads and account for the extra 12 bytes. */
struct v3 { int a, b, c; };
struct Box { struct v3 min, max; };
struct Pose { struct v3 v; int nScale; };

struct Ov281Actor {
    char pad000[0x08];
    void *fn008;
    void *fn00c;
    char pad010[0x0c];
    void *fn01c;
    char pad020[0x08];
    void *fn028;
    void *fn02c;
    void *fn030;
    void *fn034;
    char pad038[0x2c];
    int camera[4];
    char pad074[0x15c];
    void *fn1d0;
    char pad1d4[0x08];
    void *fn1dc;
    void *fn1e0;
    void *fn1e4;
    char pad1e8[0x14];
    struct Box box1fc;
};

extern struct v3 data_02041dc8;

extern unsigned short data_ov281_020ce48c[];
extern unsigned short data_ov281_020ce494[];
extern unsigned short data_ov281_020ce49c[];
extern unsigned short data_ov281_020ce4a8[];
extern unsigned short data_ov281_020ce4b8[];
extern unsigned short data_ov281_020ce4c8[];
extern unsigned short data_ov281_020ce4d4[];
extern unsigned short data_ov281_020ce4e4[];
extern unsigned short data_ov281_020ce4f0[];
extern unsigned short data_ov281_020ce500[];
extern unsigned short data_ov281_020ce510[];
extern unsigned short data_ov281_020ce520[];
extern int data_ov281_020ce530;

extern int func_ov281_020cc3dc, func_ov281_020cc41c, func_ov281_020cc440;
extern int func_ov281_020cc7dc, WM_EndKeySharing_0x020cc63c, WM_EndKeySharing_0x020cc648;
extern int func_ov281_020cc68c, func_ov281_020cc838, func_ov281_020cc654;
extern int func_ov281_020cca88, func_ov281_020ccab4;

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern void *func_0203bee8();
extern void *func_ov107_020c9e50();
extern void func_ov107_020c9074();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern long long func_ov107_020c319c();
extern void func_0203355c();

void func_ov281_020cbfc4(struct Ov281Actor *actor) {
    int minX;
    int minY;
    int minZ;
    register int cameraScale;
    register int actionScale;
    register void *fn2c;

    struct Box box;
    struct Pose g;
    char *pg;
    void *sub;
    long long r;

    minX = -0xeea;
    minZ = -0x858;
    minY = 0x17;
    cameraScale = 0x14cc;

    actor->fn008 = &func_ov281_020cc3dc;
    actor->fn00c = &func_ov281_020cc41c;
    actor->fn01c = &func_ov281_020cc440;
    actor->fn030 = &func_ov281_020cc7dc;
    actor->fn028 = &WM_EndKeySharing_0x020cc63c;

    fn2c = &WM_EndKeySharing_0x020cc648;

    box.min.a = minX;
    box.min.b = minY;
    box.min.c = minZ;
    box.max.a = box.min.a + 0x1dd3;
    box.max.b = box.min.b + 0x1c27;
    box.max.c = box.min.c + 0xd64;

    actor->fn02c = fn2c;
    actor->fn034 = &func_ov281_020cc68c;
    actor->fn1d0 = &func_ov281_020cc838;
    actor->fn1dc = &func_ov281_020cc654;
    actor->fn1e0 = &func_ov281_020cca88;
    actor->fn1e4 = &func_ov281_020ccab4;
    actor->camera[3] = cameraScale;
    actor->camera[0] = 0;
    actor->camera[1] = cameraScale;
    actor->camera[2] = 0;

    actor->box1fc = box;

    *(void **)(((unsigned int)actor) + 0x384) = func_0203b898(func_ov107_020c9440(((unsigned int)actor), 0));
    {
        int *self = (int *)actor;
        func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
        ((void **)self)[0xe4] = func_0203bee8(self[0xe1], 1, data_ov281_020ce48c);
        ((void **)self)[0xe5] = func_0203bee8(self[0xe1], 1, data_ov281_020ce494);
        ((void **)self)[0xe6] = func_0203bee8(self[0xe1], 1, data_ov281_020ce49c);
        ((void **)self)[0xe7] = func_0203bee8(self[0xe1], 1, data_ov281_020ce4a8);
        ((void **)self)[0xe8] = func_0203bee8(self[0xe1], 1, data_ov281_020ce4b8);
        ((void **)self)[0xe9] = func_0203bee8(self[0xe1], 1, data_ov281_020ce4c8);
        ((void **)self)[0xea] = func_0203bee8(self[0xe1], 1, data_ov281_020ce4d4);
        ((void **)self)[0xeb] = func_0203bee8(self[0xe1], 1, data_ov281_020ce4e4);
        ((void **)self)[0xec] = func_0203bee8(self[0xe1], 1, data_ov281_020ce4f0);
        ((void **)self)[0xed] = func_0203bee8(self[0xe1], 1, data_ov281_020ce500);
        ((void **)self)[0xee] = func_0203bee8(self[0xe1], 1, data_ov281_020ce510);
        ((void **)self)[0xef] = func_0203bee8(self[0xe1], 1, data_ov281_020ce520);

        ((void **)self)[0xf0] =
            func_ov107_020c9e50(func_ov107_020c9440(self, 1), &data_ov281_020ce530);

        actionScale = 0x2998;
        func_ov107_020c92b0(self, 0, 1, 0, actionScale);
        actionScale = 0x1b4c;
        func_ov107_020c92b0(self, 2, 1, 0, actionScale);
        func_ov107_020c92b0(self, 1, 1, 0, actionScale);
        func_ov107_020c92b0(self, 4, 1, 0, actionScale);

        ((void **)self)[0xf2] = func_0203b898(func_ov107_020c9440(self, 2));
        sub = ((void **)self)[0xf2];
        func_ov107_020c9074(self, sub);
        *(int *)((char *)sub + 0x5c) |= 2;

        func_ov107_020c9074(self, sub = ((void **)self)[0xf4] =
            func_0203b898(func_ov107_020c9440(self, 3)));
        *(int *)((char *)sub + 0x5c) |= 2;

        func_ov107_020c9074(self, sub = ((void **)self)[0xf6] =
            func_0203b898(func_ov107_020c9440(self, 4)));
        *(int *)((char *)sub + 0x5c) |= 2;

        func_ov107_020c9074(self, sub = ((void **)self)[0xf8] =
            func_0203b898(func_ov107_020c9440(self, 5)));
        *(int *)((char *)sub + 0x5c) |= 2;

        g = *(struct Pose *)(self + 0x19);
        g.v = data_02041dc8;
        pg = (char *)&g;

        ((void **)self)[0xe2] = func_01fffca8(self + 0x8b, 0x10, 100);
        {
            int *p = func_01fffca8(self + 0x51, 4, 100);
            *((int **)self)[0xe2] = (int)func_ov107_020c319c(pg);
            r = func_ov107_020c319c(pg);
            *p = (int)r;
            self[0xe3] = (int)r;
        }
        func_0203355c(0x169, (int)((unsigned long long)r >> 32));
    }
}
