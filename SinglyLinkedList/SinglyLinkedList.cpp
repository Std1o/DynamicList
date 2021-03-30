#include <iostream>

struct node {
	node* next;
	double   val;
	node(double v) :next(NULL), val(v) {}
};

struct slist {
	node* head, *tail;
	int size = 0;
};

void  init_list(slist* ls) { ls->head = ls->tail = NULL; }
node* push_front(slist* ls, double val);
node* push_back(slist* ls, double val);
node* insert(slist* ls, node* p, double val);
node* remove(slist* ls, node* p);
node *findNode(node *L, int p);
void push_2_items_before_last(slist* ls, double val1, double val2);
void delete_first_negative_value(slist* ls, node* p);
double remove_max_value(slist* ls);
void show_list(slist ls);
void create_list(slist* ls, int n);

using namespace std;

int main(void) {
	setlocale(LC_ALL, "RUS");
	node* p;
	slist ls;

	cout << "Element count: ";
	int count = 0;
	cin >> count;
	cout << "Enter " << count << " items:\n";
	create_list(&ls, count);
	show_list(ls);

	double item1 = 0, item2 = 0;
	cout << "Enter 2 items:\n";
	cin >> item1 >> item2;
	push_2_items_before_last(&ls, item1, item2);
	show_list(ls);

	delete_first_negative_value(&ls, ls.head);
	cout << endl << "After deleting first nagative value: \n";
	show_list(ls);

	//moving the maximum value to the end of the list
	push_back(&ls, remove_max_value(&ls));
	show_list(ls);

	cin.get();
	return 0;
}

void create_list(slist* ls, int n) {
	init_list(ls);
	double val = 0;
	for (int i = 0; i < n; i++) {
		cin >> val;
		push_front(ls, val);
	}
}

void show_list(slist ls) {
	cout << "Current list: ";
	for (node* p = ls.head; p != NULL; p = p->next)
		cout << p->val << ' ';
	cout << endl;
}

double remove_max_value(slist* ls) {
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
	remove(ls, findNode(ls->head, maxValPos));
	cout << endl << "Max value: " << maxVal << endl << "After moving:\n";
	return maxVal;
}

void push_2_items_before_last(slist* ls, double val1, double val2) {
	node* pos1 = findNode(ls->head, ls->size - 1);
	node* pos2 = findNode(ls->head, ls->size - 1);
	insert(ls, pos1, val1);
	insert(ls, pos2, val2);
}

void delete_first_negative_value(slist* ls, node* pos) {
	for (pos; pos != NULL; pos = pos->next)
		if (pos->val < 0) {
			remove(ls, pos);
			return;
		}
}

node *findNode(node *L, int p) {
	int i = 0;
	node *q = L;
	while (q != 0 && i < p) {
		i++; q = q->next;
	}
	return q;
}

//вставка в начало списка
node* push_front(slist* ls, double val) {
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
node* push_back(slist* ls, double val) {
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
node* insert(slist* ls, node* pos, double val) {
	node* p, *i = ls->head, *j = ls->head;
	while (i != pos) {
		j = i;
		i = i->next;
	}

	if (i == ls->head)
		p = push_front(ls, val);
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