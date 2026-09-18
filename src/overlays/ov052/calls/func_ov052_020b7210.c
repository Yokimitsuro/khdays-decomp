/* Starts the ov032 enemy's effect block (and its byte-identical twins) unless it is already
 * running outside states 4/5: releases the five handles it still holds, retimes sequences 0, 2
 * and 1 against the owner's +0x22f8 period from zero, resets the three +0xbc scales to 1.0 and
 * enters state 1. */
typedef unsigned char u8;
typedef unsigned short u16;

extern void func_02014dc4(void *p, int handle);
extern int func_ov022_0209560c(void *p);
extern void func_0202accc(void *p, u16 idx, int a, short b);

void func_ov052_020b7210(int self, int *block)
{
    int i;

    if (*(u8 *)((char *)block + 0x114) != 0 && (u8)(*(u8 *)((char *)block + 0x114) + 0xfc) > 1) {
        return;
    }
    for (i = 0; i < 5; i++) {
        if (block[i + 6] != 0) {
            func_02014dc4((char *)block + 0x2c, block[i + 6]);
            block[i + 6] = 0;
        }
    }
    func_0202accc((char *)block + 0xc, 0, func_ov022_0209560c((void *)(self + 0x22f8)), 0);
    func_0202accc((char *)block + 0xc, 2, func_ov022_0209560c((void *)(self + 0x22f8)), 0);
    func_0202accc((char *)block + 0xc, 1, func_ov022_0209560c((void *)(self + 0x22f8)), 0);
    block[0x31] = 0x1000;
    block[0x30] = 0x1000;
    block[0x2f] = 0x1000;
    *(u8 *)((char *)block + 0x114) = 1;
}
