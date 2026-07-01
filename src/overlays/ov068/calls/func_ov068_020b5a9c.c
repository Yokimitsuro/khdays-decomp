extern char *NNSi_FndGetCurrentRootHeap(void);
extern unsigned char data_0204c240;
extern void func_0202a440(void *);
extern void NNSi_FndFreeFromDefaultHeap(void *);
extern void func_ov002_02051fc8(void *, void *);
extern void func_ov068_020b62ec(void *);
extern void func_ov022_0209fab4(void *);

void func_ov068_020b5a9c(void)
{
    char *r4 = NNSi_FndGetCurrentRootHeap();
    if (!(data_0204c240 & 4)) {
        func_0202a440(r4 + 0x2c2c);
        NNSi_FndFreeFromDefaultHeap(*(void **)(r4 + 0x2c50));
    }
    func_ov002_02051fc8(r4 + 0x2c54, r4 + 0x910);
    func_ov002_02051fc8(r4 + 0x2ca8, r4 + 0x910);
    func_ov068_020b62ec(r4);
    func_ov022_0209fab4(r4);
}
