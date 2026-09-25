/* Constructor of the ov291 enemy: installs the handlers (+8 tick, +0xc draw, +0x30/+0x38 hit
 * callbacks, +0x1dc finish, +0x1d0 callback), sets +0x1c9 to 2, the +0x64 pose (scale 0x1d00,
 * y 0x1d00), bit 5 of the +0x60 high byte and bit 3 of +0x1ae; builds the primary item from
 * pool entry 0 (subscribed, back-linked into its render object's +0x4c, its named joint
 * resolved into +0x39c, the node matrix callback armed with mode 6/3 and channel 3 bound),
 * keeps the named motion handle from pool entry 2 (+0x394), creates an effect node (+0x398,
 * subscribed, bit 0) hosting the pool entry 1 item (+0x388, placed at y 0x100 z -0x1000,
 * channels 0/1 bound), a placement on the +0x144 list (+0x38c), a shape on the +0x22c list
 * (+0x390, active), clears bits 1-3 of the +0x60 high byte and loads sound 0x16f. Finally a
 * 7-entry hit table (kind + offset each) is handed to the +0x38 hit callback and freed. */
typedef unsigned short u16;

struct Bit0 {
    unsigned bit0 : 1;
};

struct w8 { unsigned int lo : 8, rest : 24; };
struct hw60 { unsigned short lo : 8, hi : 8; };

struct HitEntry {
    unsigned int kind : 16;
    unsigned int flags : 16;
    int x;
    int y;
    int z;
};

struct HitTable {
    int word0;
    int word1;
    int nCount;
    struct HitEntry entries[7];
};

extern void func_ov291_020cc4c8(void);
extern void func_ov291_020cc50c(void);
extern void func_ov291_020cc604(void);
extern void func_ov291_020cc550(void);
extern void func_ov291_020cc530(void);
extern void func_ov291_020cc5f4(void);
extern void func_ov291_020cbfc4(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_0203bdfc(int item, const char *name);
extern void func_02014e18(int renderObj, void *cb, int ptr, int timing, int opt);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern int func_0203bf44(void);
extern void func_0203ca14(void *placement, int x, int y, int z);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern void func_0203355c(int id);
extern void *func_0203d15c(int size);
extern void func_0203d194(void *p);
extern const char data_ov291_020cd62c[];
extern const char data_ov291_020cd638[];

void func_ov291_020cc128(char *self)
{
    int *p;
    struct HitTable *tbl;

    /* The first handler store is written four times: the three dead copies vanish after scheduling
     * but spend the function's scheduling budget, which leaves the hit-table fill below in source
     * order as in the ROM (same device as Ov261_EnemyConstruct). */
    *(void **)(self + 0x8) = func_ov291_020cc4c8;
    *(void **)(self + 0x8) = func_ov291_020cc4c8;
    *(void **)(self + 0x8) = func_ov291_020cc4c8;
    *(void **)(self + 0x8) = func_ov291_020cc4c8;
    *(void **)(self + 0xc) = func_ov291_020cc50c;
    *(void **)(self + 0x30) = func_ov291_020cc604;
    *(void **)(self + 0x38) = func_ov291_020cc550;
    *(void **)(self + 0x1dc) = func_ov291_020cc530;
    *(void **)(self + 0x1d0) = func_ov291_020cc5f4;
    *(unsigned char *)(self + 0x1c9) = 2;
    *(int *)(self + 0x70) = 0x1d00;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x1d00;
    *(int *)(self + 0x6c) = 0;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x20) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 8;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440((int)self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(char **)(*(int *)(*(int *)(self + 0x384) + 0x88) + 0x4c) = self;
    *(u16 *)(self + 0x39c) = func_0203bdfc(*(int *)(self + 0x384), data_ov291_020cd62c);
    func_02014e18(*(int *)(*(int *)(self + 0x384) + 0x88) + 0x20, func_ov291_020cbfc4, 0, 6, 3);
    func_0203b9fc(*(int *)(self + 0x384), 3, 0, 1);
    *(int *)(self + 0x394) = func_ov107_020c9e50(func_ov107_020c9440((int)self, 2), data_ov291_020cd638);
    *(int *)(self + 0x398) = func_0203bf44();
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x398));
    ((struct Bit0 *)(*(int *)(self + 0x398) + 0x5c))->bit0 = 1;
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440((int)self, 1));
    func_0203bfb4(*(int *)(self + 0x398), *(int *)(self + 0x388));
    func_0203ca14((void *)(*(int *)(self + 0x388) + 4), 0, 0x100, -0x1000);
    func_0203b9fc(*(int *)(self + 0x388), 0, 0, 0);
    func_0203b9fc(*(int *)(self + 0x388), 1, 0, 0);
    p = func_01fffca8(self + 0x144, 4, 0x64);
    *(int *)(self + 0x38c) = *p = func_ov107_020c319c(self + 0x64);
    *(int **)(self + 0x390) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x390) = func_ov107_020c319c(self + 0x64);
    ((struct w8 *)(*(int *)(self + 0x390) + 8))->lo |= 1;
    ((struct hw60 *)(self + 0x60))->hi &= ~0xe;
    func_0203355c(0x16f);

    tbl = func_0203d15c(0x7c);
    tbl->nCount = 7;
    tbl->entries[0].kind = 0;
    tbl->entries[0].x = 0;
    tbl->entries[0].y = 0;
    tbl->entries[0].z = -0x8000;
    tbl->entries[1].kind = 2;
    tbl->entries[1].x = -0x590;
    tbl->entries[1].y = 0;
    tbl->entries[1].z = 0x1805;
    tbl->entries[2].kind = 1;
    tbl->entries[2].x = 0xc97a;
    tbl->entries[2].y = 0;
    tbl->entries[2].z = 0x2dc8;
    tbl->entries[3].kind = 0;
    tbl->entries[3].x = -0x590;
    tbl->entries[3].y = 0;
    tbl->entries[3].z = 0x1805;
    tbl->entries[4].kind = 1;
    tbl->entries[4].x = -0x13d96;
    tbl->entries[4].y = 0x1c01;
    tbl->entries[4].z = 0x1e09;
    tbl->entries[5].kind = 0;
    tbl->entries[5].x = -0x590;
    tbl->entries[5].y = 0;
    tbl->entries[5].z = 0x1805;
    tbl->entries[6].kind = 3;
    tbl->entries[6].x = -0xee2;
    tbl->entries[6].y = 0;
    tbl->entries[6].z = 0x14eac;
    if (*(void (**)(char *, int, struct HitTable *))(self + 0x38) != 0) {
        (*(void (**)(char *, int, struct HitTable *))(self + 0x38))(self, 0x7c, tbl);
    }
    func_0203d194(tbl);
}
