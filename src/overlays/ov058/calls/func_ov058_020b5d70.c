/*
 * Apply a mode change to the actor -- the two-stage variant with a secondary UI id.
 *
 * Stage one is keyed on `mode - 0x2e` and only acts when the mode really changed (+0x6bc caches
 * the previous one): 0x2e re-arms via the veneer at 020b3e80; 0x2f resets the rig block
 * (+0x2cd4) and re-binds its first channel; 0x30/0x31 only notify the local player (8);
 * 0x32 sets the rig's flag, re-binds both channels (1 and 2), notifies (10) and is then
 * remapped to 0x2f, remembering the mode it came from in `reached`; 0x33 is remapped to 0xb the
 * same way. Only the local player's actor (slot byte +8 == 02030788, bit 16 of the flags clear)
 * sends the notification.
 *
 * Stage two hands the mode down (020a384c, with `reached` overriding the cached mode), forwards
 * it to the primary UI channel (020519b0 -> 02052024 at/above 0x2e, 020521a4 below), then maps
 * it to a secondary id for the block at +0x2c80: 0x11/0x12 -> 0/1, 0x17..0x19 -> 2..4 (flagged),
 * 0x30/0x31 -> 6/7, 0x2f -> 8 when it came from 0x32 else 5, and 0x1e..0x2d pass through
 * flagged. A valid id drives the secondary channel (setting bit 0 of +0xf0c first when the
 * unflagged path has +0xf0d set); no id clears that bit and parks the block's slot at -1.
 */
extern void WM_EndKeySharing_0x020b6680(char *self);
extern void func_ov058_020b6718(char *chan, int which);
extern unsigned short func_02030788(void);
extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cb70(int owner, int what, int arg);
extern void func_ov022_020a384c(char *self, int mode);
extern int func_ov002_020519b0(int a, int b, int c);
extern void func_ov002_02052024(void *a, char *b, int c, int d, int e);
extern void func_ov002_020521a4(void *a, char *b, int c, int d);

void func_ov058_020b5d70(char *self, int mode) {
    int reached = -1;
    char *rig = self + 0xd4 + 0x2c00;
    int kind;
    int id;
    int flag;
    int ret;

    switch (mode - 0x2e) {
    case 0:
        if (*(int *)(self + 0x6bc) != mode) {
            WM_EndKeySharing_0x020b6680(self);
        }
        break;
    case 1:
        if (*(int *)(self + 0x6bc) != mode) {
            *(int *)rig = 0;
            *(int *)(rig + 0x10) = 0;
            func_ov058_020b6718(rig + 0x18, 0);
            if (*(unsigned char *)(self + 8) == func_02030788()
                && (*(int *)self & 0x10000) == 0) {
                func_ov002_0204cb70(func_ov022_02083f0c(), 10, 0);
            }
        }
        break;
    case 4:
        if (*(int *)(self + 0x6bc) != mode) {
            *(int *)rig = 1;
            *(int *)(rig + 0x10) = 0;
            func_ov058_020b6718(rig + 0x18, 1);
            func_ov058_020b6718(rig + 0x124, 2);
            if (*(unsigned char *)(self + 8) == func_02030788()
                && (*(int *)self & 0x10000) == 0) {
                func_ov002_0204cb70(func_ov022_02083f0c(), 10, 0);
            }
        }
        reached = mode;
        mode = 0x2f;
        break;
    case 5:
        reached = mode;
        mode = 0xb;
        break;
    case 2:
    case 3:
        if (*(int *)(self + 0x6bc) != mode) {
            if (*(unsigned char *)(self + 8) == func_02030788()
                && (*(int *)self & 0x10000) == 0) {
                func_ov002_0204cb70(func_ov022_02083f0c(), 8, 0);
            }
        }
        break;
    }
    func_ov022_020a384c(self, mode);
    if (reached >= 0) { *(int *)(self + 0x6bc) = reached; }
    kind = 0;
    id = -1;
    flag = 0;
    if (*(signed char *)(self + 0x2bb2) == 2) { kind = 1; }
    ret = func_ov002_020519b0(mode, *(int *)(self + 0x6bc), *(int *)(self + 0xc));
    if (mode >= 0x2e) {
        kind = 2;
        func_ov002_02052024((void *)(self + 0xda8), self + 0x2c2c, mode, kind, ret);
    } else {
        func_ov002_020521a4((void *)(self + 0xda8), self + 0x2c2c, mode, kind);
    }
    switch (mode) {
    case 0x11: id = 0; break;
    case 0x12: id = 1; break;
    case 0x17: id = 2; flag = 1; break;
    case 0x18: id = 3; flag = 1; break;
    case 0x19: id = 4; flag = 1; break;
    case 0x30: id = 6; break;
    case 0x31: id = 7; break;
    case 0x2f:
        if (reached == 0x32) { id = 8; } else { id = 5; }
        break;
    default:
        if (mode >= 0x1e && mode < 0x2e) {
            id = mode;
            flag = 1;
        }
        break;
    }
    if (id >= 0) {
        if (flag == 0) {
            if (*(signed char *)(self + 0xf0d) != 0) { *(unsigned char *)(self + 0xf0c) |= 1; }
        }
        func_ov002_02052024((void *)(self + 0xf0c), self + 0x2c80, id, kind, ret);
    } else {
        if (*(signed char *)(self + 0xf0d) != 0) { *(unsigned char *)(self + 0xf0c) &= ~1; }
        *(signed char *)(self + 0x2c80) = -1;
    }
}
