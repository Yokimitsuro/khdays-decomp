extern void func_0203bfb4(int list, int child);
/* Register the actor's attached sub-object (obj+0x9c) into the region's child list, if present. */
void func_ov107_020c4e9c(int obj, int region) {
    int child = *(int *)(obj + 0x9c);
    if (child != 0) {
        func_0203bfb4(*(int *)(region + 0x100), child);
    }
}
