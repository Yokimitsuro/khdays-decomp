/* Constructor of the ov213 actor's third form: installs the handlers (+8 tick, +0xc draw,
 * +0x20 hook, +0x1c message, +0x30 callback, +0x1d0 position broadcast), raises bits 2-3 of
 * +0x1ae and flags 0x44 in the +0x60 high byte, queues pose 2 at +0x1c9, zeroes the +0x64
 * velocity, sets the +0x70 scale to 0.5 and bit 2 on the subscriber's +0x5c. The collision item
 * comes from pool entry 0x42 (subscribed, its four channels bound with (0, 1)), the two sub-items
 * from the data_ov213_020d2f3c entries into a fresh 16-byte slot table (+0x394, attached, bit 1
 * on their +0x5c), and a shape on the +0x144 list (+0x38c) is built from the +0x64 velocity. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef void (*Callback)(void);

struct Ov213SubitemSlot {
    int pItem;
    int pad4;
};

extern void func_ov213_020d1824(void);
extern void func_ov213_020d1864(void);
extern void func_ov213_020d18a4(void);
extern void func_ov213_020d1908(void);
extern void func_ov213_020d1aac(void);
extern void func_ov213_020d1afc(void);
extern void *func_ov107_020c9440(int pool, int index);
extern int func_0203b898(void *item);
extern int func_0203bfb4(int subscriber, int item);
extern void func_0203b9fc(int item, int channel, int a, int b);
extern void *func_0203d15c(int size);
extern void func_ov107_020c9074(char *self, int item);
extern int *func_01fffca8(char *list, int stride, int max);
extern int func_ov107_020c319c(char *pose);
extern const int data_ov213_020d2f3c[2];
extern const Vec3 data_02041dc8;

void func_ov213_020d165c(char *self)
{
    int kinds[2];
    u16 hw;
    int i;
    int *slot;
    kinds[0] = data_ov213_020d2f3c[0];
    kinds[1] = data_ov213_020d2f3c[1];
    *(Callback *)(self + 0x8) = func_ov213_020d1824;
    *(Callback *)(self + 0xc) = func_ov213_020d1864;
    *(Callback *)(self + 0x20) = func_ov213_020d18a4;
    *(Callback *)(self + 0x1c) = func_ov213_020d1908;
    *(Callback *)(self + 0x30) = func_ov213_020d1aac;
    *(Callback *)(self + 0x1d0) = func_ov213_020d1afc;
    *(u16 *)(self + 0x100 + 0xae) |= 0xc;
    hw = *(u16 *)(self + 0x60);
    *(u16 *)(self + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 0x44) << 0x18) >> 0x10);
    *(unsigned char *)(self + 0x1c9) = 2;
    *(Vec3 *)(self + 0x64) = data_02041dc8;
    *(int *)(self + 0x70) = 0x800;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x388) = func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), 0x42));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x388));
    func_0203b9fc(*(int *)(self + 0x388), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x388), 2, 0, 1);
    func_0203b9fc(*(int *)(self + 0x388), 4, 0, 1);
    func_0203b9fc(*(int *)(self + 0x388), 1, 0, 1);
    *(void **)(self + 0x394) = func_0203d15c(0x10);
    for (i = 0; i < 2; i++) {
        (*(struct Ov213SubitemSlot **)(self + 0x394))[i].pItem =
            func_0203b898(func_ov107_020c9440(*(int *)(self + 0x384), kinds[i]));
        func_ov107_020c9074(self, (*(struct Ov213SubitemSlot **)(self + 0x394))[i].pItem);
        *(int *)((*(struct Ov213SubitemSlot **)(self + 0x394))[i].pItem + 0x5c) |= 2;
    }
    slot = func_01fffca8(self + 0x144, 4, 0x64);
    *(int *)(self + 0x38c) = *slot = func_ov107_020c319c(self + 0x64);
}
