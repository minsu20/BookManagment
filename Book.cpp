//--------------------------------------------------------------------------------
//  2020112377 ��ǻ�Ͱ������� ��μ�
//  ��ȭ���α׷���-01 ������Ʈ
//  Book.cpp
//----------------------------------------------------------------------------------

#include "Book.h"
#include <fstream>
#include <string>
#include <cstring>
#pragma warning(disable : 4996)


BookListNode::BookListNode(string& _name, int& _number, string& _reservid, BookListNode* nextPtr) 
	:name(_name), number(_number), reservid(_reservid), next(nextPtr)
{

}

BookList::BookList() 
	:head(NULL), cursor(NULL)
{

}

//�Ҹ���
BookList::~BookList() {
	BookListNode* tempPtr;

	cursor = head;
	while (cursor != NULL) {
		tempPtr = cursor;
		cursor = tempPtr->next;
		delete tempPtr;
	}
	cursor = NULL;
	head = NULL;
}

//���� �����
void BookList::fileRead() {
	ifstream readFile;
	readFile.open("��������.txt");
	if (readFile.is_open()) {
		while (!readFile.eof()) {
			if (isEmpty()) { //ù��° ��
				string name;
				int number = NULL;
				string reservid;
				readFile >> name>>number >> reservid;
				BookListNode* location = new BookListNode(name, number, reservid, nullptr);
				head = location;
				cursor = location;
			}
			else {
				string name;
				int number = NULL;
				string reservid, phead;
				getline(readFile, phead);
				readFile >>name>> number >> reservid;
				BookListNode* location = new BookListNode(name, number, reservid, nullptr);
				cursor->next = location;
				cursor = location;
			}
		}
	}
	else {
		cout << "   ������ ���� �� �����ϴ�." << endl;
		return;
	}
	readFile.close();
}//���� �о����

void BookList::fileWrite() {
	ofstream writeFile;
	writeFile.open("��������.txt");
	if (writeFile.is_open()) {
		cursor = head;
		while (cursor != NULL) {
			if(cursor==head)
				writeFile << cursor->name << endl << cursor->number << "   " << cursor->reservid;
			else {
				writeFile << endl << endl;
				writeFile << cursor->name << endl << cursor->number << "   " << cursor->reservid;

			}
			cursor = cursor->next;
		}
	}
	else {
		cout << "   ������ ����� �� �����ϴ�. " << endl;
	}
	writeFile.close();
	cout << "   �������� ������ ���������� ������Ʈ�Ǿ����ϴ�." << endl;
}//�����ϱ� ������ å ����Ʈ�� ���Ͽ� ����	
//-----------------------------------------------------------------------------���� �����

bool BookList::canFind(string& bookname) { //å�̸��� ����Ʈ�� �����ϴ���->å�� �����ϴ���
	cursor = head;
	while (cursor != NULL) {
		if (cursor->name == bookname)
			break;
		cursor = cursor->next;
	}
	if (cursor != NULL)
		return true;
	else
		return false;
}

bool BookList::canBorrow(string& bookname) {//���� �� �ִ� ��
	if (canFind(bookname) == true) {
		if (cursor->number > 0)
			return true;
		else
			return false; //å�� ������ �̹� �� ������
	}
}

void BookList::borrowBook(string& bookname){ //å ����
	cursor = head;
	while (cursor != NULL) {
		if (cursor->name == bookname)
			break;
		cursor = cursor->next;
	}
		int temp = cursor->number;
		cursor->number = temp - 1; //å ���� 1 ����
		cout << "   å�� ���Ƚ��ϴ�." << endl;
}

void BookList::returnBook(string& bookname) { //å �ݳ�
	cursor = head;
	while (cursor != NULL) {
		if (cursor->name == bookname)
			break;
		cursor = cursor->next;
	}
	int temp = cursor->number;
	cursor->number = temp + 1;
	cout << "   å�� �ݳ��߽��ϴ�." << endl; //å �ݳ��ϱ�

}
//---------------------------------------------------------------------------------���� ����, �ݳ�

bool BookList::isEmpty() {
	return head == nullptr;
}

bool BookList::isFull() {
	string str1 = "";
	int num2 = NULL;
	string str3 = "";
	BookListNode* tempPtr = new BookListNode(str1, num2, str3, NULL);
	if (tempPtr == nullptr)
		return true; //�� ��尡 ������ �ȵǸ� true
	else {
		delete tempPtr;
		return false;
	}
}
//---------------------------------------------------------------------------------����Ʈ ����(full&empty)

bool BookList::canReserv(string& bookname) { //������ id�� N����
	if (canFind(bookname) == true) {//å ���� �� ����
		if (cursor->reservid=="N")
			return true;
		else
			return false;
	}
}

void BookList::insertReserv(string& memberid, string& bookname) {//������
	cursor = head;
	while (cursor != NULL) {
		if (cursor->name == bookname)
			break;
		cursor = cursor->next;
	}
	cout << "   å�� ����Ǿ����ϴ�." << endl;
	string temp = cursor->reservid;
	cursor->reservid = memberid;//N->memberid
}

void BookList::removeReserv(string& memberid, string& bookname) { //������ ����
	cursor = head;
	while (cursor != NULL) {
		if (cursor->name == bookname)
			break;
		cursor = cursor->next;
	}
	string temp = cursor->reservid;
	cursor->reservid = "N"; //memberid->N
}

string BookList::reservId(string& bookname) {//reservId ��ȯ
	if (canFind(bookname) == true) {//å�� ã��
		return cursor->reservid;
	}
}
//---------------------------------------------------------------------------------���� ����
