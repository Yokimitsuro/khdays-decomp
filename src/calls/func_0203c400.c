extern void *func_0203d15c(int size);
extern void func_01fffc24(void *p);

void *func_0203c400(void) {
    int *p = (int *)func_0203d15c(0x30);
    p[10] = 0;
    func_01fffc24(p);
    return p;
}
