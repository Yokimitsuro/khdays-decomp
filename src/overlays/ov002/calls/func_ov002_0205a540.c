/* Which slot carries this key? Returns its index, or -1.
 *
 * The panel session keeps how many slots there are at 0x4ae and the keys from 0x4b8, one every
 * 0xc bytes. The count is re-read on every pass, as the original does.
 *
 * Three details carry the codegen. The count is widened to int before the zero test, or the
 * compiler uses an equality branch where the original has a signed one. The index is declared
 * before the result, which fixes which register each gets. And the result is assigned before the
 * index, or the compiler builds -1 by subtracting from the zero it just made rather than
 * materialising it.
 *
 * Ghidra carries the two fields as wSlotCount and wSlotKey on Ov002PanelSession.
 */

typedef unsigned short u16;
typedef unsigned int u32;

extern char *data_ov002_0207f620;

int func_ov002_0205a540(u32 key) {
    char *session = data_ov002_0207f620;
    int i;
    int found = -1;
    char *entry = session;

    i = 0;

    if ((int)*(u16 *)(session + 0x4ae) > 0) {
        do {
            if (key == *(u16 *)(entry + 0x4b8)) {
                found = i;
                break;
            }
            i++;
            entry += 0xc;
        } while (i < *(u16 *)(session + 0x4ae));
    }
    return found;
}
