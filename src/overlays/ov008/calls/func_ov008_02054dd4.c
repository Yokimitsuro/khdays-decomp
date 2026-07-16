/* func_ov008_02054dd4 -- apply func_ov008_02054d90(.,.,param_2) to every node in the object list
 * at param_1+0x4a38. */
extern int  NNS_FndGetNextListObject(void *list, int obj);
extern void func_ov008_02054d90(int owner, int node, unsigned int arg);

void func_ov008_02054dd4(int param_1, unsigned int param_2) {
    int node = NNS_FndGetNextListObject((void *)(param_1 + 0x4a38), 0);
    if (node != 0) {
        do {
            func_ov008_02054d90(param_1, node, param_2);
            node = NNS_FndGetNextListObject((void *)(param_1 + 0x4a38), node);
        } while (node != 0);
    }
}
