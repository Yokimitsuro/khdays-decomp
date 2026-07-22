/* Pushes the stance byte at +0x310 out to state channels 0 and 2 of the sub-object at
 * +0x384, then closes the update.  The flag at +0x311 is a bitfield read (lsl#31/lsr#31),
 * not `& 1`. */
typedef struct {
    unsigned char b0 : 1;
    unsigned char rest : 7;
} Flags;

extern void func_0203b9fc(void *sub, int channel, short value, int flag);
extern void func_0203c7ac(void *sub, int a);

void func_ov245_020d154c(char *self) {
    func_0203b9fc(*(void **)(self + 0x384), 0, *(signed char *)(self + 0x310),
                  ((Flags *)(self + 0x311))->b0);
    func_0203b9fc(*(void **)(self + 0x384), 2, *(signed char *)(self + 0x310),
                  ((Flags *)(self + 0x311))->b0);
    func_0203c7ac(*(void **)(self + 0x384), 0);
}
