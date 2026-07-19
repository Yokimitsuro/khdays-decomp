extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern void func_02001f10(void *queue);
extern char data_020464e0;

/* Blocks until the card's pending transfer finishes; true if it succeeded. */
int CARDi_WaitAsync(void) {
    char *card = (char *)&data_020464e0;
    int enabled = OS_DisableInterrupts();
    goto test;
loop:
    func_02001f10(card + 0x10c);
test:
    if ((*(volatile int *)(card + 0x114) & 4) != 0) {
        goto loop;
    }
    OS_RestoreInterrupts(enabled);
    return **(int **)card == 0;
}
