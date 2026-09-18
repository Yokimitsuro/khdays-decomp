/* Steps one attack slot of the ov037 enemy (x4: ov037/055/075/092): a busy effect context marks
 * the slot armed (+0x114); in modes 0x2f/0x30, or while the slot is in phase 2, the local
 * player's flag bit 16 is raised in both words. Phase 1 fires once the +0x7b0 timer passes
 * 0x27000 on an armed slot: tracks 0, 2 and 1 are bound to the slot's table (+0x10c) at the
 * elapsed frame, the slot is pinned to the actor's heading and origin, 0xcf is told and phase 2
 * begins; phase 2 keeps the slot pinned and advances the tracks until they finish. The slot's
 * time step runs afterwards. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_ov022_02095554(char *context);
extern int func_02030788(void);
extern void func_0202accc(void *animation, int track, void *table, short mode);   /* BindAnimTrack */
extern void func_01fff774(void *animation, int track, int frame);                /* Anim_SetFrameWrapped */
extern int func_0202a818(void *animation, int delta);                            /* Sequence_UpdateTracks */
extern void func_ov022_020a4490(char *self, int nSound, int nVariant);
extern void func_ov093_020bbbbc(char *self, char *slot, int dt);

/* Pins the slot's node to the actor's heading and origin. */
static inline void Ov037_PinSlot(char *slot, u16 heading, Vec3 *origin)
{
    *(u16 *)(slot + 0x80) = heading;
    *(u16 *)(slot + 4) |= 0x20;
    *(Vec3 *)(slot + 0xa8) = *origin;
}

void func_ov093_020bb900(char *self, char *slot, int dt)
{
    Vec3 origin;
    u16 heading;
    int frame;
    int bLocal = 0;

    if (func_ov022_02095554(self + 0x2f8 + 0x2000) != 0) {
        *(int *)(slot + 0x114) = 1;
    }
    if (*(int *)(self + 0x6bc) == 0x2f || *(int *)(self + 0x6bc) == 0x30 || *(int *)slot == 2) {
        bLocal = 1;
    }
    if (bLocal != 0) {
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x464) |= 0x10000;
        }
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x46c) |= 0x10000;
        }
    }
    origin = *(Vec3 *)(self + 0x8c + 0x400);
    heading = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    switch (*(int *)slot) {
    case 1:
        if (*(int *)(self + 0x7b0) >= 0x27000 && *(int *)(slot + 0x114) != 0) {
            frame = *(int *)(self + 0x7b0) - 0x27000;
            func_0202accc(slot + 4, 0, *(void **)(slot + 0x10c), 0);
            func_0202accc(slot + 4, 2, *(void **)(slot + 0x10c), 0);
            func_0202accc(slot + 4, 1, *(void **)(slot + 0x10c), 0);
            func_01fff774(slot + 4, 0, frame);
            func_01fff774(slot + 4, 2, frame);
            func_01fff774(slot + 4, 1, frame);
            Ov037_PinSlot(slot, heading, &origin);
            func_ov022_020a4490(self, 0xcf, 1);
            *(int *)slot = 2;
        }
        break;
    case 2:
        Ov037_PinSlot(slot, heading, &origin);
        if (func_0202a818(slot + 4, dt) != 0) {
            *(int *)slot = 0;
        }
        break;
    }
    func_ov093_020bbbbc(self, slot, dt);
}
