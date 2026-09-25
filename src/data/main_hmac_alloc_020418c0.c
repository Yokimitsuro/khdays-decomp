/* main .rodata 0x020418c0-0x02041924, one dsd symbol spanning two SDK objects:
 * - the three HMAC-SHA1 driver templates of NitroSDK math (MATHiHMACFuncs initialisers
 *   { MATH_SHA1_DIGEST_SIZE, 512 / 8 }); MATH_CalcHMACSHA1 (func_0200baec) copies the first one
 *   and fills in its context, buffer and SHA-1 callbacks;
 * - the NitroSystem FND allocator callback pairs of the expanded heap (allocate / free), which
 *   NNS_FndInitAllocatorFor*Heap install into an NNSFndAllocator. */

typedef unsigned long u32;

typedef struct MATHiHMACFuncs {
    u32 dlength;
    u32 blength;
    void *context;
    void *hash_buf;
    void (*HashReset)(void *context);
    void (*HashSetSource)(void *context, const void *input, u32 length);
    void (*HashGetDigest)(void *context, void *digest);
} MATHiHMACFuncs;

typedef void *(*NNSFndFuncAllocatorAlloc)(void *allocator, u32 size);
typedef void (*NNSFndFuncAllocatorFree)(void *allocator, void *memBlock);

typedef struct NNSFndAllocatorFunc {
    NNSFndFuncAllocatorAlloc pfAlloc;
    NNSFndFuncAllocatorFree pfFree;
} NNSFndAllocatorFunc;

#define MATH_SHA1_DIGEST_SIZE 20

extern void *func_02010d70(void *allocator, u32 size);
extern void AllocatorFreeForExpHeap_0x02010d90(void *allocator, void *memBlock);
extern void *AllocatorAllocForExpHeap_0x02010d58(void *allocator, u32 size);
extern void func_02010d6c(void *allocator, void *memBlock);

const struct {
    MATHiHMACFuncs hmacSha1[3];
    NNSFndAllocatorFunc allocator[2];
} data_020418c0 = {
    {
        { MATH_SHA1_DIGEST_SIZE, 512 / 8 },
        { MATH_SHA1_DIGEST_SIZE, 512 / 8 },
        { MATH_SHA1_DIGEST_SIZE, 512 / 8 },
    },
    {
        { func_02010d70, AllocatorFreeForExpHeap_0x02010d90 },
        { AllocatorAllocForExpHeap_0x02010d58, func_02010d6c },
    },
};
