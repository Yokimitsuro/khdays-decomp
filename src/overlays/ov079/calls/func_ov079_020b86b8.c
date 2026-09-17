/* Build step of the ov040 enemy (x4: ov040/059/079/096): clears the ready flags, requests
 * animation set 2, binds two render handles -- one against the scene link the enemy was spawned
 * from, one against the rig's own model at +0x2c5c -- clears the 0xce-byte work block at +0xda0,
 * then latches the ready bits 0xb and returns them. */
typedef unsigned char u8;

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot, int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern char *data_ov079_020b9a00;
extern char data_ov079_020b9990[];
extern char data_ov079_020b99a0[];

u8 func_ov079_020b86b8(char *self)
{
    char *rig = data_ov079_020b9a00 + 0x2c50;
    char *block = self + 0x2f8 + 0x2000;

    block[0x334] = 0;
    func_ov022_020b15b0(*(u8 *)(self + 9), 2);
    *(u8 **)(block + 0x340) = func_ov022_020b14a4(data_ov079_020b9990, *(u8 *)(self + 9), 0, *(char **)(self + 0x20) + 4);
    *(u8 **)(block + 0x344) = func_ov022_020b14a4(data_ov079_020b99a0, *(u8 *)(self + 9), 1, rig + 0xc);
    func_ov022_020b1cec(self + 0xda0, 0xce);
    return *(u8 *)(block + 0x334) |= 0xb;
}
