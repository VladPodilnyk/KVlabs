/*
* file cArray.cpp
* cArray methods definition
* written 25/02/16
*/
#include "cArray.h"

int cArray::GetSize() const {
	return size;
}

int cArray::GetCount() const {
	return count;
}

int cArray::GetUpperBound() const {
	return count - 1;
}

bool cArray::IsEmpty() const {
	if (NULL == buf || 0 == count)
		return 0;
	return 1;
}

void cArray::SetSize(int NewSize) {
	int *tmp;
	if (!buf) {
		buf = new (int[NewSize]);
		size = NewSize;
		return;
	}
	if (NewSize == 0) {
		RemoveAll();
		return;
	}
	tmp = buf;
	buf = new (int[NewSize]);
	if (NewSize < size)
		for (int i = 0; i < NewSize; i++) 
			buf[i] = tmp[i];
	else
		for (int i = 0; i < size; i++)
			buf[i] = tmp[i];

	size = NewSize;
	if (size < count)
		count = size;
	delete []tmp;
	return;
}

void cArray::FreeExtra() {
	int *tmp;
	if (!buf || 0 == size - count)
		return;
	tmp = buf;
	buf = new (int[count]);
	for (int i = 0; i < count; i++)
		buf[i] = tmp[i];
	size = count;
	delete []tmp;
	return;
}

void cArray::RemoveAll() {
	if (!buf)
		return;
	delete []buf;
	buf = NULL;
	size = 0;
	count = 0;
	return;
}

int& cArray::operator [] (int indx) {
	if (indx < count && indx > -1) 
		return buf[indx];
}

int cArray::GetAt(int indx) const {
	if (indx < count && indx > -1)
		return buf[indx];
}

void cArray::SetAt(int n, int indx) {
	if (-1 == indx) {
		buf[0] = n;
		return;
	}
	if (indx <= count - 1  && indx > -1)
		buf[indx] = n;
	return;
}

void cArray::Add(int n) {
	int *tmp;
	int i;
	if (size > count) {
		count++;
		SetAt(n, count - 1);
		return;
	}
	tmp = buf;
	size += GROWBY;
	buf = new int[size];
	for (i = 0; i < count; i++)
		buf[i] = tmp[i];
	buf[count] = n;
	count++;
	delete []tmp;
	return;
}

void cArray::Append(cArray *ar) {
	int i, j, k;
	int *tmp;
	if (!buf || 0 == ar->size)
		return;
	if (ar->count <= size - count) {
		for (i = count - 1, j = 0; j < ar->count; i++, j++)
			buf[i] = ar->buf[j];
		count += ar->count;
	}
	else {
		k = (int)ceil(ar->count / float(GROWBY));
		tmp = buf;
		size = size + k * GROWBY;
		buf = new int[size];
		for (i = 0; i < count; i++)
			buf[i] = tmp[i];
		for (i = count, j = 0; j < ar->count; i++, j++)
			buf[i] = ar->buf[j];
		count += ar->count;
		delete []tmp;
	}

	return;
}

void cArray::Copy(cArray *ar) {
	int *tmp;
	int i,k;
	if (0 == ar->size)
		return;
	if (ar->count <= size) {
		for (i = 0; i < ar->count; i++)
			buf[i] = ar->buf[i];
		count = ar->count;
	}
	else {
		k = (int)ceil(ar->count / float(GROWBY));
		tmp = buf;
		size = size + k * GROWBY;
		buf = new int[size];
		for (i = 0; i < ar->count; i++)
			buf[i] = ar->buf[i];
		count = ar->count;
	}
	return;
}

void cArray::InsertAt(int n, int indx) {
	int i;
	if (indx > count - 1 || size == count)
		return;
	for (i = count; i > indx; i--)
		buf[i] = buf[i - 1];
	buf[i] = n;
	count++;
	return;
}

void cArray::RemoveAt(int indx) {
	int i;
	if (indx > count - 1)
		return;
	for (i = indx + 1; i < count; i++)
		buf[i - 1] = buf[i];
	count--;
}

