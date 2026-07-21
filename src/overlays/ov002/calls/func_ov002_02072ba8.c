extern int func_ov002_02072754(void);
extern int func_ov002_02076688(unsigned short id);
/* Walk the current widget's sibling chain, stopping at the first one whose kind (+0x4c of its
 * descriptor) is 0xe. */
void func_ov002_02072ba8(void) {
    int p = func_ov002_02076688((unsigned short)func_ov002_02072754());
    while (p != 0) {
        if (*(unsigned short *)(*(int *)(p + 8) + 0x4c) == 0xe) {
            return;
        }
        p = *(int *)(p + 4);
    }
}
