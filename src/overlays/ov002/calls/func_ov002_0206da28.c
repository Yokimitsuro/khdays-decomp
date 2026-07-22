/* Pick the retry delay from the elapsed counter: still under 10000 ticks means
 * wait another 0x338, past it means stop waiting. Tail call. */
extern int func_02033500(int delay);

typedef struct {
    char pad0000[2];
    unsigned short wElapsed;    /* +2 */
} Ov002RetryState;

extern Ov002RetryState data_0204c240;

int func_ov002_0206da28(void) {
    return func_02033500(data_0204c240.wElapsed >= 10000 ? 0 : 0x338);
}
