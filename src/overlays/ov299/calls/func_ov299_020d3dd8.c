/* Constructor of the ov299 enemy: installs the handlers (+8 tick, +0xc draw, +0x1c message,
 * +0x30 hit callback, +0x1d0 callback), sets bits 1-4/6 of the +0x60 high byte and bit 2 of
 * +0x1ae, the +0x70 scale (0x800) and clears +0x54/+0x58; builds the primary item from entry 2
 * of the +0x390 pool (subscribed), the three +0x394 sub-items from the pool entries named by the
 * overlay's kind table (attached, bit 1), a shape on the +0x22c list (+0x388, bit 1) and clears
 * +0x38c. */
typedef unsigned char u8;
typedef unsigned short u16;

struct w8 { unsigned int lo : 8, rest : 24; };

struct Kinds3 { u8 a, b, c; };

struct Ov299Actor {
    char pad000[0x394];
    struct { int pItem; int nPad; } subitems[3];
};

extern void func_ov299_020d3f44(void);
extern void func_ov299_020d3f7c(void);
extern void func_ov299_020d3fb4(void);
extern void func_ov299_020d41c0(void);
extern void func_ov299_020d4284(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_ov107_020c9074(int self, int item);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern const struct Kinds3 data_ov299_020d4de8;

void func_ov299_020d3dd8(char *self)
{
    struct Kinds3 kinds;
    int pool;
    int i;
    int item;

    kinds = data_ov299_020d4de8;
    pool = *(int *)(self + 0x390);
    *(void **)(self + 0x8) = func_ov299_020d3f44;
    *(void **)(self + 0xc) = func_ov299_020d3f7c;
    *(void **)(self + 0x1c) = func_ov299_020d3fb4;
    *(void **)(self + 0x30) = func_ov299_020d4284;
    *(void **)(self + 0x1d0) = func_ov299_020d41c0;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x5e) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 4;
    *(int *)(self + 0x70) = 0x800;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(pool, 2));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    for (i = 0; i < 3; i++) {
        ((struct Ov299Actor *)self)->subitems[i].pItem = func_0203b898(func_ov107_020c9440(pool, ((u8 *)&kinds)[i]));
        func_ov107_020c9074((int)self, ((struct Ov299Actor *)self)->subitems[i].pItem);
        *(int *)(((struct Ov299Actor *)self)->subitems[i].pItem + 0x5c) |= 2;
    }
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    ((struct w8 *)(*(int *)(self + 0x388) + 8))->lo |= 2;
    *(int *)(self + 0x38c) = 0;
}
