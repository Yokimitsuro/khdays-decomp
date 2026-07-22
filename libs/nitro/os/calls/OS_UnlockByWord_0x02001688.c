/* Constant-argument forwarding veneer onto OSi_DoUnlockByWord (fourth argument 0). */
extern void *OSi_DoUnlockByWord();

void *OS_UnlockByWord_0x02001688(int a, void *b, void *c) {
    return OSi_DoUnlockByWord(a, b, c, 0);
}
