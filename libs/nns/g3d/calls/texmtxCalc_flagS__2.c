

#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nitro/fx_types.h"
#include "nitro/pxi.h"
#include "nitro/spi.h"
#include "nitro/rtc.h"
#include "nitro/fs.h"
#include "nitro/wm.h"
#include "nnsys/g3d.h"

typedef enum WVRResult {
    WVR_RESULT_SUCCESS = 0,
    WVR_RESULT_OPERATING,
    WVR_RESULT_DISABLE,
    WVR_RESULT_INVALID_PARAM,
    WVR_RESULT_FIFO_ERROR,
    WVR_RESULT_ILLEGAL_STATUS,
    WVR_RESULT_VRAM_LOCKED,
    WVR_RESULT_FATAL_ERROR,
    WVR_RESULT_MAX
} WVRResult;
typedef void (*WVRCallbackFunc) (void * arg, WVRResult result);
typedef enum STDResult {
    STD_RESULT_SUCCESS,
    STD_RESULT_ERROR,
    STD_RESULT_INVALID_PARAM,
    STD_RESULT_CONVERSION_FAILED
} STDResult;
typedef STDResult (*STDConvertUnicodeCallback) (u16 * dst, int * dst_len, const char * src, int * src_len);
typedef STDResult (*STDConvertSjisCallback) (char * dst, int * dst_len, const u16 * src, int * src_len);
void FX_DivAsync(fx32 numer, fx32 denom);
fx32 FX_GetDivResult(void);
typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);
typedef void (*WBTCallback) (void *);
typedef s16 WBTResult;
typedef enum {
    WBT_CMD_REQ_NONE = 0,
    WBT_CMD_REQ_WAIT,
    WBT_CMD_REQ_SYNC,
    WBT_CMD_RES_SYNC,
    WBT_CMD_REQ_GET_BLOCK,
    WBT_CMD_RES_GET_BLOCK,
    WBT_CMD_REQ_GET_BLOCKINFO,
    WBT_CMD_RES_GET_BLOCKINFO,
    WBT_CMD_REQ_GET_BLOCK_DONE,
    WBT_CMD_RES_GET_BLOCK_DONE,
    WBT_CMD_REQ_USER_DATA,
    WBT_CMD_RES_USER_DATA,
    WBT_CMD_SYSTEM_CALLBACK,
    WBT_CMD_PREPARE_SEND_DATA,
    WBT_CMD_REQ_ERROR,
    WBT_CMD_RES_ERROR,
    WBT_CMD_CANCEL
} WBTCommandType;
typedef u8 WBTCommandCounter;
typedef u16 WBTAidBitmap;
typedef s16 WBTBlockNumEntry;
typedef struct {
    u32 id;
    s32 block_size;
    u8 user_id[32 ];
} WBTBlockInfo;
typedef struct WBTBlockInfoList {
    WBTBlockInfo data_info;
    struct WBTBlockInfoList * next;
    void * data_ptr;
    WBTAidBitmap permission_bmp;
    u16 block_type;
} WBTBlockInfoList;
typedef struct {
    WBTBlockInfo * block_info[((1 + 15 - 1) + 1) ];
} WBTBlockInfoTable;
typedef struct {
    u32 * packet_bitmap[((1 + 15 - 1) + 1) ];
} WBTPacketBitmapTable;
typedef struct {
    u8 * recv_buf[((1 + 15 - 1) + 1) ];
} WBTRecvBufTable;
typedef struct {
    WBTBlockNumEntry num_of_list;
    s16 peer_packet_size;
    s16 my_packet_size;
    u16 pad1;
    u32 padd2[2];
} WBTRequestSyncCallback;
typedef struct {
    u32 block_id;
} WBTGetBlockDoneCallback;
typedef struct {
    u32 block_id;
    s32 block_seq_no;
    void * data_ptr;
    s16 own_packet_size;
    u16 padd;
} WBTPrepareSendDataCallback;
typedef struct {
    u8 data[9 ];
    u8 size;
    u8 padd[3];
} WBTRecvUserDataCallback;
typedef struct {
    u32 block_id;
    u32 recv_data_size;
    WBTRecvBufTable recv_buf_table;
    WBTPacketBitmapTable pkt_bmp_table;
} WBTGetBlockCallback;
typedef struct {
    WBTCommandType command;
    WBTCommandType event;
    u16 target_bmp;
    u16 peer_bmp;
    WBTCommandCounter my_cmd_counter;
    WBTCommandCounter peer_cmd_counter;
    WBTResult result;
    WBTCallback callback;
    union {
        WBTRequestSyncCallback sync;
        WBTGetBlockDoneCallback blockdone;
        WBTPrepareSendDataCallback prepare_send_data;
        WBTRecvUserDataCallback user_data;
        WBTGetBlockCallback get;
    };
} WBTCommand;
struct WBTContext;
struct WBTCommandList;
typedef void (*WBTEventCallback)(void *, WBTCommand *);
typedef struct WBTCommandList {
    struct WBTCommandList * next;
    WBTCommand command;
    WBTEventCallback callback;
} WBTCommandList;
typedef struct WBTRecvToken {
    u8 token_command;
    u8 token_peer_cmd_counter;
    u8 last_peer_cmd_counter;
    u8 dummy[1];
    u32 token_block_id;
    s32 token_block_seq_no;
} WBTRecvToken;
typedef struct WBTPacketBitmap {
    s32 length;
    void * buffer;
    s32 count;
    s32 total;
    u32 * bitmap;
    s32 current;
} WBTPacketBitmap;
typedef struct WBTContext {
    WBTCommandList * command;
    WBTCommandList * command_pool;
    void * userdata;
    WBTEventCallback callback;
    WBTCommand system_cmd;
    struct {
        WBTRecvToken recv_token;
        WBTPacketBitmap pkt_bmp;
    } peer_param[16];
    int my_aid;
    s16 peer_data_packet_size;
    s16 my_data_packet_size;
    WBTBlockInfoList * list;
    u8 my_command_counter;
    u8 padding[3];
    int last_target_aid;
    u32 last_block_id;
    s32 last_seq_no_1;
    s32 last_seq_no_2;
    int req_bitmap;
    u32 binfo_bitmap[16][(((sizeof(WBTBlockInfo)) + (( sizeof(u32)) - 1)) & ~(( sizeof(u32)) - 1)) / sizeof(u32)];
} WBTContext;
typedef enum WFSTableRegionType {
    WFS_TABLE_REGION_FAT,
    WFS_TABLE_REGION_FNT,
    WFS_TABLE_REGION_OV9,
    WFS_TABLE_REGION_OV7,
    WFS_TABLE_REGION_MAX
} WFSTableRegionType;
typedef enum WFSEventType {
    WFS_EVENT_SERVER_SEGMENT_REQUEST,
    WFS_EVENT_CLIENT_READY
} WFSEventType;
typedef struct WFSTableFormat {
    u32 origin;
    u8 * buffer;
    u32 length;
    CARDRomRegion region[WFS_TABLE_REGION_MAX];
} WFSTableFormat;
typedef void (*WFSEventCallback)(void * context, WFSEventType, void * argument);
struct WFSClientContext;
typedef void (*WFSRequestClientReadDoneCallback)(struct WFSClientContext * context, BOOL succeeded, void * arg);
typedef struct WFSClientContext {
    void * userdata;
    WFSEventCallback callback;
    MIAllocator * allocator;
    u32 fat_ready :1;
    u32 flags :31;
    WBTContext wbt[1];
    WBTCommandList wbt_list[2];
    WBTRecvBufTable recv_buf_table;
    WBTPacketBitmapTable recv_buf_packet_bmp_table;
    WBTBlockInfoTable block_info_table;
    WBTBlockInfo block_info[16];
    u32 * recv_pkt_bmp_buf;
    u32 max_file_size;
    WFSTableFormat table[1];
    u32 block_id;
    CARDRomRegion request_region;
    void * request_buffer;
    WFSRequestClientReadDoneCallback request_callback;
    void * request_argument;
    u8 padding[12];
} WFSClientContext;

/* texmtxCalc_flagS__2 -- NitroSystem 3dsmax.c: texmtxCalc_flagS_. */
void texmtxCalc_flagS__2 (MtxFx44 * m, const NNSG3dMatAnmResult * anm)
{
    fx32 p, q;
    fx32 tmpW, tmpH;

    tmpW = (s32)anm->origWidth << FX32_SHIFT;
    tmpH = (s32)anm->origHeight << FX32_SHIFT;
    FX_DivAsync(tmpH, tmpW);

    m->_00 = anm->cosR;
    m->_11 = anm->cosR;

    m->_01 = anm->sinR * FX_GetDivResult() >> FX32_SHIFT;
    FX_DivAsync(tmpW, tmpH);

    p = (-anm->origWidth << (FX32_SHIFT - 1)) - anm->transS * anm->origWidth;
    q = (-anm->origHeight << (FX32_SHIFT - 1)) + anm->transT * anm->origHeight;

    m->_30 = (fx32)(((fx64)anm->cosR * p - (fx64)anm->sinR * q) >> (FX32_SHIFT - 4)) +
             (anm->origWidth << (FX32_SHIFT - 1 + 4));

    m->_31 = (fx32)(((fx64)anm->sinR * p + (fx64)anm->cosR * q) >> (FX32_SHIFT - 4)) +
             (anm->origHeight << (FX32_SHIFT - 1 + 4));

    m->_10 = -anm->sinR * FX_GetDivResult() >> FX32_SHIFT;
}
