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
extern void func_ov012_0205c048(MobiClipStream *pStream);

int func_ov012_0205bbac(MobiClipStream *pStream) {
    int nPosition;
    int nStep;

    nStep = pStream->nBaseStep + func_0202fae8(pStream);
    nPosition = (pStream->nWindowPosition += nStep);
    if (nPosition + nStep - pStream->nBaseStep > pStream->nStepLimit) {
        pStream->nWindowPosition -= nStep;
        func_0202fb8c(pStream, nStep);
    }
    func_ov012_0205c048(pStream);
    return 1;
}