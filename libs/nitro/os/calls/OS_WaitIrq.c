typedef int BOOL;
typedef int OSIntrMode;
typedef unsigned int u32;

extern OSIntrMode OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(OSIntrMode state);
extern void func_02001f10(void *queue);

/* The IRQ check flags and the wait queue both sit near the top of DTCM. The pool
   carries the base and the compiler splits the 0x3ff8 offset itself. */
extern u32 data_027e0000;
extern u32 data_027e006c;

#define DTCM ((char *)&data_027e0000)
#define OSi_IrqCheckFlags (*(volatile u32 *)(DTCM + 0x3ff8))

void OS_WaitIrq(BOOL clear, u32 irqFlags)
{
    OSIntrMode last = OS_DisableInterrupts();

    if (clear) {
        OSi_IrqCheckFlags &= ~irqFlags;
    }
    OS_RestoreInterrupts(last);

    /* The base belongs to the block holding BOTH the early exit and the wait, and the
       wait's own pointer to a block inside that one. Hoist either to function scope and
       the scheduler builds the loop's address in the load-use shadow of the first read,
       which is the whole difference against the original. */
    {
        char *const dtcm = DTCM;

        if (irqFlags & *(volatile u32 *)(dtcm + 0x3ff8)) {
            return;
        }
        {
            volatile u32 *flags = (volatile u32 *)(dtcm + 0x3ff8);

            do {
                func_02001f10(&data_027e006c);
            } while ((irqFlags & *flags) == 0);
        }
    }
}
