/* Is the leave finished? Needs the request bit 0x10 in the byte at +0x8b68, and
 * every leave flag except 0x100 already cleared -- the bics leaves exactly that
 * test, so it is `(flags & ~0x100) == 0` rather than a check on one bit. */
typedef struct {
    char pad0000[0x8b64];
    unsigned int dwLeaveFlags;  /* +0x8b64 */
    unsigned char bLeaveState;  /* +0x8b68 */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

int func_ov002_0206b7f4(void) {
    Ov002RootContext *root = data_ov002_0207fa00;

    if ((root->bLeaveState & 0x10) != 0 && (root->dwLeaveFlags & ~0x100) == 0) {
        return 1;
    }

    return 0;
}
