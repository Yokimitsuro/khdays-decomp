/*
 * Ov002_EmitMessageLine - expand a message and hand it to the caption emitter,
 * optionally after a fixed opening line.
 *
 * The opening line comes from a constant string; the message itself is expanded
 * into a 128-byte buffer through the scene's message context, with a 0x40 cap
 * and the caller's trailing arguments.
 *
 * Variadic: mwcc has no stdarg.h on this include path, so the APCS va macros
 * are inlined. va_start aligns &last down to 4 then adds 4.
 *
 * ARM.
 */

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

typedef struct {
    char pad000[0x1b4];
    char msgCtx[0x40];
} Ov002TextScene;

extern int data_ov002_0207f62c;
extern const char data_ov002_0207ed1c[];

extern void func_ov002_02062608(void *pSink, const char *pText, int nArg);
extern int func_ov002_020528b8(void *pMsg, unsigned int nId, char *pOut,
                               unsigned int nSize, void *pVa);

void func_ov002_020626cc(void *pSink, unsigned int nId, int bOpen, int nArg,
                         ...)
{
    va_list ap;
    char aText[0x80];
    Ov002TextScene *s;

    s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);
    if (bOpen != 0) {
        func_ov002_02062608(pSink, data_ov002_0207ed1c, nArg);
    }

    va_start(ap, nArg);
    func_ov002_020528b8(s->msgCtx, nId, aText, 0x40, ap);
    func_ov002_02062608(pSink, aText, nArg);
}
