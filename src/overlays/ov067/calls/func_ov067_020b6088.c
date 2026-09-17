/* Build step of the ov048 enemy (x4: ov048/067/086/103): clears the ready flags, requests
 * animation set 3, binds three render handles -- one against the scene link the enemy was
 * spawned from, two against the rig's own models at +0x2c38 and +0x2e78 -- clears the
 * 0xd5-byte work block at +0xda0, then latches the ready bits 0xf and returns them. */
typedef unsigned char u8;

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot, int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern char *data_ov067_020b7380;
extern char data_ov067_020b72fc[];
extern char data_ov067_020b730c[];
extern char data_ov067_020b7320[];

u8 func_ov067_020b6088(char *self)
{
    char *rig = data_ov067_020b7380 + 0x2c + 0x2c00;
    char *block = self + 0x2f8 + 0x2000;

    block[0x334] = 0;
    func_ov022_020b15b0(*(u8 *)(self + 9), 3);
    *(u8 **)(block + 0x340) = func_ov022_020b14a4(data_ov067_020b72fc, *(u8 *)(self + 9), 0, *(char **)(self + 0x20) + 4);
    *(u8 **)(block + 0x344) = func_ov022_020b14a4(data_ov067_020b730c, *(u8 *)(self + 9), 1, rig + 0xc);
    *(u8 **)(block + 0x348) = func_ov022_020b14a4(data_ov067_020b7320, *(u8 *)(self + 9), 2, rig + 0x24c);
    func_ov022_020b1cec(self + 0xda0, 0xd5);
    return *(u8 *)(block + 0x334) |= 0xf;
}
