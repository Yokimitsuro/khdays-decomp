/* NONMATCHING — equivalent C (twin of the matched func_ov131_020cbfc4), scheduler tie.
 *
 * 348B byte-exact except 3 mwcc slot-filling spots: the ROM hoists the bitfield base
 * `add r2,r4,#0x100` early to fill the +0x1d0 vtable ldr->str delay (into r2, separate
 * from the r1 scalar-store temp) while mwcc computes it late in r1; plus the g.scale
 * store position and the *p store register. Register-pressure driven, not source-
 * steerable; confirmed unreproducible across all 26 mwcc generations and statement
 * reorders. Structure validated against the byte-exact twin func_ov131_020cbfc4. */
struct v3 { int a, b, c; };

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

    *(void **)(param_1 + 8) = func_ov294_020d1b80;
    *(void **)(param_1 + 0xc) = func_ov294_020d1b9c;
    *(void **)(param_1 + 0x30) = func_ov294_020d1c00;
    *(void **)(param_1 + 0x1d0) = func_ov294_020d1c4c;
    *(char *)(param_1 + 0x1c9) = 2;
    *(int *)(param_1 + 0x70) = 0x1200;
    *(int *)(param_1 + 0x64) = 0;
    *(int *)(param_1 + 0x68) = 0;
    *(int *)(param_1 + 0x6c) = 0;
    *(unsigned short *)(param_1 + 0x1ae) |= 0x10;
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
