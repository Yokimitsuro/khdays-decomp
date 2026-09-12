extern void *func_01fffd70(void *list);
extern void func_ov107_020c3368(int v);
extern void *func_01fffd8c(void *list);

typedef struct { int w0, w1, w2; } Word3;
extern Word3 data_02041dc8;

typedef struct {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char rest : 5;
} Flags17a;

void func_ov107_020c4d9c(char *self) {
    if (*(int *)(self + 0x50) == 1) {
        Flags17a *f = (Flags17a *)(self + 0x17a);
        f->bit1 = f->bit2;
    }

    unsigned int flags = (unsigned)(*(unsigned short *)(self + 0x60) << 24) >> 24;
    if ((flags & 1) != 0 && (flags & 2) == 0) {
        void *node = func_01fffd70(self + 0x144);
        while (node != 0) {
            if (*(int *)node != 0) {
                func_ov107_020c3368(*(int *)node);
            }
            node = func_01fffd8c(self + 0x144);
        }
    }

    *(Word3 *)(self + 0xd8) = data_02041dc8;
}
