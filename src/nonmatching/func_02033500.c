/* NONMATCHING: semantically complete, address-CSE tie. The ROM recomputes obj+0x9c inside each
 * branch (add r0,r4; add r0,#0x9c) for both the compare and the store; mwcc hoists it into a
 * callee-saved reg before the branch. Inline expressions do not defeat the CSE. Rest matches.
 * Behaviour: switch active card-transfer id -- if unchanged re-arm the +0x98 slot; else store
 * the id, wait on FSi_WaitForCardThread (u64 -> func_0203358c), re-arm +0x94, bind, alloc +0x98. */
extern void func_0201ba54(int *list, int value);
extern long long FSi_WaitForCardThread(void);
extern void func_0203358c(long long tick);
extern void func_0201bbf4(unsigned int id, int *list);
extern int func_0201ba08(int *list);

void func_02033500(unsigned int id) {
    int obj = (int)data_0204c234;

    if (*(unsigned int *)(obj + 0x9c) == id) {
        func_0201ba54(*(int **)(obj + 0xb04a0), *(int *)(obj + 0x98));
        return;
    }
    *(unsigned int *)(obj + 0x9c) = id;
    func_0203358c(FSi_WaitForCardThread());
    func_0201ba54(*(int **)(obj + 0xb04a0), *(int *)(obj + 0x94));
    func_0201bbf4(id, *(int **)(obj + 0xb04a0));
    *(int *)(obj + 0x98) = func_0201ba08(*(int **)(obj + 0xb04a0));
}
