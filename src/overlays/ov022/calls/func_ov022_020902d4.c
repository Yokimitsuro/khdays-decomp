/* Store a new value in the record at +0xc; if it actually changed, also raise the dirty byte
 * at +2. Either way bit 7 of the flags halfword at +0 goes up, so the owner re-reads it.
 *
 * The original does NOT factor the shared `|= 0x80` -- it duplicates it, predicating the whole
 * unchanged path (ldrheq/orreq/strheq/bxeq). Writing the UNCHANGED case first, as the park did,
 * lets mwcc tail-merge the two copies into one unconditional tail and the body comes out four
 * bytes short. Writing the CHANGED case first, with its own copy of the tail and an explicit
 * `return`, keeps them apart. Branch orientation is the whole axis here; it is not a
 * tail-merge tie. */
void func_ov022_020902d4(unsigned short *record, int value) {
    if (*(int *)(record + 6) != value) {
        *(int *)(record + 6) = value;
        *(char *)(record + 1) = 1;
        *record |= 0x80;
        return;
    }
    *record |= 0x80;
}
