/* Build step of the ov049 enemy (x4: ov049/068/087/104): clears the ready flags, requests
 * animation set 4, binds three render handles -- one against the scene link the enemy was
 * spawned from, one against the model of the object it is attached to, one against the rig's
 * own model at +0x2d00 -- clears the 0xd2-byte work block at +0xda0, then latches the ready
 * bits 0xf and returns them. */
typedef unsigned char u8;

extern void func_ov022_020b15b0(int slot, int mode);
extern u8 *func_ov022_020b14a4(char *descriptor, int slot, int variant, void *parameters);
extern void func_ov022_020b1cec(void *block, int size);
extern char *data_ov104_020bc2a0;
extern char data_ov104_020bc260[];
extern char data_ov104_020bc270[];
extern char data_ov104_020bc284[];

u8 func_ov104_020bbab8(char *self)
{
    char *rig = data_ov104_020bc2a0 + 0xfc + 0x2c00;
    char *block = self + 0x2f8 + 0x2000;

    block[0x334] = 0;
    func_ov022_020b15b0(*(u8 *)(self + 9), 4);
    *(u8 **)(block + 0x340) = func_ov022_020b14a4(data_ov104_020bc260, *(u8 *)(self + 9), 0, *(char **)(self + 0x20) + 4);
    *(u8 **)(block + 0x344) = func_ov022_020b14a4(data_ov104_020bc270, *(u8 *)(self + 9), 1, *(char **)(*(char **)(self + 0x2644) + 0xc) + 0x28);
    *(u8 **)(block + 0x348) = func_ov022_020b14a4(data_ov104_020bc284, *(u8 *)(self + 9), 2, rig + 4);
    func_ov022_020b1cec(self + 0xda0, 0xd2);
    return *(u8 *)(block + 0x334) |= 0xf;
}
