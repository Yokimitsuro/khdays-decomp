/* Constructor of the ov266 tail sub-actor: installs the handlers (+0xc draw veneer, +0x30
 * callback, +0x1d0 hit), flags 0x4e in the +0x60 high byte and bits 0x14 of +0x1ae, sets the
 * +0x70 latch to 0x1800 with the +0x64/+0x68 scale cleared and +0x6c at -0x1800/2, clears
 * +0x54/+0x58, then creates the +0x388 pool seeded with the camera key and flags it. Codegen:
 * the -latch/2 is computed from the just-stored +0x70 (forwarded, so the ROM negates the 0x1800
 * register) into a local BEFORE the zero stores, which keeps the zero in r0 and the half in r1
 * and gives the ROM's store order. */
typedef void (*Callback)(void);
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int value;
    int pad_0004;
    u32 flags : 8;
} PoolEntry;

extern void func_ov267_020d5810(void);
extern void func_ov267_020d5908(void);
extern void func_ov267_020d58a4(void);
extern PoolEntry *func_01fffca8(void *pool, int elementSize, int capacity);
extern int func_ov107_020c319c(void *camera);

void func_ov267_020d573c(char *self)
{
    u16 hw;
    int nHalf;

    *(Callback *)(self + 0xc) = func_ov267_020d5810;
    *(Callback *)(self + 0x30) = func_ov267_020d5908;
    *(Callback *)(self + 0x1d0) = func_ov267_020d58a4;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((u32)hw << 0x10) >> 0x18) | 0x4e) << 0x18) >> 0x10);
    *(u16 *)(self + 0x100 + 0xae) |= 0x14;
    *(int *)(self + 0x70) = 0x1800;
    nHalf = -*(int *)(self + 0x70) / 2;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0;
    *(int *)(self + 0x6c) = nHalf;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(PoolEntry **)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 100);
    (*(PoolEntry **)(self + 0x388))->value = func_ov107_020c319c(self + 0x64);
    (*(PoolEntry **)(self + 0x388))->flags |= 2;
}
