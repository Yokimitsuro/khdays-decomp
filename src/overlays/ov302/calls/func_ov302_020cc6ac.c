extern void func_ov002_02052834();
extern void func_ov302_020cc538();
extern void NNSi_FndFreeFromDefaultHeap();

struct S {
    char pad[0x14];
    void *f14;
};

void func_ov302_020cc6ac(struct S *p)
{
    func_ov002_02052834(p);
    func_ov302_020cc538(p);
    if (p->f14) {
        NNSi_FndFreeFromDefaultHeap(p->f14);
        p->f14 = 0;
    }
}
