/* Stamp an owner on every member of a group, and clear the group's low flag nibble.
 *
 * The group table hangs two indirections off the root pointer: the root's word at +4 leads to an
 * array of entry pointers starting at +8. An entry is a signed count byte, a flag byte, and then
 * one four-byte member per count. Each member takes the mark at its own +1: 0xff when the caller
 * passes -1 for nobody, otherwise the owner index plus one, so zero stays free to mean unset.
 *
 * Three details are what the original codegen turns on. The flag nibble is cleared with an AND
 * against the complement rather than against 0xf0. The mark is unsigned while the two header
 * bytes are signed, which is why only one zero extension appears. And the counter is declared
 * before the entry pointer, which is what settles the two into the registers the ROM uses.
 *
 * Ghidra carries the layout as Ov002GroupEntry and Ov002GroupMember.
 */

typedef unsigned char u8;

extern char *data_ov002_0207fa14;

void func_ov002_02073fb0(int group, int owner) {
    int i = 0;
    char *entry = *(char **)(*(char **)(data_ov002_0207fa14 + 4) + group * 4 + 8);

    entry[1] &= ~0xf;
    if (entry[0] > 0) {
        char *member = entry + 4;
        do {
            if (owner == -1) {
                *(u8 *)(member + 1) = 0xff;
            } else {
                *(u8 *)(member + 1) = (u8)(owner + 1);
            }
            i++;
            member += 4;
        } while (i < entry[0]);
    }
}
