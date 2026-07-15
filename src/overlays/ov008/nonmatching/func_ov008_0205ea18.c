/* NONMATCHING: correct; +4B register-allocation tie -- the ROM holds the list ptr in r8 and the
 * popped node in r6 (no extra copy); our mwcc uses an extra reg + mov. Free all 8 widget lists. */
/* func_ov008_0205ea18 -- free every node in the object's 8 widget lists, ov008.
 * For each of the 8 lists (0xc-byte stride from obj+0x304), pops each node, unlinks it
 * (NNS_FndRemoveListObject) and frees it. */
extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern void  NNS_FndRemoveListObject(void *list, void *obj);
extern void  NNSi_FndFreeFromDefaultHeap(int p);

void func_ov008_0205ea18(int obj) {
    int i = 0;
    int *list = (int *)(obj + 0x304);
    do {
        int node = (int)NNS_FndGetNextListObject(list, 0);
        int cur;
        while ((cur = node) != 0) {
            node = (int)NNS_FndGetNextListObject(list, (void *)cur);
            NNS_FndRemoveListObject(list, (void *)cur);
            if (cur != 0) {
                NNSi_FndFreeFromDefaultHeap(cur);
            }
        }
        i++;
        list += 3;
    } while (i < 8);
}
