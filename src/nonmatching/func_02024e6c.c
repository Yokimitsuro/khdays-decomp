/* NONMATCHING: semantics correct, loop char-read optimization tie (116B vs 124B).
 * The ROM re-reads *param_1 with a fresh ldrsb at the loop top AND bottom (and once
 * before the loop); mwcc 3.0/139 keeps it in a register / uses post-increment loads,
 * shaving the redundant reads. No C form (cached char, per-branch increment, explicit
 * *param_1 reads) reproduces the ROM's un-CSE'd triple read.
 */
/* Expand a filename template into the shared scratch buffer: copy each char, but
 * replace '&' with the current language's 2-char code (langTable[curLang]). Returns
 * the scratch buffer (langState+4). langState = data_0204c1ec {s16 curLang; char*
 * out}; langTable = data_020427d4 (char* per language). */
extern short data_0204c1ec;
extern int data_020427d4;
char *func_02024e6c(char *param_1) {
    char *out = *(char **)((char *)&data_0204c1ec + 4);
    char *lang = *(char **)((char *)&data_020427d4 + *(short *)&data_0204c1ec * 4);
    while (*param_1 != 0) {
        if (*param_1 == '&') {
            *out = *lang;
            out[1] = *++lang;
            out += 2;
            param_1++;
        } else {
            *out = *param_1;
            out++;
            param_1++;
        }
    }
    *out = 0;
    return *(char **)((char *)&data_0204c1ec + 4);
}
