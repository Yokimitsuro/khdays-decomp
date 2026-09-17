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
typedef unsigned short vu16;
typedef unsigned int vu32;
typedef unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

/* NitroSDK FS library (file system / archives / overlays), as linked into the main binary.
 * Types from include/nitro/fs/{archive,file,overlay}.h and the library's internal headers. */

#define FS_FILE_NAME_MAX    127
#define FS_ARCHIVE_NAME_LEN_MAX 3
#define FS_DMA_NOT_USE      ((u32) ~0)

typedef enum {
    FS_SEEK_SET,
    FS_SEEK_CUR,
    FS_SEEK_END
} FSSeekFileMode;

#define FS_FILE_STATUS_BUSY                 0x00000001
#define FS_FILE_STATUS_CANCEL               0x00000002
#define FS_FILE_STATUS_SYNC                 0x00000004
#define FS_FILE_STATUS_ASYNC                0x00000008
#define FS_FILE_STATUS_IS_FILE              0x00000010
#define FS_FILE_STATUS_IS_DIR               0x00000020
#define FS_FILE_STATUS_OPERATING            0x00000040

#define FS_ARCHIVE_FLAG_REGISTER              0x00000001
#define FS_ARCHIVE_FLAG_LOADED                0x00000002
#define FS_ARCHIVE_FLAG_TABLE_LOAD            0x00000004
#define FS_ARCHIVE_FLAG_SUSPEND               0x00000008
#define FS_ARCHIVE_FLAG_RUNNING               0x00000010
#define FS_ARCHIVE_FLAG_CANCELING             0x00000020
#define FS_ARCHIVE_FLAG_SUSPENDING            0x00000040
#define FS_ARCHIVE_FLAG_UNLOADING             0x00000080
#define FS_ARCHIVE_FLAG_IS_ASYNC              0x00000100
#define FS_ARCHIVE_FLAG_IS_SYNC               0x00000200

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

#define FS_ARCHIVE_PROC_READFILE        (1 << FS_COMMAND_READFILE)
#define FS_ARCHIVE_PROC_WRITEFILE       (1 << FS_COMMAND_WRITEFILE)
#define FS_ARCHIVE_PROC_ASYNC           (FS_ARCHIVE_PROC_READFILE | FS_ARCHIVE_PROC_WRITEFILE)
#define FS_ARCHIVE_PROC_SEEKDIR         (1 << FS_COMMAND_SEEKDIR)
#define FS_ARCHIVE_PROC_READDIR         (1 << FS_COMMAND_READDIR)
#define FS_ARCHIVE_PROC_FINDPATH        (1 << FS_COMMAND_FINDPATH)
#define FS_ARCHIVE_PROC_GETPATH         (1 << FS_COMMAND_GETPATH)
#define FS_ARCHIVE_PROC_OPENFILEFAST    (1 << FS_COMMAND_OPENFILEFAST)
#define FS_ARCHIVE_PROC_OPENFILEDIRECT  (1 << FS_COMMAND_OPENFILEDIRECT)
#define FS_ARCHIVE_PROC_CLOSEFILE       (1 << FS_COMMAND_CLOSEFILE)
#define FS_ARCHIVE_PROC_SYNC \
    (FS_ARCHIVE_PROC_SEEKDIR | FS_ARCHIVE_PROC_READDIR | \
     FS_ARCHIVE_PROC_FINDPATH | FS_ARCHIVE_PROC_GETPATH | \
     FS_ARCHIVE_PROC_OPENFILEFAST | FS_ARCHIVE_PROC_OPENFILEDIRECT | FS_ARCHIVE_PROC_CLOSEFILE)
#define FS_ARCHIVE_PROC_ACTIVATE        (1 << FS_COMMAND_ACTIVATE)
#define FS_ARCHIVE_PROC_IDLE            (1 << FS_COMMAND_IDLE)
#define FS_ARCHIVE_PROC_SUSPENDING      (1 << FS_COMMAND_SUSPEND)
#define FS_ARCHIVE_PROC_RESUME          (1 << FS_COMMAND_RESUME)
#define FS_ARCHIVE_PROC_STATUS \
    (FS_ARCHIVE_PROC_ACTIVATE | FS_ARCHIVE_PROC_IDLE | FS_ARCHIVE_PROC_SUSPENDING | FS_ARCHIVE_PROC_RESUME)
#define FS_ARCHIVE_PROC_ALL (~0)

typedef enum {
    FS_RESULT_SUCCESS = 0,
    FS_RESULT_FAILURE,
    FS_RESULT_BUSY,
    FS_RESULT_CANCELED,
    FS_RESULT_UNSUPPORTED,
    FS_RESULT_ERROR,
    FS_RESULT_PROC_ASYNC,
    FS_RESULT_PROC_DEFAULT,
    FS_RESULT_PROC_UNKNOWN
} FSResult;

struct FSFile;
struct FSArchive;

typedef FSResult (*FS_ARCHIVE_PROC_FUNC)(struct FSFile *, FSCommandType);
typedef FSResult (*FS_ARCHIVE_READ_FUNC)(struct FSArchive *p, void *dst, u32 pos, u32 size);
typedef FSResult (*FS_ARCHIVE_WRITE_FUNC)(struct FSArchive *p, const void *src, u32 pos, u32 size);

typedef struct FSFileLink {
    struct FSFile *prev;
    struct FSFile *next;
} FSFileLink;

typedef struct OSThreadQueue {
    struct OSThread *head;
    struct OSThread *tail;
} OSThreadQueue;

typedef struct FSArchiveFAT {
    u32 top;
    u32 bottom;
} FSArchiveFAT;

typedef struct FSArchiveFNT {
    u32 start;
    u16 index;
    u16 parent;
} FSArchiveFNT;

typedef struct FSArchive {
    union {
        char ptr[FS_ARCHIVE_NAME_LEN_MAX + 1];
        u32 pack;
    } name;                       /* 0x00 */
    struct FSArchive *next;       /* 0x04 */
    struct FSArchive *prev;       /* 0x08 */
    OSThreadQueue sync_q;         /* 0x0c */
    OSThreadQueue stat_q;         /* 0x14 */
    u32 flag;                     /* 0x1c: FS_ARCHIVE_FLAG_* */
    FSFileLink list;              /* 0x20: the queued commands */
    u32 base;                     /* 0x28 */
    u32 fat;                      /* 0x2c */
    u32 fat_size;                 /* 0x30 */
    u32 fnt;                      /* 0x34 */
    u32 fnt_size;                 /* 0x38 */
    u32 fat_bak;                  /* 0x3c */
    u32 fnt_bak;                  /* 0x40 */
    void *load_mem;               /* 0x44 */
    FS_ARCHIVE_READ_FUNC read_func;    /* 0x48 */
    FS_ARCHIVE_WRITE_FUNC write_func;  /* 0x4c */
    FS_ARCHIVE_READ_FUNC table_func;   /* 0x50 */
    FS_ARCHIVE_PROC_FUNC proc;    /* 0x54 */
    u32 proc_flag;                /* 0x58 */
} FSArchive;

typedef struct {
    struct FSArchive *arc;
    u16 own_id;
    u16 index;
    u32 pos;
} FSDirPos;

typedef struct {
    struct FSArchive *arc;
    u32 file_id;
} FSFileID;

typedef struct {
    union {
        FSFileID file_id;
        FSDirPos dir_id;
    };
    u32 is_directory;
    u32 name_len;
    char name[FS_FILE_NAME_MAX + 1];
} FSDirEntry;

typedef struct {
    FSDirPos pos;
} FSSeekDirInfo;

typedef struct {
    FSDirEntry *p_entry;
    BOOL skip_string;
} FSReadDirInfo;

typedef struct {
    FSDirPos pos;
    const char *path;
    BOOL find_directory;
    union {
        FSFileID *file;
        FSDirPos *dir;
    } result;
} FSFindPathInfo;

typedef struct {
    u8 *buf;
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
    void *dst;
    u32 len_org;
    u32 len;
} FSReadFileInfo;

typedef struct {
    const void *src;
    u32 len_org;
    u32 len;
} FSWriteFileInfo;

typedef struct FSFile {
    FSFileLink link;              /* 0x00 */
    struct FSArchive *arc;        /* 0x08 */
    u32 stat;                     /* 0x0c: FS_FILE_STATUS_* */
    FSCommandType command;        /* 0x10 */
    FSResult error;               /* 0x14 */
    OSThreadQueue queue[1];       /* 0x18 */
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
    } prop;                       /* 0x20 */
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
    } arg;                        /* 0x30 */
} FSFile;

static inline BOOL FS_IsBusy(volatile const FSFile *p_file)
{
    return (p_file->stat & FS_FILE_STATUS_BUSY) ? TRUE : FALSE;
}

static inline BOOL FS_IsCanceling(volatile const FSFile *p_file)
{
    return (p_file->stat & FS_FILE_STATUS_CANCEL) ? TRUE : FALSE;
}

static inline BOOL FS_IsSucceeded(volatile const FSFile *p_file)
{
    return (p_file->error == FS_RESULT_SUCCESS) ? TRUE : FALSE;
}

static inline BOOL FS_IsFile(volatile const FSFile *p_file)
{
    return (p_file->stat & FS_FILE_STATUS_IS_FILE) ? TRUE : FALSE;
}

static inline BOOL FS_IsDir(volatile const FSFile *p_file)
{
    return (p_file->stat & FS_FILE_STATUS_IS_DIR) ? TRUE : FALSE;
}

static inline BOOL FS_IsFileSyncMode(const volatile FSFile *p)
{
    return (p->stat & FS_FILE_STATUS_SYNC) ? TRUE : FALSE;
}

static inline BOOL FS_IsArchiveLoaded(volatile const FSArchive *p_arc)
{
    return (p_arc->flag & FS_ARCHIVE_FLAG_LOADED) ? TRUE : FALSE;
}

static inline BOOL FS_IsArchiveTableLoaded(volatile const FSArchive *p_arc)
{
    return (p_arc->flag & FS_ARCHIVE_FLAG_TABLE_LOAD) ? TRUE : FALSE;
}

static inline BOOL FS_IsArchiveSuspended(volatile const FSArchive *p_arc)
{
    return (p_arc->flag & FS_ARCHIVE_FLAG_SUSPEND) ? TRUE : FALSE;
}

static inline void FSi_CutFromListCore(FSFileLink *trg)
{
    FSFile *const nx = trg->next;
    FSFile *const pr = trg->prev;
    if (pr)
        pr->link.next = nx;
    if (nx)
        nx->link.prev = pr;
}

static inline void FSi_CutFromList(FSFile *elem)
{
    FSFileLink *const trg = &elem->link;
    FSi_CutFromListCore(trg);
    trg->next = trg->prev = NULL;
}

static inline void FSi_AppendToList(FSFile *elem, FSFile *list)
{
    FSFileLink *const trg = &elem->link;
    FSi_CutFromListCore(trg);
    {
        while (list->link.next)
            list = list->link.next;
        list->link.next = elem;
        trg->prev = list;
        trg->next = NULL;
    }
}

static inline BOOL FSi_IsSlash(u32 c)
{
    return (c == '/') || (c == '\\');
}

static inline BOOL FSi_IsArchiveRunning(const volatile FSArchive *p_arc)
{
    return ((p_arc->flag & FS_ARCHIVE_FLAG_RUNNING) != 0);
}

static inline BOOL FSi_IsArchiveCanceling(const volatile FSArchive *p_arc)
{
    return ((p_arc->flag & FS_ARCHIVE_FLAG_CANCELING) != 0);
}

static inline BOOL FSi_IsArchiveSuspending(const volatile FSArchive *p_arc)
{
    return ((p_arc->flag & FS_ARCHIVE_FLAG_SUSPENDING) != 0);
}

static inline BOOL FSi_IsArchiveAsync(const volatile FSArchive *p_arc)
{
    return ((p_arc->flag & FS_ARCHIVE_FLAG_IS_ASYNC) != 0);
}

static inline BOOL FSi_IsArchiveSync(const volatile FSArchive *p_arc)
{
    return ((p_arc->flag & FS_ARCHIVE_FLAG_IS_SYNC) != 0);
}

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void func_02001f10(OSThreadQueue *queue);   /* OS_SleepThread */
extern void OS_WakeupThread(OSThreadQueue *queue);
#define OS_SleepThread func_02001f10

#define BIT_MASK(n) ((1 << (n)) - 1)
#define ALIGN_MASK(a)   ((a) - 1)
#define ALIGN_BYTE(n, a)    (((u32)(n) + ALIGN_MASK(a)) & ~ALIGN_MASK(a))
static inline u8 MI_ReadByte(const void *address) { return *(const vu8 *)address; }
typedef int MIProcessor;
#define MI_PROCESSOR_ARM9 0
#define MI_PROCESSOR_ARM7 1
typedef u32 FSOverlayID;
typedef void (*FSOverlayInitFunc)(void);

typedef struct {
    u32 offset;
    u32 length;
} CARDRomRegion;

typedef struct {
    u32 id;                       /* 0x00 */
    u8 *ram_address;              /* 0x04 */
    u32 ram_size;                 /* 0x08 */
    u32 bss_size;                 /* 0x0c */
    FSOverlayInitFunc *sinit_init;        /* 0x10 */
    FSOverlayInitFunc *sinit_init_end;    /* 0x14 */
    u32 file_id;                  /* 0x18 */
    u32 compressed : 24;          /* 0x1c */
    u32 flag : 8;
} FSOverlayInfoHeader;

typedef struct {
    FSOverlayInfoHeader header;   /* 0x00 */
    MIProcessor target;           /* 0x20 */
    CARDRomRegion file_pos;       /* 0x24 */
} FSOverlayInfo;

#define FS_OVERLAY_FLAG_COMP      0x0001
#define FS_OVERLAY_FLAG_AUTH      0x0002
#define FS_OVERLAY_DIGEST_SIZE    20
#define HW_ROM_HEADER_BUF         0x027ffe00
#define HW_WM_BOOT_BUF            0x027ffc40
#define MB_TYPE_MULTIBOOT         2

static inline u32 FS_GetOverlayTotalSize(const FSOverlayInfo *p_ovi)
{
    return (u32)(p_ovi->header.ram_size + p_ovi->header.bss_size);
}

static inline u32 FS_GetOverlayImageSize(const FSOverlayInfo *p_ovi)
{
    return (u32)(p_ovi->header.ram_size);
}

static inline void *FS_GetOverlayAddress(const FSOverlayInfo *p_ovi)
{
    return p_ovi->header.ram_address;
}

static inline const CARDRomRegion *CARD_GetRomRegionOVT(MIProcessor target)
{
    return (target == MI_PROCESSOR_ARM9) ?
           (const CARDRomRegion *)((const u8 *)HW_ROM_HEADER_BUF + 0x50) :
           (const CARDRomRegion *)((const u8 *)HW_ROM_HEADER_BUF + 0x58);
}

static inline BOOL MB_IsMultiBootChild(void)
{
    return *(const u16 *)HW_WM_BOOT_BUF == MB_TYPE_MULTIBOOT;
}

static inline u32 FS_GetFileImageTop(const FSFile *p_file)
{
    return p_file->prop.file.top;
}

static inline u32 FS_GetLength(const FSFile *p_file)
{
    return p_file->prop.file.bottom - p_file->prop.file.top;
}

extern void FSi_ReleaseCommand(FSFile *p_file, FSResult ret);
extern void FSi_ExecuteAsyncCommand(FSFile *p_file);
extern FSFile *FSi_NextCommand(FSArchive *p_arc);
extern void FS_InitFile(FSFile *p_file);
extern BOOL FS_CloseFile(FSFile *p_file);
extern BOOL FS_OpenFileDirect(FSFile *p_file, FSArchive *p_arc, u32 image_top, u32 image_bottom, u32 file_index);
extern BOOL FS_OpenFileFast(FSFile *p_file, FSFileID file_id);
extern int OS_UnlockByWord_0x0200ae4c(FSFile *p_file, void *dst, s32 len);   /* FS_ReadFile */
#define FS_ReadFile OS_UnlockByWord_0x0200ae4c
extern FSFileID FS_GetOverlayFileID(const FSOverlayInfo *p_ovi);
extern u32 FSi_GetOverlayBinarySize(const FSOverlayInfo *p_ovi);
extern void FS_ClearOverlayImage(FSOverlayInfo *p_ovi);
extern BOOL FSi_LoadOverlayInfoCore(FSOverlayInfo *p_ovi, MIProcessor target, FSOverlayID id, FSArchive *p_arc, u32 offset_arm9, u32 len_arm9, u32 offset_arm7, u32 len_arm7);
extern BOOL FSi_CompareDigest(const u8 *spec_digest, void *src, int len);
extern BOOL FS_LoadOverlayInfo(FSOverlayInfo *p_ovi, MIProcessor target, FSOverlayID id);
extern BOOL FS_LoadOverlayImage(FSOverlayInfo *p_ovi);
extern void FS_StartOverlay(FSOverlayInfo *p_ovi);
extern BOOL FS_UnloadOverlayImage(FSOverlayInfo *p_ovi);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 data, u32 size);
#define MI_CpuClear8(dst, size) MI_CpuFill8((dst), 0, (size))
extern void DC_FlushRange(void *addr, u32 size);
extern void MIi_UncompressBackward(void *bottom);
extern void OS_Terminate(void);
#define OS_TPanic(...) OS_Terminate()
extern void func_0200baec(u8 *digest, const void *src, int len, const void *key, int key_len);   /* DGT_Hash2CalcHmac */
#define DGT_Hash2CalcHmac func_0200baec
extern CARDRomRegion data_02046324;   /* fsi_ovt9 */
extern CARDRomRegion data_0204632c;   /* fsi_ovt7 */
extern FSArchive data_02046334;       /* fsi_arc_rom */
#define fsi_ovt9 data_02046324
#define fsi_ovt7 data_0204632c
#define fsi_arc_rom data_02046334
/* fsi_digest_key_ptr / fsi_digest_key_len: two adjacent .data statics of fs_overlay.c (the
 * pointer names the 64-byte fsi_def_digest_key in .rodata), read together off one base. */
extern struct { const void *ptr; int len; } data_020422c4;
#define fsi_digest_key_ptr data_020422c4.ptr
#define fsi_digest_key_len data_020422c4.len
extern u8 data_02042af0[];            /* SDK_OVERLAY_DIGEST */
extern u8 data_0204429c[];            /* SDK_OVERLAY_DIGEST_END */
#define SDK_OVERLAY_DIGEST data_02042af0
#define SDK_OVERLAY_DIGEST_END data_0204429c

/* FSi_LoadOverlayInfoCore -- NitroSDK fs_overlay.c. */
BOOL FSi_LoadOverlayInfoCore (FSOverlayInfo *p_ovi, MIProcessor target, FSOverlayID id,
                            FSArchive *p_arc,
                            u32 offset_arm9, u32 len_arm9, u32 offset_arm7, u32 len_arm7)
{
    CARDRomRegion pr[1];
    u32 pos;

    if (target == MI_PROCESSOR_ARM9) {
        pr->offset = offset_arm9;
        pr->length = len_arm9;
    } else {
        pr->offset = offset_arm7;
        pr->length = len_arm7;
    }

    pos = (u32)id * sizeof(FSOverlayInfoHeader);

    if (pos >= pr->length) {
        return FALSE;
    } else {
        FSFile file[1];
        FS_InitFile(file);

        if (!FS_OpenFileDirect(file, p_arc, pr->offset + pos, pr->offset + pr->length, (u32) ~0)) {
            return FALSE;
        } else {
            if (FS_ReadFile(file, p_ovi, sizeof(FSOverlayInfoHeader)) !=
                sizeof(FSOverlayInfoHeader)) {
                (void)FS_CloseFile(file);
                return FALSE;
            }

            (void)FS_CloseFile(file);
            p_ovi->target = target;

            if (!FS_OpenFileFast(file, FS_GetOverlayFileID(p_ovi))) {
                return FALSE;
            } else {
                p_ovi->file_pos.offset = FS_GetFileImageTop(file);
                p_ovi->file_pos.length = FS_GetLength(file);
                (void)FS_CloseFile(file);
            }
        }
    }

    return TRUE;
}
