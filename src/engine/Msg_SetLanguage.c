/* Sets the game's language (OS_LANGUAGE_*, 1-5: English .. Spanish), which GetLanguage returns and
 * Msg_BuildLangPath uses to pick the two-letter code of localized files, allocating the 0x40-byte
 * path buffer out of the heap in data_0204c024 the first time. main hands it a second word, 0,
 * which it does not read. */

#include "nitro/types.h"

typedef struct LangPath {
    s16 lang;                           /* +0x00 */
    s16 pad02;
    char *buf;                          /* +0x04 */
} LangPath;

extern LangPath gLangPath;
extern void *data_0204c024;
extern void *AllocFromExpHeapWrapper(int size, void *heap);

void Msg_SetLanguage(int language, int unused) {
    if (gLangPath.buf == 0) {
        gLangPath.buf = (char *)AllocFromExpHeapWrapper(0x40, data_0204c024);
    }
    gLangPath.lang = (s16)language;
}
