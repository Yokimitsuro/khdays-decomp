typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
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

#define offsetof(type, member) ((u32)&(((type *)0)->member))



typedef struct CPContext {
    u64 div_numer;
    u64 div_denom;
    u64 sqrt;
    u16 div_mode;
    u16 sqrt_mode;
} CPContext;
typedef struct OSContext {
    u32 cpsr;
    u32 r[13];
    u32 sp;
    u32 lr;
    u32 pc_plus4;
    u32 sp_svc;
    CPContext cp_context;
} OSContext;
typedef struct _OSThread OSThread;
typedef struct _OSThreadQueue OSThreadQueue;
typedef struct _OSThreadLink OSThreadLink;
typedef struct _OSMutexQueue OSMutexQueue;
typedef struct _OSMutexLink OSMutexLink;
typedef struct OSMutex OSMutex;
typedef struct OSiAlarm OSAlarm;
struct _OSThreadQueue {
        OSThread * head;
        OSThread * tail;
    };
struct _OSThreadLink {
        OSThread * prev;
        OSThread * next;
    };
struct _OSMutexQueue {
        OSMutex * head;
        OSMutex * tail;
    };
struct _OSMutexLink {
        OSMutex * next;
        OSMutex * prev;
    };
typedef enum {
    OS_THREAD_STATE_WAITING       = 0,
    OS_THREAD_STATE_READY         = 1,
    OS_THREAD_STATE_TERMINATED    = 2
} OSThreadState;
typedef void (*OSThreadDestructor) (void *);
struct _OSThread {
    OSContext context;
    OSThreadState state;
    OSThread * next;
    u32 id;
    u32 priority;
    void * profiler;
    OSThreadQueue * queue;
    OSThreadLink link;
    OSMutex * mutex;
    OSMutexQueue mutexQueue;
    u32 stackTop;
    u32 stackBottom;
    u32 stackWarningOffset;
    OSThreadQueue joinQueue;
    void * specific[3 ];
    OSAlarm * alarmForSleep;
    OSThreadDestructor destructor;
    void * userParameter;
    int systemErrno;
};
struct OSMutex {
    OSThreadQueue queue;
    OSThread * thread;
    s32 count;
    OSMutexLink link;
};
typedef u64 OSTick;
typedef void (*OSAlarmHandler) (void *);
struct OSiAlarm {
    OSAlarmHandler handler;
    void * arg;
    u32 tag;
    OSTick fire;
    OSAlarm * prev;
    OSAlarm * next;
    OSTick period;
    OSTick start;
};
typedef struct {
    void * prevObject;
    void * nextObject;
} NNSFndLink;
typedef struct {
    void * headObject;
    void * tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;
enum {
    FS_ARCHIVE_NAME_LEN_MAX = 3
};
typedef enum {
    FS_COMMAND_ASYNC_BEGIN = 0,
    FS_COMMAND_READFILE = FS_COMMAND_ASYNC_BEGIN,
    FS_COMMAND_WRITEFILE,
    FS_COMMAND_ASYNC_END,
    FS_COMMAND_SYNC_BEGIN = FS_COMMAND_ASYNC_END,
    FS_COMMAND_SEEKDIR = FS_COMMAND_SYNC_BEGIN,
    FS_COMMAND_READDIR,
    FS_COMMAND_FINDPATH,
    FS_COMMAND_GETPATH,
    FS_COMMAND_OPENFILEFAST,
    FS_COMMAND_OPENFILEDIRECT,
    FS_COMMAND_CLOSEFILE,
    FS_COMMAND_SYNC_END,
    FS_COMMAND_STATUS_BEGIN = FS_COMMAND_SYNC_END,
    FS_COMMAND_ACTIVATE = FS_COMMAND_STATUS_BEGIN,
    FS_COMMAND_IDLE,
    FS_COMMAND_SUSPEND,
    FS_COMMAND_RESUME,
    FS_COMMAND_STATUS_END,
    FS_COMMAND_INVALID
} FSCommandType;
typedef enum {
    FS_RESULT_SUCCESS = 0,
    FS_RESULT_FAILURE,
    FS_RESULT_BUSY,
    FS_RESULT_CANCELED,
    FS_RESULT_CANCELLED = FS_RESULT_CANCELED,
    FS_RESULT_UNSUPPORTED,
    FS_RESULT_ERROR,
    FS_RESULT_PROC_ASYNC,
    FS_RESULT_PROC_DEFAULT,
    FS_RESULT_PROC_UNKNOWN
} FSResult;
struct FSFile;
struct FSFileLink;
struct FSArchive;
typedef FSResult (*FS_ARCHIVE_PROC_FUNC) (struct FSFile *, FSCommandType);
typedef FSResult (*FS_ARCHIVE_READ_FUNC) (struct FSArchive * p, void * dst, u32 pos, u32 size);
typedef FSResult (*FS_ARCHIVE_WRITE_FUNC) (struct FSArchive * p, const void * src, u32 pos, u32 size);
typedef struct FSFileLink {
    struct FSFile * prev;
    struct FSFile * next;
} FSFileLink;
typedef struct FSArchive {
    union {
        char ptr[FS_ARCHIVE_NAME_LEN_MAX + 1];
        u32 pack;
    } name;
    struct FSArchive * next;
    struct FSArchive * prev;
    OSThreadQueue sync_q;
    OSThreadQueue stat_q;
    u32 flag;
    FSFileLink list;
    u32 base;
    u32 fat;
    u32 fat_size;
    u32 fnt;
    u32 fnt_size;
    u32 fat_bak;
    u32 fnt_bak;
    void * load_mem;
    FS_ARCHIVE_READ_FUNC read_func;
    FS_ARCHIVE_WRITE_FUNC write_func;
    FS_ARCHIVE_READ_FUNC table_func;
    FS_ARCHIVE_PROC_FUNC proc;
    u32 proc_flag;
} FSArchive;
typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
struct FSFile;
typedef struct {
    struct FSArchive * arc;
    u16 own_id;
    u16 index;
    u32 pos;
} FSDirPos;
typedef struct {
    struct FSArchive * arc;
    u32 file_id;
} FSFileID;
typedef struct {
    union {
        FSFileID file_id;
        FSDirPos dir_id;
    };
    u32 is_directory;
    u32 name_len;
    char name[127 + 1];
} FSDirEntry;
typedef struct {
    FSDirPos pos;
} FSSeekDirInfo;
typedef struct {
    FSDirEntry * p_entry;
    BOOL skip_string;
} FSReadDirInfo;
typedef struct {
    FSDirPos pos;
    const char * path;
    BOOL find_directory;
    union {
        FSFileID * file;
        FSDirPos * dir;
    }
    result;
} FSFindPathInfo;
typedef struct {
    u8 * buf;
    u32 buf_len;
    u16 total_len;
    u16 dir_id;
} FSGetPathInfo;
typedef struct {
    FSFileID id;
} FSOpenFileFastInfo;
typedef struct {
    u32 top;
    u32 bottom;
    u32 index;
} FSOpenFileDirectInfo;
typedef struct {
    u32 reserved;
} FSCloseFileInfo;
typedef struct {
    void * dst;
    u32 len_org;
    u32 len;
} FSReadFileInfo;
typedef struct {
    const void * src;
    u32 len_org;
    u32 len;
} FSWriteFileInfo;
typedef struct FSFile {
    FSFileLink link;
    struct FSArchive * arc;
    u32 stat;
    FSCommandType command;
    FSResult error;
    OSThreadQueue queue[1];
    union {
        struct {
            u32 own_id;
            u32 top;
            u32 bottom;
            u32 pos;
        } file;
        struct {
            FSDirPos pos;
            u32 parent;
        } dir;
    }
    prop;
    union {
        FSReadFileInfo readfile;
        FSWriteFileInfo writefile;
        FSSeekDirInfo seekdir;
        FSReadDirInfo readdir;
        FSFindPathInfo findpath;
        FSGetPathInfo getpath;
        FSOpenFileFastInfo openfilefast;
        FSOpenFileDirectInfo openfiledirect;
        FSCloseFileInfo closefile;
    } arg;
} FSFile;
typedef enum {
    SND_DUTY_1_8,
    SND_DUTY_2_8,
    SND_DUTY_3_8,
    SND_DUTY_4_8,
    SND_DUTY_5_8,
    SND_DUTY_6_8,
    SND_DUTY_7_8
} SNDDuty;
struct SNDExChannel;
typedef enum SNDExChannelCallbackStatus {
    SND_EX_CHANNEL_CALLBACK_DROP,
    SND_EX_CHANNEL_CALLBACK_FINISH
} SNDExChannelCallbackStatus;
typedef void (*SNDExChannelCallback) (struct SNDExChannel * ch_p, SNDExChannelCallbackStatus status, void * userData);
typedef struct SNDWaveParam {
        u8 format;
        u8 loopflag;
        u16 rate;
        u16 timer;
        u16 loopstart;
        u32 looplen;
    } SNDWaveParam;
typedef struct SNDLfoParam {
    u8 target;
    u8 speed;
    u8 depth;
    u8 range;
    u16 delay;
} SNDLfoParam;
typedef struct SNDLfo {
    struct SNDLfoParam param;
    u16 delay_counter;
    u16 counter;
} SNDLfo;
typedef struct SNDExChannel {
    u8 myNo;
    u8 type;
    u8 env_status;
    u8 active_flag : 1;
    u8 start_flag : 1;
    u8 auto_sweep : 1;
    u8 sync_flag : 5;
    u8 pan_range;
    u8 original_key;
    s16 user_decay2;
    u8 key;
    u8 velocity;
    s8 init_pan;
    s8 user_pan;
    s16 user_decay;
    s16 user_pitch;
    s32 env_decay;
    s32 sweep_counter;
    s32 sweep_length;
    u8 attack;
    u8 sustain;
    u16 decay;
    u16 release;
    u8 prio;
    u8 pan;
    u16 volume;
    u16 timer;
    struct SNDLfo lfo;
    s16 sweep_pitch;
    s32 length;
    struct SNDWaveParam wave;
    union {
        const void * data;
        SNDDuty duty;
    };
    SNDExChannelCallback callback;
    void * callback_data;
    struct SNDExChannel * nextLink;
} SNDExChannel;
typedef struct SNDBinaryFileHeader {
    char signature[4];
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} SNDBinaryFileHeader;
typedef struct SNDBinaryBlockHeader {
    u32 kind;
    u32 size;
} SNDBinaryBlockHeader;
struct SNDExChannel;
typedef void (*NNSSndHeapDisposeCallback)(void * mem, u32 size, u32 data1, u32 data2);
typedef enum {
    TP_REQUEST_COMMAND_SAMPLING         = 0x0,
    TP_REQUEST_COMMAND_AUTO_ON          = 0x1,
    TP_REQUEST_COMMAND_AUTO_OFF         = 0x2,
    TP_REQUEST_COMMAND_SET_STABILITY    = 0x3,
    TP_REQUEST_COMMAND_AUTO_SAMPLING    = 0x10
} TPRequestCommand;
typedef enum {
    TP_RESULT_SUCCESS = 0,
    TP_RESULT_INVALID_PARAMETER,
    TP_RESULT_ILLEGAL_STATUS,
    TP_RESULT_EXCLUSIVE,
    TP_RESULT_PXI_BUSY
} TPRequestResult;
typedef void (*TPRecvCallback) (TPRequestCommand command, TPRequestResult result, u16 index);
typedef enum {
    PXI_FIFO_TAG_EX = 0,
    PXI_FIFO_TAG_USER_0,
    PXI_FIFO_TAG_USER_1,
    PXI_FIFO_TAG_SYSTEM,
    PXI_FIFO_TAG_NVRAM,
    PXI_FIFO_TAG_RTC,
    PXI_FIFO_TAG_TOUCHPANEL,
    PXI_FIFO_TAG_SOUND,
    PXI_FIFO_TAG_PM,
    PXI_FIFO_TAG_MIC,
    PXI_FIFO_TAG_WM,
    PXI_FIFO_TAG_FS,
    PXI_FIFO_TAG_OS,
    PXI_FIFO_TAG_CTRDG,
    PXI_FIFO_TAG_CARD,
    PXI_FIFO_TAG_WVR,
    PXI_FIFO_TAG_CTRDG_Ex,
    PXI_FIFO_TAG_CTRDG_PHI,
    PXI_MAX_FIFO_TAG = 32
} PXIFifoTag;
typedef void (*PXIFifoCallback) (PXIFifoTag tag, u32 data, BOOL err);
typedef enum MICResult {
    MIC_RESULT_SUCCESS = 0,
    MIC_RESULT_BUSY,
    MIC_RESULT_ILLEGAL_PARAMETER,
    MIC_RESULT_SEND_ERROR,
    MIC_RESULT_INVALID_COMMAND,
    MIC_RESULT_ILLEGAL_STATUS,
    MIC_RESULT_FATAL_ERROR,
    MIC_RESULT_MAX
} MICResult;
typedef void (*MICCallback) (MICResult result, void * arg);
typedef void (*PMCallback) (u32 result, void * arg);
typedef void (*PMSleepCallback) (void *);
typedef struct PMiSleepCallbackInfo PMSleepCallbackInfo;
struct PMiSleepCallbackInfo {
    PMSleepCallback callback;
    void * arg;
    PMSleepCallbackInfo * next;
};
typedef enum NNSSndStrmFormat {
    NNS_SND_STRM_FORMAT_PCM8,
    NNS_SND_STRM_FORMAT_PCM16
} NNSSndStrmFormat;
typedef enum NNSSndStrmCallbackStatus {
    NNS_SND_STRM_CALLBACK_SETUP,
    NNS_SND_STRM_CALLBACK_INTERVAL
} NNSSndStrmCallbackStatus;
typedef void (*NNSSndStrmCallback)(NNSSndStrmCallbackStatus status, int numChannles, void * buffer[], u32 len, NNSSndStrmFormat format, void * arg);
typedef struct NNSSndStrm {
    NNSFndLink link;
    PMSleepCallbackInfo preSleepInfo;
    PMSleepCallbackInfo postSleepInfo;
    NNSSndStrmFormat format;
    BOOL activeFlag :1;
    BOOL startFlag :1;
    u32 chBufLen;
    int interval;
    NNSSndStrmCallback callback;
    void * callbackArg;
    int curBuffer;
    int volume;
    int alarmNo;
    u32 chBitMask;
    int numChannels;
    u8 channelNo[16 ];
} NNSSndStrm;
struct NNSSndStrmPlayer;
typedef enum NNSSndArcStrmCallbackStatus {
    NNS_SND_ARC_STRM_CALLBACK_DATA_END
} NNSSndArcStrmCallbackStatus;
typedef struct NNSSndArcStrmCallbackInfo {
    int playerNo;
    int strmNo;
} NNSSndArcStrmCallbackInfo;
typedef struct NNSSndArcStrmCallbackParam {
    int strmNo;
    u32 offset;
} NNSSndArcStrmCallbackParam;
typedef BOOL (*NNSSndArcStrmCallback)(NNSSndArcStrmCallbackStatus status, const NNSSndArcStrmCallbackInfo * info, NNSSndArcStrmCallbackParam * param, void * arg);
typedef struct NNSSndStrmHandle {
    struct NNSSndStrmPlayer * player;
} NNSSndStrmHandle;
typedef struct NNSSndStrmThread {
    OSThread thread;
    u64 stack[ 1024 / sizeof(u64) ];
    OSThreadQueue threadQ;
    OSMutex mutex;
    NNSFndList commandList;
} NNSSndStrmThread;
inline BOOL NNS_SndStrmHandleIsValid (const NNSSndStrmHandle * handle)
{
    return handle->player != NULL ;
}
typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;
struct NNSSndStrmPlayer;
typedef BOOL (*OpenStreamFunc)(struct NNSSndStrmPlayer * player, u32 fileId);
typedef void (*CloseStreamFunc)(struct NNSSndStrmPlayer * player);
typedef s32 (*ReadStreamFunc)(struct NNSSndStrmPlayer * player, void * dest, u32 size, u32 offset);
typedef void (*CancelStreamFunc)(struct NNSSndStrmPlayer * player);
typedef struct NNSSndStrmData {
    struct SNDBinaryFileHeader fileHeader;
    struct SNDBinaryBlockHeader blockHeader;
    u8 format;
    u8 loopFlag;
    u8 numChannels;
    u8 pad_;
    u16 sampleRate;
    u16 timer;
    u32 loopStart;
    u32 loopEnd;
    u32 dataOffset;
    u32 numBlocks;
    u32 blockSize;
    u32 blockSamples;
    u32 lastBlockSize;
    u32 lastBlockSamples;
} NNSSndStrmData;
typedef struct AdpcmState {
    s16 prevSample;
    u8 prevIndex;
    u8 padding;
} AdpcmState;
typedef struct NNSSndStrmPlayer {
    NNSSndStrm stream;
    FSFile file;
    u32 fileOffset;
    NNSSndStrmData info;
    NNSSndFader fader;
    AdpcmState adpcmState[6 ];
    BOOL activeFlag  : 1;
    BOOL playFlag    : 1;
    BOOL startFlag   : 1;
    BOOL fadeOutFlag : 1;
    BOOL dirtyFlag   : 1;
    BOOL finishFlag  : 1;
    BOOL monoFlag    : 1;
    volatile int finishCounter;
    volatile BOOL prepareFlag;
    volatile int commandCount;
    int allocChannelCount;
    u8 numChannels;
    u8 padding;
    u8 chNoList[6 ];
    void * buffer;
    u32 bufSize;
    NNSSndStrmCallback strmCallback;
    void * strmCallbackArg;
    NNSSndArcStrmCallback sndArcStrmCallback;
    void * sndArcStrmCallbackArg;
    int strmNo;
    int playerNo;
    NNSSndStrmHandle * handle;
    int prio;
    int initVolume;
    int extVolume;
    int volume;
    u32 curSample;
    OpenStreamFunc openStreamFunc;
    CloseStreamFunc closeStreamFunc;
    ReadStreamFunc readStreamFunc;
    CancelStreamFunc cancelStreamFunc;
} NNSSndStrmPlayer;
extern void SNDi_FreeVoiceChannel(NNSSndStrmPlayer * player, int fadeFrame);
extern void SNDi_FreeVoiceChannel (NNSSndStrmPlayer * player, int fadeFrame);

/* khdays: shared-bss */
NNSSndStrmThread * sPrepareThread = 0;   /* sPrepareThread */
BOOL data_0204ad8c = 0;   /* initialized$3434 */
u8 * sDecodeBuffer = 0;   /* sDecodeBuffer */

/* func_0201cb64 -- NitroSDK sndarc_stream.c: NNS_SndArcStrmStop. */
void func_0201cb64 (NNSSndStrmHandle * handle, int fadeFrame)
{

    if (!NNS_SndStrmHandleIsValid(handle)) return;

    SNDi_FreeVoiceChannel(handle->player, fadeFrame);
}
