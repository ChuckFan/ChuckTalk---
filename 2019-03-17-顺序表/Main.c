#include "SeqList.h"

int main() {
#if 0//��������������Ϊ0
	SeqList *p = SeqListInit();
#endif

	SeqList seqlist;
	SeqListInit(&seqlist, 10);

	SeqListDestroy(&seqlist);
}