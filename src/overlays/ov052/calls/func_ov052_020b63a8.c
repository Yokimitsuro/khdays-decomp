/* Applies a mode change to the ov032 enemy (and its byte-identical twins). Bit 2 of the +0x2c30
 * flags is cleared first. Modes 0x1b/0x1c pick secondary ids 0/1 when the mode really changed
 * (+0x6bc caches the previous one), 0x26 and 0x28 pick animation set 1/2; 0x2e re-arms through
 * 4e5c, 0x2f starts the +0x2e78 effect block and notifies the local player (10), 0x31 notifies
 * (8) and stops it (4bd8), 0x30/0x32 stop it through 4ae8 (alternate 1 / the current set) and
 * raise bit 2 of the flags; the last four leave animation set 3/4/3/3. Both +0xdac animation
 * blocks are then rebound to that set on channels 0/1 from their +0x2ee4 tables, and the mode is
 * handed down either as a secondary id (020a3c78, caching the mode) or plainly (020a384c). */
typedef unsigned char u8;
typedef unsigned short u16;

extern void func_0202accc(void *p, u16 channel, void *table, short set);
extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */
extern void func_ov002_0204cb70(int owner, int what, int arg);
extern int func_ov022_02083f0c(void);
extern void func_ov022_020a384c(char *self, int mode);
extern void func_ov022_020a3c78(char *self, void *block, int id, int a);
extern void func_ov052_020b7210(char *self, void *block);
extern void func_ov052_020b72e8(char *self, void *block, int alt);
extern void func_ov052_020b73d8(char *self, void *block);
extern void func_ov052_020b765c(char *self, int prev);   /* the callee ignores the second argument */

void func_ov052_020b63a8(char *self, int mode)
{
    int sec = -1;
    int set = 0;
    int i;
    char *table;
    char *anim;

    *(u8 *)(self + 0x2000 + 0xc30) &= ~4;
    switch (mode) {
    case 0x1b:
        if (*(int *)(self + 0x6bc) != mode) {
            sec = 0;
        }
        break;
    case 0x1c:
        if (*(int *)(self + 0x6bc) != mode) {
            sec = 1;
        }
        break;
    case 0x26:
        set = 1;
        break;
    case 0x28:
        set = 2;
        break;
    case 0x2e:
        if (mode != *(int *)(self + 0x6bc)) {
            func_ov052_020b765c(self, *(int *)(self + 0x6bc));
        }
        break;
    case 0x2f:
        if (mode != *(int *)(self + 0x6bc)) {
            func_ov052_020b7210(self, self + 0x278 + 0x2c00);
            if (*(u8 *)(self + 8) == func_02030788() && (*(int *)self & 0x10000) == 0) {
                func_ov002_0204cb70(func_ov022_02083f0c(), 0xa, set);
            }
        }
        set = 3;
        break;
    case 0x31:
        if (mode != *(int *)(self + 0x6bc)) {
            if (*(u8 *)(self + 8) == func_02030788() && (*(int *)self & 0x10000) == 0) {
                func_ov002_0204cb70(func_ov022_02083f0c(), 8, set);
            }
            func_ov052_020b73d8(self, self + 0x278 + 0x2c00);
        }
        set = 4;
        break;
    case 0x32:
        if (mode != *(int *)(self + 0x6bc)) {
            func_ov052_020b72e8(self, self + 0x278 + 0x2c00, set);
        }
        *(u8 *)(self + 0x2000 + 0xc30) |= 4;
        set = 3;
        break;
    case 0x30:
        if (mode != *(int *)(self + 0x6bc)) {
            func_ov052_020b72e8(self, self + 0x278 + 0x2c00, 1);
        }
        *(u8 *)(self + 0x2000 + 0xc30) |= 4;
        set = 3;
        break;
    }
    table = self + 0x2e4 + 0xc00;
    anim = self + 0x1ac + 0xc00;
    for (i = 0; i < 2; i++) {
        func_0202accc(anim, 0, table, (short)set);
        func_0202accc(anim, 1, table, (short)set);
        table += 0x164;
        anim += 0x164;
    }
    if (sec != -1) {
        func_ov022_020a3c78(self, self + 0x244 + 0x2c00, sec, 0);
        *(int *)(self + 0x6bc) = mode;
    } else {
        func_ov022_020a384c(self, mode);
    }
}
