extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void MI_CpuFill8(void *dst, int value, int size);
extern void func_02001f10(void *queue);
extern void func_02001dec(void);
extern char data_02046f28;

typedef struct {
    int (*run)(void *);
    void (*done)(void *);
    int result;
    int rest[6];
} Ov_CardJob;

/* Worker loop: waits for a job to be posted, copies it out under interrupts-off, runs it, reports
 * the result, and goes back for the next one. Exits when the queue is shut down. */
void func_0200fad0(char *ctx) {
    Ov_CardJob job;
    void (*done)(void *);
    int enabled;
    for (;;) {
        MI_CpuFill8(&job, 0, 0x24);
        enabled = OS_DisableInterrupts();
        while (*(char *volatile *)(ctx + 0xc0) == 0) {
            func_02001f10(0);
        }
        job = *(Ov_CardJob *)*(char *volatile *)(ctx + 0xc0);
        OS_RestoreInterrupts(enabled);
        if (job.run != 0) {
            job.result = job.run(&job);
        }
        enabled = OS_DisableInterrupts();
        done = job.done;
        *((char *)&data_02046f28 + 0x26) = 0;
        if (done != 0) {
            done(&job);
        }
        if (*(int *)&data_02046f28 != 0) {
            *(char *volatile *)(ctx + 0xc0) = 0;
            OS_RestoreInterrupts(enabled);
        } else {
            func_02001dec();
            return;
        }
    }
}
