
#include "game/heap.h"
extern char *NNSi_FndGetCurrentRootHeap(void);
extern int Session_IsActive(void);
extern int Ov105_WM_SetPortCallback(unsigned short port, void (*callback)(void *), void *arg);
extern int data_0204c22c;
extern GameHeap *gMainHeap;

/* Closes the debug overlay if it is up: stops its task (only while the gate is open) and frees
 * the window. The "up" flag is cleared either way. */
void CloseDebugOverlay(void) {
    char *heap = NNSi_FndGetCurrentRootHeap();
    if (data_0204c22c != 0) {
        if (Session_IsActive() != 0) {
            Ov105_WM_SetPortCallback(0xc, 0, 0);
        }
        ExpHeap_Free(*(void **)(heap + 0x5c), gMainHeap);
    }
    data_0204c22c = 0;
}
