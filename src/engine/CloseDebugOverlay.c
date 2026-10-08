extern char *NNSi_FndGetCurrentRootHeap(void);
extern int Session_IsActive(void);
extern int Ov105_WM_SetPortCallback(unsigned short port, void (*callback)(void *), void *arg);
extern void ExpHeap_Free(int a, int b);
extern int data_0204c22c;
extern int data_0204c024;

/* Closes the debug overlay if it is up: stops its task (only while the gate is open) and frees
 * the window. The "up" flag is cleared either way. */
void CloseDebugOverlay(void) {
    char *heap = NNSi_FndGetCurrentRootHeap();
    if (data_0204c22c != 0) {
        if (Session_IsActive() != 0) {
            Ov105_WM_SetPortCallback(0xc, 0, 0);
        }
        ExpHeap_Free(*(int *)(heap + 0x5c), data_0204c024);
    }
    data_0204c22c = 0;
}
