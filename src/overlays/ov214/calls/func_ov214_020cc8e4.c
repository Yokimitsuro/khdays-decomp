extern void func_ov214_020cc64c(void *this);
extern void func_ov107_020c7ca4(void *this);

void func_ov214_020cc8e4(char *this) {
    if (*(signed char *)(this + 0x1c6) != 5) {
        func_ov214_020cc64c(this);
    } else {
        if (*(int *)(this + 0x454) != 0) {
            int *p = *(int **)(this + 0x450);
            *(int *)((char *)p + 0x5c) = (*(int *)((char *)p + 0x5c) & ~2) |
                (((unsigned)(*(unsigned char *)(this + 0x1c4) & 2) << 0x1f) >> 0x1e);
        }
        if (*(int *)(this + 0x464) != 0) {
            int *p = *(int **)(this + 0x460);
            *(int *)((char *)p + 0x5c) = (*(int *)((char *)p + 0x5c) & ~2) |
                (((unsigned)(*(unsigned char *)(this + 0x1c4) & 2) << 0x1f) >> 0x1e);
        }
    }
    func_ov107_020c7ca4(this);
}
