typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef void (*WMCallbackFunc)(void *arg);

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0

/* NitroSDK WM (wireless manager) library, ARM9 side, as linked into ov105. */
#define WM_FIFO_BUF_SIZE        256
#define WM_ARM9WM_BUF_SIZE      512
#define WM_ARM7WM_BUF_SIZE      (256 + 512)
#define WM_STATUS_BUF_SIZE      2048
#define WM_API_REQUEST_ACCEPTED 0x8000
#define WM_NUM_OF_PORT          16
#define WM_NUM_OF_CALLBACK      44
#define WM_BUF_MSG_NUM          10
#define PXI_FIFO_TAG_WM         10
#define PXI_PROC_ARM7           1
#define OS_MESSAGE_NOBLOCK      0
#define OS_MESSAGE_BLOCK        1
#define MI_DMA_MAX_NUM          3

enum {
    WM_ERRCODE_SUCCESS = 0,
    WM_ERRCODE_FAILED = 1,
    WM_ERRCODE_OPERATING = 2,
    WM_ERRCODE_ILLEGAL_STATE = 3,
    WM_ERRCODE_WM_DISABLE = 4,
    WM_ERRCODE_NO_KEYSET = 5,
    WM_ERRCODE_INVALID_PARAM = 6,
    WM_ERRCODE_NO_CHILD = 7,
    WM_ERRCODE_FIFO_ERROR = 8,
    WM_ERRCODE_TIMEOUT = 9,
    WM_ERRCODE_SEND_QUEUE_FULL = 10,
    WM_ERRCODE_NO_ENTRY = 11,
    WM_ERRCODE_OVER_MAX_ENTRY = 12,
    WM_ERRCODE_INVALID_POLLBITMAP = 13,
    WM_ERRCODE_NO_DATA = 14,
    WM_ERRCODE_SEND_FAILED = 15
};
typedef int WMErrCode;

enum {
    WM_STATE_READY = 0, WM_STATE_STOP, WM_STATE_IDLE, WM_STATE_CLASS1, WM_STATE_TESTMODE,
    WM_STATE_SCAN, WM_STATE_CONNECT, WM_STATE_PARENT, WM_STATE_CHILD, WM_STATE_MP_PARENT,
    WM_STATE_MP_CHILD, WM_STATE_DCF_CHILD, WM_STATE_TESTMODE_RX
};

enum {
    WM_APIID_INITIALIZE = 0, WM_APIID_RESET, WM_APIID_END, WM_APIID_ENABLE, WM_APIID_DISABLE,
    WM_APIID_POWER_ON, WM_APIID_POWER_OFF, WM_APIID_SET_P_PARAM, WM_APIID_START_PARENT,
    WM_APIID_END_PARENT, WM_APIID_START_SCAN, WM_APIID_END_SCAN, WM_APIID_START_CONNECT,
    WM_APIID_DISCONNECT, WM_APIID_START_MP, WM_APIID_SET_MP_DATA, WM_APIID_END_MP,
    WM_APIID_START_DCF, WM_APIID_SET_DCF_DATA, WM_APIID_END_DCF, WM_APIID_SET_WEPKEY,
    WM_APIID_START_KS, WM_APIID_END_KS, WM_APIID_GET_KEYSET, WM_APIID_SET_GAMEINFO,
    WM_APIID_SET_BEACON_IND, WM_APIID_START_TESTMODE, WM_APIID_STOP_TESTMODE,
    WM_APIID_VALARM_MP, WM_APIID_SET_LIFETIME, WM_APIID_MEASURE_CHANNEL,
    WM_APIID_INIT_W_COUNTER, WM_APIID_GET_W_COUNTER, WM_APIID_SET_ENTRY, WM_APIID_AUTO_DEAUTH,
    WM_APIID_SET_MP_PARAMETER, WM_APIID_SET_BEACON_PERIOD, WM_APIID_AUTO_DISCONNECT,
    WM_APIID_START_SCAN_EX, WM_APIID_SET_WEPKEY_EX, WM_APIID_SET_PS_MODE,
    WM_APIID_START_TESTRXMODE, WM_APIID_STOP_TESTRXMODE, WM_APIID_KICK_MP_PARENT,
    WM_APIID_KICK_MP_CHILD, WM_APIID_ASYNC_KIND_MAX,
    WM_APIID_INDICATION = 128, WM_APIID_PORT_SEND, WM_APIID_PORT_RECV, WM_APIID_READ_STATUS
};
typedef int WMApiid;

typedef struct WMStatus {
    u16 state;                    /* 0x000 */
    u16 BusyApiid;                /* 0x002 */
    BOOL apiBusy;                 /* 0x004 */
    u8 reserved0[0x7f8];
} WMStatus;

typedef struct WMArm7Buf {
    WMStatus *status;             /* 0x00 */
    u8 reserved_a[4];
    u32 *fifo7to9;                /* 0x08 */
    u8 reserved_b[0x2f4];
} WMArm7Buf;

typedef struct WMArm9Buf {
    WMArm7Buf *WM7;               /* 0x000 */
    WMStatus *status;             /* 0x004 */
    u32 *indbuf;                  /* 0x008 */
    u32 *fifo9to7;                /* 0x00c */
    u32 *fifo7to9;                /* 0x010 */
    u16 dmaNo;                    /* 0x014 */
    u16 scanOnlyFlag;             /* 0x016 */
    WMCallbackFunc CallbackTable[WM_NUM_OF_CALLBACK];   /* 0x018 */
    WMCallbackFunc indCallback;                         /* 0x0c8 */
    WMCallbackFunc portCallbackTable[WM_NUM_OF_PORT];   /* 0x0cc */
    void *portCallbackArgument[WM_NUM_OF_PORT];         /* 0x10c */
    u32 connectedAidBitmap;                             /* 0x14c */
    u16 myAid;                                          /* 0x150 */
} WMArm9Buf;

/* wm_system.c file statics, one .bss block: wmInitialized (u16) then wm9buf. */
extern u16 data_ov105_020bfa20;
#define wmInitialized data_ov105_020bfa20
#define wm9buf (*(WMArm9Buf **)((u8 *)&data_ov105_020bfa20 + 4))

typedef struct OSMessageQueue OSMessageQueue;

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void WM_EndKeySharing_0x0200926c(void);   /* the PXI_Init veneer of main */
extern BOOL PXI_IsCallbackReady(int tag, int proc);
extern void DC_InvalidateRange(void *addr, u32 size);
extern void DC_StoreRange(void *addr, u32 size);
extern void MI_DmaFill32(u32 dmaNo, void *dst, u32 value, u32 size);
extern void OS_InitMessageQueue(OSMessageQueue *queue, OSMessage *msgArray, s32 msgCount);
extern BOOL OS_SendMessage(OSMessageQueue *queue, OSMessage msg, s32 flags);
extern void PXI_SetFifoRecvCallback(int tag, void (*callback)(int, u32, BOOL));
extern void func_ov105_020bd4dc(void);                       /* WmClearFifoRecvFlag */
extern void func_ov105_020bd134(int tag, u32 fifo_buf_adr, BOOL err);   /* WmReceiveFifo */

extern OSMessageQueue data_ov105_020bfa28;   /* bufMsgQ */
extern OSMessage data_ov105_020bfa48[WM_BUF_MSG_NUM];   /* bufMsg */
extern u32 data_ov105_020bfac0[WM_BUF_MSG_NUM][WM_FIFO_BUF_SIZE / sizeof(u32)];   /* fifoBuf */
#define bufMsgQ data_ov105_020bfa28
#define bufMsg data_ov105_020bfa48
#define fifoBuf data_ov105_020bfac0

/* func_ov105_020bcc4c -- WmInitCore: the WM library init shared by WM_Init and
 * WMi_InitForScan. Carves the system buffer into the ARM7 block, the status block and
 * the two FIFO buffers, clears the port callbacks, primes the ten command buffers in
 * the message queue and installs the FIFO receive callback.
 * Codegen: this object was built at optimization_level 2 with opt_common_subs off (push/pop scoped):
 * at -O4 both constant-trip loops rotate and strength-reduce.
 */
#pragma push
#pragma optimization_level 2
#pragma opt_common_subs off
WMErrCode func_ov105_020bcc4c(void *wmSysBuf, u16 dmaNo, u32 bufSize)
{
    OSIntrMode e;

    e = OS_DisableInterrupts();

    if (wmInitialized) {
        (void)OS_RestoreInterrupts(e);
        return WM_ERRCODE_ILLEGAL_STATE;
    }
    if (wmSysBuf == NULL) {
        (void)OS_RestoreInterrupts(e);
        return WM_ERRCODE_INVALID_PARAM;
    }
    if (dmaNo > MI_DMA_MAX_NUM) {
        (void)OS_RestoreInterrupts(e);
        return WM_ERRCODE_INVALID_PARAM;
    }
    if ((u32)wmSysBuf & 0x01f) {
        (void)OS_RestoreInterrupts(e);
        return WM_ERRCODE_INVALID_PARAM;
    }

    WM_EndKeySharing_0x0200926c();
    if (!PXI_IsCallbackReady(PXI_FIFO_TAG_WM, PXI_PROC_ARM7)) {
        (void)OS_RestoreInterrupts(e);
        return WM_ERRCODE_WM_DISABLE;
    }

    DC_InvalidateRange(wmSysBuf, bufSize);

    MI_DmaFill32(dmaNo, wmSysBuf, 0, bufSize);
    wm9buf = (WMArm9Buf *)wmSysBuf;
    wm9buf->WM7 = (WMArm7Buf *)((u32)wm9buf + WM_ARM9WM_BUF_SIZE);
    wm9buf->status = (WMStatus *)((u32)(wm9buf->WM7) + WM_ARM7WM_BUF_SIZE);
    wm9buf->fifo9to7 = (u32 *)((u32)(wm9buf->status) + WM_STATUS_BUF_SIZE);
    wm9buf->fifo7to9 = (u32 *)((u32)(wm9buf->fifo9to7) + WM_FIFO_BUF_SIZE);

    func_ov105_020bd4dc();

    wm9buf->dmaNo = dmaNo;
    wm9buf->connectedAidBitmap = 0x0000;
    wm9buf->myAid = 0;

    {
        s32 i;

        for (i = 0; i < WM_NUM_OF_PORT; i++) {
            wm9buf->portCallbackTable[i] = NULL;
            wm9buf->portCallbackArgument[i] = NULL;
        }
    }

    {
        s32 i;

        OS_InitMessageQueue(&bufMsgQ, bufMsg, WM_BUF_MSG_NUM);
        for (i = 0; i < WM_BUF_MSG_NUM; i++) {
            *((u16 *)(fifoBuf[i])) = WM_API_REQUEST_ACCEPTED;
            DC_StoreRange(fifoBuf[i], 2);
            (void)OS_SendMessage(&bufMsgQ, fifoBuf[i], OS_MESSAGE_BLOCK);
        }
    }

    PXI_SetFifoRecvCallback(PXI_FIFO_TAG_WM, func_ov105_020bd134);

    wmInitialized = 1;
    (void)OS_RestoreInterrupts(e);
    return WM_ERRCODE_SUCCESS;
}
#pragma pop
