extern char data_ov008_02090fb4[];
extern int OS_IsThreadTerminated(void *thread);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

int func_ov008_0208ba3c(void)
{
    int result = -1;

    if (*(void **)(data_ov008_02090fb4 + 8) != 0 && OS_IsThreadTerminated(*(void **)(data_ov008_02090fb4 + 8)) != 0) {
        result = *(int *)(*(char **)(data_ov008_02090fb4 + 8) + 0x2cc);
        NNSi_FndFreeFromDefaultHeap(*(void **)(data_ov008_02090fb4 + 8));
        *(int *)(data_ov008_02090fb4 + 8) = 0;
    }

    return result;
}
