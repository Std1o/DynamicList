#include <iostream>
#include <sstream>
#include <fstream>

struct node {
	node* next;
	double   val;
	node(double v) :next(NULL), val(v) {}
	node() :next(NULL), val() {}
};

struct slist {
	node* head, *tail;
	int size = 0;
};

void  slist_init(slist* ls) { ls->head = ls->tail = NULL; }
node* slist_push_front(slist* ls, double val);
node* slist_push_back(slist* ls, double val);
node* slist_insert(slist* ls, node* p, double val);
node* remove(slist* ls, node* p);
node *findeNode(node *L, int p);
void push_2_items_before_last(slist* ls, double val1, double val2);
void delete_first_negative_value(slist* ls, node* p);
double removeMaxValue(slist* ls);
void showList(slist ls);

void createList(slist* ls, int n) {
	slist_init(ls);
	double val = 0;
	for (int i = 0; i < n; i++) {
		std::cin >> val;
		slist_push_front(ls, val);
	}
}

int main(void) {
	setlocale(LC_ALL, "RUS");
	node* p;
	slist ls;
	createList(&ls, 3);
	showList(ls);

	std::cout << std::endl << "Afer deleting: ";
	remove(&ls, ls.head);
	showList(ls);

	std::cout << std::endl << "В позиции 0: " << findeNode(ls.head, 0)->val;
	std::cout << std::endl << "В позиции 1: " << findeNode(ls.head, 1)->val << std::endl;

	push_2_items_before_last(&ls, 88, 99);
	showList(ls);

	delete_first_negative_value(&ls, ls.head);

	std::cout << std::endl << "After deleting first nagative value: ";
	showList(ls);

	slist_push_back(&ls, removeMaxValue(&ls));
	showList(ls);

	std::cin.get();
	return 0;
}

void showList(slist ls) {
	for (node* p = ls.head; p != NULL; p = p->next)
		std::cout << p->val << ' ';
	std::cout << std::endl << "Size = " << ls.size;
}

double removeMaxValue(slist* ls) {
	double maxVal = ls->head->val;
	int maxValPos = 0;
	int i = 0;
	for (node* p = ls->head; p != NULL; p = p->next) {
		if (p->val > maxVal) {
			maxVal = p->val;
			maxValPos = i;
		}
		i++;
	}
	remove(ls, findeNode(ls->head, maxValPos));
	std::cout << std::endl << "max: " << maxVal << std::endl << "После перемещения: ";
	return maxVal;
}

void push_2_items_before_last(slist* ls, double val1, double val2) {
	node* pos1 = findeNode(ls->head, ls->size - 1);
	node* pos2 = findeNode(ls->head, ls->size - 1);
	slist_insert(ls, pos1, val1);
	slist_insert(ls, pos2, val2);
}

void delete_first_negative_value(slist* ls, node* pos) {
	for (pos; pos != NULL; pos = pos->next)
		if (pos->val < 0) {
			remove(ls, pos);
			return;
		}
}

node *findeNode(node *L, int p) {
	int i = 0;
	node *q = L;
	while (q != 0 && i < p) {
		i++; q = q->next;
	}
	return q;
}

//вставка в начало списка
node* slist_push_front(slist* ls, double val) {
	node* p = new node(val);
	if (ls->head == NULL)
		ls->head = ls->tail = p;
	else {
		p->next = ls->head;
		ls->head = p;
	}
	ls->size++;
	return p;
}

//вставка в конец списка
node* slist_push_back(slist* ls, double val) {
	node* p = new node(val);
	if (ls->head == NULL)
		ls->head = ls->tail = p;
	else {
		ls->tail->next = p;
		ls->tail = p;
	}
	ls->size++;
	return p;
}

//вставка в произвольное место
node* slist_insert(slist* ls, node* pos, double val) {
	node* p, *i = ls->head, *j = ls->head;
	while (i != pos) {
		j = i;
		i = i->next;
	}

	if (i == ls->head)
		p = slist_push_front(ls, val);
	else {
		p = new node(val);
		j->next = p;
		p->next = i;
	}
	ls->size++;
	return p->next;
}

//удаление элемента
node* remove(slist* ls, node* pos) {
	node* p, *i = ls->head, *j = ls->head;
	while (i != pos) {
		j = i;
		i = i->next;
	}

	p = pos->next;
	if (i == ls->head) {
		ls->head = ls->head->next;
		if (ls->head == NULL)
			ls->tail = NULL;
	}
	else {
		j->next = i->next;
		if (pos == ls->tail)
			ls->tail = j;
	}
	delete pos;
	ls->size--;
	return p;
}