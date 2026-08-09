/* ov190 actor: install the handler table, set the bounding box, resolve the twelve bone
 * handles and open the four sub-items.
 *
 * The six words at +0x1fc are a bounding box, a pair of Vec3 holding the minimum and the
 * maximum, not six unrelated numbers: the matched func_ov234_020cbfc4 in the same family
 * carries the identical shape at the identical offset with the identical three addends
 * 0x1dd3, 0x1c27 and 0xd64, and models it as min and max of a box. Same family as the matched ov188 constructor, written in its idioms:
 * the subitem is created as func_0203b898(func_ov107_020c9440(...)) in one expression, the
 * bone handles come back from func_0203bee8 with a literal 1 in the middle, and the two
 * stack blocks are whole-struct assignments rather than field-by-field stores. */
struct v3 { int a, b, c; };
struct Box { struct v3 min, max; };
struct Pose { struct v3 v; int nScale; };

extern struct v3 data_02041dc8;

extern unsigned short data_ov190_020d5cec[];
extern unsigned short data_ov190_020d5cf4[];
extern unsigned short data_ov190_020d5cfc[];
extern unsigned short data_ov190_020d5d08[];
extern unsigned short data_ov190_020d5d18[];
extern unsigned short data_ov190_020d5d28[];
extern unsigned short data_ov190_020d5d34[];
extern unsigned short data_ov190_020d5d44[];
extern unsigned short data_ov190_020d5d50[];
extern unsigned short data_ov190_020d5d60[];
extern unsigned short data_ov190_020d5d70[];
extern unsigned short data_ov190_020d5d80[];
extern int data_ov190_020d5d90;

extern void func_ov190_020d3c50(void), func_ov190_020d3c90(void), func_ov190_020d3cb4(void);
extern void func_ov190_020d4050(void), WM_EndKeySharing_0x020d3eb0(void), WM_EndKeySharing_0x020d3ebc(void);
extern void func_ov190_020d3f00(void), func_ov190_020d40ac(void), func_ov190_020d3ec8(void);
extern void func_ov190_020d42fc(void), func_ov190_020d4328(void);

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

void func_ov190_020d7484(int param_1) {
    struct Box box;
    struct Pose g;
    char *pg;
    void *sub;
    long long r;

    box.min.a = -0xeea;
    box.min.b = 0x17;
    box.min.c = -0x858;
    box.max.a = box.min.a + 0x1dd3;
    box.max.b = box.min.b + 0x1c27;
    box.max.c = box.min.c + 0xd64;
    *(void **)(((unsigned int)param_1) + 8) = func_ov190_020d3c50;
    *(void **)(((unsigned int)param_1) + 0xc) = func_ov190_020d3c90;
    *(void **)(((unsigned int)param_1) + 0x1c) = func_ov190_020d3cb4;
    *(void **)(((unsigned int)param_1) + 0x30) = func_ov190_020d4050;
    *(void **)(((unsigned int)param_1) + 0x28) = WM_EndKeySharing_0x020d3eb0;
    *(void **)(((unsigned int)param_1) + 0x2c) = WM_EndKeySharing_0x020d3ebc;
    *(void **)(((unsigned int)param_1) + 0x34) = func_ov190_020d3f00;
    *(void **)(((unsigned int)param_1) + 0x1d0) = func_ov190_020d40ac;
    *(void **)(((unsigned int)param_1) + 0x1dc) = func_ov190_020d3ec8;
    *(void **)(((unsigned int)param_1) + 0x1e0) = func_ov190_020d42fc;
    *(void **)(((unsigned int)param_1) + 0x1e4) = func_ov190_020d4328;
    *(int *)(((unsigned int)param_1) + 0x70) = 0x1000;
    *(int *)(((unsigned int)param_1) + 0x64) = 0;
    *(int *)(((unsigned int)param_1) + 0x68) = 0x1000;
    *(int *)(((unsigned int)param_1) + 0x6c) = 0;

    *(struct Box *)(((unsigned int)param_1) + 0x1fc) = box;

    *(void **)(((unsigned int)param_1) + 0x384) = func_0203b898(func_ov107_020c9440(((unsigned int)param_1), 0));
    int *self = (int *)param_1;
    func_0203bfb4(self[0x27], ((void **)self)[0xe1]);
    ((void **)self)[0xe4] = func_0203bee8(self[0xe1], 1, data_ov190_020d5cec);
    ((void **)self)[0xe5] = func_0203bee8(self[0xe1], 1, data_ov190_020d5cf4);
    ((void **)self)[0xe6] = func_0203bee8(self[0xe1], 1, data_ov190_020d5cfc);
    ((void **)self)[0xe7] = func_0203bee8(self[0xe1], 1, data_ov190_020d5d08);
    ((void **)self)[0xe8] = func_0203bee8(self[0xe1], 1, data_ov190_020d5d18);
    ((void **)self)[0xe9] = func_0203bee8(self[0xe1], 1, data_ov190_020d5d28);
    ((void **)self)[0xea] = func_0203bee8(self[0xe1], 1, data_ov190_020d5d34);
    ((void **)self)[0xeb] = func_0203bee8(self[0xe1], 1, data_ov190_020d5d44);
    ((void **)self)[0xec] = func_0203bee8(self[0xe1], 1, data_ov190_020d5d50);
    ((void **)self)[0xed] = func_0203bee8(self[0xe1], 1, data_ov190_020d5d60);
    ((void **)self)[0xee] = func_0203bee8(self[0xe1], 1, data_ov190_020d5d70);
    ((void **)self)[0xef] = func_0203bee8(self[0xe1], 1, data_ov190_020d5d80);

    ((void **)self)[0xf0] =
        func_ov107_020c9e50(func_ov107_020c9440(self, 1), &data_ov190_020d5d90);

    func_ov107_020c92b0(self, 0, 1, 0, 0x2000);
    func_ov107_020c92b0(self, 2, 1, 0, 0x1500);
    func_ov107_020c92b0(self, 1, 1, 0, 0x1500);
    func_ov107_020c92b0(self, 4, 1, 0, 0x1500);

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
    func_0203355c(0x12f, (int)((unsigned long long)r >> 32));
}






