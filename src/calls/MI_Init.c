extern int MI_SetWramBank();
extern int MI_StopDma();

void MI_Init(void) {
    MI_SetWramBank(3);
    MI_StopDma(0);
}
