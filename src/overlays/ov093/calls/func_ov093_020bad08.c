/* Build step of the ov037 enemy (x4: ov037/055/075/092): clears the ready flags, requests
 * animation set 2, binds two render handles -- one against the scene link the enemy was spawned
 * from, one against the rig's own model at +0x2c30 -- clears the 0xcf-byte work block at +0xda0,
 * then latches the ready bits 0xb and returns them. */
typedef unsigned char u8;

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot, int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern char *data_ov093_020bc3c0;
extern char data_ov093_020bc370[];
extern char data_ov093_020bc380[];

u8 func_ov093_020bad08(char *self)
{
    char *rig = data_ov093_020bc3c0 + 0x2c + 0x2c00;
    char *block = self + 0x2f8 + 0x2000;

    block[0x334] = 0;
    func_ov022_020b15b0(*(u8 *)(self + 9), 2);
    *(u8 **)(block + 0x340) = func_ov022_020b14a4(data_ov093_020bc370, *(u8 *)(self + 9), 0, *(char **)(self + 0x20) + 4);
    *(u8 **)(block + 0x344) = func_ov022_020b14a4(data_ov093_020bc380, *(u8 *)(self + 9), 1, rig + 4);
    func_ov022_020b1cec(self + 0xda0, 0xcf);
    return *(u8 *)(block + 0x334) |= 0xb;
}
