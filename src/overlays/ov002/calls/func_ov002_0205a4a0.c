/* Count the entries in the panel's list at +0x480. The global is re-read on
 * every iteration rather than cached, which is what keeps the list head out of a
 * callee-saved register. */
extern void *NNS_FndGetNextListObject(void *list, void *from);

extern char *data_ov002_0207f620;

int func_ov002_0205a4a0(void) {
    int count = 0;
    void *node = NNS_FndGetNextListObject(data_ov002_0207f620 + 0x480, 0);

    while (node != 0) {
        count++;
        node = NNS_FndGetNextListObject(data_ov002_0207f620 + 0x480, node);
    }

    return count;
}
