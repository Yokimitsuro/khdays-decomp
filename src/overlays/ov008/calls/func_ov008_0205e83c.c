extern int NNS_FndGetNextListObject(void *entry, int arg1);

int func_ov008_0205e83c(void *context, int index)
{
    int result = 0;

    if (NNS_FndGetNextListObject((char *)context + 0x304 + index * 12, result) != 0) {
        result = 1;
    }

    return result;
}
