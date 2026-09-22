/*
 * Per-frame update of the actor's UI animation (three-track variant with a sequence table).
 *
 * Reads the model's current frame and bails unless the actor is drivable (0209fc48) with bit 0
 * of +0x694 set. When the heading matches the owner's and bit 52 of +0x464 is clear the frame is
 * rebased on the heading. The mode then picks a slot: 0x11/0x12 -> 0/1, 0x17..0x19 -> 2..4 when
 * bit 12 of +0x464 is set, 0x2e..0x32 -> 0..4 and 0x33 -> 3 through the rig's own sequence
 * (`special`); modes 0x1e..0x2d also read a secondary slot from the rig's +0x2cd4 table, and
 * below 0x2e a still-raised sequence latch (+0x2e1c) is released (020bb1a4). No slot at all
 * clears bit 0 of +0xf0c; otherwise that bit is set, the bind table is the rig's sequence
 * (+0x2e18, raising the latch), the actor's own (+0x1048) or the +0x2ccc row of the secondary
 * slot (which forces slot 0), and all three tracks of +0xf10 are bound to it. For sequence slots
 * 0 and 4 the rig's +0x2cf4 counter advances by the heading and wraps at the sequence length,
 * and it replaces the frame of track 2. Unless +0x2c30 is held the three tracks are framed,
 * and the draw is submitted (material triple from +0xdd0, cached block, optional +0xeb0
 * parameter, the +0xeb4 matrix, then the channels at +0xf30).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

extern int func_0202aee0(void *animation, int track);                          /* Anim_GetFrame */
extern int func_ov022_0209fc48(char *self, int i);
extern int func_ov022_02083f90(void);
extern void func_ov090_020bb1a4(char *self);
extern void func_0202accc(char *anim, int track, char *bind, short group);       /* BindAnimTrack */
extern void func_01fff774(char *anim, int track, int frame);                     /* Anim_SetFrameWrapped */
extern void func_01ff9f00(unsigned int cmd, const void *src, unsigned int words); /* GX_SendFifoWords */
extern void func_0201571c(void);                                                  /* submit the cached block */
extern void func_01ffcec0(unsigned int value);
extern void func_020279e0(char *channels);

void func_ov090_020bade4(char *self)
{
    char *rig;
    int *seq;
    int frame;
    int id;
    int frame3;
    char *blk;
    char *table;
    unsigned int aMaterial[3];
    int id2;
    int mode;
    int special;
    char *seqInfo;
    int cur;
    u16 len;

    rig = self + 0xe4 + 0x2c00;
    frame = func_0202aee0(*(char **)(self + 0x20) + 4, 0);
    id = -1;
    special = 0;
    id2 = id;

    if (func_ov022_0209fc48(self, 0) == 0) {
        return;
    }
    if (!((Flags *)(self + 0x694))->b0) {
        return;
    }
    cur = *(short *)(self + 0x2aba);
    if (cur == func_ov022_02083f90() && (*(u64 *)(self + 0x464) & 0x10000000000000ULL) == 0) {
        if (frame <= cur) {
            frame = cur;
        }
        frame -= cur;
    }
    mode = *(int *)(self + 0x6bc);
    frame3 = frame;
    switch (mode) {
    case 0x11:
        id = 0;
        break;
    case 0x12:
        id = 1;
        break;
    case 0x17:
        if ((*(u64 *)(self + 0x464) & 0x1000) != 0) {
            id = 2;
        }
        break;
    case 0x18:
        if ((*(u64 *)(self + 0x464) & 0x1000) != 0) {
            id = 3;
        }
        break;
    case 0x19:
        if ((*(u64 *)(self + 0x464) & 0x1000) != 0) {
            id = 4;
        }
        break;
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
        id = mode - 0x2e;
        special = 1;
        break;
    case 0x33:
        id = 3;
        special = 1;
        break;
    }
    if (mode >= 0x1e && mode < 0x2e) {
        id2 = *(signed char *)(self + (mode - 0x1e) + 0x2c00 + 0xd4);
    }
    if (mode < 0x2e && *(int *)(self + 0x2000 + 0xe1c) != 0) {
        func_ov090_020bb1a4(self);
        *(int *)(self + 0x2000 + 0xe1c) = 0;
    }
    if (id >= 0 || id2 >= 0) {
        blk = self + 0x1ac + 0xc00;
        if (*(signed char *)(self + 0xf0d) != 0) {
            *(u8 *)(self + 0xf0c) |= 1;
        }
        if (special == 0) {
            if (id2 < 0) {
                table = self + 0x48 + 0x1000;
            } else {
                table = *(char **)(self + 0x2000 + 0xccc) + id2 * 0x24;
                id = 0;
            }
        } else {
            table = *(char **)(rig + 0x134);
            *(int *)(self + 0x2000 + 0xe1c) = 1;
        }
        func_0202accc(self + 0xf10, 0, table, id);
        func_0202accc(self + 0xf10, 1, table, id);
        func_0202accc(self + 0xf10, 2, table, id);
        if (special != 0 && (id == 0 || id == 4)) {
            seq = *(int **)(*(char **)(*(char **)(rig + 0x134) + 0x18));
            *(int *)(rig + 0x10) += *(short *)(self + 0x2aba);
            seqInfo = *(char **)(seq + 2);
            len = *(volatile u16 *)(seqInfo + 4);
            if (*(int *)(rig + 0x10) + *(short *)(self + 0x2aba) >= len << 12) {
                *(int *)(rig + 0x10) = (len << 12) - *(short *)(self + 0x2aba);
            }
            frame3 = *(int *)(rig + 0x10);
        }
        if (*(int *)(self + 0x2000 + 0xc30) == 0) {
            func_01fff774(self + 0xf10, 0, frame);
            func_01fff774(self + 0xf10, 1, frame);
            func_01fff774(self + 0xf10, 2, frame3);
        }
        aMaterial[0] = *(unsigned int *)(*(char **)(blk + 0x24) + 0x1c);
        aMaterial[1] = aMaterial[0];
        aMaterial[2] = aMaterial[0];
        func_01ff9f00(0x1b, aMaterial, 3);
        func_0201571c();
        if ((*(u16 *)blk & 0x40) != 0) {
            func_01ffcec0(*(u16 *)(blk + 0x104));
        }
        func_01ff9f00(0x17, self + 0x2b4 + 0xc00, 0xc);
        func_020279e0(self + 0xf30);
    } else {
        if (*(signed char *)(self + 0xf0d) != 0) {
            *(u8 *)(self + 0xf0c) &= ~1;
        }
    }
}
