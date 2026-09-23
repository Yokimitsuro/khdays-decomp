/* Move dispatcher (brain slot 0) of the ov237 actor: a pending next move (+0x1c7) clears the per-move
 * state (+0x58 set; the actor's +0x4b4, +0x49e and the +0x57 hit mask cleared), becomes 0xd (separate)
 * when the pair is split (alone with +0x4b0 and no +0x494 grab once idle, or linked to a busy partner)
 * unless +0x4c0 forbids it, and becomes the current move (+0x1c6). A linked actor clears bits 1, 2, 6
 * and 7 of its +0x60 high byte and bit 0 of +0x1ae, sets bit 0 and clears bit 1 of the +0x488 rig's
 * flags and clears bit 6 of the brain's +0x60 byte. Brain slot 1 then runs the move's entry
 * (move 3 also drops +0x4c0), and the next move is cleared. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020ce2ac(void);
extern void func_ov237_020ce378(void);
extern void func_ov237_020ce5e8(void);
extern void func_ov237_020ce6cc(void);
extern void func_ov237_020ce89c(void);
extern void func_ov237_020cefe4(void);
extern void func_ov237_020cf508(void);
extern void func_ov237_020cfb10(void);
extern void func_ov237_020cfea4(void);
extern void func_ov237_020d02dc(void);
extern void func_ov237_020d0478(void);
extern void func_ov237_020d0a20(void);

void func_ov237_020cd554(int *node)
{
    int *state = (int *)node[1];

    if (*(signed char *)(*state + 0x1c7) != -1) {
        state[0x16] = 1;
        *(int *)(*state + 0x4b4) = 0;
        *(u8 *)(*state + 0x49e) = 0;
        *((u8 *)state + 0x57) = 0;
        if (*(int *)(*state + 0x4c0) == 0) {
            if (*(int *)(*state + 0x4ac) == 0 && *(int *)(*state + 0x4b0) != 0 &&
                *(int *)(*state + 0x494) == 0 && *(u8 *)(state[1] + 0xad) == 0) {
                *(signed char *)(*state + 0x1c7) = 0xd;
            }
            if (*(int *)(*state + 0x4ac) != 0 && *(int *)(*state + 0x494) == 0 &&
                *(int *)(*(int *)(*state + 0x4a4) + 0x4b0) != 0) {
                *(signed char *)(*state + 0x1c7) = 0xd;
            }
        }
        *(signed char *)(*state + 0x1c6) = *(signed char *)(*state + 0x1c7);
        if (*(int *)(*state + 0x4ac) != 0) {
            {
                u16 hw = *(u16 *)(*state + 0x60);

                *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                    (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0xc6) << 0x18) >> 0x10);
            }
            *(u16 *)(*state + 0x1ae) &= ~1;
            ((B8 *)(*(int *)(*state + 0x488) + 8))->f |= 1;
            ((B8 *)(*(int *)(*state + 0x488) + 8))->f &= ~2;
            {
                u16 hw = *(u16 *)(state + 0x18);

                *(u16 *)(state + 0x18) = (hw & ~0xff00) |
                    (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
            }
        }
        switch (*(signed char *)(*state + 0x1c6)) {
        case 0:
            func_0203c634(node, 1, func_ov237_020ce2ac);
            break;
        case 1:
            func_0203c634(node, 1, func_ov237_020ce378);
            break;
        case 2:
            func_0203c634(node, 1, func_ov237_020ce5e8);
            break;
        case 4:
            func_0203c634(node, 1, func_ov237_020ce6cc);
            break;
        case 5:
            func_0203c634(node, 1, func_ov237_020ce89c);
            break;
        case 6:
            func_0203c634(node, 1, func_ov237_020cefe4);
            break;
        case 7:
            func_0203c634(node, 1, func_ov237_020cf508);
            break;
        case 9:
            func_0203c634(node, 1, func_ov237_020cfb10);
            break;
        case 10:
            func_0203c634(node, 1, func_ov237_020cfea4);
            break;
        case 12:
            func_0203c634(node, 1, func_ov237_020d02dc);
            break;
        case 13:
            func_0203c634(node, 1, func_ov237_020d0478);
            break;
        case 3:
            *(int *)(*state + 0x4c0) = 0;
            func_0203c634(node, 1, func_ov237_020d0a20);
            break;
        }
    }
    *(signed char *)(*state + 0x1c7) = -1;
}
