/* Steps one effect slot of the ov049 enemy (x4: ov049/068/087/104). A slot in phase 3 whose
 * owner lost the local flag bit 16 or left modes 0x2f/0x30 rebinds its tracks in mode 3,
 * releases its sound handle and goes to phase 5; a slot in phase 6 goes idle once the emitter
 * at +0x22f8 is quiet. Phase 1 waits for the +0x7b0 timer to reach 0x9000, then starts sound
 * 0xd2 (variant and scale by the slot's alternate flag), binds and rewinds tracks 0 and 2 and
 * goes to phase 2; 2 advances and, when done, rebinds in mode 2 (1 without the flag) into
 * phase 3; 3 only advances; 4 advances and on completion releases the sound into phase 1; 5
 * advances into phase 6. */
extern void func_0202accc(void *animation, int track, void *table, short mode);   /* BindAnimTrack */
extern void func_01fff774(void *animation, int track, int frame);                /* Anim_SetFrameWrapped */
extern int func_0202a818(void *animation, int delta);                            /* Sequence_UpdateTracks */
extern void func_02033e48(int handle);
extern int func_ov022_02095524(char *emitter);
extern int func_ov022_020a4490(char *self, int nSound, int nVariant);

void func_ov104_020bb14c(char *self, char *slot, int dt)
{
    int scale;
    int variant;
    int nBlend;

    if (*(signed char *)slot == 3
        && ((*(unsigned long long *)(self + 0x464) & 0x10000) == 0
            || (*(int *)(self + 0x6bc) != 0x2f && *(int *)(self + 0x6bc) != 0x30))) {
        func_0202accc(slot + 4, 0, *(void **)(slot + 0x10c), 3);
        func_0202accc(slot + 4, 2, *(void **)(slot + 0x10c), 3);
        if (*(int *)(slot + 0x120) != 0) {
            func_02033e48(*(int *)(slot + 0x120));
        }
        *(int *)(slot + 0x120) = 0;
        *slot = 5;
    }
    if (*(signed char *)slot == 6 && (*(unsigned long long *)(self + 0x464) & 0x10000) == 0
        && func_ov022_02095524(self + 0x2f8 + 0x2000) == 0) {
        *slot = 0;
    }
    switch (*(signed char *)slot) {
    case 1:
        if (*(int *)(self + 0x7b0) < 0x9000) {
            return;
        }
        if (*(int *)(slot + 0x118) != 0) {
            scale = 0x1000;
            variant = 1;
        } else {
            scale = 0x99a;
            variant = 0;
        }
        *(int *)(slot + 0x120) = func_ov022_020a4490(self, 0xd2, variant);
        *(int *)(slot + 0xbc) = scale;
        *(int *)(slot + 0xb8) = scale;
        *(int *)(slot + 0xb4) = scale;
        func_0202accc(slot + 4, 0, *(void **)(slot + 0x10c), 0);
        func_0202accc(slot + 4, 2, *(void **)(slot + 0x10c), 0);
        func_01fff774(slot + 4, 0, 0);
        func_01fff774(slot + 4, 2, 0);
        *slot = 2;
        break;
    case 2:
        if (func_0202a818(slot + 4, dt) != 0) {
            nBlend = *(int *)(slot + 0x118) != 0 ? 2 : 1;
            func_0202accc(slot + 4, 0, *(void **)(slot + 0x10c), nBlend);
            func_0202accc(slot + 4, 2, *(void **)(slot + 0x10c), nBlend);
            *slot = 3;
        }
        break;
    case 3:
        func_0202a818(slot + 4, dt);
        break;
    case 4:
        if (func_0202a818(slot + 4, dt) != 0) {
            if (*(int *)(slot + 0x120) != 0) {
                func_02033e48(*(int *)(slot + 0x120));
            }
            *(int *)(slot + 0x120) = 0;
            *slot = 1;
        }
        break;
    case 5:
        if (func_0202a818(slot + 4, dt) != 0) {
            *slot = 6;
        }
        break;
    }
}
