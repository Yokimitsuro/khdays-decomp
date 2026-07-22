/* Mark a peer slot ready in the mask at +0x8c8a, but only when the slot passes
 * the join check; a slot that fails is reported as 0 and left out of the mask. */
extern int func_ov002_0206b828(int slot);

typedef struct {
    char pad0000[0x8c8a];
    unsigned char bReadyMask;   /* +0x8c8a, bit per peer slot */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

int func_ov002_0206bb7c(int slot) {
    Ov002RootContext *root = data_ov002_0207fa00;

    if (func_ov002_0206b828(slot) != 0) {
        return 0;
    }

    root->bReadyMask |= 1 << slot;
    return 1;
}
