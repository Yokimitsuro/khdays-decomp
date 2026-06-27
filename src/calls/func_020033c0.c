extern unsigned int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(unsigned int);
extern void func_020030c4(int);

typedef struct {
    unsigned short active;
} Data_02044674;

extern Data_02044674 data_02044674;

void func_020033c0(void)
{
    unsigned int irq = OS_DisableInterrupts();

    if (data_02044674.active != 0) {
        func_020030c4(1);
        data_02044674.active = 0;
    }

    OS_RestoreInterrupts(irq);
}
