/* Command 5 (slot 0 only): spawn a child of kind 0x17 at a packed 24-bit big-endian offset, then
 * chain to the next handler.
 *
 * The command carries three signed 24-bit coordinates as raw bytes (cmd[5..7], [8..a], [b..d]).
 * Each is assembled big-endian into the top 3 bytes of a 4-byte scratch word and read back with an
 * arithmetic >>8, sign-extending the 24-bit value. The three become an SrtTransform translation
 * (identity rotation via func_0203c960, then Srt_SetTranslation) and func_ov107_020c0794 spawns
 * the child under the +0x3a8 record's parent, storing its handle in that record's +4. The command
 * kind is a switch: an `if` chain would predicate the slot test. */

typedef struct {
    int aRot[4];
    int aTranslation[3];
    int aScale[3];
    unsigned char bFlags;
    unsigned char aPad29[3];
} SrtTransform;

extern void func_0203c960(int *aRot);
extern void func_0203ca30(SrtTransform *srt, int *translation);
extern int func_ov107_020c0794(int model, int parent, int kind, int arg, SrtTransform *srt);
extern void func_ov107_020c7500(int this_, int cmd, int p3);

void func_ov213_020d07c4(int this_, int cmd, int p3) {
    SrtTransform srt;
    int pos[3];
    int w2, w1, w0;

    switch (*(unsigned char *)(cmd + 2)) {
    case 5:
        if (*(unsigned char *)(cmd + 3) == 0) {
            func_0203c960(srt.aRot);
            *((unsigned char *)&w0 + 3) = *(unsigned char *)(cmd + 5);
            *((unsigned char *)&w0 + 2) = *(unsigned char *)(cmd + 6);
            *((unsigned char *)&w0 + 1) = *(unsigned char *)(cmd + 7);
            pos[0] = w0 >> 8;
            *((unsigned char *)&w1 + 3) = *(unsigned char *)(cmd + 8);
            *((unsigned char *)&w1 + 2) = *(unsigned char *)(cmd + 9);
            *((unsigned char *)&w1 + 1) = *(unsigned char *)(cmd + 0xa);
            pos[1] = w1 >> 8;
            *((unsigned char *)&w2 + 3) = *(unsigned char *)(cmd + 0xb);
            *((unsigned char *)&w2 + 2) = *(unsigned char *)(cmd + 0xc);
            *((unsigned char *)&w2 + 1) = *(unsigned char *)(cmd + 0xd);
            pos[2] = w2 >> 8;
            func_0203ca30(&srt, pos);
            *(int *)(*(int *)(this_ + 0x3a8) + 4) =
                func_ov107_020c0794(*(int *)(this_ + 0x3c), *(int *)(*(int *)(this_ + 0x3a8)), 0x17, 0, &srt);
        }
        break;
    }
    func_ov107_020c7500(this_, cmd, p3);
}
