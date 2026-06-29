extern void (*data_0204bd88[])(void *ptr);
extern void *data_0204bd94[];

void func_020208a4(int index) {
    void (*callback)(void *ptr) = data_0204bd88[index];

    if (callback != 0) {
        callback(data_0204bd94[index]);
    }
}
