/* Grab-release hook of the ov261 enemy (and its byte-identical twin): when both +0x3a4/+0x3a8
 * grab slots are set, bit 1 of the +0x40 flags is set and the new state is 0, the grabbed
 * +0x3a0 list's first entry is released (func_ov015_02080c00, slot +0x3ad, "carried" when the
 * slot's kind is 1), sub-state 2 is asked for and the grab slots are cleared. Bit 1 of +0x40
 * then follows the new state. */
typedef unsigned char u8;

extern void func_ov015_02080c00(int piece, int slot, int carried, int a);

void func_ov262_020d3c60(char *actor, int state)
{
    if (*(int *)(actor + 0x3a4) != 0 && *(int *)(actor + 0x3a8) != 0 &&
        ((*(int *)(actor + 0x40) << 30) >> 31) != 0 && state == 0) {
        if (*(int *)(*(int *)(actor + 0x3a0)) != 0) {
            int e = *(u8 *)(actor + 0x3ad);
            int flag = 0;
            if ((unsigned short)*(int *)(*(int *)(actor + 0x3a0) + e * 0x24 + 0x18) == 1)
                flag = 1;
            func_ov015_02080c00(*(int *)(*(int *)(actor + 0x3a0)), e, flag, 1);
            *(u8 *)(actor + 0x1c7) = 2;
            *(int *)(actor + 0x3a4) = 0;
            *(int *)(actor + 0x3a8) = 0;
        }
    }
    *(unsigned int *)(actor + 0x40) = (*(unsigned int *)(actor + 0x40) & ~2) | (((unsigned int)state << 31) >> 30);
}
