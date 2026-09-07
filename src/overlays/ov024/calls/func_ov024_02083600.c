/* MobiClip: advance the stream window by one frame and refill when it runs out.
 *
 * One frame costs the fixed base step plus whatever the stream's own header
 * says this frame carries. If stepping again would run past the window limit
 * the position is put back and the reader is asked for more data first.
 */
typedef unsigned char u8;

typedef struct MobiClipStream {
    u8 _pad00[0x44];
    int nStepLimit;
    u8 _pad48[0x0c];
    int nBaseStep;
    u8 _pad58[0x04];
    int nWindowPosition;
} MobiClipStream;

extern u8 func_0202fae8(MobiClipStream *pStream);
extern void func_0202fb8c(MobiClipStream *pStream, int nStep);
extern void func_ov024_02083a9c(MobiClipStream *pStream);

int func_ov024_02083600(MobiClipStream *pStream) {
    int nPosition;
    int nStep;

    nStep = pStream->nBaseStep + func_0202fae8(pStream);
    nPosition = (pStream->nWindowPosition += nStep);
    if (nPosition + nStep - pStream->nBaseStep > pStream->nStepLimit) {
        pStream->nWindowPosition -= nStep;
        func_0202fb8c(pStream, nStep);
    }
    func_ov024_02083a9c(pStream);
    return 1;
}
