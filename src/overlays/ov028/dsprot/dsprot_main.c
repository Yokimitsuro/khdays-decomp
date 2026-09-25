/* DS Protect 1.10, the six exported detectors (ov028 0x0208b040-0x0208b560). Each runs a
 * task list of checks through pointers stored with a +0x320 bias (so no call inside the encrypted
 * range needs a relocation), folds the results and calls the optional callback when its verdict
 * holds; the "Not" variants invert the verdict. KH Days calls them from ov000, ov001, ov004,
 * ov005 and ov023. Reconstruction after taxicat1/dsprot (branch 1.10). */
#include "dsprot_types.h"
#include "dsprot_ranges.h"

#define KEY_DSPROT_MAIN_1    0x6981
#define KEY_DSPROT_MAIN_2    0x61ae
#define KEY_DSPROT_MAIN_3    0x2578
#define KEY_DSPROT_MAIN_4    0x275e
#define KEY_DSPROT_MAIN_5    0x0351
#define KEY_DSPROT_MAIN_6    0x2e37

#define TASK_BIAS           0x320   /* added to every queued task address, removed before the call */
#define TASK_QUEUE_END      0

typedef u32 (*DSProtTask)(void);
typedef void (*DSProtCallback)(void);

/* DSProt_DetectFlashcart: run the ROM test; TRUE (and the callback) when a flashcart is detected. */
u32 func_ov028_0208b040(void *callback)
{
    u32 queue[32];
    BOOL taskResult;
    s32 resultSum;
    u32 i;
    BOOL result;

    result = FALSE;
    queue[0] = (u32)&func_ov028_0208af30 + TASK_BIAS;
    queue[1] = TASK_QUEUE_END;

    resultSum = 0;

    DSPROT_RANGE_BEGIN(KEY_DSPROT_MAIN_1)
    for (i = 0; queue[i] != TASK_QUEUE_END; i++) {
        queue[i] -= TASK_BIAS;
        taskResult = ((DSProtTask)queue[i])() != 0;
        resultSum += taskResult;
        resultSum <<= 1;
    }
    resultSum >>= 1;
    if (resultSum != 0) {
        result = TRUE;
    } else if (resultSum == 0) {
        result = FALSE;
    }
    if (callback != NULL && result) {
        ((DSProtCallback)callback)();
    }
    DSPROT_RANGE_END(KEY_DSPROT_MAIN_1)

    return (u32)result;
}

/* DSProt_DetectNotFlashcart: run the ROM test; TRUE (and the callback) when NO flashcart is detected. */
u32 func_ov028_0208b120(void *callback)
{
    u32 queue[32];
    BOOL taskResult;
    s32 resultSum;
    u32 i;
    BOOL result;

    result = FALSE;
    queue[0] = (u32)&func_ov028_0208af30 + TASK_BIAS;
    queue[1] = TASK_QUEUE_END;

    resultSum = 0;

    DSPROT_RANGE_BEGIN(KEY_DSPROT_MAIN_2)
    for (i = 0; queue[i] != TASK_QUEUE_END; i++) {
        queue[i] -= TASK_BIAS;
        taskResult = ((DSProtTask)queue[i])() != 0;
        resultSum += taskResult;
        resultSum <<= 1;
    }
    resultSum >>= 1;
    if (resultSum != 0) {
        result = FALSE;
    } else if (resultSum == 0) {
        result = TRUE;
    }
    if (callback != NULL && result) {
        ((DSProtCallback)callback)();
    }
    DSPROT_RANGE_END(KEY_DSPROT_MAIN_2)

    return (u32)result;
}

/* DSProt_DetectEmulator: run the MAC/owner check; TRUE (and the callback) when an emulator is detected. */
u32 func_ov028_0208b200(void *callback)
{
    u32 queue[32];
    BOOL taskResult;
    s32 resultSum;
    u32 i;
    BOOL result;

    result = FALSE;
    queue[0] = (u32)&func_ov028_0208abd0 + TASK_BIAS;
    queue[1] = TASK_QUEUE_END;

    resultSum = 0;

    DSPROT_RANGE_BEGIN(KEY_DSPROT_MAIN_3)
    for (i = 0; queue[i] != TASK_QUEUE_END; i++) {
        queue[i] -= TASK_BIAS;
        taskResult = ((DSProtTask)queue[i])() != 0;
        resultSum += taskResult;
        resultSum <<= 1;
    }
    resultSum >>= 1;
    if (resultSum != 0) {
        result = TRUE;
    } else if (resultSum == 0) {
        result = FALSE;
    }
    if (callback != NULL && result) {
        ((DSProtCallback)callback)();
    }
    DSPROT_RANGE_END(KEY_DSPROT_MAIN_3)

    return (u32)result;
}

/* DSProt_DetectNotEmulator: run the MAC/owner check; TRUE (and the callback) when NO emulator is detected. */
u32 func_ov028_0208b2e0(void *callback)
{
    u32 queue[32];
    BOOL taskResult;
    s32 resultSum;
    u32 i;
    BOOL result;

    result = FALSE;
    queue[0] = (u32)&func_ov028_0208abd0 + TASK_BIAS;
    queue[1] = TASK_QUEUE_END;

    resultSum = 0;

    DSPROT_RANGE_BEGIN(KEY_DSPROT_MAIN_4)
    for (i = 0; queue[i] != TASK_QUEUE_END; i++) {
        queue[i] -= TASK_BIAS;
        taskResult = ((DSProtTask)queue[i])() != 0;
        resultSum += taskResult;
        resultSum <<= 1;
    }
    resultSum >>= 1;
    if (resultSum != 0) {
        result = FALSE;
    } else if (resultSum == 0) {
        result = TRUE;
    }
    if (callback != NULL && result) {
        ((DSProtCallback)callback)();
    }
    DSPROT_RANGE_END(KEY_DSPROT_MAIN_4)

    return (u32)result;
}

/* DSProt_DetectDummy: an empty task list: always FALSE, the callback never runs (a decoy). */
u32 func_ov028_0208b3c0(void *callback)
{
    u32 queue[32];
    BOOL taskResult;
    s32 resultSum;
    u32 i;
    BOOL result;

    result = FALSE;
    /* kept despite the empty list: the range markers stop the compiler from folding it */
    queue[0] = TASK_QUEUE_END;

    resultSum = 0;

    DSPROT_RANGE_BEGIN(KEY_DSPROT_MAIN_5)
    for (i = 0; queue[i] != TASK_QUEUE_END; i++) {
        queue[i] -= TASK_BIAS;
        taskResult = ((DSProtTask)queue[i])() != 0;
        resultSum += taskResult;
        resultSum <<= 1;
    }
    resultSum >>= 1;
    if (resultSum != 0) {
        result = TRUE;
    } else if (resultSum == 0) {
        result = FALSE;
    }
    if (callback != NULL && result) {
        ((DSProtCallback)callback)();
    }
    DSPROT_RANGE_END(KEY_DSPROT_MAIN_5)

    return (u32)result;
}

/* DSProt_DetectNotDummy: an empty task list: always TRUE, the callback always runs (a decoy). */
u32 func_ov028_0208b490(void *callback)
{
    u32 queue[32];
    BOOL taskResult;
    s32 resultSum;
    u32 i;
    BOOL result;

    result = FALSE;
    /* kept despite the empty list: the range markers stop the compiler from folding it */
    queue[0] = TASK_QUEUE_END;

    resultSum = 0;

    DSPROT_RANGE_BEGIN(KEY_DSPROT_MAIN_6)
    for (i = 0; queue[i] != TASK_QUEUE_END; i++) {
        queue[i] -= TASK_BIAS;
        taskResult = ((DSProtTask)queue[i])() != 0;
        resultSum += taskResult;
        resultSum <<= 1;
    }
    resultSum >>= 1;
    if (resultSum != 0) {
        result = FALSE;
    } else if (resultSum == 0) {
        result = TRUE;
    }
    if (callback != NULL && result) {
        ((DSProtCallback)callback)();
    }
    DSPROT_RANGE_END(KEY_DSPROT_MAIN_6)

    return (u32)result;
}
