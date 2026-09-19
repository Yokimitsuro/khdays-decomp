/* Constructor of the ov213 actor: installs the handlers (+8 tick, +0x20 hook, +0x1c message,
 * +0x30 callback, +0x1dc collision-set), sets the +0x70/+0x68 scales to 1/16 and clears the
 * +0x64/+0x6c/+0x58/+0x54 words, queues pose 2 at +0x1c9, raises bit 2 of the +0x9c list's
 * +0x5c word, flags 0x66 in the +0x60 high byte and bits 0x1d of +0x1ae, clears the two +0x218
 * halfwords, then builds the two collision items from pool entries 0x3f / 0x40 (+0x388 / +0x38c,
 * subscribed to +0x9c) and the +0x394 slot item from the data_ov213_020d2f70 entry (attached,
 * bit 1 of its +0x5c). The pool entry is a one-word wrapper struct copied to the stack early
 * (the ROM's [sp] spill). */
typedef void (*Callback)(void);
typedef unsigned short u16;

extern void func_ov213_020d2504(void);
extern void func_ov213_020d2530(void);
extern void func_ov213_020d2594(void);
extern void func_ov213_020d275c(void);
extern void func_ov213_020d2678(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_ov107_020c9074(int self, int item);
struct Ov213PoolEntry { int index; };
extern const struct Ov213PoolEntry data_ov213_020d2f70;

void func_ov213_020d23c0(int self) {
    struct Ov213PoolEntry entry = data_ov213_020d2f70;
    int item;

    *(Callback *)(self + 0x8) = func_ov213_020d2504;
    *(Callback *)(self + 0x20) = func_ov213_020d2530;
    *(Callback *)(self + 0x1c) = func_ov213_020d2594;
    *(Callback *)(self + 0x30) = func_ov213_020d275c;
    *(Callback *)(self + 0x1dc) = func_ov213_020d2678;
    *(int *)(self + 0x70) = 0x100;
    *(int *)(self + 0x64) = 0;
    *(int *)(self + 0x68) = 0x100;
    *(int *)(self + 0x6c) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(self + 0x54) = 0;
    *(unsigned char *)(self + 0x1c9) = 2;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x66) << 0x18) >> 0x10);
    }
    *(u16 *)(self + 0x100 + 0xae) |= 0x1d;
    *(u16 *)(self + 0x200 + 0x18) = 0;
    *(u16 *)(self + 0x200 + 0x1a) = 0;
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), 0x3f));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    *(int *)(self + 0x38c) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), 0x40));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x38c));
    item = *(int *)(self + 0x394) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), entry.index));
    func_ov107_020c9074(self, item);
    *(int *)(*(int *)(self + 0x394) + 0x5c) |= 2;
}
