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

typedef struct WMGameInfo {
    u16 magicNumber;              /* 0x00 */
    u8 ver;                       /* 0x02 */
    u8 platform;                  /* 0x03 */
    u32 ggid;                     /* 0x04 */
    u16 tgid;                     /* 0x08 */
    u8 userGameInfoLength;        /* 0x0a */
    u8 attribute;                 /* 0x0b */
    u16 parentMaxSize;            /* 0x0c */
    u16 childMaxSize;             /* 0x0e */
    u16 userGameInfo[112 / 2];    /* 0x10 */
} WMGameInfo;

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
    WMGameInfo gameInfo;          /* 0x40 */
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
    void *mp_recvBuf[2];          /* 0x074 */
    u32 *mp_sendBuf;              /* 0x07c */
    u16 mp_sendBufSize;           /* 0x080 */
    u16 mp_ackTime;               /* 0x082 */
    u16 mp_waitAckFlag;           /* 0x084 */
    u16 mp_readyBitmap;           /* 0x086 */
    u8 reserved88[0x9c - 0x88];
    u16 mp_ignoreSizePrecheckMode;   /* 0x09c */
    u8 reserved9e[0xbc - 0x9e];
    u16 linkLevel;                /* 0x0bc */
    u16 minRssi;                  /* 0x0be */
    u16 rssiCounter;              /* 0x0c0 */
    u16 beaconIndicateFlag;       /* 0x0c2 */
    u16 wepKeyId;                 /* 0x0c4 */
    u16 pwrMgtMode;               /* 0x0c6 */
    u8 reservedc8[0xe0 - 0xc8];
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

/* The wireless helper (the SDK demos' wh.c, trimmed for the game) that drives the WM
 * library above: one state machine per role, its callbacks and the file statics. */
typedef enum WHSysState {
    WH_SYSSTATE_STOP = 0,
    WH_SYSSTATE_IDLE,
    WH_SYSSTATE_SCANNING,
    WH_SYSSTATE_BUSY,
    WH_SYSSTATE_CONNECTED,
    WH_SYSSTATE_DATASHARING,
    WH_SYSSTATE_KEYSHARING,
    WH_SYSSTATE_MEASURECHANNEL,
    WH_SYSSTATE_CONNECT_FAIL,
    WH_SYSSTATE_ERROR,
    WH_SYSSTATE_FATAL
} WHSysState;

enum {
    WH_CONNECTMODE_MP_PARENT = 0,
    WH_CONNECTMODE_MP_CHILD,
    WH_CONNECTMODE_KS_PARENT,
    WH_CONNECTMODE_KS_CHILD,
    WH_CONNECTMODE_DS_PARENT,
    WH_CONNECTMODE_DS_CHILD
};

enum {
    WM_STATECODE_PARENT_START = 0,
    WM_STATECODE_BEACON_SENT = 2,
    WM_STATECODE_SCAN_START = 3,
    WM_STATECODE_PARENT_NOT_FOUND = 4,
    WM_STATECODE_PARENT_FOUND = 5,
    WM_STATECODE_CONNECT_START = 6,
    WM_STATECODE_CONNECTED = 7,
    WM_STATECODE_BEACON_LOST = 8,
    WM_STATECODE_DISCONNECTED = 9,
    WM_STATECODE_MP_START = 10,
    WM_STATECODE_MPEND_IND = 11,
    WM_STATECODE_MP_IND = 12,
    WM_STATECODE_MPACK_IND = 13,
    WM_STATECODE_PORT_SEND = 20,
    WM_STATECODE_PORT_RECV = 21,
    WM_STATECODE_DISCONNECTED_FROM_MYSELF = 26
};

#define WH_ERRCODE_DISCONNECTED  20
#define WH_ERRCODE_NO_RADIO      22
#define WH_ERRCODE_LOST_PARENT   23
#define WH_ERRCODE_NOMORE_CHANNEL 24
#define WH_DATA_PORT             14
#define WH_DATA_PRIO             2
#define WH_DMA_NO                2
#define WH_BITMAP_EMPTY          0
#define WH_CHANNEL_MAX           16

/* WMCallback family, only the fields the helper reads. */
typedef struct WMCallback {
    u16 apiid;                    /* 0x00 */
    u16 errcode;                  /* 0x02 */
} WMCallback;

typedef struct WMStartParentCallback {
    u16 apiid;                    /* 0x00 */
    u16 errcode;                  /* 0x02 */
    u16 wlCmdID;                  /* 0x04 */
    u16 wlResult;                 /* 0x06 */
    u16 state;                    /* 0x08 */
    u8 macAddress[6];             /* 0x0a */
    u16 aid;                      /* 0x10 */
    u16 reason;                   /* 0x12 */
    u8 ssid[24];                  /* 0x14 */
    u16 parentSize;               /* 0x2c */
    u16 childSize;                /* 0x2e */
} WMStartParentCallback;

typedef struct WMStartConnectCallback {
    u16 apiid;                    /* 0x00 */
    u16 errcode;                  /* 0x02 */
    u16 wlCmdID;                  /* 0x04 */
    u16 wlResult;                 /* 0x06 */
    u16 state;                    /* 0x08 */
    u16 aid;                      /* 0x0a */
    u16 reason;                   /* 0x0c */
    u16 reserved;                 /* 0x0e */
    u8 macAddress[6];             /* 0x10 */
    u16 parentSize;               /* 0x16 */
    u16 childSize;                /* 0x18 */
} WMStartConnectCallback;

typedef struct WMStartMPCallback {
    u16 apiid;                    /* 0x00 */
    u16 errcode;                  /* 0x02 */
    u16 state;                    /* 0x04 */
} WMStartMPCallback;

typedef struct WMStartScanCallback {
    u16 apiid;                    /* 0x00 */
    u16 errcode;                  /* 0x02 */
    u16 wlCmdID;                  /* 0x04 */
    u16 wlResult;                 /* 0x06 */
    u16 state;                    /* 0x08 */
    u16 macAddress[3];            /* 0x0a */
    u16 channel;                  /* 0x10 */
    u16 linkLevel;                /* 0x12 */
    u16 ssidLength;               /* 0x14 */
    u16 ssid[16];                 /* 0x16 */
    u16 gameInfoLength;           /* 0x36 */
    WMGameInfo gameInfo;          /* 0x38 */
} WMStartScanCallback;
#define WM_SIZE_SYSTEM_GAMEINFO 16
#define WM_GAMEINFO_MAGIC_NUMBER 0x0001
#define WM_ATTR_FLAG_ENTRY 0x01
#define WM_ATTR_FLAG_MB 0x02
static inline BOOL WM_IsValidGameInfo(const WMGameInfo *gameInfo, u16 gameInfoLength)
{
    return (gameInfoLength >= WM_SIZE_SYSTEM_GAMEINFO && gameInfo->magicNumber == WM_GAMEINFO_MAGIC_NUMBER) ? TRUE : FALSE;
}

typedef struct WMMeasureChannelCallback {
    u16 apiid;                    /* 0x00 */
    u16 errcode;                  /* 0x02 */
    u16 wlCmdID;                  /* 0x04 */
    u16 wlResult;                 /* 0x06 */
    u16 channel;                  /* 0x08 */
    u16 ccaBusyRatio;             /* 0x0a */
} WMMeasureChannelCallback;

typedef struct WMPortRecvCallback {
    u16 apiid;                    /* 0x00 */
    u16 errcode;                  /* 0x02 */
    u16 state;                    /* 0x04 */
    u16 port;                     /* 0x06 */
    u16 *recvBuf;                 /* 0x08 */
    u16 *data;                    /* 0x0c */
    u16 length;                   /* 0x10 */
    u16 aid;                      /* 0x12 */
    u8 macAddress[6];             /* 0x14 */
    u16 seqNo;                    /* 0x1a */
    void *arg;                    /* 0x1c */
    u16 myAid;                    /* 0x20 */
    u16 connectedAidBitmap;       /* 0x22 */
    u8 ssid[24];                  /* 0x24 */
    u16 reason;                   /* 0x3c */
    u16 reserved;                 /* 0x3e */
    u16 maxSendDataSize;          /* 0x40 */
    u16 maxRecvDataSize;          /* 0x42 */
} WMPortRecvCallback;

typedef struct WMPortSendCallback {
    u16 apiid;                    /* 0x00 */
    u16 errcode;                  /* 0x02 */
    u16 state;                    /* 0x04 */
    u16 port;                     /* 0x06 */
    u16 destBitmap;               /* 0x08 */
    u16 restBitmap;               /* 0x0a */
    u16 sentBitmap;               /* 0x0c */
    u16 reserved;                 /* 0x0e */
    u16 *data;                    /* 0x10 */
    u16 length;                   /* 0x14 */
    u16 seqNo;                    /* 0x16 */
    u32 reserved2;                /* 0x18 */
    WMCallbackFunc callback;      /* 0x1c */
    void *arg;                    /* 0x20: the helper passes its WhSendCallbackFunc here */
} WMPortSendCallback;

typedef void (*WhScanCallbackFunc)(WMBssDesc *pBssDesc);
typedef void (*WhReceiverFunc)(u16 nAid, u16 *pData, u16 nSize);
typedef void (*WhSendCallbackFunc)(BOOL bDelivered);
typedef BOOL (*WhJudgeAcceptFunc)(WMStartParentCallback *pCb);
typedef u16 (*WhParentWEPKeyGeneratorFunc)(u16 *pWepKey, const WMParentParam *pParentParam);
typedef u16 (*WhChildWEPKeyGeneratorFunc)(u16 *pWepKey, const WMBssDesc *pBssDesc);

/* The helper's file statics, one .bss block at data_ov105_020c04c0 (0x1c0 bytes). The
 * scalar statics come first; the aligned WM parameter blocks follow at 32-byte slots
 * and are also addressed as their own symbols (data_ov105_020c0520 .. 020c05c0). */
typedef struct WhStatics {
    u16 nChannelIndex;            /* 0x00: the channel asked for (0 = walk the allowed set) */
    u16 nMeasuredChannel;         /* 0x02: the channel picked after measuring */
    u16 nMpFreq;                  /* 0x04: MP polls per frame handed to WM_StartMP */
    u16 bAutoConnect;             /* 0x06: connect to the parent the scan callback accepted */
    u16 nChannelBusyRatio;        /* 0x08: the lowest busy ratio measured so far */
    u16 nChannelBitmap;           /* 0x0a: the channels that measured that ratio */
    u16 nDisconnectReason;        /* 0x0c: the first disconnect reason seen */
    u16 nField0e;
    WhScanCallbackFunc pScanCallback;         /* 0x10 */
    u8 *pRecvBuffer;              /* 0x14 */
    u32 nRand;                    /* 0x18: the channel-pick LCG state */
    u8 *pSendBuffer;              /* 0x1c */
    WhReceiverFunc pReceiver;     /* 0x20 */
    WHSysState nSysState;         /* 0x24 */
    u32 nRecvBufferSize;          /* 0x28 */
    u32 nSendBufferSize;          /* 0x2c */
    int nErrCode;                 /* 0x30 */
    int nConnectMode;             /* 0x34: WH_CONNECTMODE_* */
    WhJudgeAcceptFunc pJudgeAccept;           /* 0x38 */
    void *pField3c;
    WhChildWEPKeyGeneratorFunc pChildWEPKeyGenerator;     /* 0x40 */
    WhParentWEPKeyGeneratorFunc pParentWEPKeyGenerator;   /* 0x44 */
    int bPictoCatch;              /* 0x48: also report PictoChat parents found by the scan */
    void *pWmBuffer;              /* 0x4c: the WM system buffer (0xf00 bytes, 32-aligned) */
    u8 reserved50[0x10];
    u16 aWEPKey[16];              /* 0x60: data_ov105_020c0520 */
    WMScanParam scanParam;        /* 0x80: data_ov105_020c0540 */
    u8 aConnectionSsid[32];       /* 0xa0: data_ov105_020c0560 */
    WMParentParam parentParam;    /* 0xc0: data_ov105_020c0580 */
    WMBssDesc bssDesc;            /* 0x100: data_ov105_020c05c0 */
} WhStatics;

extern WhStatics data_ov105_020c04c0;
#define sWh data_ov105_020c04c0
extern u16 data_ov105_020c0520[16];         /* sWh.aWEPKey */
extern WMScanParam data_ov105_020c0540;     /* sWh.scanParam */
extern u8 data_ov105_020c0560[24];          /* sWh.aConnectionSsid */
extern WMParentParam data_ov105_020c0580;   /* sWh.parentParam */
extern WMBssDesc data_ov105_020c05c0;       /* sWh.bssDesc */
#define sWEPKey data_ov105_020c0520
#define sScanParam data_ov105_020c0540
#define sConnectionSsid data_ov105_020c0560
#define sParentParam data_ov105_020c0580
#define sBssDesc data_ov105_020c05c0
/* Two helper statics live in the shared work area instead. */
extern u16 data_027e0064;                   /* sMyAid */
extern u16 data_027e0068;                   /* sConnectBitmap */
#define sMyAid data_027e0064
#define sConnectBitmap data_027e0068

extern void func_ov105_020be49c(int nState);      /* WH_ChangeSysState */
extern void func_ov105_020be4ac(int nError);      /* WH_SetError */
#define WH_ChangeSysState func_ov105_020be49c
#define WH_SetError func_ov105_020be4ac

extern void DC_InvalidateRange(void *addr, u32 size);
extern void DC_StoreRange(void *addr, u32 size);
extern void OS_Terminate(void);
extern void MI_CpuFill8(void *dst, u8 data, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CpuClear16(u16 data, void *dst, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
#define MI_CpuClear8(dst, size) MI_CpuFill8((dst), 0, (size))
#define MI_CpuClear16(dst, size) MIi_CpuClear16(0, (dst), (size))
#define MI_CpuCopy16(src, dst, size) MIi_CpuCopy16((src), (dst), (size))
extern WMErrCode func_ov105_020bce30(void);       /* WM_Finish */
extern void func_ov105_020bd4dc(void);            /* WmClearFifoRecvFlag */
#define WM_ERRCODE_FLASH_ERROR 19
#define WM_SIZE_MACADDR 6
#define WM_SIZE_CHILD_SSID 24

typedef struct WMStartMPCallbackFull {
    u16 apiid;                    /* 0x00 */
    u16 errcode;                  /* 0x02 */
    u16 state;                    /* 0x04 */
    u16 reserved;                 /* 0x06 */
    u16 *recvBuf;                 /* 0x08 */
} WMStartMPCallbackFull;

/* the port-receive record WmReceiveFifo synthesises for connection events */
extern WMPortRecvCallback data_ov105_020bfa70;
#define cb_Port data_ov105_020bfa70

/* func_ov105_020bd134 -- WmReceiveFifo: the PXI receive callback of the WM library: an
 * ARM7 completion buffer arrives, is pulled into the data cache and dispatched: port
 * receives and sends go to the port callbacks, indications to the indication callback,
 * API completions to their registered callback (WM_APIID_END also finishes the library
 * first); a parent/child connect or disconnect updates the connected-aid bitmap and is
 * replayed to every port callback as a synthetic port record. The buffer is then
 * marked accepted and handed back.
 */
void func_ov105_020bd134(int tag, u32 fifo_buf_adr, BOOL err)
{
    WMCallback *callback_p = (WMCallback *)fifo_buf_adr;
    WMArm9Buf *w9b = wm9buf;

    if (err)
        return;

    DC_InvalidateRange(w9b->fifo7to9, WM_FIFO_BUF_SIZE);
    if (!w9b->scanOnlyFlag) {
        DC_InvalidateRange(w9b->status, WM_STATUS_BUF_SIZE);
    }

    if ((u32)callback_p != (u32)(w9b->fifo7to9)) {
        DC_InvalidateRange(callback_p, WM_FIFO_BUF_SIZE);
    }

    if (callback_p->apiid >= WM_NUM_OF_CALLBACK) {
        if (callback_p->apiid == WM_APIID_INDICATION) {
            if (callback_p->errcode == WM_ERRCODE_FLASH_ERROR) {
                OS_Terminate();
            }
            if (w9b->indCallback != NULL) {
                w9b->indCallback((void *)callback_p);
            }
        } else if (callback_p->apiid == WM_APIID_PORT_RECV) {
            WMPortRecvCallback *cb_PortRecv = (WMPortRecvCallback *)callback_p;

            if (w9b->portCallbackTable[cb_PortRecv->port] != NULL) {
                cb_PortRecv->arg = w9b->portCallbackArgument[cb_PortRecv->port];
                cb_PortRecv->connectedAidBitmap = (u16)w9b->connectedAidBitmap;
                DC_InvalidateRange(cb_PortRecv->recvBuf, w9b->status->mp_recvBufSize);
                (w9b->portCallbackTable[cb_PortRecv->port])((void *)cb_PortRecv);
            }
        } else if (callback_p->apiid == WM_APIID_PORT_SEND) {
            WMPortSendCallback *cb_PortSend = (WMPortSendCallback *)callback_p;
            callback_p->apiid = WM_APIID_SET_MP_DATA;
            if (cb_PortSend->callback != NULL) {
                (cb_PortSend->callback)((void *)cb_PortSend);
            }
        }
    } else {
        if (callback_p->apiid == WM_APIID_START_MP) {
            WMStartMPCallbackFull *cb_StartMP = (WMStartMPCallbackFull *)callback_p;
            if (cb_StartMP->state == WM_STATECODE_MPEND_IND
                || cb_StartMP->state == WM_STATECODE_MP_IND) {
                if (cb_StartMP->errcode == WM_ERRCODE_SUCCESS) {
                    DC_InvalidateRange(cb_StartMP->recvBuf, w9b->status->mp_recvBufSize);
                }
            }
        }

        if (callback_p->apiid == WM_APIID_END) {
            if (callback_p->errcode == WM_ERRCODE_SUCCESS) {
                WMCallbackFunc cb = w9b->CallbackTable[callback_p->apiid];

                (void)func_ov105_020bce30();
                if (cb != NULL) {
                    cb((void *)callback_p);
                }
                return;
            }
        }

        if (NULL != w9b->CallbackTable[callback_p->apiid]) {
            (w9b->CallbackTable[callback_p->apiid])((void *)callback_p);

            if (!wmInitialized) {
                return;
            }
        }

        if (callback_p->apiid == WM_APIID_START_PARENT
            || callback_p->apiid == WM_APIID_START_CONNECT) {
            u16 state, aid, myAid, reason;
            u8 *macAddress;
            u8 *ssid;
            u16 parentSize, childSize;

            if (callback_p->apiid == WM_APIID_START_PARENT) {
                WMStartParentCallback *cb = (WMStartParentCallback *)callback_p;
                state = cb->state;
                aid = cb->aid;
                myAid = 0;
                macAddress = cb->macAddress;
                ssid = cb->ssid;
                reason = cb->reason;
                parentSize = cb->parentSize;
                childSize = cb->childSize;
            } else if (callback_p->apiid == WM_APIID_START_CONNECT) {
                WMStartConnectCallback *cb = (WMStartConnectCallback *)callback_p;
                state = cb->state;
                aid = 0;
                myAid = cb->aid;
                macAddress = cb->macAddress;
                ssid = NULL;
                reason = cb->reason;
                parentSize = cb->parentSize;
                childSize = cb->childSize;
            }
            if (state == WM_STATECODE_CONNECTED ||
                state == WM_STATECODE_DISCONNECTED
                || state == WM_STATECODE_DISCONNECTED_FROM_MYSELF) {
                u16 iPort;

                if (state == WM_STATECODE_CONNECTED) {
                    w9b->connectedAidBitmap |= (1 << aid);
                } else {
                    w9b->connectedAidBitmap &= ~(1 << aid);
                }
                w9b->myAid = myAid;

                MI_CpuClear8(&cb_Port, sizeof(WMPortRecvCallback));
                cb_Port.apiid = WM_APIID_PORT_RECV;
                cb_Port.errcode = WM_ERRCODE_SUCCESS;
                cb_Port.state = state;
                cb_Port.recvBuf = NULL;
                cb_Port.data = NULL;
                cb_Port.length = 0;
                cb_Port.aid = aid;
                cb_Port.myAid = myAid;
                cb_Port.connectedAidBitmap = (u16)w9b->connectedAidBitmap;
                cb_Port.seqNo = 0xffff;
                cb_Port.reason = reason;
                MI_CpuCopy8(macAddress, cb_Port.macAddress, WM_SIZE_MACADDR);
                if (ssid != NULL) {
                    MI_CpuCopy16(ssid, cb_Port.ssid, WM_SIZE_CHILD_SSID);
                } else {
                    MI_CpuClear16(cb_Port.ssid, WM_SIZE_CHILD_SSID);
                }
                cb_Port.maxSendDataSize = (myAid == 0) ? parentSize : childSize;
                cb_Port.maxRecvDataSize = (myAid == 0) ? childSize : parentSize;

                for (iPort = 0; iPort < WM_NUM_OF_PORT; iPort++) {
                    cb_Port.port = iPort;
                    if (w9b->portCallbackTable[iPort] != NULL) {
                        cb_Port.arg = w9b->portCallbackArgument[iPort];
                        (w9b->portCallbackTable[iPort])((void *)&cb_Port);
                    }
                }
            }
        }
    }

    DC_InvalidateRange(w9b->fifo7to9, WM_FIFO_BUF_SIZE);
    func_ov105_020bd4dc();

    if ((u32)callback_p != (u32)(w9b->fifo7to9)) {
        callback_p->apiid |= WM_API_REQUEST_ACCEPTED;
        DC_StoreRange(callback_p, WM_FIFO_BUF_SIZE);
    }

    return;
}
