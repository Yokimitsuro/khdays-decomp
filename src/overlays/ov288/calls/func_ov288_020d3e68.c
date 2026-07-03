struct ent { int w[3]; };
extern void NNSi_FndDestroyDoubleList(void *p);
extern void func_01fffc24(void *p);
extern void *func_01fffca8(int a, int b, int c);
void func_ov288_020d3e68(int obj, int size, int *entries) {
    struct ent *src;
    int count, i;
    *(int *)(obj + 0x390) = entries[0];
    src = (struct ent *)((char *)entries + 4);
    NNSi_FndDestroyDoubleList((void *)(obj + 0x398));
    func_01fffc24((void *)(obj + 0x398));
    count = (int)((unsigned int)(size - 4) / 12);
    for (i = 0; i < count; i++) {
        struct ent *slot = (struct ent *)func_01fffca8(obj + 0x398, 12, 0x64);
        *slot = *src;
        src++;
    }
}
