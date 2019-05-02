#include "SeqList.h"

int main() {
#if 0//下面条件满足则为0
	SeqList *p = SeqListInit();
#endif

	SeqList seqlist;
	SeqListInit(&seqlist, 10);

	SeqListDestroy(&seqlist);
}