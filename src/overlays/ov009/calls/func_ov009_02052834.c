extern void *NNSi_FndGetCurrentRootHeap(void);
extern void *data_ov009_020563f4;
extern void func_ov009_02052858(void);

void (*func_ov009_02052834(void))(void)
{
    data_ov009_020563f4 = NNSi_FndGetCurrentRootHeap();
    return func_ov009_02052858;
}
