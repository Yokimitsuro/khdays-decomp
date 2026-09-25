/* Build step of the ov072 enemy (byte-identical twin of ov032 020b48e0): clears the ready flags,
 * requests animation set 3, binds three
 * render handles -- one against the scene link the enemy was spawned from, one against the
 * model of the attachment's part at +0x3c, one against the rig's own model at +0x2e84 -- clears
 * the 0xc5-byte work block at +0xda0, then latches the ready bits 0xf. Unlike the u8-returning
 * build steps of ov033-049 this one returns nothing; with a return value the argument setup
 * around the calls is scheduled differently. */
typedef unsigned char u8;

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot, int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern char *data_ov072_020ba7a0;
extern char data_ov072_020ba724[];
extern char data_ov072_020ba734[];
extern char data_ov072_020ba748[];

void func_ov072_020b97c0(char *self)
{
    char *base = data_ov072_020ba7a0;
    char *block = self + 0x2f8 + 0x2000;
    char *model;

    block[0x334] = 0;
    func_ov022_020b15b0(*(u8 *)(self + 9), 3);
    model = *(char **)(*(char **)(self + 0x2644) + 0x3c);
    *(u8 **)(block + 0x340) = func_ov022_020b14a4(data_ov072_020ba724, *(u8 *)(self + 9), 0, *(char **)(self + 0x20) + 4);
    *(u8 **)(block + 0x344) = func_ov022_020b14a4(data_ov072_020ba734, *(u8 *)(self + 9), 1, model + 0x28);
    *(u8 **)(block + 0x348) = func_ov022_020b14a4(data_ov072_020ba748, *(u8 *)(self + 9), 2, base + 0x284 + 0x2c00);
    func_ov022_020b1cec(self + 0xda0, 0xc5);
    *(u8 *)(block + 0x334) |= 0xf;
}
