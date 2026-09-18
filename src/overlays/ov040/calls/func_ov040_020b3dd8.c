/* Steps one attack slot of the ov040 enemy (x4: ov040/059/079/096). Any slot that is neither
 * idle nor already ending is forced to phase 3 when the enemy leaves mode 0x33. Phase 1
 * accumulates the timer and advances the tracks; when they finish tracks 0 and 2 are rebound in
 * mode 1 and the slot goes to phase 2; from 0x3000 on the timer the local player's flag bit 33
 * is raised. Phase 2 only advances the tracks and raises that flag. Phase 3 accumulates and
 * advances, goes idle when the tracks finish, raises the flag while the timer is at most 0x3000
 * and, past it in mode 0x31, drops bit 49 of the actor flags, hides the node and runs the
 * slot's finish handler. */
extern int func_0202a818(void *animation, int delta);                          /* Sequence_UpdateTracks */
extern void func_0202accc(void *animation, int track, void *table, short mode); /* BindAnimTrack */
extern int func_02030788(void);
extern void func_0202af2c(void *node);                                          /* SceneNode_Disable */
extern void func_ov040_020b3bcc(char *self, char *slot);

/* Raises bit 33 of the +0x46c flags on the local player. */
static inline void Ov040_FlagLocalSlot(char *self)
{
    if (func_02030788() == 0) {
        if (func_02030788() == 0) {
            *(unsigned long long *)(self + 0x46c) |= 0x200000000ULL;
        }
    }
}

void func_ov040_020b3dd8(char *self, char *slot, int dt)
{
    if (*(int *)(self + 0x6bc) != 0x33 && *(int *)(slot + 0x234) != 0 && *(int *)(slot + 0x234) != 3) {
        *(int *)(slot + 0x234) = 3;
    }
    switch (*(int *)(slot + 0x234)) {
    case 1:
        *(int *)(slot + 0x230) += dt;
        if (func_0202a818(slot + 0x238, dt) != 0) {
            func_0202accc(slot + 0x238, 0, slot + 0x318, 1);
            func_0202accc(slot + 0x238, 2, slot + 0x318, 1);
            *(int *)(slot + 0x234) = 2;
        }
        if (*(int *)(slot + 0x230) >= 0x3000) {
            Ov040_FlagLocalSlot(self);
        }
        break;
    case 2:
        func_0202a818(slot + 0x238, dt);
        Ov040_FlagLocalSlot(self);
        break;
    case 3:
        *(int *)(slot + 0x230) += dt;
        if (func_0202a818(slot + 0x238, dt) != 0) {
            *(int *)(slot + 0x234) = 0;
        }
        if (*(int *)(slot + 0x230) <= 0x3000) {
            Ov040_FlagLocalSlot(self);
        } else if (*(int *)(self + 0x6bc) == 0x31) {
            if (func_02030788() == 0) {
                *(unsigned long long *)self &= ~0x2000000000000ULL;
                if ((**(unsigned int **)(self + 0x20) & 0x20) == 0) {
                    func_0202af2c(*(char **)(self + 0x20) + 4);
                }
            }
            func_ov040_020b3bcc(self, slot);
        }
        break;
    }
}
