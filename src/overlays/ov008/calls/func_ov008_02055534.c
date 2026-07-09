extern char *func_0201ef9c(void *source, int count);
extern void func_ov008_02054e94(void *context, void *data);
extern void func_ov008_02054ed4(void *context, void *data);
extern void func_ov008_02054f3c(void *context, void *data);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void func_ov008_02055534(void *context, void *source)
{
    char *block = func_0201ef9c(source, 0xe);
    int offset0 = *(int *)block;
    int offset2 = *(int *)(block + 8);
    int offset1 = *(int *)(block + 4);

    func_ov008_02054e94(context, block + offset0);
    func_ov008_02054ed4(context, block + offset1);
    func_ov008_02054f3c(context, block + offset2);

    if (block != 0) {
        NNSi_FndFreeFromDefaultHeap(block);
    }
}
