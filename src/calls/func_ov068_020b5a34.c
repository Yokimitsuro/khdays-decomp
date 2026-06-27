extern char *NNSi_FndGetCurrentRootHeap(void);
extern unsigned char data_0204c240;
extern void *data_ov068_020b745c;
extern void func_ov068_020b5afc(void *);
extern void *func_0201ef9c(void *, int);
extern void func_0202a3cc(void *, int, void *, int);
extern void func_ov068_020b625c(void *);
extern void func_ov022_020a4798(void *, int, int);
extern void func_ov022_0209fb24(void);

void *func_ov068_020b5a34(void *a)
{
    char *r = NNSi_FndGetCurrentRootHeap();
    *(void **)(r + 0x2c50) = 0;
    func_ov068_020b5afc(a);
    if (!(data_0204c240 & 4)) {
        void *p = func_0201ef9c(&data_ov068_020b745c, *(int *)a + 7);
        *(void **)(r + 0x2c50) = p;
        func_0202a3cc(r + 0x2c2c, *(int *)(r + 0x20) + 4, *(void **)(r + 0x2c50), *(int *)a + 7);
    }
    func_ov068_020b625c(r);
    func_ov022_020a4798(r, 0x51, 0xd2);
    return (void *)func_ov022_0209fb24;
}
