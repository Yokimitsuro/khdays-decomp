/* Build step of the ov034 enemy (x4: ov034/052/072/090): clears the ready flags, requests
 * animation set 3, binds three render handles -- one against the scene link the enemy was
 * spawned from, two against the enemy's own sub-models at +0xf10 and +0xdac -- clears the
 * 0xc6-byte work block at +0xda0, then latches the ready bits 0xf and returns them. */
typedef unsigned char u8;

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot, int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern char data_ov034_020b55fc[];
extern char data_ov034_020b560c[];
extern char data_ov034_020b5620[];

u8 func_ov034_020b3e94(char *self)
{
    char *block = self + 0x2f8 + 0x2000;

    block[0x334] = 0;
    func_ov022_020b15b0(*(u8 *)(self + 9), 3);
    *(u8 **)(block + 0x340) = func_ov022_020b14a4(data_ov034_020b55fc, *(u8 *)(self + 9), 0, *(char **)(self + 0x20) + 4);
    *(u8 **)(block + 0x344) = func_ov022_020b14a4(data_ov034_020b560c, *(u8 *)(self + 9), 1, self + 0xf10);
    *(u8 **)(block + 0x348) = func_ov022_020b14a4(data_ov034_020b5620, *(u8 *)(self + 9), 2, self + 0xdac);
    func_ov022_020b1cec(self + 0xda0, 0xc6);
    return *(u8 *)(block + 0x334) |= 0xf;
}
