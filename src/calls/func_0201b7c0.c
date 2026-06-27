typedef struct { unsigned int arc; unsigned int file_id; } FSFileID;

typedef struct {
    char pad[0x7c];
    unsigned int field_7c;
    unsigned int field_80;
} S_0201b7c0;

extern S_0201b7c0 *data_0204ad4c;

void func_0201b7c0(FSFileID *id) {
    *id = *(FSFileID *)&data_0204ad4c->field_7c;
}
