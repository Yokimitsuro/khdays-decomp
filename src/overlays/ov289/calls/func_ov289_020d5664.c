/*
 * func_ov289_020d5664 -- Ov287_Actor_InitClassAndSpawnParts.
 *
 * Class init for the ov287/ov288/ov289 actor triplet, installed at +0x18c by the
 * constructor at 020cfb78. It installs the nine class handlers, raises flags 0x100 and
 * 0x8000, sets the state byte at +0x1c9 to 2, ORs 0x44 into the high byte of the flags
 * halfword at +0x60 and 0xc into the flags at +0x1ae, loads the two unit-scale pairs at
 * +0x64..+0x70, spawns three subitems -- the first registered with the owner and its node
 * list initialised, the other two attached with bit 1 raised on their +0x5c -- then builds
 * an identity basis at unit 0x800 scale, allocates the 0x10 x 100 pool at +0x22c and starts
 * resource 0x15b on the node it creates.
 *
 * Ghidra: Ov287_Actor_InitClassAndSpawnParts(Ov287Actor *pActor), types /khdays/Ov287Actor
 * and /khdays/ActorSpawnBasis, with the handler slots at 0x1c/0x20/0x24/0x38 carved out of
 * /khdays/Actor's former padding.
 *
 * Byte-exact codegen notes (mwccarm 3.0/139), all three needed:
 *  - The two later subitems are stored with a chained assignment through the object field,
 *    `sub = *(void **)(obj + off) = f(...)`. That stores straight out of r0 before the next
 *    argument setup overwrites it. Writing it as two statements costs the allocator lr, and
 *    the halfword temp twenty-five instructions earlier moves out of lr with it.
 *  - Three callees are declared int rather than void even though the results are discarded.
 *    A non-void return on the callee keeps r0 reserved across the call, so the following
 *    load lands in r1 and the scheduler can hoist the next call's argument setup into the
 *    block. It only works with all three changed together.
 *  - The unit scale is written `scale = obj->nScale070 = 0x1000;` and read back for +0x68.
 *    Chaining it into a local makes mwcc materialise the constant at block entry, which the
 *    four plain assignments do not (measured: a plain constant floats exactly fifteen
 *    instructions, never the thirty-eight this function needs), while keeping the stores in
 *    the ROM's 0x70, 0x64, 0x68, 0x6c order that a two-target chain would collapse.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* the 0x3c basis block built on the stack and handed to func_ov107_020c32b8 */
struct ActorSpawnBasis {
    int scale;
    int field04;
    int field08;
    VecFx32 right;
    VecFx32 up;
    VecFx32 forward;
    int scaleX;
    int scaleY;
    int scaleZ;
};

struct Actor {
    u16 flags000;
    char pad002[6];
    void *pfnHandler008;
    void *pfnHandler00c;
    char pad010[0xc];
    void *pfnHandler01c;
    void *pfnHandler020;
    void *pfnHandler024;
    char pad028[8];
    void *pfnHandler030;
    char pad034[4];
    void *pfnHandler038;
    char pad03c[0x24];
    u16 flags060;
    u16 field062;
    int field064;
    int scale068;
    int field06c;
    int scale070;
    char pad074[0x28];
    int owner09c;
    char pad0a0[0x18c];
    u16 flags22c;
    char pad22e[0xfa];
    void *pfnHandler328;
};

extern void *func_ov107_020c9440(void *actor, int index);
extern void *func_0203b898(void *node);
extern int func_0203bfb4(int owner, void *sub);
extern int func_01fffc24(void *list);
extern int func_ov107_020c9074(void *actor, void *sub);
extern u32 func_01fffca8(int pool, int itemSize, int count);
extern void *func_ov107_020c32b8(struct ActorSpawnBasis *basis);
extern void func_0203355c(short resId, void *entry);

extern void func_ov289_020d5858(void);
extern void func_ov289_020d58a0(void);
extern void func_ov289_020d5970(void);
extern void func_ov289_020d5d08(void);
extern void func_ov289_020d5c88(void);
extern void func_ov289_020d58ec(void);
extern void func_ov289_020d5954(void);
extern void func_ov289_020d5d64(void);
extern void func_ov289_020d5bb8(void);

extern const VecFx32 data_02042270;
extern const VecFx32 data_02042264;
extern const VecFx32 data_02042258;

void func_ov289_020d5664(struct Actor *actor)
{
    struct ActorSpawnBasis basis;
    void *sub;
    void **entry;
    void *node;
    unsigned short *hw;
    unsigned int h;
    int scale;

    actor->flags000 |= 0x100;
    actor->pfnHandler008 = (void *)func_ov289_020d5858;
    actor->pfnHandler00c = (void *)func_ov289_020d58a0;
    actor->pfnHandler01c = (void *)func_ov289_020d5970;
    actor->pfnHandler030 = (void *)func_ov289_020d5d08;
    actor->pfnHandler038 = (void *)func_ov289_020d5c88;
    actor->pfnHandler020 = (void *)func_ov289_020d58ec;
    actor->pfnHandler024 = (void *)func_ov289_020d5954;
    *(void **)((char *)actor + 0x1d0) = (void *)func_ov289_020d5d64;
    *(void **)((char *)actor + 0x1dc) = (void *)func_ov289_020d5bb8;

    *(u8 *)((char *)actor + 0x1c9) = 2;
    /* flags060.hi |= 0x44 -- explicit-shift form; a bitfield |= adds a redundant mask */
    hw = (unsigned short *)((char *)actor + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x44) << 0x18) >> 0x10);
    *(u16 *)((char *)actor + 0x1ae) |= 0xc;

    actor->flags000 |= 0x8000;

    scale = actor->scale070 = 0x1000;
    actor->field064 = 0;
    actor->scale068 = scale;
    actor->field06c = 0;

    sub = func_0203b898(func_ov107_020c9440(actor, 0));
    *(void **)((char *)actor + 0x384) = sub;
    func_0203bfb4(actor->owner09c, *(void **)((char *)actor + 0x384));
    func_01fffc24((char *)actor + 0x398);

    sub = *(void **)((char *)actor + 0x3c0) = func_0203b898(func_ov107_020c9440(actor, 1));
    func_ov107_020c9074(actor, sub);
    *(u32 *)((char *)sub + 0x5c) |= 2;

    sub = *(void **)((char *)actor + 0x3c8) = func_0203b898(func_ov107_020c9440(actor, 2));
    func_ov107_020c9074(actor, sub);
    *(u32 *)((char *)sub + 0x5c) |= 2;

    basis.right = data_02042270;
    basis.up = data_02042264;
    basis.forward = data_02042258;
    basis.scaleZ = 0x800;
    basis.scaleY = 0x800;
    basis.scaleX = 0x800;
    basis.field04 = 0x800;
    basis.scale = 0;
    basis.field08 = 0;

    *(u32 *)((char *)actor + 0x388) = func_01fffca8((int)((char *)actor + 0x22c), 0x10, 100);
    node = func_ov107_020c32b8(&basis);
    entry = *(void ***)((char *)actor + 0x388);
    *entry = node;
    func_0203355c((short)0x15b, entry);
}
