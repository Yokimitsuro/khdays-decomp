/* Walks the record list appending the records whose kind byte (+0x23) is 0. */

extern unsigned short Ov025_WalkRecordsAppendMatching();
extern int Ov025_RecordFilter_StoryRow();

int Ov025_AppendRecordsKindZero(int arg0, int arg1, int arg2) {
    return Ov025_WalkRecordsAppendMatching(arg0, arg1, arg2, Ov025_RecordFilter_StoryRow);
}
