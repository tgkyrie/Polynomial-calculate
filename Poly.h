#pragma once
#include<iostream>
using namespace std;
class Poly
{
public:
	Poly();
	Poly(double k);
	Poly(double c,char x);
	Poly(const Poly& P);
	Poly(Poly&& P);
	~Poly();
	Poly operator+(Poly P);
	Poly operator-(Poly P);
	Poly operator*(Poly P);
	Poly operator=(Poly& P);
	Poly operator=(Poly&& P);
	//friend ostream& operator<<(ostream& os, Poly P);
	friend istream& operator>>(ostream& is, Poly& P);
	int int_part();
	void remove_zero();
private:
	struct Node
	{
		double coeff;
		int times;
		Node* next;
		Node(double c,int t,Node* p=nullptr):coeff(c),times(t),next(p){}
	};
	Node* head;
	void insert(Node* &n1);
	void insert(double c, int t);
	void deleteNode();
public:
	Node* gethead() { return head; }
};



Poly::Poly()
{
	Node* n1 = new Node(0, 0);
	head = n1;
}
Poly::Poly(double k){
	Node* n1 = new Node(0, 0);
	head = n1;
	head->next = new Node(k, 0);
}

Poly::Poly(double c,char x) {
	Node* n1 = new Node(0, 0);
	head = n1;
	if (x == 'x') {
		head->next = new Node(c, 1);
	}
}
Poly::Poly(const Poly& P) {
	head = new Node(0, 0);
	Node* p1=head, *p2 = P.head;
	while (p2->next != nullptr) {
		p2 = p2->next;
		p1->next = new Node(p2->coeff, p2->times);
		p1 = p1->next;
	}
}

Poly::Poly(Poly&& P) {
	head = new Node(0, 0);
	Node* p1 = head, * p2 = P.head;
	while (p2->next != nullptr) {
		p2 = p2->next;
		p1->next = new Node(p2->coeff, p2->times);
		p1 = p1->next;
	}
}
//Éî¿½±´

Poly::~Poly()
{
	deleteNode();
}

void Poly::insert(Node* &n1) {
	Node* p = head;
	while (p->next!=nullptr&&p->next->times>n1->times)
	{
		p = p->next;
	}
	if (p->next == nullptr || p->next->times < n1->times) {
		Node* n = new Node(n1->coeff, n1->times, p->next);
		p->next = n;
	}
	else 
		p->next->coeff += n1->coeff;
}


void Poly::remove_zero() {
	Node* p = head;
	while (p->next != nullptr) {
		if (p->next->coeff == 0) {
			Node* old = p->next;
			p->next = old->next;
			delete old;
			old = nullptr;
		}
		else p = p->next;
	}
}

int Poly::int_part() {
	Node* p = head;
	int ret=0;
	while (p->next != nullptr) {
		if (p->next->times == 0) {
			ret = p->next->coeff;
			break;
		}
		p = p->next;
	}
	return ret;
}

void Poly::deleteNode() {
	Node* p1 = nullptr;
	while (head != nullptr) {
		p1 = head;
		head = head->next;
		delete p1;
	}
	head = nullptr;
}

Poly Poly::operator+(Poly P) {
	Node* p1=this->head,*p2 = P.head;
	Poly ret;
	while (p1->next != nullptr)
	{
		p1 = p1->next;
		Node* p3 = new Node(p1->coeff, p1->times);
		ret.insert(p3);
		delete p3;
		p3 = nullptr;
	}
	while (p2->next!=nullptr)
	{
		p2 = p2->next;
		Node* p3 = new Node(p2->coeff, p2->times);
		ret.insert(p3);
		delete p3;
		p3 = nullptr;
	}
	ret.remove_zero();
	return ret;
}
Poly operator+(double k, Poly &P) {
	return P + k;
}

Poly Poly::operator-(Poly P) {
	Node* p1 = this->head, * p2 = P.head;
	Poly ret;
	while (p1->next != nullptr)
	{
		p1 = p1->next;
		Node* p3 = new Node(p1->coeff, p1->times);
		ret.insert(p3);
		delete p3;
		p3 = nullptr;
	}
	while (p2->next != nullptr)
	{
		p2 = p2->next;
		Node* p3 = new Node(-p2->coeff, p2->times);
		ret.insert(p3);
		delete p3;
		p3 = nullptr;
	}
	ret.remove_zero();
	return ret;
}

Poly operator-(double k, Poly P) {
	Poly P1(k);
	return P1 - P;
}

Poly Poly::operator*(Poly P) {
	Poly ret;
	Node* p1 = this->head, *p2 = P.head;
	while (p1->next != nullptr) {
		p2 = P.head;
		p1 = p1->next;
		while (p2->next!=nullptr)
		{
			p2 = p2->next;
			Node* p3 = new Node(p1->coeff * p2->coeff, p1->times + p2->times);
			ret.insert(p3);
			delete p3;
			p3 = nullptr;
		}
	}
	ret.remove_zero();
	return ret;
}

Poly operator*(double k, Poly P) {
	return P * k;
}

Poly operator^(Poly P,int k) {
	Poly P1(1);
	for (int i = 1; i <= k; i++) {
		P1 = P1 * P;
	}
	P1.remove_zero();
	return P1;
}

Poly Poly::operator=(Poly& P) {
	deleteNode();
	head = new Node(0, 0);
	Node* p1 = head, * p2 = P.head;
	while (p2->next != nullptr) {
		p2 = p2->next;
		p1->next = new Node(p2->coeff, p2->times);
		p1 = p1->next;
	}
	return *this;
}

Poly Poly::operator=(Poly&& P) {
	deleteNode();
	head = new Node(0, 0);
	Node* p1 = head, * p2 = P.head;
	while (p2->next != nullptr) {
		p2 = p2->next;
		p1->next = new Node(p2->coeff, p2->times);
		p1 = p1->next;
	}
	return *this;
}

ostream& operator<<(ostream& os, Poly P) {
	auto p = P.gethead();
	//Poly::Node* p = P.gethead();
	int i = 0;
	if (p->next == nullptr) {
		os << 0 << endl;
		return os;
	}
	while (p->next != nullptr) {
		p = p->next;
		if (p->coeff > 0 && i != 0)os << '+';
		else if (p->coeff < 0)os << '-';
		if (!((p->coeff == 1||p->coeff==-1) && p->times != 0)) {
			os << abs(p->coeff);
			if (p->times != 0)os << '*';
		}
		if (p->times != 0) {
			os << 'x';
			if (p->times != 1)os << '^' << p->times;
		}
		i++;
	}
	os << endl;
	return os;
}


//istream& operator>>(istream& is,Poly& P){}