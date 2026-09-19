/* Construction of the ov226 enemy's item: installs the handlers (+8 020d411c, +0xc 020d4140,
 * +0x1c 020d4178, +0x30 020d42d8), raises bits 1-3 and 6 of the +0x60 high byte and bit 2 of
 * +0x1ae and of the +0x9c parent's +0x5c, sets +0x70 to 0xbe6, clears +0x54/+0x58/+0x64/+0x6c
 * and copies +0x70 to +0x68 (the data_ov226_020d4b50 kind is copied to the stack meanwhile),
 * builds the +0x384 item from pose 0x1a of the +0x390 pool (channels 0 and 4 enabled),
 * subscribes it to the parent and finalises it, builds the +0x394 sub-item from the saved kind
 * (registered on the actor, bit 1 of +0x5c raised), and finally a +0x22c list slot takes the
 * +0x64 pose as +0x388 with bit 1 of its +8 low byte raised; +0x38c clears. */
typedef struct {
    unsigned f : 8;
} B8;

struct Ov226Saved { int w; };
typedef struct { int x, y, z; } Vec3;
static inline void VEC_Set(Vec3 *v, int x, int y, int z) { v->x = x; v->y = y; v->z = z; }

extern int func_ov107_020c9440(int owner, int kind);
extern int func_0203b898(int a);
extern void func_0203b9fc(int obj, int mode, int a, int b);
extern void func_0203bfb4(int a, int obj);
extern void func_0203c7ac(int obj, int a);
extern void func_ov107_020c9074(int self, int obj);
extern int func_01fffca8(int a, int b, int c);
extern int func_ov107_020c319c(int a);
extern void func_ov226_020d411c(void);
extern void func_ov226_020d4140(void);
extern void func_ov226_020d4178(void);
extern void func_ov226_020d42d8(void);
extern const struct Ov226Saved data_ov226_020d4b50;

void func_ov226_020d3f94(char *self) {
    int owner;
    unsigned short v;
    struct Ov226Saved saved;
    int sub;

    owner = *(int *)(self + 0x390);
    *(void **)(self + 8) = (void *)func_ov226_020d411c;
    *(void **)(self + 0xc) = (void *)func_ov226_020d4140;
    *(void **)(self + 0x1c) = (void *)func_ov226_020d4178;
    *(void **)(self + 0x30) = (void *)func_ov226_020d42d8;

    saved = data_ov226_020d4b50;
    v = *(unsigned short *)(self + 0x60);
    *(unsigned short *)(self + 0x60) =
        (unsigned short)((v & ~0xff00)
                         | (((((unsigned int)v << 0x10) >> 0x18 | 0x4e) << 0x18) >> 0x10));

    *(unsigned short *)(self + 0x1ae) |= 4;
    *(int *)(self + 0x70) = 0xbe6;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    VEC_Set((Vec3 *)(self + 0x64), 0, *(int *)(self + 0x70), 0);

    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(owner, 0x1a));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 4, 0, 1);
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203c7ac(*(int *)(self + 0x384), 0);

    sub = *(int *)(self + 0x394) = func_0203b898(func_ov107_020c9440(owner, saved.w));
    func_ov107_020c9074((int)self, sub);
    *(int *)(*(int *)(self + 0x394) + 0x5c) |= 2;

    *(int *)(self + 0x388) = func_01fffca8((int)(self + 0x22c), 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c((int)(self + 0x64));
    ((B8 *)(*(int *)(self + 0x388) + 8))->f |= 2;
    *(int *)(self + 0x38c) = 0;
}
