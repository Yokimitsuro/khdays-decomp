/* Build step of the ov036 enemy (x4: ov036/054/074/091): clears the ready flags, requests
 * animation set 3, binds three render handles -- one against the scene link the enemy was
 * spawned from, two against the models of the attachment's parts at +0x3c and +0x6c -- clears
 * the 0xcc-byte work block at +0xda0, then latches the ready bits 0xf and returns them. */
typedef unsigned char u8;

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot, int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern char data_ov036_020b4e90[];
extern char data_ov036_020b4ea0[];
extern char data_ov036_020b4eb4[];

u8 func_ov036_020b37ec(char *self)
{
    char *block = self + 0x2f8 + 0x2000;

    block[0x334] = 0;
    func_ov022_020b15b0(*(u8 *)(self + 9), 3);
    *(u8 **)(block + 0x340) = func_ov022_020b14a4(data_ov036_020b4e90, *(u8 *)(self + 9), 0, *(char **)(self + 0x20) + 4);
    *(u8 **)(block + 0x344) = func_ov022_020b14a4(data_ov036_020b4ea0, *(u8 *)(self + 9), 1, *(char **)(*(char **)(self + 0x2644) + 0x3c) + 0x28);
    *(u8 **)(block + 0x348) = func_ov022_020b14a4(data_ov036_020b4eb4, *(u8 *)(self + 9), 2, *(char **)(*(char **)(self + 0x2644) + 0x6c) + 0x28);
    func_ov022_020b1cec(self + 0xda0, 0xcc);
    return *(u8 *)(block + 0x334) |= 0xf;
}
