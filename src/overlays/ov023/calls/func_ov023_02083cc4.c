/* func_ov023_02083cc4 -- Ov023_BuildEventTextPath: build the path of an event's text file.
 * The path starts as "ev/EV_" (data_ov023_0208a0a4) and gets, by the event code's third
 * character, "S" for 'S' (the shared file), "DP" for 'D', or otherwise the code's fifth and
 * sixth characters one at a time (STD_StrnCat 0201fa6c), then ".p2" (STD_StrCat 0201fa3c).
 * Returns the path, which lives in the caller's frame as a 0x40 stack buffer. */
typedef unsigned char  u8;
typedef unsigned int   u32;

extern char *func_0201fa3c(char *pszDst, const char *pszSrc);           /* STD_StrCat */
extern char *func_0201fa6c(char *pszDst, const char *pszSrc, int nMax); /* STD_StrnCat */
extern const u8 data_ov023_0208a0a4[];                              /* "ev/EV_" */
extern const char data_ov023_0208a0ac[];                            /* "S" */
extern const char data_ov023_0208a0b0[];                            /* "DP" */
extern const char data_ov023_0208a0b4[];                            /* ".p2" */

char *func_ov023_02083cc4(const char *pszCode)
{
    char szPath[0x40];

    {
        u32 nRemaining;
        const u8 *pSrc;
        u8 *pDst;

        pSrc = data_ov023_0208a0a4;
        pDst = (u8 *)szPath;
        nRemaining = 7;
        do {
            *pDst = *pSrc;
            pSrc++;
            pDst++;
            nRemaining--;
        } while (nRemaining != 0);
    }
    if (pszCode[2] == 'S') {
        func_0201fa3c(szPath, data_ov023_0208a0ac);
    } else if (pszCode[2] == 'D') {
        func_0201fa3c(szPath, data_ov023_0208a0b0);
    } else {
        func_0201fa6c(szPath, pszCode + 4, 1);
        func_0201fa6c(szPath, pszCode + 5, 1);
    }
    func_0201fa3c(szPath, data_ov023_0208a0b4);
    return szPath;
}
