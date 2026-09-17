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

typedef struct WMParentParam {
    u16 *userGameInfo;            /* 0x00 */
    u16 userGameInfoLength;       /* 0x04 */
    u16 padding;                  /* 0x06 */
    u32 ggid;                     /* 0x08 */
    u16 tgid;                     /* 0x0c */
    u16 entryFlag;                /* 0x0e */
    u16 maxEntry;                 /* 0x10 */
    u16 multiBootFlag;            /* 0x12 */
    u16 KS_Flag;                  /* 0x14 */
    u16 CS_Flag;                  /* 0x16 */
    u16 beaconPeriod;             /* 0x18 */
    u16 rsv1[8];                  /* 0x1a */
    u16 rsv2[4];                  /* 0x2a */
    u16 channel;                  /* 0x32 */
    u16 parentMaxSize;            /* 0x34 */
    u16 childMaxSize;             /* 0x36 */
    u16 rsv[4];                   /* 0x38 */
} WMParentParam;                  /* 0x40 = WM_PARENT_PARAM_SIZE */
#define WM_PARENT_PARAM_SIZE 64

typedef struct WMBssDesc {
    u16 length;                   /* 0x00: in halfwords */
    u16 rssi;
    u8 bssid[6];
    u16 ssidLength;
    u8 ssid[32];
    u16 capaInfo;
    struct { u16 basic; u16 support; } rateSet;
    u16 beaconPeriod;
    u16 dtimPeriod;
    u16 channel;
    u16 cfpPeriod;
    u16 cfpMaxDuration;
    u16 gameInfoLength;
    u16 otherElementCount;
    u8 gameInfo[128];
} WMBssDesc;

typedef struct WMScanParam {
    WMBssDesc *scanBuf;           /* 0x00 */
    u16 channel;                  /* 0x04 */
    u16 maxChannelTime;           /* 0x06 */
    u8 bssid[6];                  /* 0x08 */
    u16 rsv[9];
} WMScanParam;

typedef struct WMStartScanReq {
    u16 apiid;
    u16 channel;
    WMBssDesc *scanBuf;
    u16 maxChannelTime;
    u8 bssid[6];
} WMStartScanReq;

typedef struct WMStartConnectReq {
    u16 apiid;
    u16 reserved;
    WMBssDesc *pInfo;
    u8 ssid[24];
    BOOL powerSave;
    u16 reserved2;
    u16 authMode;
} WMStartConnectReq;

/* The ARM7-owned status block; only the offsets the ARM9 side reads are named. */
typedef struct WMStatus {
    u16 state;                    /* 0x000 */
    u16 BusyApiid;                /* 0x002 */
    BOOL apiBusy;                 /* 0x004 */
    BOOL scan_continue;           /* 0x008 */
    BOOL mp_flag;                 /* 0x00c */
    BOOL dcf_flag;                /* 0x010 */
    BOOL ks_flag;                 /* 0x014 */
    BOOL dcf_sendFlag;            /* 0x018 */
    BOOL VSyncFlag;               /* 0x01c */
    u8 wlVersion[8];              /* 0x020 */
    u16 macVersion;               /* 0x028 */
    u16 rfVersion;                /* 0x02a */
    u16 bbpVersion[2];            /* 0x02c */
    u16 mp_parentSize;            /* 0x030 */
    u16 mp_childSize;             /* 0x032 */
    u16 mp_parentMaxSize;         /* 0x034 */
    u16 mp_childMaxSize;          /* 0x036 */
    u16 mp_sendSize;              /* 0x038 */
    u16 mp_recvSize;              /* 0x03a */
    u16 mp_maxSendSize;           /* 0x03c */
    u16 mp_maxRecvSize;           /* 0x03e */
    u8 reserved40[0x72 - 0x40];
    u16 mp_recvBufSize;           /* 0x072 */
    u8 reserved74[0xbc - 0x74];
    u16 linkLevel;                /* 0x0bc */
    u8 reservedbe[0xe0 - 0xbe];
    u8 MacAddress[6];             /* 0x0e0 */
    u16 mode;                     /* 0x0e6 */
    WMParentParam pparam;         /* 0x0e8 */
    u8 childMacAddress[15][6];    /* 0x128 */
    u16 child_bitmap;             /* 0x182 */
    void *pInfoBuf;               /* 0x184 */
    u16 aid;                      /* 0x188 */
    u8 parentMacAddress[6];       /* 0x18a */
    u16 scan_channel;             /* 0x190 */
    u8 reserved192[0x800 - 0x192];
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


typedef struct WMMpRecvBuf {
    u16 rsv1[3];
    u16 length;
    u16 rsv2[1];
    u16 ackTimeStamp;
    u16 timeStamp;
    u16 rate_rssi;
    u16 rsv3[2];
    u16 rsv4[2];
    u8 destAdrs[6];
    u8 srcAdrs[6];
    u16 rsv5[3];
    u16 seqCtrl;
    u16 txop;
    u16 bitmap;
    u16 wmHeader;
    u16 data[2];
} WMMpRecvBuf;

typedef struct WMMpRecvData {
    u16 length;
    u16 rate_rssi;
    u16 aid;
    u16 noResponse;
    u16 wmHeader;
    u16 cdata[1];
} WMMpRecvData;

typedef struct WMMpRecvHeader {
    u16 bitmap;
    u16 errBitmap;
    u16 count;
    u16 length;
    u16 txCount;
    WMMpRecvData data[1];
} WMMpRecvHeader;

/* wm_system.c file statics, one .bss block: wmInitialized (u16) then wm9buf. */
extern u16 data_ov105_020bfa20;
#define wmInitialized data_ov105_020bfa20
#define wm9buf (*(WMArm9Buf **)((u8 *)&data_ov105_020bfa20 + 4))

extern WMArm9Buf *func_ov105_020bd02c(void);      /* WMi_GetSystemWork */
extern WMErrCode func_ov105_020bd03c(void);       /* WMi_CheckInitialized */
extern WMErrCode func_ov105_020bd0a0(s32 paramNum, ...);   /* WMi_CheckStateEx */
extern WMErrCode func_ov105_020bcf10(WMApiid id, u16 paramNum, ...);   /* WMi_SendCommand */
extern WMErrCode func_ov105_020bcfbc(void *data, u32 length);   /* WMi_SendCommandDirect */
extern void func_ov105_020bcea0(WMApiid id, WMCallbackFunc callback);   /* WMi_SetCallbackTable */
extern void DC_InvalidateRange(void *addr, u32 size);
extern void DC_StoreRange(void *addr, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 data, u32 size);
#define MI_CpuClear8(dst, size) MI_CpuFill8((dst), 0, (size))
#define WMi_CheckState(state) func_ov105_020bd0a0(1, (state))
#define WM_CHECK_RESULT(res) if ((res) != WM_ERRCODE_SUCCESS) { return (res); }
#define WM_SIZE_MP_DATA_MAX 512
#define WM_SIZE_KS_PARENT_DATA (2 * 16 + 4)
#define WM_SIZE_KS_CHILD_DATA 2
#define WM_SIZE_MP_PARENT_PADDING 6
#define WM_SIZE_MP_CHILD_PADDING 4
#define WM_SIZE_USER_GAMEINFO 112
#define WM_NUM_MAX_CHILD 15
#define WM_SIZE_CHILD_SSID 24

/* func_ov105_020bdea4 -- WM_Disconnect: drop one connection (DISCONNECT): a parent
 * names a connected child's aid (1..15, checked against the child bitmap), a child
 * passes 0.
 */
WMErrCode func_ov105_020bdea4(WMCallbackFunc callback, u16 aid)
{
    WMErrCode result;
    WMArm9Buf *p = func_ov105_020bd02c();

    result = func_ov105_020bd0a0(5,
                                 WM_STATE_PARENT, WM_STATE_MP_PARENT,
                                 WM_STATE_CHILD, WM_STATE_MP_CHILD, WM_STATE_DCF_CHILD);
    WM_CHECK_RESULT(result);

    if ((p->status->state == WM_STATE_PARENT) || (p->status->state == WM_STATE_MP_PARENT)) {
        if ((aid < 1) || (aid > WM_NUM_MAX_CHILD)) {
            return WM_ERRCODE_INVALID_PARAM;
        }
        DC_InvalidateRange(&(p->status->child_bitmap), 2);
        if (!(p->status->child_bitmap & (0x0001 << aid))) {
            return WM_ERRCODE_NO_CHILD;
        }
    } else {
        if (aid != 0) {
            return WM_ERRCODE_INVALID_PARAM;
        }
    }

    func_ov105_020bcea0(WM_APIID_DISCONNECT, callback);

    result = func_ov105_020bcf10(WM_APIID_DISCONNECT, 1, (u32)(0x0001 << aid));
    WM_CHECK_RESULT(result);

    return WM_ERRCODE_OPERATING;
}
