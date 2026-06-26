extern int func_01ff8cb8();
extern int func_01ff8d18();
extern int func_ov022_020a23a4();
extern int func_ov022_020a1064();
extern int func_ov022_020a4490();

typedef struct { int x, y, z; } Vec3;

typedef struct {
    Vec3 a;       /* 0x00 */
    Vec3 b;       /* 0x0c */
    int flags;    /* 0x18 */
    int k;        /* 0x1c */
    void *ptr;    /* 0x20 */
    int zero;     /* 0x24 */
} ReqA;

typedef struct {
    int o0;          /* 0x00 */
    int o1;          /* 0x04 */
    char pad08[8];   /* 0x08 */
    char b10;        /* 0x10 */
    char pad11[3];   /* 0x11 */
    Vec3 v;          /* 0x14 */
    int one;         /* 0x20 */
    char pad24;      /* 0x24 */
    unsigned char flag25; /* 0x25 */
    char pad26[2];   /* 0x26 */
} ReqB;

typedef struct {
    char pad[0xa4];
    Vec3 pos;        /* 0xa4 */
    char pad2[0xac]; /* 0xb0 .. 0x15b */
    unsigned char b15c; /* 0x15c */
    char pad3[3];
    char ext[1];     /* 0x160 */
} Obj;

void func_ov030_020b4410(int *base, Obj *obj, int unused, char *r3p)
{
    int *ent;
    ReqA reqA;
    ReqB reqB;
    unsigned char t;
    int flag;

    ent = (int *)base[0xdb4 / 4];

    reqA.b = obj->pos;
    reqA.a = reqA.b;
    reqA.a.y += 0x7800;
    reqA.k = 0xc00;
    reqA.flags = obj->b15c;
    reqA.ptr = obj->ext;
    reqA.zero = 0;

    flag = 0;
    if (func_01ff8cb8(r3p, 0x625, obj->ext, obj->b15c, 0x625, flag) != 0) {
        func_01ff8d18(r3p, &reqB.v);
    } else {
        reqB.v = *(Vec3 *)r3p;
    }

    t = reqB.flag25;
    reqB.one = 1;
    t &= ~1;
    t = (unsigned char)t;
    t &= ~2;
    reqB.flag25 = t;
    reqB.b10 = 0;
    func_ov022_020a23a4(ent, 0x12c0, &reqB.o0, &reqB.o1);

    flag = 0;
    if (func_ov022_020a1064(ent, &reqA, &reqB.o0) != 0) {
        flag = 1;
    } else if (*((unsigned char *)ent + 0x26c4) == 4) {
        flag = 1;
    }
    if (flag == 0) {
        return;
    }
    func_ov022_020a4490(ent, *(short *)((char *)ent + 0x7aa), 1);
}
