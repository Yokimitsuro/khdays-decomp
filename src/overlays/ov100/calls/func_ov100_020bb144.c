/* Build step of the ov045 enemy (x4: ov045/064/083/100): clears the ready flags, requests
 * animation set 2, binds two render handles -- one against the model of the object the enemy is
 * attached to (+0x28 of the attachment's model), one against the scene link it was spawned from
 * -- clears the 0xc9-byte work block at +0xda0, then latches the ready bits 0xb and returns
 * them. */
typedef unsigned char u8;

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot, int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern char data_ov100_020bc170[];
extern char data_ov100_020bc184[];

u8 func_ov100_020bb144(char *self)
{
    char *block = self + 0x2f8 + 0x2000;

    block[0x334] = 0;
    func_ov022_020b15b0(*(u8 *)(self + 9), 2);
    *(u8 **)(block + 0x344) = func_ov022_020b14a4(data_ov100_020bc170, *(u8 *)(self + 9), 0, *(char **)(*(char **)(self + 0x2644) + 0xc) + 0x28);
    *(u8 **)(block + 0x340) = func_ov022_020b14a4(data_ov100_020bc184, *(u8 *)(self + 9), 1, *(char **)(self + 0x20) + 4);
    func_ov022_020b1cec(self + 0xda0, 0xc9);
    return *(u8 *)(block + 0x334) |= 0xb;
}
