/* Ticks the mission enemy's node request: while the request is in a running stage (1..3) and
 * the enemy has left modes 0x2f/0x30/0x32, sound 0xc4 is stopped on both variants, the local
 * player is told action 8 (unless the actor is flagged 0x10000) and the request is reset.
 * Stage 1 accumulates the tick at +0x120 and after 0x18000 plays sound 0xc4, arms the
 * +0x47a/+0x47b pair (3, 2) for the local player and moves to stage 2; stage 2 steps the +0x10
 * request until it completes, rebinds the animation tracks (mode 1) and moves to stage 3;
 * stage 3 only steps the request; stage 4 steps it and, once complete, stops the sound, tells
 * the player action 8 and resets. Both +0x12c rows (stride 0x240) are then advanced. */
typedef unsigned char u8;

extern void func_02033bb4(int nSound, int nVariant, int nFlag);
extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */
extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cb70(int owner, int what, int arg);
extern void func_ov022_020a4490(char *self, int nSound, int nVariant);
extern int func_0202a818(void *req, int tick);
extern void func_ov062_020b7360(char *node, int mode);
extern void func_ov062_020b78ac(char *self, char *row, int tick);

void func_ov062_020b7098(char *self, char *node, int tick)
{
    int i;
    char *pRow;

    if (*(int *)(node + 0x11c) != 0 && *(int *)(node + 0x11c) != 4
        && *(int *)(self + 0x6bc) != 0x2f && *(int *)(self + 0x6bc) != 0x30
        && *(int *)(self + 0x6bc) != 0x32) {
        func_02033bb4(0xc4, 0, 0);
        func_02033bb4(0xc4, 1, 0);
        if (*(u8 *)(self + 8) == func_02030788() && (*(int *)self & 0x10000) == 0) {
            func_ov002_0204cb70(func_ov022_02083f0c(), 8, 0);
        }
        *(int *)(node + 0x11c) = 0;
    }
    switch (*(int *)(node + 0x11c)) {
    case 1:
        *(int *)(node + 0x120) += tick;
        if (*(int *)(node + 0x120) >= 0x18000) {
            func_ov022_020a4490(self, 0xc4, 0);
            if (func_02030788() == 0 && (*(int *)self & 0x10000) == 0) {
                *(u8 *)(self + 0x47a) = 3;
                *(u8 *)(self + 0x47b) = 2;
            }
            *(int *)(node + 0x11c) = 2;
        }
        break;
    case 2:
        if (func_0202a818(node + 0x10, tick) != 0) {
            func_ov062_020b7360(node, 1);
            *(int *)(node + 0x11c) = 3;
        }
        break;
    case 3:
        func_0202a818(node + 0x10, tick);
        break;
    case 4:
        if (func_0202a818(node + 0x10, tick) != 0) {
            func_02033bb4(0xc4, 0, 0);
            func_02033bb4(0xc4, 1, 0);
            if (*(u8 *)(self + 8) == func_02030788() && (*(int *)self & 0x10000) == 0) {
                func_ov002_0204cb70(func_ov022_02083f0c(), 8, 0);
            }
            *(int *)(node + 0x11c) = 0;
        }
        break;
    }
    pRow = node + 0x12c;
    for (i = 0; i < 2; i++) {
        func_ov062_020b78ac(self, pRow, tick);
        pRow += 0x240;
    }
}
