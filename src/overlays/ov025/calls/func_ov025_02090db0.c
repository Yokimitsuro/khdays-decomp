extern int NNS_FndGetNextListObject(void *entry, int arg1);

int func_ov025_02090db0(void *context, int index)
{
    int result = 0;

    if (NNS_FndGetNextListObject((char *)context + 0x304 + index * 12, result) != 0) {
        result = 1;
    }

    return result;
}
