#include "SeqList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// ȷ���������ã�����Ҫ���ݣ�ʲô������
// ��Ҫ���ݾ�����
// Ӱ�캯�����������ԣ����ⲿ�������� -> �ڲ���������
// O(n)
static void CheckCapacity(SeqList *ps) {
	//��������Ƿ���Ҫ���ݣ�
	//���ݵĻ���Ҫ��ԭ�������ݰ������������ƻ�
	if (ps->size < ps->capacity) {
		return;
	}//�������ò���Ҫ����

	// ��Ҫ����
	int newCapacity = ps->capacity * 2;//һ������Ϊԭ������2��
	int *newArray = (int *)malloc(sizeof(int)* newCapacity);
	assert(newArray != NULL);

	// ���
	for (int i = 0; i < ps->size; i++) {
		newArray[i] = ps->array[i];
	}

	// �ͷ��Ͽռ䣬���¿ռ�
	free(ps->array);
	ps->array = newArray;
	//���������������ֻ���м���ʱ������
	//֮��Ҫ�ظ���ʼ�����������
	ps->capacity = newCapacity;
}

void SeqListInit(SeqList *ps, int capacity) {//��ʼ��
	// ps �����Ǳ����ĵ�ַ
	assert(ps != NULL);//ȷ����ǰ��ǰ˳���Ϊ��
	//if (ps != NULL);
	ps->array = malloc(sizeof(int) * capacity);
	assert(ps->array != NULL);//ȷ��ָ�����һ������ָ�벻Ϊ��
	ps->size = 0;//��ʼ��ʱsizeΪ0
	ps->capacity = capacity;
}


void SeqListDestroy(SeqList *ps) {//����
	assert(ps != NULL);//�ṹ��ָ�벻ΪNULL
	assert(ps->array != NULL);//�ṹ��������ָ�벻ΪNULL

	// �ͷ� array �Ŀռ�
	free(ps->array);

	// ������
	ps->array = NULL;
	ps->size = 0;
	ps->capacity = 0;
}

// O(1)
void SeqListPushBack(SeqList *ps, int v) {//β��
	CheckCapacity(ps);
	ps->array[ps->size] = v;//��ΪsizeΪʵ����������һ���±���+1��
	//������size��Ϊ�±�պ�Ϊ����ĩβ�����һ��
	ps->size++;
}

// O(n)
void SeqListPushFront(SeqList *ps, int v) {//ͷ��
	CheckCapacity(ps);
	// i �������ǿռ���±�
	for (int i = ps->size; i >= 1; i--) {
		ps->array[i] = ps->array[i - 1];//��������β����ʼ�������Ųһ��
	}

	ps->array[0] = v;//Ȼ��v�������λ
	ps->size++;
}

// O(n)
void SeqListInsert(SeqList *ps, int pos, int v) {//��pos������v
	CheckCapacity(ps);
	assert(pos >= 0 && pos <= ps->size);//�ж�pos�ڲ���ԭ������
	// pos = 0 ����ͷ�壬pos = size ����β��

	// i ���ݵ��±�
	for (int i = ps->size - 1; i >= pos; i--) {
		ps->array[i + 1] =ps-> array[i];//�����һ��Ԫ�ؿ�ʼ���Ų����posΪֹ
	}

	ps->array[pos] = v;
	ps->size++;
}

// O(1)
void SeqListPopBack(SeqList *ps) {//βɾ
	assert(ps->size > 0);
	ps->size--;
}

// O(n)
void SeqListPopFront(SeqList *ps) {//ͷɾ
	assert(ps->size > 0);

	for (int i = 0; i <= ps->size - 2; i++) {//����λ��ʼ�������һ��Ԫ�ظ��ǵ�����λ�ã�
		//��Ϊ����i-1��Ԫ�أ�ͷɾ��n-2֮���û�����ֿɸ�����
		ps->array[i] = ps->array[i + 1];//����һλ����������λ
	}

	ps->size--;
}

// O(n)
void SeqListErase(SeqList *ps, int pos) {//��posλɾ�����������ɾ����v��һλ��ͬ
	// [0, size - 1]
	assert(pos >= 0 && pos < ps->size);//ȷ���ڷ�Χ��
	for (int i = pos + 1; i < ps->size; i++) {//�ֿ����䣬��size-1Ϊֹ������size
		ps->array[i - 1] = ps->array[i];
	}

	ps->size--;
}

int SeqListFind(SeqList *ps, int v) {//����v�ڼ�λ
	for (int i = 0; i < ps->size; i++) {//0��size-1���в���
		if (ps->array[i] == v) {
			return i;
		}
	}

	return -1;
}

int SeqListModify(SeqList *ps, int pos, int v) {//�޸�
	assert(pos >= 0 && pos < ps->size);
	ps->array[pos] = v;
}

// O(n)
void SeqListRemove(SeqList *ps, int v) {//��v����λ�Ƴ�����Ҫ�Ȳ���v��λ��
	int pos = SeqListFind(ps, v);
	if (pos == -1) {
		return;
	}

	SeqListErase(ps, pos);
}

void SeqListRemoveAll(SeqList *ps, int v) {//ɾ�����е�vԪ��
	int i, j;
	for (i = 0, j = 0; i < ps->size; i++) {
		if (ps->array[i] != v) {
			ps->array[j] = ps->array[i];
			j++;
		}
	}
	//i��jһ���ƶ�������vʱ��jͣ����i�������Ѱ����һ����v������Ȼ��j����
	//֮��i���ƶ�Ѱ�һ������Ÿ�j������󸲸�
	ps->size = j;
}