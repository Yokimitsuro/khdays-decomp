/* ov001 heap bootstrap.
 *
 * Loads the protected overlay ov028, queries five predicates inside it to decide
 * how main RAM is carved up, builds up to two NNS expanded heaps out of the OS
 * arena, then unloads ov028 again.
 *
 * The overlay id arrives as the ADDRESS of a linker-absolute symbol -- this is
 * the stock NitroSDK FS_EXTERN_OVERLAY / FS_OVERLAY_ID idiom:
 *     #define FS_EXTERN_OVERLAY(name) extern u32 SDK_OVERLAY_ ## name ## _ID[1]
 *     #define FS_OVERLAY_ID(name)     ((u32) & (SDK_OVERLAY_ ## name ## _ID))
 * dsd emits that symbol into arm9.lcf as `OVERLAY_28_ID = 28;`. It is why the
 * original loads 0x1c from the literal pool instead of using an ARM immediate,
 * and it must stay spelled inline at both call sites: mwcc then CSEs the pool
 * load into r4, which is what the ROM does. Binding it to a local first shuffles
 * r4/r5/r6 and the match is lost.
 */

typedef unsigned int u32;
typedef unsigned short u16;
typedef int BOOL;

typedef u32 FSOverlayID;
typedef void *NNSFndHeapHandle;

typedef enum { MI_PROCESSOR_ARM9 = 0, MI_PROCESSOR_ARM7 = 1 } MIProcessor;
typedef enum { OS_ARENA_MAIN = 0 } OSArenaId;

/* FS_EXTERN_OVERLAY(ov028) -- dsd names the absolute symbol OVERLAY_28_ID. */
extern u32 OVERLAY_28_ID[1];
#define FS_OVERLAY_ID_ov028 ((FSOverlayID)(u32) & (OVERLAY_28_ID))

extern BOOL FS_LoadOverlay(MIProcessor target, FSOverlayID id);
extern BOOL FS_UnloadOverlay(MIProcessor target, FSOverlayID id);
extern void *OS_AllocFromArenaLo(OSArenaId id, u32 size, u32 align);
extern void *OS_GetArenaLo(OSArenaId id);
extern void *OS_GetArenaHi(OSArenaId id);
extern NNSFndHeapHandle NNS_FndCreateExpHeapEx(void *startAddress, u32 size, u16 optFlag);

/* Self-decrypting anti-tamper predicates living in ov028's encrypted .rodata
   block. Their bodies are ciphertext in the static ROM and only become ARM
   instructions at run time; we only ever need their addresses. See
   docs/ov028_encrypted_code.md. */
extern BOOL func_ov028_0208b040(int);
extern BOOL func_ov028_0208b120(int);
extern BOOL func_ov028_0208b200(int);
extern BOOL func_ov028_0208b2e0(int);
extern BOOL func_ov028_0208b490(int);

#define MAIN_HEAP_SIZE 0xc8000 /* 800 KiB */
#define HEAP_ALIGN 0x10

void func_ov001_0204ce40(NNSFndHeapHandle *outMainHeap, NNSFndHeapHandle *outSubHeap)
{
    NNSFndHeapHandle mainHeap = 0;
    NNSFndHeapHandle subHeap = 0;
    u32 arenaLo, arenaHi;

    FS_LoadOverlay(MI_PROCESSOR_ARM9, FS_OVERLAY_ID_ov028);

    if (func_ov028_0208b490(0)) {
        mainHeap = NNS_FndCreateExpHeapEx(
            OS_AllocFromArenaLo(OS_ARENA_MAIN, MAIN_HEAP_SIZE, HEAP_ALIGN),
            MAIN_HEAP_SIZE, 0);
    }

    arenaLo = ((u32)OS_GetArenaLo(OS_ARENA_MAIN) + 0xf) & ~0xf;
    arenaHi = (u32)OS_GetArenaHi(OS_ARENA_MAIN) & ~0xf;

    if (func_ov028_0208b200(0) || func_ov028_0208b040(0)) {
        /* share the remaining arena: sub heap gets half */
        u32 size = (arenaHi - arenaLo) >> 1;
        subHeap = NNS_FndCreateExpHeapEx(
            OS_AllocFromArenaLo(OS_ARENA_MAIN, size, HEAP_ALIGN), size, 0);
    } else if (func_ov028_0208b120(0) && func_ov028_0208b2e0(0)) {
        /* sub heap takes all of the remaining arena */
        u32 size = arenaHi - arenaLo;
        subHeap = NNS_FndCreateExpHeapEx(
            OS_AllocFromArenaLo(OS_ARENA_MAIN, size, HEAP_ALIGN), size, 0);
    }

    FS_UnloadOverlay(MI_PROCESSOR_ARM9, FS_OVERLAY_ID_ov028);

    *outMainHeap = mainHeap;
    *outSubHeap = subHeap;
}
