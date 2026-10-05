/* Formats the world's path string from its index. */

extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern char gOv002StrIntFmt[];
extern char gOv002PentName[];

void Ov002_FormatWorldPath(int arg0, int arg1) {
    OS_SPrintf((char *)arg1, gOv002StrIntFmt, gOv002PentName, *(signed char *)(arg0 + 1));
}
