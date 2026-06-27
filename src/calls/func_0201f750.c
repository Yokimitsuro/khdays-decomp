extern void *func_0201e4c8(void);
extern void OS_SendMessage(void *queue, void *message, int flags);

extern int data_0204bc1c;

typedef struct {
    char _0[4];
    int type;
    unsigned short id0;
    unsigned short id1;
    int arg2;
    int arg3;
} Message_0201f750;

void func_0201f750(unsigned short id0, unsigned short id1, int arg2, int arg3)
{
    Message_0201f750 *msg = func_0201e4c8();

    if (msg == 0)
        return;

    msg->type = 3;
    msg->id0 = id0;
    msg->id1 = id1;
    msg->arg2 = arg2;
    msg->arg3 = arg3;
    OS_SendMessage(&data_0204bc1c, msg, 1);
}
