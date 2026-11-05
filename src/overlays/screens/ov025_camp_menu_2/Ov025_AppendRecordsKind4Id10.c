/* Walks the record list appending the records of kind 4 with id (+2) 10. */

extern unsigned short Ov025_WalkRecordsAppendMatching();
extern int Ov025_RecordFilter_TutorialRow();

int Ov025_AppendRecordsKind4Id10(int arg0, int arg1, int arg2) {
    return Ov025_WalkRecordsAppendMatching(arg0, arg1, arg2, Ov025_RecordFilter_TutorialRow);
}
