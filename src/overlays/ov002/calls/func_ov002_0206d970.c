/* Post the result report: message 0x1b when there is nothing to report, or the
 * payload parked at +0x10 of the result block followed by message 0x1e. */
extern void func_020235e8(int channel, int priority, int message);

typedef struct {
    char pad0000[0x10];
    int nPayload;               /* +0x10 */
} Ov002ResultContext;

typedef struct {
    char pad0000[0x8ba8];
    Ov002ResultContext result;  /* +0x8ba8 */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

void func_ov002_0206d970(int payload) {
    Ov002ResultContext *result = &data_ov002_0207fa00->result;

    if (payload == 0) {
        func_020235e8(0x2080, 5, 0x1b);
        return;
    }

    result->nPayload = payload;
    func_020235e8(0x2080, 5, 0x1e);
}
