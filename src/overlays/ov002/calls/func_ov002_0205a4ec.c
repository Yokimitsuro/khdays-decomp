/* Count the entries in the panel's second list at +0x498. Sibling of
 * func_ov002_0205a4a0 over the list at +0x480; the global is likewise re-read on
 * every iteration. ARM cannot encode 0x498 as one immediate, so the +0x98/+0x400
 * split is forced rather than chosen. */
extern void *NNS_FndGetNextListObject(void *list, void *from);

extern char *data_ov002_0207f620;

int func_ov002_0205a4ec(void) {
    int count = 0;
    void *node = NNS_FndGetNextListObject(data_ov002_0207f620 + 0x498, 0);

    while (node != 0) {
        count++;
        node = NNS_FndGetNextListObject(data_ov002_0207f620 + 0x498, node);
    }

    return count;
}
