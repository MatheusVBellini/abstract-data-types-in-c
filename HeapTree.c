#include <stdio.h>
#include <stdlib.h>
#define HEAP_MAX_SIZE 100

typedef int elem;

typedef struct {
	int size;
	elem* values;
} Heap;

Heap newHeap() {
	Heap heap;
	heap.size = 0;
	heap.values = (elem*)malloc(HEAP_MAX_SIZE * sizeof(elem));

	return heap;
}

void deleteHeap(Heap** this) {
	free((*this)->values);
	(*this)->size = -1;
	
	Heap* tmp = (*this);
	free(tmp);

	*this = NULL;
}

int parentIndex(int current_index) {
	return (current_index - 1) / 2;
}

int leftChildIndex(int current_index) {
	return (2*current_index + 1);
}

int rightChildIndex(int current_index) {
	return (2*current_index + 2);
}

void _maxHeapify(Heap* this, int index) {
	int l = leftChildIndex(index);
	int r = rightChildIndex(index);
	int greatest = index;

	if (l < this->size && this->values[l] > this->values[greatest]) {
		greatest = l;
	}

	if (r < this->size && this->values[r] > this->values[greatest]) {
		greatest = r;
	}

	if (greatest != index) {
		elem tmp = this->values[greatest];
		this->values[greatest] = this->values[index];
		this->values[index] = tmp;
		_maxHeapify(this,greatest);
	}
}

void maxHeapify(Heap* this) {
	for (int i = this->size / 2 - 1; i >= 0; i--)
		_maxHeapify(this,i);
}

void _minHeapify(Heap* this, int index) {
	int l = leftChildIndex(index);
	int r = rightChildIndex(index);
	int smallest = index;

	if (l < this->size && this->values[l] < this->values[smallest]) {
		smallest = l;
	}

	if (r < this->size && this->values[r] < this->values[smallest]) {
		smallest = r;
	}

	if (smallest != index) {
		elem tmp = this->values[smallest];
		this->values[smallest] = this->values[index];
		this->values[index] = tmp;
		_maxHeapify(this,smallest);
	}
}

void minHeapify(Heap* this) {
	for (int i = this->size / 2 - 1; i >= 0; i--)
		_minHeapify(this,i);
}

void insert(Heap* this, elem x) {
	if (this->size >= HEAP_MAX_SIZE) {
		return;
	}

	this->values[this->size] = x;
	this->size++;
	maxHeapify(this);
}

void delete(Heap* this, elem x) {
	char found = '0';
	int index;

	for (index = 0; index < this->size; index++) {
		if (this->values[index] == x) {
			found = '1';
			break;
		}
	}
	
	// values not found
	if (found == '0') {
		return;
	}

	// values found
	for (int i = index; i < this->size - 1; i++) {
		this->values[i] = this->values[i+1];
	}

	this->size--;

	maxHeapify(this);
}

void toString(Heap this) {
	for (int i = 0; i < this.size; i++) {
		printf(" %d ", this.values[i]);
	}
	printf("\n");
}


int main() {
	Heap heap = newHeap();

	insert(&heap, 10);
	insert(&heap, 9);
	insert(&heap, 8);
	insert(&heap, 10);
	insert(&heap, 11);
	insert(&heap, 7);
	toString(heap);

	delete(&heap, 10);
	toString(heap);

	return 0;
}
