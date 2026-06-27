extern void func_02019d94(int p);
extern void NNS_FndRemoveListObject(void *list, void *obj);
extern char data_0204abe4[];

void func_0201ad60(int *p) {
    func_02019d94(p[16]);
    NNS_FndRemoveListObject(data_0204abe4, p);
    p[9] &= ~1;
}
