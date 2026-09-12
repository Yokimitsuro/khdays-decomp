typedef struct FSFile {
    char pad[0x24];
    int imageTop;      /* 0x24 -- start of the file's data range */
    int imageBot;       /* 0x28 -- end of the file's data range */
    int curOffset;       /* 0x2c -- current seek position */
} FSFile;

int FS_SeekFile(FSFile *file, int offset, int origin) {
    switch (origin) {
    case 0:
        offset = offset + file->imageTop;
        break;
    case 1:
        offset = offset + file->curOffset;
        break;
    case 2:
        offset = offset + file->imageBot;
        break;
    default:
        return 0;
    }

    if (offset < file->imageTop) offset = file->imageTop;
    if (offset > file->imageBot) offset = file->imageBot;
    file->curOffset = offset;
    return 1;
}
