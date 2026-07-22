/* Publish the value into the active slot of the 0x14-stride table, notifying
 * func_ov002_02066cb0 first when the caller asks for it. The slot index lives at
 * +4 of the context at data_ov002_0207f99c. */
typedef struct {
    int nValue;
    char pad04[0x10];
} Ov002TableSlot;

extern void func_ov002_02066cb0(int value, int notify);

extern int data_ov002_0207f99c;
extern Ov002TableSlot data_ov002_0207f9a4[];

void func_ov002_02065904(int value, int notify) {
    int ctx = data_ov002_0207f99c;

    if (notify != 0) {
        func_ov002_02066cb0(value, notify);
    }

    data_ov002_0207f9a4[*(int *)(ctx + 4)].nValue = value;
}
