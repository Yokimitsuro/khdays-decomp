/* Begin the timed phase: mark it running and start the timer. A solo machine has
 * no phase to time, so it reports done straight away. */
extern int func_02030694(void);
extern int func_ov002_0206f318(void);

typedef struct {
    unsigned int dwFlags;       /* +0 */
} Ov002TimingConfig;

extern Ov002TimingConfig *data_ov002_0207fa08;

int func_ov002_0206f4e0(void) {
    Ov002TimingConfig *ctx = data_ov002_0207fa08;

    if (func_02030694() == 0) {
        return 1;
    }

    ctx->dwFlags |= 4;
    return func_ov002_0206f318();
}
