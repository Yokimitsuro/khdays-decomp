/* func_ov063_020b6844 -- issue a "spawn at the object's position" request. Builds the request
 * descriptor from the object's position (raised by 0x7800), its kind byte and its extension block,
 * builds a second descriptor whose direction vector is either the caller's raw vector or its
 * normalised form, clears the two one-shot bytes, marks it live, and hands the pair to the request
 * queue. Only continues past the queue call when the queue accepted it or the slot byte reads 4,
 * in which case it notifies func_ov022_020a4490.
 *
 * !! THIS WAS MIS-DIAGNOSED AS A REGISTER-ALLOCATION TIE FOR A LONG TIME. It is not one:
 * VEC_Mag takes ONE argument. The old source called it as
 * `VEC_Mag(r3p, 0x625, obj->ext, kind)` -- four. Because the extern was unprototyped
 * (`extern int VEC_Mag();`) that compiled silently, and the three phantom arguments were exactly
 * enough extra live values to push mwcc over its keep-vs-rematerialise threshold: it parked the
 * constant 1 (the `one` field) in a callee-saved register so it could reuse it for the later
 * `flag = 1`, emitting `movne r5,r6` where the ROM emits `movne r5,#1`. That one decision then
 * rotated three registers through the whole tail and looked exactly like an allocator coin-flip.
 * With the correct single argument every register falls into place.
 *
 * The tell was that the phantom arguments were invisible: the values 0x625, obj->ext and kind are
 * ALSO stored into the descriptors right before the call, so they legitimately sit in r1/r2/r3 at
 * the branch and the disassembly looks identical either way. Only grepping the matched tree for
 * real `VEC_Mag(` call sites -- every one of them one-argument -- exposed it.
 *
 * Also load-bearing: the three tail stores must be written in the ROM's order
 * one(0x20) -> flag25(0x25) -> b10(0x10); the `t = reqB.flag25` read only has to precede its
 * write, so the b10 store goes last. */
extern int VEC_Mag();
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
    int f08;         /* 0x08 */
    int f0c;         /* 0x0c */
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

void func_ov063_020b6844(int *base, Obj *obj, int unused, char *r3p)
{
    int *ent;
    ReqA reqA;
    ReqB reqB;
    unsigned char t;
    int flag;
    int kind;
    int one;

    ent = (int *)base[0xdb4 / 4];

    reqA.b = obj->pos;
    reqA.a = reqA.b;
    reqA.a.y += 0x7800;
    reqA.k = 0xc00;
    kind = obj->b15c;
    reqA.flags = kind;
    reqA.ptr = obj->ext;
    reqA.zero = 0;

    flag = 0;

    reqB.f0c = flag;
    reqB.f08 = 0x625;
    if (VEC_Mag(r3p) == 0) {
        reqB.v = *(Vec3 *)r3p;
    } else {
        func_01ff8d18(r3p, &reqB.v);
    }

    t = reqB.flag25;
    one = 1;
    reqB.one = one;
    t &= ~1;
    t = (unsigned char)t;
    t &= ~2;
    reqB.flag25 = t;
    reqB.b10 = 0;
    func_ov022_020a23a4(ent, 0x12c0, &reqB.o0, &reqB.o1);

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
