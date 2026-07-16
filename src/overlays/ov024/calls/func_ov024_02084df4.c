/* func_ov024_02084df4 -- MobiClip: ask a player slot to start, by kind.
 * data_ov024_02093a2c holds the player globals; +8 and +0xc are the two live slots (audio and
 * video), +0x18 a standby the video slot is swapped to. Non-zero `which` pokes the +8 slot,
 * zero pokes the +0xc slot; either way nothing happens if that slot is empty.
 * The +0xc path first retires a slot that has reached state 6 by swapping in the standby, so
 * the poke lands on the incoming one. Note the slot is NOT re-checked for NULL after the swap.
 * This is the entry ov012 (the movie scene wrapper) calls to drive playback. */
extern int data_ov024_02093a2c[];

static inline void Ov024_KickSlot(int slot) {
    if (*(unsigned char *)(slot + 0x38) == 0) {
        *(unsigned char *)(slot + 0x38) = 1;
    }
}

void func_ov024_02084df4(int which) {
    int slot;

    if (which != 0) {
        slot = data_ov024_02093a2c[2];
        if (slot == 0) {
            return;
        }
        Ov024_KickSlot(slot);
        return;
    }

    slot = data_ov024_02093a2c[3];
    if (slot == 0) {
        return;
    }
    if (*(unsigned char *)(slot + 0x38) == 6) {
        if (data_ov024_02093a2c[6] != 0) {
            data_ov024_02093a2c[3] = data_ov024_02093a2c[6];
        }
    }
    Ov024_KickSlot(data_ov024_02093a2c[3]);
}
