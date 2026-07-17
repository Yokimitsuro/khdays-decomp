/* func_ov212_020cc4e0 -- reset the sub-object, then probe the world and cache the hit position.
 *
 * One of a 3-member shape family; the twins live in ov266/ov267 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * func_02016320 fills a 0x30-byte probe record; only the vector at +0x24 of it is kept, and only
 * when the probe reports a hit. It lands in the owner's slot at +0x4fc. The callback pointer at
 * +0x6c is re-armed to func_0203bc78 either way -- note that is the same function called directly
 * a few lines above, so the pool entry does double duty as a value and as a call target. */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    char pad0[0x24];
    VecFx32 pos;
} Probe;

extern void func_0203c960(int a);
extern void func_0203bc78(int a, int b);
extern int func_02016320(int a, Probe *out, int b, int c);

void func_ov212_020cc4e0(int obj) {
    Probe probe;
    int owner;

    owner = *(int *)(obj + 0x84);
    func_0203c960(obj + 0x30);
    func_0203bc78(obj, 1);
    if (func_02016320(*(int *)(obj + 0x88) + 0x20, &probe, 0, *(int *)(owner + 0x594)) != 0) {
        *(VecFx32 *)(owner + 0x4fc) = probe.pos;
    }
    *(void **)(obj + 0x6c) = (void *)func_0203bc78;
}
