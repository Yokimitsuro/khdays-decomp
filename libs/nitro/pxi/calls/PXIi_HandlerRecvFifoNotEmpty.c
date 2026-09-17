typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000



typedef int PXIFifoTag;
typedef enum {
    PXI_FIFO_SUCCESS = 0,
    PXI_FIFO_FAIL_SEND_ERR = -1,
    PXI_FIFO_FAIL_SEND_FULL = -2,
    PXI_FIFO_FAIL_RECV_ERR = -3,
    PXI_FIFO_FAIL_RECV_EMPTY = -4,
    PXI_FIFO_NO_CALLBACK_ENTRY = -5
} PXIFifoStatus;
#define PXI_FIFOMESSAGE_BITSZ_TAG   5
#define PXI_FIFOMESSAGE_BITSZ_ERR   1
#define PXI_FIFOMESSAGE_BITSZ_DATA  26
typedef union {
    struct {
        u32 tag : PXI_FIFOMESSAGE_BITSZ_TAG;
        u32 err : PXI_FIFOMESSAGE_BITSZ_ERR;
        u32 data : PXI_FIFOMESSAGE_BITSZ_DATA;
    } e;
    u32 raw;
} PXIFifoMessage;
typedef void (*PXIFifoCallback)(PXIFifoTag tag, u32 data, BOOL err);

#define reg_PXI_FIFO_CNT   (*(vu16 *)0x04000184)
#define reg_PXI_SEND_FIFO  (*(vu32 *)0x04000188)
#define reg_PXI_RECV_FIFO  (*(vu32 *)0x04100000)
#define REG_PXI_FIFO_CNT_E_MASK         0x8000
#define REG_PXI_FIFO_CNT_ERR_MASK       0x4000
#define REG_PXI_FIFO_CNT_RECV_EMP_MASK  0x0100
#define REG_PXI_FIFO_CNT_SEND_FULL_MASK 0x0002

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern PXIFifoCallback data_02046288[32];   /* FifoRecvCallbackTable */
#define FifoRecvCallbackTable data_02046288

static inline PXIFifoStatus PXIi_SetToFifo(u32 data)
{
    OSIntrMode enabled;

    if (reg_PXI_FIFO_CNT & REG_PXI_FIFO_CNT_ERR_MASK) {
        reg_PXI_FIFO_CNT |= (REG_PXI_FIFO_CNT_E_MASK | REG_PXI_FIFO_CNT_ERR_MASK);
        return PXI_FIFO_FAIL_SEND_ERR;
    }

    enabled = OS_DisableInterrupts();
    if (reg_PXI_FIFO_CNT & REG_PXI_FIFO_CNT_SEND_FULL_MASK) {
        (void)OS_RestoreInterrupts(enabled);
        return PXI_FIFO_FAIL_SEND_FULL;
    }

    reg_PXI_SEND_FIFO = data;
    (void)OS_RestoreInterrupts(enabled);
    return PXI_FIFO_SUCCESS;
}

static inline PXIFifoStatus PXIi_GetFromFifo(u32 *data_buf)
{
    OSIntrMode enabled;

    if (reg_PXI_FIFO_CNT & REG_PXI_FIFO_CNT_ERR_MASK) {
        reg_PXI_FIFO_CNT |= (REG_PXI_FIFO_CNT_E_MASK | REG_PXI_FIFO_CNT_ERR_MASK);
        return PXI_FIFO_FAIL_RECV_ERR;
    }

    enabled = OS_DisableInterrupts();
    if (reg_PXI_FIFO_CNT & REG_PXI_FIFO_CNT_RECV_EMP_MASK) {
        (void)OS_RestoreInterrupts(enabled);
        return PXI_FIFO_FAIL_RECV_EMPTY;
    }

    *data_buf = reg_PXI_RECV_FIFO;
    (void)OS_RestoreInterrupts(enabled);

    return PXI_FIFO_SUCCESS;
}

/* PXIi_HandlerRecvFifoNotEmpty -- NitroSDK pxi_fifo.c: the fifo receive interrupt: drain
 * every message, dispatch it to the tag's callback, and bounce a message nobody listens
 * for back to the sender with the error bit set. */
void PXIi_HandlerRecvFifoNotEmpty(void)
{
    PXIFifoMessage fifomsg;
    PXIFifoStatus ret_code;
    PXIFifoTag tag;

    while (1) {
        ret_code = PXIi_GetFromFifo(&fifomsg.raw);

        if (ret_code == PXI_FIFO_FAIL_RECV_EMPTY)
            break;

        if (ret_code == PXI_FIFO_FAIL_RECV_ERR)
            continue;

        tag = (PXIFifoTag)fifomsg.e.tag;

        if (tag) {
            if (FifoRecvCallbackTable[tag]) {
                (FifoRecvCallbackTable[tag])(tag, fifomsg.e.data, (BOOL)fifomsg.e.err);
            } else {
                if (fifomsg.e.err) {
                } else {
                    fifomsg.e.err = TRUE;
                    (void)PXIi_SetToFifo(fifomsg.raw);
                }
            }
        } else {

        }
    }
}
