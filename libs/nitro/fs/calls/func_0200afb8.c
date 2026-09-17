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

typedef struct {
    u32 offset;
    u32 length;
} CARDRomRegion;
#define HW_ROM_HEADER_BUF         0x027ffe00
#define HW_WM_BOOT_BUF            0x027ffc40
#define MB_TYPE_MULTIBOOT         2

static inline BOOL MB_IsMultiBootChild(void)
{
    return *(const u16 *)HW_WM_BOOT_BUF == MB_TYPE_MULTIBOOT;
}

/* The ROM header's FNT / FAT regions (CARDRomHeader +0x40 / +0x48). */
static inline const CARDRomRegion *CARD_GetRomRegionFNT(void)
{
    return (const CARDRomRegion *)((const u8 *)HW_ROM_HEADER_BUF + 0x40);
}

static inline const CARDRomRegion *CARD_GetRomRegionFAT(void)
{
    return (const CARDRomRegion *)((const u8 *)HW_ROM_HEADER_BUF + 0x48);
}

/* fs_rom.c statics, one .bss block at data_0204631c: the card lock id, the default DMA channel
 * and the two overlay tables (fsi_ovt9 = data_02046324, fsi_ovt7 = data_0204632c). */
extern struct {
    u32 card_lock_id;             /* 0x00: fsi_card_lock_id */
    u32 default_dma_no;           /* 0x04: fsi_default_dma_no */
    CARDRomRegion ovt9;           /* 0x08: fsi_ovt9 */
    CARDRomRegion ovt7;           /* 0x10: fsi_ovt7 */
} data_0204631c;
#define fsi_card_lock_id data_0204631c.card_lock_id
#define fsi_default_dma_no data_0204631c.default_dma_no
#define fsi_ovt9 data_0204631c.ovt9
#define fsi_ovt7 data_0204631c.ovt7
extern FSArchive data_02046334;   /* fsi_arc_rom */
#define fsi_arc_rom data_02046334
extern const char data_020422c0[];   /* "rom", the ROM archive's name */

extern u32 OS_GetLockID(void);
extern void CARD_Init(void);
extern void FS_InitArchive(FSArchive *p_arc);
extern BOOL FS_RegisterArchiveName(FSArchive *p_arc, const char *name, u32 name_len);
extern void FS_SetArchiveProc(struct FSArchive *p_arc, FS_ARCHIVE_PROC_FUNC proc, u32 flags);
extern BOOL FS_LoadArchive(FSArchive *p_arc, u32 base, u32 fat, u32 fat_size, u32 fnt, u32 fnt_size,
                           FS_ARCHIVE_READ_FUNC read_func, FS_ARCHIVE_WRITE_FUNC write_func);
extern FSResult FSi_EmptyArchiveProc(FSFile *p_file, FSCommandType cmd);
extern FSResult FSi_RomArchiveProc(FSFile *p_file, FSCommandType cmd);
extern FSResult func_0200aeec(FSArchive *p_arc, void *dst, u32 src, u32 len);         /* FSi_ReadRomCallback */
#define FSi_ReadRomCallback func_0200aeec
extern FSResult func_0200af34(FSArchive *p_arc, const void *src, u32 dst, u32 len);   /* FSi_WriteDummyCallback */
#define FSi_WriteDummyCallback func_0200af34
extern FSResult func_0200afa8(FSArchive *p_arc, void *dst, u32 src, u32 len);         /* FSi_ReadDummyCallback */
#define FSi_ReadDummyCallback func_0200afa8

/* func_0200afb8 -- NitroSDK fs_file.c: FS_Init. In this SDK version FS_Init(default_dma_no) is the whole
 * ROM archive setup (4.x splits it as FS_Init -> FSi_InitRom): record the DMA channel and the card
 * lock, register the "rom" archive and load its FAT/FNT from the ROM header (dummy archive when
 * booted as a multiboot child). */
void func_0200afb8 (u32 default_dma_no)
{
	fsi_default_dma_no = default_dma_no;
	fsi_card_lock_id = OS_GetLockID();
	fsi_ovt9.offset = 0;
	fsi_ovt9.length = 0;
	fsi_ovt7.offset = 0;
	fsi_ovt7.length = 0;

	CARD_Init();

	FS_InitArchive(&fsi_arc_rom);
	(void)FS_RegisterArchiveName(&fsi_arc_rom, data_020422c0, 3);

	if (MB_IsMultiBootChild()) {
		fsi_ovt9.offset = (u32) ~0;
		fsi_ovt9.length = 0;
		fsi_ovt7.offset = (u32) ~0;
		fsi_ovt7.length = 0;

		FS_SetArchiveProc(&fsi_arc_rom, FSi_EmptyArchiveProc, (u32)FS_ARCHIVE_PROC_ALL);
		(void)FS_LoadArchive(&fsi_arc_rom, 0x00000000,
		                     0, 0, 0, 0, FSi_ReadDummyCallback, FSi_WriteDummyCallback);
	} else {
		const CARDRomRegion *const fnt = CARD_GetRomRegionFNT();
		const CARDRomRegion *const fat = CARD_GetRomRegionFAT();

		FS_SetArchiveProc(&fsi_arc_rom, FSi_RomArchiveProc,
		                  FS_ARCHIVE_PROC_WRITEFILE |
		                  FS_ARCHIVE_PROC_ACTIVATE | FS_ARCHIVE_PROC_IDLE);

		if ((fnt->offset == 0xFFFFFFFF) || (fnt->offset == 0x00000000) ||
		    (fat->offset == 0xFFFFFFFF) || (fat->offset == 0x00000000)) {
		} else {
			(void)FS_LoadArchive(&fsi_arc_rom, 0x00000000,
			                     fat->offset, fat->length,
			                     fnt->offset, fnt->length,
			                     FSi_ReadRomCallback, FSi_WriteDummyCallback);
		}
	}

}
