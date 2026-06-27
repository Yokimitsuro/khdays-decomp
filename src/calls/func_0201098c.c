extern void GetRegionOfMBlock(void *region_out, void *mblock);
extern void RemoveMBlock(void *list, void *mblock);
extern void RecycleRegion(void *region_list, void *region);

void func_0201098c(void *heap, void *user_ptr) {
    char local[8];
    void *mblock = (char *)user_ptr - 0x10;
    GetRegionOfMBlock(&local, mblock);
    RemoveMBlock((char *)heap + 0x2c, mblock);
    RecycleRegion((char *)heap + 0x24, &local);
}
