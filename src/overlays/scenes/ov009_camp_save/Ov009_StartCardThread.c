/* The 0x2d0 block is an OSThread + its 0x200 stack (top at +0x2c0), followed by
 * the three call parameters the thread reads back. */
typedef struct {
    unsigned char osThread[0x2c0];
    int paramA;   /* +0x2c0 */
    int paramC;   /* +0x2c4 */
    int paramB;   /* +0x2c8 */
    int pad2cc;
} CardThreadBlock;

typedef struct {
    unsigned char blockCounter;
    unsigned char slot;
    unsigned char pad02[2];
    int resultCode;
    CardThreadBlock *thread;   /* +8 */
} CardTransferCtx;

extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void OS_CreateThread(void *thread, void (*func)(void *), void *arg,
                            void *stack, unsigned stackSize, unsigned prio);
extern void OS_WakeupThreadDirect(void *thread);
extern void Ov009_Backup_ReadChunked(void *arg);

extern CardTransferCtx data_ov009_020563f8;

void Ov009_StartCardThread(int a, int b, int c) {
    data_ov009_020563f8.thread = NNSi_FndAllocFromDefaultExpHeap(0x2d0);
    data_ov009_020563f8.thread->paramA = a;
    data_ov009_020563f8.thread->paramC = c;
    data_ov009_020563f8.thread->paramB = b;
    OS_CreateThread(data_ov009_020563f8.thread, Ov009_Backup_ReadChunked,
                    data_ov009_020563f8.thread,
                    (char *)data_ov009_020563f8.thread + 0x2c0, 0x200, 0x11);
    OS_WakeupThreadDirect(data_ov009_020563f8.thread);
}
