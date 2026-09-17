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
typedef void (*NNSSndHeapDisposeCallback)(void * mem, u32 size, u32 data1, u32 data2);
typedef struct NNSSndArcStrmPlayerInfo {
    u8 numChannels;
    u8 chNoList[2];
} NNSSndArcStrmPlayerInfo;
typedef struct NNSSndArcOffsetTable {
    u32 count;
    u32 offset[0];
} NNSSndArcOffsetTable;
typedef struct NNSSndArcFileInfo {
    u32 offset;
    u32 size;
    void * mem;
    u32 reserved;
} NNSSndArcFileInfo;
typedef struct NNSSndArcFat {
    struct SNDBinaryBlockHeader blockHeader;
    u32 count;
    NNSSndArcFileInfo files[0];
} NNSSndArcFat;
typedef struct NNSSndArcInfo {
    struct SNDBinaryBlockHeader blockHeader;
    u32 seqOffset;
    u32 seqArcOffset;
    u32 bankOffset;
    u32 waveArcOffset;
    u32 playerInfoOffset;
    u32 groupInfoOffset;
    u32 strmPlayerInfoOffset;
    u32 strmOffset;
} NNSSndArcInfo;
typedef struct NNSSndArcSymbol {
    struct SNDBinaryBlockHeader blockHeader;
    u32 seqOffset;
    u32 seqArcOffset;
    u32 bankOffset;
    u32 waveArcOffset;
    u32 playerOffset;
    u32 groupOffset;
    u32 strmPlayerOffset;
    u32 strmOffset;
} NNSSndArcSymbol;
typedef struct NNSSndArcHeader {
    struct SNDBinaryFileHeader fileHeader;
    u32 symbolDataOffset;
    u32 symbolDataSize;
    u32 infoOffset;
    u32 infoSize;
    u32 fatOffset;
    u32 fatSize;
    u32 fileImageOffset;
    u32 fileImageSize;
} NNSSndArcHeader;
typedef struct NNSSndArc {
    NNSSndArcHeader header;
    BOOL file_open;
    FSFile file;
    FSFileID fileId;
    struct NNSSndArcFat * fat;
    struct NNSSndArcSymbol * symbol;
    struct NNSSndArcInfo * info;
    s32 loadBlockSize;
} NNSSndArc;
extern const void * GetPtrConst(const void * base, u32 offset);
extern const NNSSndArcOffsetTable * GetOffsetTable(const NNSSndArcInfo * info, u32 offset);
static inline
const void * GetPtrConst (const void * base, u32 offset)
{
    if (offset == 0) return NULL ;
    return (const u8 *)base + offset;
}
static inline
const NNSSndArcOffsetTable * GetOffsetTable (const NNSSndArcInfo * info, u32 offset)
{
    return (const NNSSndArcOffsetTable *)GetPtrConst(info, offset);
}

/* khdays: shared-bss */
NNSSndArc * data_0204ad4c = 0;   /* sCurrent */

/* func_0201b640 -- NitroSystem sndarc.c: NNS_SndArcGetStrmPlayerInfo. */
const NNSSndArcStrmPlayerInfo * func_0201b640 (int playerNo)
{
    NNSSndArc * arc = data_0204ad4c;
    const NNSSndArcOffsetTable * table;


    table = GetOffsetTable(arc->info, arc->info->strmPlayerInfoOffset);
    if (table == NULL) return NULL;

    if (playerNo < 0) return NULL;
    if (playerNo >= table->count) return NULL;

    return (const NNSSndArcStrmPlayerInfo *)GetPtrConst(arc->info, table->offset[ playerNo ]);
}
