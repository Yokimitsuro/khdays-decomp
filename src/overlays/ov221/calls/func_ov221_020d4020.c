/* Construction of the ov221 enemy's item: installs the handlers (+8 020d4218, +0xc 020d424c,
 * +0x1c 020d42b0, +0x30 020d443c), raises bit 5 and then bits 1-3 and 6 of the +0x60 high byte
 * (the data_ov221_020d4ddc kind is copied to the stack between the two writes), bit 2 of +0x1ae
 * and of the +0x9c parent's +0x5c, sets +0x70 to 1 and clears +0x54/+0x58, builds the +0x384
 * item from pose 0x1a of the +0x390 pool (channels 0, 2 and 4 enabled) and gives its +0x88 track's
 * +0x78 the rolling data_ov221_020d4e54 slot (which then advances, wrapping to 3 at 0x1f);
 * a built item is subscribed to the parent and finalised. A non-negative saved kind builds the
 * +0x394 sub-item (registered on the actor, bit 1 of +0x5c raised). Finally a +0x22c list slot
 * takes the +0x64 pose as +0x388 with bit 1 of its +8 low byte raised, and +0x38c clears. */
typedef struct {
    unsigned f : 8;
} B8;

struct Ov221Saved { int w; };
struct RollingCounter { unsigned char value; };

extern int func_ov107_020c9440(int owner, int kind);
extern int func_0203b898(int a);
extern void func_0203b9fc(int obj, int mode, int a, int b);
extern void func_02016b60(int a, unsigned int b, unsigned int slot);
extern void func_0203bfb4(int a, int obj);
extern void func_0203c7ac(int obj, int a);
extern void func_ov107_020c9074(int self, int obj);
extern int func_01fffca8(int a, int b, int c);
extern int func_ov107_020c319c(int a);
extern void func_ov221_020d4218(void);
extern void func_ov221_020d424c(void);
extern void func_ov221_020d42b0(void);
extern void func_ov221_020d443c(void);
extern const struct Ov221Saved data_ov221_020d4ddc;
extern struct RollingCounter data_ov221_020d4e54;

void func_ov221_020d4020(char *self) {
    int owner;
    unsigned short v;
    struct Ov221Saved saved;

    owner = *(int *)(self + 0x390);
    *(void **)(self + 8) = (void *)func_ov221_020d4218;
    *(void **)(self + 0xc) = (void *)func_ov221_020d424c;
    *(void **)(self + 0x1c) = (void *)func_ov221_020d42b0;
    *(void **)(self + 0x30) = (void *)func_ov221_020d443c;

    v = *(unsigned short *)(self + 0x60);
    *(unsigned short *)(self + 0x60) =
        (unsigned short)((v & ~0xff00)
                         | (((((unsigned int)v << 0x10) >> 0x18 | 0x20) << 0x18) >> 0x10));

    saved = data_ov221_020d4ddc;

    v = *(unsigned short *)(self + 0x60);
    *(unsigned short *)(self + 0x60) =
        (unsigned short)((v & ~0xff00)
                         | (((((unsigned int)v << 0x10) >> 0x18 | 0x4e) << 0x18) >> 0x10));

    *(unsigned short *)(self + 0x1ae) |= 4;
    *(int *)(self + 0x70) = 1;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;

    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(owner, 0x1a));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 4, 0, 1);
    func_02016b60(*(int *)(*(int *)(*(int *)(self + 0x384) + 0x88) + 0x78), 0,
                  data_ov221_020d4e54.value);

    /* Stored, then re-read through the byte for the wrap test -- that is what pins the store
     * ahead of the compare, which is where the ROM puts it. */
    data_ov221_020d4e54.value = data_ov221_020d4e54.value + 1;
    if (data_ov221_020d4e54.value >= 0x1f) {
        data_ov221_020d4e54.value = 3;
    }

    if (*(int *)(self + 0x384) != 0) {
        func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
        func_0203c7ac(*(int *)(self + 0x384), 0);
    }

    if (saved.w >= 0) {
        *(int *)(self + 0x394) = func_0203b898(func_ov107_020c9440(owner, saved.w));
        func_ov107_020c9074((int)self, *(int *)(self + 0x394));
        *(int *)(*(int *)(self + 0x394) + 0x5c) |= 2;
    }

    *(int *)(self + 0x388) = func_01fffca8((int)(self + 0x22c), 0x10, 0x64);
    **(int **)(self + 0x388) = func_ov107_020c319c((int)(self + 0x64));
    ((B8 *)(*(int *)(self + 0x388) + 8))->f |= 2;
    *(int *)(self + 0x38c) = 0;
}
