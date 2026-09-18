/*
 * Per-frame update of the actor's UI anchors and animation channels.
 *
 * Reads the model's current frame, ticks the attachment at +0x2644 (drive, settle, and when it
 * reports idle and this is the local player, sets bit 16 on both 64-bit flag words at +0x464
 * and +0x46c), then drives the primary channel (+0xda8 with the +0x2d38 config) at the actor's
 * heading. When the actor is drivable (0209fc48), it picks the secondary slot: modes 0x17/0x18
 * map to 0/1 when bit 12 of +0x464 is set, modes 0x25..0x2a read the slot from the +0x2de0 table
 * -- and when the heading matches the owner's and bit 52 of +0x464 is clear, the frame is
 * rebased on the heading. A primary slot binds and frames the +0xf10 animation (and, with bit 0
 * of +0x694, submits the draw: material triple from the model at +0xdd0, cached block, optional
 * +0xeb0 parameter, the +0xeb4 matrix, then the channels); a secondary slot does the same on
 * both tracks of the +0x2c30 animation with the +0x2d34 parameter. Finally 020ad588 runs.
 *
 * The bind's group argument is a `short` in the prototype: the ROM re-truncates the slot at each
 * of the two secondary binds (`lsl/asr` per call), which a `(short)` cast at the call sites CSEs
 * into one truncation.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;
typedef struct { unsigned char b0 : 1, b1 : 1; } Flags;

extern int func_0202aee0(void *animation, int track);                          /* Anim_GetFrame */
extern int func_ov022_02083f90(void);
extern void func_ov022_0209145c(void *attach, int tick);
extern void func_ov022_02091474(void *attach);
extern int func_ov022_020912d8(void *attach);
extern int func_02030788(void);
extern void func_ov002_020521e4(char *channel, char *config, int heading, int frame);
extern int func_ov022_0209fc48(char *self, int i);
extern void func_0202accc(char *anim, int track, char *bind, short group);         /* BindAnimTrack */
extern void func_01fff774(char *anim, int track, int frame);                     /* Anim_SetFrameWrapped */
extern void func_01ff9f00(unsigned int cmd, const void *src, unsigned int words); /* GX_SendFifoWords */
extern void func_0201571c(void);                                                  /* submit the cached block */
extern void func_01ffcec0(unsigned int value);
extern void func_020279e0(char *channels);
extern void func_ov022_020ad588(char *self);

void func_ov064_020b5f60(char *self)
{
    unsigned int aMaterial[3];
    unsigned int aMaterial2[3];
    int frame = func_0202aee0(*(char **)(self + 0x20) + 4, 0);
    int cur;
    int id2;
    unsigned int material;
    char *blk;
    char *anim;
    int id;
    int mode;

    func_ov022_0209145c(*(void **)(self + 0x2644), func_ov022_02083f90());
    func_ov022_02091474(*(void **)(self + 0x2644));
    if (func_ov022_020912d8(*(void **)(self + 0x2644)) == 0) {
        if (func_02030788() == 0) {
            *(u64 *)(self + 0x464) |= 0x10000;
        }
        if (func_02030788() == 0) {
            *(u64 *)(self + 0x46c) |= 0x10000;
        }
    }
    func_ov002_020521e4(self + 0x1a8 + 0xc00, self + 0x138 + 0x2c00, *(short *)(self + 0x2aba), frame);
    if (func_ov022_0209fc48(self, 0) != 0) {
        blk = self + 0x1ac + 0xc00;
        cur = *(short *)(self + 0x2aba);
        material = *(unsigned int *)(*(char **)(blk + 0x24) + 0x1c);
        if (cur == func_ov022_02083f90() && (*(u64 *)(self + 0x464) & 0x10000000000000ULL) == 0) {
            if (frame <= cur) {
                frame = cur;
            }
            frame -= cur;
        }
        mode = *(int *)(self + 0x6bc);
        id = -1;
        id2 = -1;
        switch (mode) {
        case 0x17:
            if ((*(u64 *)(self + 0x464) & 0x1000) != 0) {
                id = 0;
            }
            break;
        case 0x18:
            if ((*(u64 *)(self + 0x464) & 0x1000) != 0) {
                id = 1;
            }
            break;
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2a:
            id2 = *(signed char *)(self + (mode - 0x1e) + 0x2d00 + 0xe0);
            break;
        }
        if (id >= 0) {
            if (*(signed char *)(self + 0xf0d) != 0) {
                *(u8 *)(self + 0xf0c) |= 1;
            }
            anim = self + 0xf10;
            func_0202accc(anim, 0, self + 0x48 + 0x1000, id);
            func_01fff774(anim, 0, frame);
            if (((Flags *)(self + 0x694))->b0) {
                aMaterial[0] = material;
                aMaterial[1] = material;
                aMaterial[2] = material;
                func_01ff9f00(0x1b, aMaterial, 3);
                func_0201571c();
                if ((*(u16 *)blk & 0x40) != 0) {
                    func_01ffcec0(*(u16 *)(blk + 0x104));
                }
                func_01ff9f00(0x17, self + 0x2b4 + 0xc00, 0xc);
                func_01ffcec0(*(u16 *)(anim + 0x104));
                func_020279e0(anim + 0x20);
            }
        } else {
            if (*(signed char *)(self + 0xf0d) != 0) {
                *(u8 *)(self + 0xf0c) &= ~1;
            }
        }
        if (id2 >= 0) {
            func_0202accc(self + 0xc30 + 0x2000, 0, self + 0xd10 + 0x2000, id2);
            func_0202accc(self + 0xc30 + 0x2000, 1, self + 0xd10 + 0x2000, id2);
            func_01fff774(self + 0xc30 + 0x2000, 0, frame);
            func_01fff774(self + 0xc30 + 0x2000, 1, frame);
            if (((Flags *)(self + 0x694))->b0) {
                aMaterial2[0] = material;
                aMaterial2[1] = material;
                aMaterial2[2] = material;
                func_01ff9f00(0x1b, aMaterial2, 3);
                func_0201571c();
                func_01ff9f00(0x17, self + 0x2b4 + 0xc00, 0xc);
                func_01ffcec0(*(u16 *)(self + 0x2d00 + 0x34));
                func_020279e0(self + 0xc50 + 0x2000);
            }
        }
    }
    func_ov022_020ad588(self);
}
