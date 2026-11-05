/* Format the name of an event script into the caller's buffer: the given name ("%s") when there
 * is one, else the field's own event script, its number ("%d" of the field root's +0x8baa). */
extern int OS_SPrintf(char *dst, const char *fmt, ...);

typedef struct {
    char pad0000[2];
    short wScriptNumber;        /* +2: the field's event script */
} Ov002ResultContext;

typedef struct {
    char pad0000[0x8ba8];
    Ov002ResultContext result;  /* +0x8ba8 */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern const char gOv002StrFmt[];
extern const char gOv002IntFmt[];

void Ov002_FormatEventScriptName(int pszName, char *buffer) {
    Ov002ResultContext *pScript = &data_ov002_0207fa00->result;

    if (pszName != 0) {
        OS_SPrintf(buffer, gOv002StrFmt, pszName);
        return;
    }

    OS_SPrintf(buffer, gOv002IntFmt, pScript->wScriptNumber);
}
