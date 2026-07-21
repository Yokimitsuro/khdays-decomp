extern void func_ov023_02083bd4(int table);
/* Script op: run the entity-table pass when the VM has one (*(vm+0x128))+0x440; always returns 1. */
int func_ov023_02085f2c(int vm) {
    int table = *(int *)(*(int *)(vm + 0x128) + 0x440);
    if (table != 0) {
        func_ov023_02083bd4(table);
    }
    return 1;
}
