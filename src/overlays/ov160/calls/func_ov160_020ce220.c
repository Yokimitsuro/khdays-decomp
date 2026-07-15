/* c634 handler: reset two sub-objects (obj->f4 and obj->f8): clear their +0x5c bit 1
 * and re-arm them (func_0203b9fc(sub, 0/2, 0, 1); func_0203c7ac(obj->f4, 0)); clear
 * obj->f28; then dispatch via func_0203c634. sub-objects re-read per use. */
extern void func_0203b9fc(int obj, int a, int b, int c);
extern void func_0203c7ac(int obj, int a);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov160_020ce31c(void);
void func_ov160_020ce220(int self) {
    int obj = *(int *)(self + 4);
    *(int *)(*(int *)(obj + 4) + 0x5c) &= ~2;
    func_0203b9fc(*(int *)(obj + 4), 0, 0, 1);
    func_0203b9fc(*(int *)(obj + 4), 2, 0, 1);
    func_0203c7ac(*(int *)(obj + 4), 0);
    *(int *)(obj + 0x28) = 0;
    *(int *)(*(int *)(obj + 8) + 0x5c) &= ~2;
    func_0203b9fc(*(int *)(obj + 8), 0, 0, 1);
    func_0203b9fc(*(int *)(obj + 8), 2, 0, 1);
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov160_020ce31c);
}
