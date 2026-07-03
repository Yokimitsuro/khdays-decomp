extern void func_0203c650(void *a, int b);
extern void func_ov107_020cb100(void *p);

void func_ov264_020cc64c(char *this) {
    if (*(int *)(this + 0x454) != 0) {
        func_0203c650(*(void **)(this + 0x3c), *(int *)(this + 0x454));
        *(int *)(this + 0x454) = 0;
    }
    if (*(int *)(this + 0x464) != 0) {
        func_0203c650(*(void **)(this + 0x3c), *(int *)(this + 0x464));
        *(int *)(this + 0x464) = 0;
    }
    {
        void *p = *(void **)(this + 0x43c);
        if (p != 0) {
            func_ov107_020cb100(p);
            *(int *)(this + 0x43c) = 0;
        }
    }
}
