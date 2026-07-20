/* Drives one step of the save-data check that runs behind the Load screen.
 *
 * Identified from its callee: func_ov000_02054e7c is Ov000_PollSaveLoad, which walks the eight
 * save slots, verifies each SHA-1 signature and restarts the card thread per block. This function
 * is the outer driver -- it dispatches on the request field, normalises the poll's result into a
 * small status set, and republishes it.
 *
 * Result codes, as this function treats them:
 *   0        finished and the data is good  -> raise bReady
 *   2, 3, 4  finished, not good             -> clear the request only
 *   1        still working                  -> falls to default, reported as -1 (busy)
 * Result 2 additionally runs func_ov000_02054c50, which memsets the save block and re-dispatches
 * roughly thirty default settings -- i.e. 2 is "no valid save, initialise a fresh one".
 *
 * bReady is cleared on entry and only ever raised on the success path, so a caller that samples it
 * mid-flight sees "not ready" rather than a stale success from the previous step.
 */

typedef unsigned char u8;

typedef struct {
    u8 pad_0000[0x6a44];
    int nRequest; /* +0x6a44 */
    u8 pad_6a48[0x0c];
    int bReady;   /* +0x6a54 */
} Ov000SceneContext;

extern Ov000SceneContext *volatile data_ov000_0205ac24;
extern int func_ov000_02054e7c(void);
extern void func_ov000_02054c50(int enabled);

int func_ov000_0204f6e0(void) {
    int result = 0;

    data_ov000_0205ac24->bReady = 0;
    {
        Ov000SceneContext *context = data_ov000_0205ac24;

        switch (context->nRequest) {
        case 1:
            result = func_ov000_02054e7c();
            break;
        case 2:
            break;
        default:
            context->nRequest = 0;
            result = 3;
            break;
        }
    }

    switch (result) {
    case 0:
        data_ov000_0205ac24->bReady = 1;
        data_ov000_0205ac24->nRequest = 0;
        break;
    case 2:
    case 3:
    case 4:
        data_ov000_0205ac24->nRequest = 0;
        break;
    default:
        result = -1;
        break;
    }

    if (result == 2) {
        func_ov000_02054c50(1);
    }
    return result;
}
