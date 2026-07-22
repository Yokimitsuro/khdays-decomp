/* Result-screen step. Runs the poll hook at root + 0x8b94 and gives up while it
 * reports nothing; then runs the advance hook at root + 0x8b88 and, for reason
 * codes -4 and -3 only, fires event 0x1e. Raises bit 0 of the byte at +0x8d0c
 * and hands back the entry step at func_ov002_02069084.
 *
 * The reason is the SIGNED halfword at root + 0x8ba8 + 2 -- the same
 * Ov002ResultContext head Ov002_EnterResultScene and Ov002_SnapshotResultReport
 * read. The hooks sit either side of it, so the ROM reaches the poll hook as
 * (result base - 0x14) rather than through its own constant. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_020336a4(int event);
extern void func_ov002_02069084(void);

void *func_ov002_02069030(void) {
    char *root = NNSi_FndGetCurrentRootHeap();
    short *result = (short *)(root + 0x8ba8);

    if ((*(int (**)(void))(root + 0x8ba8 - 0x14))() == 0) {
        return 0;
    }

    (*(void (**)(void))(root + 0x8b88))();

    switch (result[1]) {
    case -4:
    case -3:
        func_020336a4(0x1e);
        break;
    }

    *(unsigned char *)(root + 0x8d0c) |= 1;
    return (void *)&func_ov002_02069084;
}
