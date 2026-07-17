/* NONMATCHING - 348/348 B, THREE instructions from exact. Was parked as a
 * "scheduler tie ... register-pressure driven, not source-steerable; confirmed
 * unreproducible across all 26 mwcc generations and statement reorders".
 *
 * That was wrong, and the biggest of the three claims is now fixed: the ROM's
 * hoisted `add r2, r4, #0x100` is not the scheduler being clever, it is a
 * SUB-OBJECT POINTER that is live as a variable. Declaring
 *     struct Body *b = (struct Body *)(param_1 + 0x100);
 * at the top and writing `b->flags |= 0x10` puts the add exactly where the ROM has
 * it, in the same register (r2), filling the same ldr->str delay. 0x100 is
 * encodable as an ARM immediate and 0xae fits an ldrh displacement, which is why
 * the split looks like a scheduling artifact -- it is really a struct base.
 *
 * REMAINING (3, all "which scratch register"):
 *   - the ldrh/orr/strh temp: ROM r3, mwcc r1;
 *   - `str r3, [sp, #0x10]` (g.scale): ROM keeps it in source order, mwcc sinks it
 *     into the func_01fffca8 argument setup;
 *   - `str r0, [r5]` vs `str r1, [r5]`: both hold the same copied value.
 * Do NOT record these as ties without trying declaration order first -- that is
 * what cracked TickTagTrackerNodes, and this file has already been wrong once.
 * The asm stub keeps the blob byte-exact. */
struct v3 { int a, b, c; };
struct Body { char pad[0xae]; unsigned short flags; };

extern struct v3 data_02041dc8;

extern void func_ov294_020d1b80(void);
extern void func_ov294_020d1b9c(void);
extern void func_ov294_020d1c00(void);
extern void func_ov294_020d1c4c(void);

extern void *func_ov107_020c9440();
extern void *func_0203b898();
extern void func_0203bfb4();
extern void func_0203ca14();
extern void func_0203b9fc();
extern void func_ov107_020c92b0();
extern void *func_01fffca8();
extern long long func_ov107_020c319c();
extern void func_0203355c();

/* ov294 actor init: install the handler vtable (update/transform/registry/damage),
 * set the fall speed (0x1200) and flags, spawn the actor's render instance (0203b898)
 * and register it, seed two sorted spline lists (020c319c fills from the shared Vec3
 * const data_02041dc8), and kick off the intro tween (0203355c). */
void func_ov294_020d1a24(int param_1) {
    struct { struct v3 t; int scale; } g;
    long long r;
    struct Body *b = (struct Body *)(param_1 + 0x100);

    *(void **)(param_1 + 8) = func_ov294_020d1b80;
    *(void **)(param_1 + 0xc) = func_ov294_020d1b9c;
    *(void **)(param_1 + 0x30) = func_ov294_020d1c00;
    *(void **)(param_1 + 0x1d0) = func_ov294_020d1c4c;
    *(char *)(param_1 + 0x1c9) = 2;
    *(int *)(param_1 + 0x70) = 0x1200;
    *(int *)(param_1 + 0x64) = 0;
    *(int *)(param_1 + 0x68) = 0;
    *(int *)(param_1 + 0x6c) = 0;
    b->flags |= 0x10;
    *(void **)(param_1 + 0x384) = func_0203b898(func_ov107_020c9440(param_1));
    func_0203bfb4(*(int *)(param_1 + 0x9c), *(void **)(param_1 + 0x384));
    func_0203ca14(*(int *)(param_1 + 0x384) + 4, 0, -0x1200, 0);
    func_0203b9fc(*(int *)(param_1 + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(param_1 + 0x384), 4, 0, 1);
    func_ov107_020c92b0(param_1, 2, 2, 0, 0x2000);
    g.t = data_02041dc8;
    g.scale = 0x1200;
    *(void **)(param_1 + 0x388) = func_01fffca8(param_1 + 0x22c, 0x10, 100);
    **(int **)(param_1 + 0x388) = (int)func_ov107_020c319c(&g);
    {
        int *p = func_01fffca8(param_1 + 0x144, 4, 100);
        r = func_ov107_020c319c(&g);
        *p = (int)r;
        *(int *)(param_1 + 0x390) = (int)r;
    }
    func_0203355c(0x171, (int)r);
}
