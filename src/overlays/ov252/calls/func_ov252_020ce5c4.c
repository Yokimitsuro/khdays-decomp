/* Hit filter of the ov252 actor (+0x1d0): ignored when already down (+0x21a <= 0), for hits from
 * its own +0x504 / +0x508 parts or in move 8. In move 0xe a flag-8/0x80 hit while charging (+0x94)
 * drains the +0x64 charge by 3.0 / 6.0 / 9.0 per hit level (+0x1d). Hits on the +0x4f4 core
 * (020cde6c) stagger it (020cdd30), fire reaction 0x148/0x10, reveal the +0x4ec shape and send it
 * to move 8 with a counter queued (+0xac, +0xa0); hits on the +0x4f8 / +0x4fc / +0x500 plates
 * break plate 1-3 (020ce56c). Part hits skip damage; any other hit takes 020c89e8 damage off the
 * +0x21a health (capped by +0x218), knocked out the next move is 3. Unless it is a flag-8/0x80
 * kind-0x80 hit, reaction 0x148 fires with the mode alternating (+0x87) between the special
 * (flag 0x22) {2, 3} and normal {0, 1} pairs. */
typedef unsigned char u8;
typedef unsigned short u16;

struct HitFlags { unsigned int low : 16; unsigned int kind : 16; };

extern int func_ov252_020cde6c(int *work, unsigned int *hit, char *self);
extern void func_ov252_020cdd30(int *work, int a, int b);
extern void func_ov252_020ce56c(char *self, int plate);
extern int func_ov107_020c89e8(char *self, unsigned int *hit);
extern void func_ov107_020c5af8(char *self, int reactionId, u8 mode, int context);
typedef struct { unsigned f : 8; } B8;

int func_ov252_020ce5c4(char *self, int source, unsigned int *hit)
{
    u8 normalModes[2] = { 0, 1 };
    u8 specialModes[2] = { 2, 3 };
    int *work = *(int **)(self + 0x214);
    int handled = 0;
    int countered = 0;
    int delta;
    int remaining;
    struct HitFlags *flags;

    if (*(short *)(self + 0x200 + 0x1a) <= 0) {
        return handled;
    }
    if (hit[6] == *(unsigned int *)(*work + 0x504) || hit[6] == *(unsigned int *)(*work + 0x508)) {
        return 0;
    }
    if (*(signed char *)(*work + 0x100 + 0xc6) == 8) {
        return handled;
    }
    flags = (struct HitFlags *)hit;
    if (*(signed char *)(*work + 0x100 + 0xc6) == 0xe && (flags->low & 8) != 0 && (flags->kind & 0x80) != 0 &&
        *((u8 *)work + 0x94) != 0) {
        switch (((u8 *)hit)[0x1d]) {
        case 0:
            work[0x19] -= 0x3000;
            break;
        case 1:
            work[0x19] -= 0x6000;
            break;
        case 2:
            work[0x19] -= 0x9000;
            break;
        }
    }
    if (hit[6] == *(unsigned int *)(*work + 0x4f4)) {
        if (func_ov252_020cde6c(work, hit, self) != 0) {
            func_ov252_020cdd30(work, 0, 0);
            func_ov107_020c5af8(self, 0x148, 0x10, work[2]);
            ((B8 *)(*(int *)(*work + 0x4ec) + 8))->f |= 1;
            countered = 1;
            work[0x2b] = 1;
            *(signed char *)(*work + 0x1c7) = 8;
        }
        handled = 1;
    } else if (hit[6] == *(unsigned int *)(*work + 0x4f8)) {
        if (func_ov252_020cde6c(work, hit, self) != 0) {
            func_ov252_020ce56c(self, 1);
        }
        handled = 1;
    } else if (hit[6] == *(unsigned int *)(*work + 0x4fc)) {
        if (func_ov252_020cde6c(work, hit, self) != 0) {
            func_ov252_020ce56c(self, 2);
        }
        handled = 1;
    } else if (hit[6] == *(unsigned int *)(*work + 0x500)) {
        if (func_ov252_020cde6c(work, hit, self) != 0) {
            func_ov252_020ce56c(self, 3);
        }
        handled = 1;
    }
    if (handled) {
        if ((int)hit[10] > 0) {
            if ((flags->low & 8) == 0 || (flags->low & 0x80) == 0 || flags->kind != 0x80) {
                if ((flags->low & 0x22) != 0) {
                    func_ov107_020c5af8(self, 0x148, specialModes[*((u8 *)work + 0x87)], work[2]);
                } else {
                    func_ov107_020c5af8(self, 0x148, normalModes[*((u8 *)work + 0x87)], work[2]);
                }
                *((u8 *)work + 0x87) ^= 1;
            }
        }
        if (countered) {
            work[0x28] = 1;
        }
        return 1;
    }
    hit[10] = func_ov107_020c89e8(self, hit);
    delta = *(short *)(self + 0x200 + 0x1a) - (int)hit[10];
    if (delta < 0) {
        remaining = 0;
    } else {
        remaining = *(short *)(self + 0x200 + 0x18);
        if (delta <= remaining) {
            remaining = delta;
        }
    }
    *(short *)(self + 0x200 + 0x1a) = (short)remaining;
    if ((int)hit[10] > 0) {
        if ((flags->low & 8) == 0 || (flags->low & 0x80) == 0 || flags->kind != 0x80) {
            if ((flags->low & 0x22) != 0) {
                func_ov107_020c5af8(self, 0x148, specialModes[*((u8 *)work + 0x87)], work[2]);
            } else {
                func_ov107_020c5af8(self, 0x148, normalModes[*((u8 *)work + 0x87)], work[2]);
            }
            *((u8 *)work + 0x87) ^= 1;
        }
    }
    if (*(short *)(self + 0x200 + 0x1a) > 0) {
        return 1;
    }
    *(signed char *)(*work + 0x1c7) = 3;
    return 1;
}
