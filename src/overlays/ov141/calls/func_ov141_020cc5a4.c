/* Release the attachments the actor's state no longer needs, then push its transform
 * down the node chain.  Sibling of OvNNN_ReleaseByStateAndSyncSrt (312 B, ov166-ov177)
 * over a different attachment layout: three handles in the sub-block at +0x390 plus
 * one at +0x3d0 for states other than 5, and a fourth handle for states other than 6.
 *
 * PARKED with no diff note, and the reason was pure arity.  It declared
 *   extern int func_0203c650();      -- really (owner, handle)
 *   extern int func_ov107_020cb100();-- really (attachment)
 * with EMPTY parentheses, so the compiler had no prototype to check the four one-
 * argument calls against and accepted every one of them silently.  Passing the handle
 * makes it match, unchanged otherwise.
 *
 * That spelling is worth recognising: `extern int f();` in a parked file is not a
 * declaration, it is the absence of one, and it disables exactly the check that would
 * have caught this.  tools/audit_arity.py only compared declared-vs-used counts, so a
 * declaration with no parameter list slipped straight through it.
 */
extern void func_0203c650(int owner, int handle);
extern void func_ov107_020c7ca4(void *actor);
extern void func_ov107_020cb100(int attachment);

struct Blk {
    int data[11];
};

struct P398 {
    char pad[4];
    struct Blk blk;        /* 0x04 */
};

struct P388 {
    char pad[0x10];
    struct Blk blk;        /* 0x10 */
};

struct Sub {
    char pad0[0xc];
    int m0c;               /* 0x0c */
    char pad1[0x14 - 0x10];
    int m14;               /* 0x14 */
    char pad2[0x1c - 0x18];
    int m1c;               /* 0x1c */
    char pad3[0x24 - 0x20];
    int m24;               /* 0x24 */
};

struct Obj {
    char pad0[0x3c];
    int f3c;               /* 0x3c */
    char pad40[0x1c6 - 0x40];
    signed char f1c6;      /* 0x1c6 */
    char pad1c7[0x388 - 0x1c7];
    struct P388 **f388;    /* 0x388 */
    struct P388 *f38c;     /* 0x38c */
    struct Sub *f390;      /* 0x390 */
    char pad394[0x398 - 0x394];
    struct P398 *f398;     /* 0x398 */
    char pad39c[0x3d0 - 0x39c];
    int f3d0;              /* 0x3d0 */
};

void func_ov141_020cc5a4(struct Obj *a) {
    if (a->f1c6 != 5) {
        if (a->f390->m0c != 0) {
            func_0203c650(a->f3c, a->f390->m0c);
            a->f390->m0c = 0;
        }
        if (a->f390->m14 != 0) {
            func_0203c650(a->f3c, a->f390->m14);
            a->f390->m14 = 0;
        }
        if (a->f390->m1c != 0) {
            func_0203c650(a->f3c, a->f390->m1c);
            a->f390->m1c = 0;
        }
        if (a->f3d0 != 0) {
            func_ov107_020cb100(a->f3d0);
            a->f3d0 = 0;
        }
    }

    if (a->f1c6 != 6 && a->f390->m24 != 0) {
        func_0203c650(a->f3c, a->f390->m24);
        a->f390->m24 = 0;
    }

    (*a->f388)->blk = a->f398->blk;
    a->f38c->blk = a->f398->blk;

    func_ov107_020c7ca4(a);
}
