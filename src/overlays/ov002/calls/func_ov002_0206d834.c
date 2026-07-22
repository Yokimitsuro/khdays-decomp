/* Format the result line into the caller's buffer: one wording when a reason
 * code is supplied, another carrying the signed score from +2 of the result
 * block when it is not. */
extern void OS_SPrintf(char *buffer, const char *format, ...);

typedef struct {
    char pad0000[2];
    short wScore;               /* +2 */
} Ov002ResultContext;

typedef struct {
    char pad0000[0x8ba8];
    Ov002ResultContext result;  /* +0x8ba8 */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern const char data_ov002_0207efe0[];
extern const char data_ov002_0207efe4[];

void func_ov002_0206d834(int reason, char *buffer) {
    Ov002ResultContext *result = &data_ov002_0207fa00->result;

    if (reason != 0) {
        OS_SPrintf(buffer, data_ov002_0207efe0, reason);
        return;
    }

    OS_SPrintf(buffer, data_ov002_0207efe4, result->wScore);
}
