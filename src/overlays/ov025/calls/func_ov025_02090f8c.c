/* func_ov025_02090f8c -- free every node in the object's 8 widget lists, ov008.
 * For each of the 8 NNSFndList heads (0xc-byte stride from obj+0x304) the list is drained: take
 * the head, look the successor up BEFORE unlinking, unlink, free, and carry on from the successor.
 *
 * Two things make it match, and the park note had guessed the wrong cause for both:
 *   - The inner loop is a do/while whose test is on the LOOKAHEAD (`while (node != 0)`) after
 *     `cur = node`, not `while ((cur = node) != 0)`. Testing through the assignment makes mwcc
 *     keep a second copy of the value -- that is the extra `mov` and the extra 4 bytes, not a
 *     register-allocation tie.
 *   - Declaration order is i, cur, node, list. mwcc colours the callee-saved registers in
 *     declaration order (r5, r6, r7, r8), and the list pointer is the LAST of the four in the
 *     ROM even though it is the first thing assigned. */
extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern void  NNS_FndRemoveListObject(void *list, void *obj);
extern void  NNSi_FndFreeFromDefaultHeap(int p);

void func_ov025_02090f8c(int obj) {
    int i;
    int cur;
    int node;
    int *list;

    i = 0;
    list = (int *)(obj + 0x304);
    do {
        cur = (int)NNS_FndGetNextListObject(list, 0);
        if (cur != 0) {
            do {
                node = (int)NNS_FndGetNextListObject(list, (void *)cur);
                NNS_FndRemoveListObject(list, (void *)cur);
                if (cur != 0) {
                    NNSi_FndFreeFromDefaultHeap(cur);
                }
                cur = node;
            } while (node != 0);
        }
        i++;
        list += 3;
    } while (i < 8);
}
