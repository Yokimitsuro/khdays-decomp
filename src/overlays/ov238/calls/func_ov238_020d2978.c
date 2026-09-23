/* Teardown of the ov238 actor: while it is shown (+0x60 bit 7) its +0x3a8 effect stops (0203c650) and
 * clears; then the base teardown runs. */
typedef unsigned short u16;
typedef struct { u16 lo : 8; u16 hi : 8; } flags16;

extern void func_0203c650(int model, int handle);
extern void func_ov107_020c7ca4(char *self);

void func_ov238_020d2978(char *self)
{
    if ((((flags16 *)(self + 0x60))->lo & 0x80) && *(int *)(self + 0x3a8) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x3a8));
        *(int *)(self + 0x3a8) = 0;
    }
    func_ov107_020c7ca4(self);
}
