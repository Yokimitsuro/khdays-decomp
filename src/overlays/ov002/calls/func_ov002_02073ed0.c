/* Show or hide the render node belonging to a key, and set its priority.
 *
 * The key maps to a slot; the slot's record is 0x18 bytes into the array at
 * +0x44 of the context, and its node pointer sits at +0xf4 of that record.
 * Showing writes a three-bit priority into bits 16 to 18 of the node's word at
 * +0xc; hiding calls the clearing counterpart and leaves the priority alone.
 *
 * The masked read must come first in the or: written the other way round mwcc
 * emits the shift pair ahead of the load.
 */
extern char *data_ov002_0207fa14;

extern int func_ov002_02074460(int nKey);
extern void func_ov107_020cb51c(void *pNode, int nFlag);
extern void func_ov107_020cb544(void *pNode, int nFlag);

void func_ov002_02073ed0(int nKey, int bVisible, int nValue) {
    char *root = data_ov002_0207fa14;
    int nIndex = func_ov002_02074460(nKey);

    if (bVisible != 0) {
        char *pNode = *(char **)(*(char **)(*(char **)(root + 0x44) +
                                            nIndex * 0x18) + 0xf4);

        *(unsigned int *)(pNode + 0xc) =
            (*(unsigned int *)(pNode + 0xc) & 0xfff8ffff) |
            ((unsigned int)(nValue & 7) << 16);
        func_ov107_020cb51c(*(char **)(*(char **)(*(char **)(root + 0x44) +
                                                  nIndex * 0x18) + 0xf4),
                            1);
        return;
    }
    func_ov107_020cb544(*(char **)(*(char **)(*(char **)(root + 0x44) +
                                              nIndex * 0x18) + 0xf4),
                        1);
}
