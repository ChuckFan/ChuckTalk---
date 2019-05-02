#include "SeqList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 确保容量够用，不需要扩容，什么都不做
// 需要扩容就扩容
// 影响函数的链接属性，从外部链接属性 -> 内部链接属性
// O(n)
static void CheckCapacity(SeqList *ps) {
	//检查容量是否需要扩容，
	//扩容的话需要把原数组内容搬至新数组再移回
	if (ps->size < ps->capacity) {
		return;
	}//容量够用不需要扩容

	// 需要扩容
	int newCapacity = ps->capacity * 2;//一般扩容为原容量的2倍
	int *newArray = (int *)malloc(sizeof(int)* newCapacity);
	assert(newArray != NULL);

	// 搬家
	for (int i = 0; i < ps->size; i++) {
		newArray[i] = ps->array[i];
	}

	// 释放老空间，绑定新空间
	free(ps->array);
	ps->array = newArray;
	//新数组和新容量都只是中间临时变量，
	//之后都要回给初始的数组和容量
	ps->capacity = newCapacity;
}

void SeqListInit(SeqList *ps, int capacity) {//初始化
	// ps 期望是变量的地址
	assert(ps != NULL);//确保当前当前顺序表不为空
	//if (ps != NULL);
	ps->array = malloc(sizeof(int) * capacity);
	assert(ps->array != NULL);//确保指向的下一个数组指针不为空
	ps->size = 0;//初始化时size为0
	ps->capacity = capacity;
}


void SeqListDestroy(SeqList *ps) {//销毁
	assert(ps != NULL);//结构体指针不为NULL
	assert(ps->array != NULL);//结构体中数组指针不为NULL

	// 释放 array 的空间
	free(ps->array);

	// 锦上添花
	ps->array = NULL;
	ps->size = 0;
	ps->capacity = 0;
}

// O(1)
void SeqListPushBack(SeqList *ps, int v) {//尾插
	CheckCapacity(ps);
	ps->array[ps->size] = v;//因为size为实际数组的最后一个下标再+1，
	//所以用size作为下标刚好为数组末尾新添加一个
	ps->size++;
}

// O(n)
void SeqListPushFront(SeqList *ps, int v) {//头插
	CheckCapacity(ps);
	// i 代表含义是空间的下标
	for (int i = ps->size; i >= 1; i--) {
		ps->array[i] = ps->array[i - 1];//从新增的尾部开始依次向后挪一个
	}

	ps->array[0] = v;//然后将v添加至首位
	ps->size++;
}

// O(n)
void SeqListInsert(SeqList *ps, int pos, int v) {//在pos处插入v
	CheckCapacity(ps);
	assert(pos >= 0 && pos <= ps->size);//判断pos在不在原区间内
	// pos = 0 就是头插，pos = size 就是尾插

	// i 数据的下标
	for (int i = ps->size - 1; i >= pos; i--) {
		ps->array[i + 1] =ps-> array[i];//从最后一个元素开始向后挪，至pos为止
	}

	ps->array[pos] = v;
	ps->size++;
}

// O(1)
void SeqListPopBack(SeqList *ps) {//尾删
	assert(ps->size > 0);
	ps->size--;
}

// O(n)
void SeqListPopFront(SeqList *ps) {//头删
	assert(ps->size > 0);

	for (int i = 0; i <= ps->size - 2; i++) {//从首位开始逐个将后一个元素覆盖到自身位置，
		//因为本身i-1个元素，头删后到n-2之后就没有数字可覆盖了
		ps->array[i] = ps->array[i + 1];//将后一位覆盖至自身位
	}

	ps->size--;
}

// O(n)
void SeqListErase(SeqList *ps, int pos) {//将pos位删除，与下面的删除数v那一位不同
	// [0, size - 1]
	assert(pos >= 0 && pos < ps->size);//确保在范围内
	for (int i = pos + 1; i < ps->size; i++) {//又开区间，到size-1为止，并非size
		ps->array[i - 1] = ps->array[i];
	}

	ps->size--;
}

int SeqListFind(SeqList *ps, int v) {//查找v第几位
	for (int i = 0; i < ps->size; i++) {//0到size-1进行查找
		if (ps->array[i] == v) {
			return i;
		}
	}

	return -1;
}

int SeqListModify(SeqList *ps, int pos, int v) {//修改
	assert(pos >= 0 && pos < ps->size);
	ps->array[pos] = v;
}

// O(n)
void SeqListRemove(SeqList *ps, int v) {//将v所在位移除，需要先查找v的位置
	int pos = SeqListFind(ps, v);
	if (pos == -1) {
		return;
	}

	SeqListErase(ps, pos);
}

void SeqListRemoveAll(SeqList *ps, int v) {//删除所有的v元素
	int i, j;
	for (i = 0, j = 0; i < ps->size; i++) {
		if (ps->array[i] != v) {
			ps->array[j] = ps->array[i];
			j++;
		}
	}
	//i、j一起移动，遇到v时，j停留，i继续向后寻找下一个非v的数，然后将j覆盖
	//之后i再移动寻找回来接着给j依次向后覆盖
	ps->size = j;
}