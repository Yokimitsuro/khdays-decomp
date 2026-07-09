extern void *func_0201ef9c(void *source, int count);
extern void func_ov008_02054638(void *context, void *block, int arg2);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void func_ov008_02054678(void *context, void *source, int arg2)
{
    void *block = func_0201ef9c(source, 0xe);

    func_ov008_02054638(context, block, arg2);

    if (block != 0) {
        NNSi_FndFreeFromDefaultHeap(block);
    }
}
