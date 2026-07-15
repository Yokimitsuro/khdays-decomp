#pragma thumb on
/* func_ov000_02054a50 -- Scene 1 (boot/logo) async save-op reaper, ov000. THUMB.
 * If a background save thread (data_ov000_0205ac2c[+8]) is running and has finished
 * (OS_IsThreadTerminated), harvest its result word (thread+0x2cc), free the thread
 * object, and clear the slot. Returns the harvested result, or -1 while still busy
 * (or if no thread is pending). Polled by func_ov000_02054e7c. */

extern char data_ov000_0205ac2c[];
extern int  OS_IsThreadTerminated(void *thread);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

#define g_saveThread (*(void **)(data_ov000_0205ac2c + 8))

int func_ov000_02054a50(void) {
    int result = -1;
    if (g_saveThread != 0 && OS_IsThreadTerminated(g_saveThread) != 0) {
        result = *(int *)((char *)g_saveThread + 0x2cc);
        NNSi_FndFreeFromDefaultHeap(g_saveThread);
        g_saveThread = 0;
    }
    return result;
}
