/* Build step of the mission enemy: clears the ready flags, requests animation set 3, binds
 * three render handles -- one against the scene link the enemy was spawned from, one against
 * the mission owner's +0x2d38 block (+0x10), one against the model of the +0x2644 record's
 * +0x3c object -- clears the 0xc4-byte work block at +0xda0, then latches the ready bits 0xf
 * and returns them. */
typedef unsigned char u8;

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot, int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern char *data_ov062_020b80e0;
extern char data_ov062_020b8064[];
extern char data_ov062_020b8074[];
extern char data_ov062_020b8088[];

u8 func_ov062_020b6498(char *self)
{
    char *rig = data_ov062_020b80e0 + 0x138 + 0x2c00;
    char *block = self + 0x2f8 + 0x2000;

    block[0x334] = 0;
    func_ov022_020b15b0(*(u8 *)(self + 9), 3);
    *(u8 **)(block + 0x340) = func_ov022_020b14a4(data_ov062_020b8064, *(u8 *)(self + 9), 0, *(char **)(self + 0x20) + 4);
    *(u8 **)(block + 0x344) = func_ov022_020b14a4(data_ov062_020b8074, *(u8 *)(self + 9), 1, rig + 0x10);
    *(u8 **)(block + 0x348) = func_ov022_020b14a4(data_ov062_020b8088, *(u8 *)(self + 9), 2, *(char **)(*(char **)(self + 0x2644) + 0x3c) + 0x28);
    func_ov022_020b1cec(self + 0xda0, 0xc4);
    return *(u8 *)(block + 0x334) |= 0xf;
}
