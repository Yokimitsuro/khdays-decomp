/* func_ov008_02050dd0 -- tear down every entry in the menu's active-widget list, ov008.
 * Walks the intrusive list at base+0x9660 and releases each node via func_ov008_02050d50,
 * fetching the next link before freeing the current one. */
extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern void  func_ov008_02050d50(int node);
extern int   data_ov008_02090f04[];

void func_ov008_02050dd0(void) {
    int node = (int)NNS_FndGetNextListObject((void *)(data_ov008_02090f04[1] + 0x9660), 0);
    if (node != 0) {
        int next;
        do {
            next = (int)NNS_FndGetNextListObject((void *)(data_ov008_02090f04[1] + 0x9660), (void *)node);
            func_ov008_02050d50(node);
            node = next;
        } while (next != 0);
    }
}
