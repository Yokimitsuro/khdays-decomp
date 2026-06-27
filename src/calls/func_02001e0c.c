extern void OS_InitContext(void *context, void *newpc, unsigned int newsp);
extern void OS_LoadContext(void *context);
extern void func_02001e68(int arg);

extern unsigned int data_0204430c[];

void func_02001e0c(unsigned int *thread, int arg)
{
    unsigned int sp = data_0204430c[7];

    if (sp != 0) {
        OS_InitContext(thread, func_02001e68, sp);
        thread[1] = arg;
        thread[0] |= 0x80;
        thread[0x19] = 1;
        OS_LoadContext(thread);
        return;
    }

    func_02001e68(arg);
}
