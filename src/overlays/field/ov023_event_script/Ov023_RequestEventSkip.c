/* Ov023_RequestEventSkip -- the pause menu's Skip: ask the event's script (its state at +0x4b88 of
 * the scene root) to skip to its end, unless bit 3 of the status halfword at +0x8758c is set. */
extern void ActionScript_RequestSkip(void *p);
extern int data_ov023_0208a784;

void Ov023_RequestEventSkip(void) {
    char *base = (char *)*(int *)((char *)&data_ov023_0208a784 + 4);
    if ((*(unsigned short *)(base + 0x8758c) & 8) == 0) {
        ActionScript_RequestSkip(base + 0x4b88);
    }
}
