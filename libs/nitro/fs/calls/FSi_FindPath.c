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
    FSFile *const pr = trg->prev;
    FSFile *const nx = trg->next;
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

typedef struct {
    FSArchive *arc;
    u32 pos;
} FSiSyncReadParam;
#define BIT_MASK(n) ((1 << (n)) - 1)
static inline u8 MI_ReadByte(const void *address) { return *(const vu8 *)address; }
static inline void MI_WriteByte(void *address, u8 value) { *(vu8 *)address = value; }
extern FSResult FSi_ReadTable(FSiSyncReadParam *p, void *dst, u32 len);
extern void FSi_SeekDirDirect(FSFile *p_dir, u32 id);
extern int FSi_StrNICmp(const char *str1, const char *str2, u32 len);
extern FSResult FSi_TranslateCommand(FSFile *p_file, FSCommandType command);
extern void FSi_ReleaseCommand(FSFile *p_file, FSResult ret);
extern void FSi_ExecuteAsyncCommand(FSFile *p_file);
extern FSFile *FSi_NextCommand(FSArchive *p_arc);
extern BOOL func_0200a4ac(FSFile *p_file, FSCommandType command);   /* FSi_SendCommand */
#define FSi_SendCommand func_0200a4ac
extern void FS_InitFile(FSFile *p_file);
extern BOOL FS_CloseFile(FSFile *p_file);
extern BOOL FS_OpenFileDirect(FSFile *p_file, FSArchive *p_arc, u32 image_top, u32 image_bottom, u32 file_index);
extern BOOL FS_OpenFileFast(FSFile *p_file, FSFileID file_id);
extern int OS_UnlockByWord_0x0200ae4c(FSFile *p_file, void *dst, s32 len);   /* FS_ReadFile */
#define FS_ReadFile OS_UnlockByWord_0x0200ae4c
extern BOOL FS_WaitAsync(FSFile *p_file);
extern FSArchive *FS_FindArchive(const char *name, int name_len);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 data, u32 size);
#define MI_CpuClear8(dst, size) MI_CpuFill8((dst), 0, (size))

extern FSDirPos data_0204630c;   /* current_dir_pos */
#define current_dir_pos data_0204630c
/* FSi_FindPath -- NitroSDK fs_file.c. */
BOOL FSi_FindPath (FSFile *p_dir, const char *path, FSFileID *p_file_id, FSDirPos *p_dir_pos)
{
	FSDirPos pos;


	if (FSi_IsSlash(MI_ReadByte(path))) {

		pos.arc = current_dir_pos.arc;
		pos.own_id = 0;
		pos.pos = 0;
		pos.index = 0;
		++path;
	} else {
		int i;

		pos = current_dir_pos;
		for (i = 0; i <= FS_ARCHIVE_NAME_LEN_MAX; ++i) {
			u32 c = MI_ReadByte(path + i);
			if (!c || FSi_IsSlash(c))
				break;
			else if (c == ':') {
				FSArchive *const p_arc = FS_FindArchive(path, i);
				if (!p_arc) {
					return FALSE;
				} else if (!FS_IsArchiveLoaded(p_arc))   {
					return FALSE;
				}

				pos.arc = p_arc;
				pos.pos = 0;
				pos.index = 0;
				pos.own_id = 0;
				path += i + 1;

				if (FSi_IsSlash(MI_ReadByte(path)))
					++path;
				break;
			}
		}
	}

	p_dir->arc = pos.arc;
	p_dir->arg.findpath.path = path;
	p_dir->arg.findpath.pos = pos;

	if (p_dir_pos) {
		p_dir->arg.findpath.find_directory = TRUE;
		p_dir->arg.findpath.result.dir = p_dir_pos;
	} else {
		p_dir->arg.findpath.find_directory = FALSE;
		p_dir->arg.findpath.result.file = p_file_id;
	}

	return FSi_SendCommand(p_dir, FS_COMMAND_FINDPATH);
}
