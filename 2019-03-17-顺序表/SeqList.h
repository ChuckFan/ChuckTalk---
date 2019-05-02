#pragma once

/*
// 静态顺序表
// 顺序表的容量，是在静态时期确定（编译期间，代码里写死）
typedef struct SeqList {
	int array[100];	// 容量是 100
	int size;		// 顺序表实际存储的数据个数
}	SeqList;
*/

// 动态顺序表
// 容量在动态时期确定（运行时期）
typedef struct SeqList {
	int *array;
	int capacity;	// 容量:
	int size;		// 1. 有效数据的个数
					// 2. 尾插时，可用位置的下标
}	SeqList;

// 初始化
void SeqListInit(SeqList *ps, int capacity);

// 销毁
void SeqListDestroy(SeqList *ps);

// 增 / 删 / 改 /查
// 尾插
void SeqListPushBack(SeqList *ps, int v);
// 头插
void SeqListPushFront(SeqList *ps, int v);
// 根据 pos 下标做插入
void SeqListInsert(SeqList *ps, int pos, int v);

// 尾删
void SeqListPopBack(SeqList *ps);
// 头删
void SeqListPopFront(SeqList *ps);
// 根据 pos 下标做删除
void SeqListErase(SeqList *ps, int pos);

// 查找
int SeqListFind(SeqList *ps, int v);

// 更新
int SeqListModify(SeqList *ps, int pos, int v);

// 删除第一个遇到的 v
void SeqListRemove(SeqList *ps, int v);
// 删除所有遇到的 v
void SeqListRemoveAll(SeqList *ps, int v);