/* MobiClip: build a stream on top of an already-open file.
 *
 * Two objects are made in turn: a small reader bound to the file, and the
 * stream itself, which is handed the reader and the retry count. Either step
 * failing tears down whatever was built and reports nothing.
 *
 * This translation unit is C++, not C. The reader is released with a plain
 * `delete`, which is the only thing that produces the original's null check
 * followed by `mov r0,this; ldr r1,[r0]; ldr r1,[r1,#4]; blx r1` -- the
 * deleting destructor in vtable slot 1. No spelling of the same call in C99
 * emits that sequence: the C compiler always loads the vtable straight out of
 * the callee-saved register and moves the argument afterwards.
 *
 * The object is still built by hand rather than with `new`, because the
 * allocator is the module's own and the two vtables are existing data symbols.
 * The allocator and the deallocator carry misleading WM_ names from the symbol
 * table; the bytes are a plain operator new and delete pair.
 */
typedef unsigned int u32;

struct MobiClipReaderRaw {
    const void *pVtable;
    void *pOwner;
    int nFlags;
    int pad000c;
    int pad0010;
};

class MobiClipReader {
public:
    virtual ~MobiClipReader();
};

extern "C" {

extern int data_ov024_020939c4;
extern int data_ov024_020939e8;

extern void *WM_EndKeySharing_0x02085e3c(u32 nSize);
extern void *WM_EndKeySharing_0x020850f8(u32 nSize);
extern void *WM_EndKeySharing_0x02085104(void *pBlock);
extern int func_ov024_02085e54(void *pReader, void *pFile);
extern void *func_ov024_02085110(void *pBlock);
extern int func_ov024_02084e94(void *pStream, void *pReader, int nTries);
extern void func_ov024_02085140(void *pStream);

void *func_ov024_02084ec4(void *pFile, int nTries)
{
    MobiClipReaderRaw *pReader;
    void *pStream;

    pReader = (MobiClipReaderRaw *)WM_EndKeySharing_0x02085e3c(0x14);
    if (pReader != 0) {
        pReader->pVtable = &data_ov024_020939c4;
        pReader->pOwner = 0;
        pReader->nFlags = 0;
        pReader->pVtable = &data_ov024_020939e8;
    }
    if (pReader == 0) {
        return 0;
    }

    if (func_ov024_02085e54(pReader, pFile) == 0) {
        delete (MobiClipReader *)pReader;
        return 0;
    }

    pStream = WM_EndKeySharing_0x020850f8(0xd8);
    if (pStream != 0) {
        pStream = func_ov024_02085110(pStream);
    }
    if (func_ov024_02084e94(pStream, pReader, nTries) == 0) {
        if (pStream != 0) {
            func_ov024_02085140(pStream);
            WM_EndKeySharing_0x02085104(pStream);
        }
        return 0;
    }
    return pStream;
}

}
