typedef unsigned short u16;

extern unsigned char *data_0204be18;

extern void NNS_FndInitList(void *list, int offset);
extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void func_ov004_0204ec6c(void *state, void *callbacks);
extern void func_ov004_0204ef74(void *state, void *work, void *list, u16 *ids);
extern void func_ov004_0204ecf8(void *state, void *work, void *list);
extern u16 *func_0203583c(int kind, unsigned int id);
extern void func_ov004_0204f7e8(int id, int count);
extern void func_ov004_0204f1c4(void *state, void *work, void *list);
extern void WM_EndKeySharing_0x0204ecec(void *state);

void func_ov004_0204f874(void) {
    char list[0xc];
    char work[0x1e0];
    char state[0x100];
    void *node;
    u16 *entry;
    int remaining;

    NNS_FndInitList(list, 0x28);
    func_ov004_0204ec6c(state, 0);
    func_ov004_0204ef74(state, work, list, (u16 *)(data_0204be18 + 0xee0));
    func_ov004_0204ecf8(state, work, list);

    for (node = NNS_FndGetNextListObject(state + 0x20, 0); node != 0;
         node = NNS_FndGetNextListObject(state + 0x20, node)) {
        if (*(int *)node >= 2 && *(int *)node <= 11) {
            entry = func_0203583c(0, *(int *)node);
            if (entry == 0) {
                remaining = *(int *)((char *)node + 4);
            } else {
                remaining = *(int *)((char *)node + 4) - (short)entry[1];
            }
            if (remaining > 0) {
                func_ov004_0204f7e8(*(int *)node, remaining);
            }
        }
    }

    func_ov004_0204f1c4(state, work, list);
    WM_EndKeySharing_0x0204ecec(state);
}
