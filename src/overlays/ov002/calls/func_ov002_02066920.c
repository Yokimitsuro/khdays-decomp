/* Swap the active pair at +0xc/+0x10: deactivate the outgoing one when there is
 * one, activate the incoming one, and record both. Passing a null incoming
 * object records only the object pointer and leaves the slot alone -- the flags
 * from the argument move itself are what the ROM branches on. */
extern void func_ov002_02066894(int object, int slot, int active);

extern char *data_ov002_0207f9f0;

void func_ov002_02066920(int object, int slot) {
    char *ctx = data_ov002_0207f9f0;

    if (slot != 0) {
        if (*(int *)(ctx + 0x10) != 0) {
            func_ov002_02066894(*(int *)(ctx + 0xc), *(int *)(ctx + 0x10), 0);
        }
        func_ov002_02066894(object, slot, 1);
        *(int *)(ctx + 0x10) = slot;
    }

    *(int *)(ctx + 0xc) = object;
}
