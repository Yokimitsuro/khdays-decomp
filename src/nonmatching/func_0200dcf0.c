/* NONMATCHING — 1-register coloring tie (byte-structurally identical otherwise).
 *
 * Spin-wait: reads the volatile int at data_02046444 until it is no longer 1,
 * then returns the value that broke the loop. The original returns that value
 * (r0 holds the last read at loop exit), which is what the `return x` form below
 * reproduces — with it, the VALUE register matches r0 exactly.
 *
 * The single remaining divergence is the register chosen for the hoisted,
 * loop-invariant ADDRESS of the global: the original colors it ip (r12), mwcc
 * colors it r1. Every other byte (both ldr shapes, cmp #1, the beq self-loop,
 * bx lr, and the literal-pool word) is identical. Tried: plain void spin, the
 * return-value form, do/while, for(;;)+if-return, and an explicit
 * `volatile int *p` local. All keep the value in r0 but color the held pointer
 * r1, never ip. Same unsteerable coloring class as func_0201a284. The asm_stub
 * keeps the build byte-exact.
 */
extern volatile int data_02046444;

int func_0200dcf0(void) {
    int x;
    while ((x = data_02046444) == 1) {
    }
    return x;
}
