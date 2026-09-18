/* Steps one effect slot of the ov045 enemy (x4: ov045/064/083/100). Unless the local player's
 * flag bit 16 is set, a slot in phase 3 rebinds tracks 0 and 2 in mode 2 and goes to phase 4,
 * and a slot in phase 5 goes idle once the emitter at +0x22f8 is quiet. Phases 1 to 3 keep the
 * slot on the actor (heading and origin); 1 waits for the +0x7b0 timer to reach 0x9000, 2
 * advances the tracks and on completion rebinds them in mode 1 for phase 3, 3 only advances,
 * and 4 advances until completion into phase 5. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_0202accc(void *animation, int track, void *table, short mode);   /* BindAnimTrack */
extern int func_ov022_02095524(char *emitter);
extern int func_0202a818(void *animation, int delta);                            /* Sequence_UpdateTracks */

/* Pins the slot's node to the actor's heading and origin. */
static inline void Ov045_PinSlot(char *slot, u16 heading, Vec3 *origin)
{
    *(u16 *)(slot + 0x80) = heading;
    *(u16 *)(slot + 4) |= 0x20;
    *(Vec3 *)(slot + 0xa8) = *origin;
}

void func_ov064_020b6a54(char *self, char *slot, int dt)
{
    Vec3 origin;
    u16 heading;

    if (*(signed char *)slot == 3 && (*(unsigned long long *)(self + 0x464) & 0x10000) == 0) {
        func_0202accc(slot + 4, 0, slot + 0xe4, 2);
        func_0202accc(slot + 4, 2, slot + 0xe4, 2);
        *slot = 4;
    }
    if (*(signed char *)slot == 5 && (*(unsigned long long *)(self + 0x464) & 0x10000) == 0
        && func_ov022_02095524(self + 0x2f8 + 0x2000) == 0) {
        *slot = 0;
    }
    origin = *(Vec3 *)(self + 0x8c + 0x400);
    heading = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    switch (*(signed char *)slot) {
    case 1:
        if (*(int *)(self + 0x7b0) < 0x9000) {
            return;
        }
        Ov045_PinSlot(slot, heading, &origin);
        *slot = 2;
        break;
    case 2:
        Ov045_PinSlot(slot, heading, &origin);
        if (func_0202a818(slot + 4, dt) != 0) {
            func_0202accc(slot + 4, 0, slot + 0xe4, 1);
            func_0202accc(slot + 4, 2, slot + 0xe4, 1);
            *slot = 3;
        }
        break;
    case 3:
        Ov045_PinSlot(slot, heading, &origin);
        func_0202a818(slot + 4, dt);
        break;
    case 4:
        if (func_0202a818(slot + 4, dt) != 0) {
            *slot = 5;
        }
        break;
    }
}
