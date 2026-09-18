/* Constructor of the ov219 enemy (twin of the ov220 constructor, sound 0x136): installs the handlers
 * (+8 tick, +0xc draw, +0x1c message, +0x30/+0x34 callbacks, +0x1d0 hit, +0x1dc finish,
 * +0x1d4/+0x1e0/+0x1e4 callbacks), seeds the +0x64 pose (scale 0x7cc, y 0x7cc), writes the
 * {-0x54f, 0, -0x625, 0x54e, 0xd34, 0x294} bounds at +0x1fc; builds the primary item from pool
 * entry 0 (+0x384, subscribed), keeps the named motion handle from pool entry 1 (+0x394), the
 * three sub-items listed by the overlay's 0x020d18a0 byte table into the inline slot table at
 * +0x3c4 (attached, bit 1), two placements on the +0x22c/+0x144 lists (+0x388/+0x38c) from the
 * +0x64 pose, then loads sound 0x136. Codegen: the box is spelled with the max corner derived
 * from the min corner (min.x - 0xd6, min.x + 0xa9d, min.y + 0xd34, min.z + 0x8b9), which is
 * what makes mwcc chain the constants from the one pool word; the slot store is chained
 * through `item` so the call result is stored before the copy. */
typedef unsigned char u8;
typedef void (*Callback)(void);
typedef struct { int w[6]; } Bounds;
typedef struct { u8 id[3]; } Kinds;
typedef struct { int pItem; int pad; } SubitemSlot;

extern void func_ov219_020cfdfc(void);
extern void func_ov219_020cfe3c(void);
extern void func_ov219_020cfee4(void);
extern void func_ov219_020d008c(void);
extern void func_ov219_020cfff0(void);
extern void func_ov219_020d00e8(void);
extern void func_ov219_020d0054(void);
extern void func_ov219_020d0320(void);
extern void func_ov219_020d0340(void);
extern void func_ov219_020d036c(void);
extern void *func_ov107_020c9440(char *self, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern int func_ov107_020c9e50(void *item, const char *name);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *pose);
extern void func_0203355c(int resourceId);
extern const Kinds data_ov219_020d18a0;
extern const char data_ov219_020d18cc[];

void func_ov219_020cfc04(char *self)
{
    Kinds kinds = data_ov219_020d18a0;
    Bounds bounds;
    const u8 *kind;
    int *slot;
    int item;
    int i;

    bounds.w[0] = -0x54f;
    bounds.w[1] = 0;
    bounds.w[2] = bounds.w[0] - 0xd6;
    bounds.w[3] = bounds.w[0] + 0xa9d;
    bounds.w[4] = bounds.w[1] + 0xd34;
    bounds.w[5] = bounds.w[2] + 0x8b9;
    *(Callback *)(self + 0x8) = func_ov219_020cfdfc;
    *(Callback *)(self + 0xc) = func_ov219_020cfe3c;
    *(Callback *)(self + 0x1c) = func_ov219_020cfee4;
    *(Callback *)(self + 0x30) = func_ov219_020d008c;
    *(Callback *)(self + 0x34) = func_ov219_020cfff0;
    *(Callback *)(self + 0x1d0) = func_ov219_020d00e8;
    *(Callback *)(self + 0x1dc) = func_ov219_020d0054;
    *(Callback *)(self + 0x1d4) = func_ov219_020d0320;
    *(Callback *)(self + 0x1e0) = func_ov219_020d0340;
    *(Callback *)(self + 0x1e4) = func_ov219_020d036c;
    *(int *)(self + 0x70) = 0x7cc;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x7cc;
    *(int *)(self + 0x6c) = 0;
    *(Bounds *)(self + 0x1fc) = bounds;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(self, 0));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    *(int *)(self + 0x394) = func_ov107_020c9e50(func_ov107_020c9440(self, 1), data_ov219_020d18cc);
    kind = kinds.id;
    for (i = 0; i < 3; i++) {
        item = ((SubitemSlot *)(self + 0x3c4))[i].pItem = func_0203b898(func_ov107_020c9440(self, *kind++));
        func_ov107_020c9074(self, item);
        *(int *)(item + 0x5c) |= 2;
    }
    *(int **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 0x64);
    slot = func_01fffca8(self + 0x144, 4, 100);
    *(int *)(self + 0x38c) = *slot = func_ov107_020c319c(self + 0x64);
    func_0203355c(0x136);
}
