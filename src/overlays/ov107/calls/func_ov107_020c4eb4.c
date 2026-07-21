extern void func_0203bfe8(int list, int child);
/* Remove the actor's attached sub-object (obj+0x9c) from the region's child list, if present. */
void func_ov107_020c4eb4(int obj, int region) {
    int child = *(int *)(obj + 0x9c);
    if (child != 0) {
        func_0203bfe8(*(int *)(region + 0x100), child);
    }
}
