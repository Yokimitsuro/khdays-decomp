extern void SNDi_FreeVoiceChannel(int, int);

void func_0201cb64(int *param_1, int param_2) {
    if (*(volatile int *)param_1 == 0) {
        return;
    }
    SNDi_FreeVoiceChannel(*(volatile int *)param_1, param_2);
}
