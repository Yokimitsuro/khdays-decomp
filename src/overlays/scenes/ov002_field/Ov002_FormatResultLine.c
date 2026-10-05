/* Format the result line into the caller's buffer: one wording when a reason
 * code is supplied, another carrying the signed score from +2 of the result
 * block when it is not. */
extern int OS_SPrintf(char *dst, const char *fmt, ...);

typedef struct {
    char pad0000[2];
    short wScore;               /* +2 */
} Ov002ResultContext;

typedef struct {
    char pad0000[0x8ba8];
    Ov002ResultContext result;  /* +0x8ba8 */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern const char gOv002StrFmt[];
extern const char gOv002IntFmt[];

void Ov002_FormatResultLine(int reason, char *buffer) {
    Ov002ResultContext *result = &data_ov002_0207fa00->result;

    if (reason != 0) {
        OS_SPrintf(buffer, gOv002StrFmt, reason);
        return;
    }

    OS_SPrintf(buffer, gOv002IntFmt, result->wScore);
}
