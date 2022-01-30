//--------------------------------------------------------------------------------
//  2020112377 ��ǻ�Ͱ������� ��μ�
//  ��ȭ���α׷���-01 ������Ʈ
//  Book.h
//----------------------------------------------------------------------------------

#pragma once
#include <iostream>
using namespace std;

class BookListNode {
private:
	BookListNode(string& _name, int& _number, string& _reservid, BookListNode* nextPtr); //������
	//�������
	string name; //å�̸�
	int number; //����
	string reservid; //������ �̸�
	BookListNode* next;//���� ����Ʈ ����Ŵ

	friend class BookList;
};

class BookList {
public:
	//������
	BookList();

	//�Ҹ���
	~BookList();

	//���� �����
	void fileRead(); //���� �о����
	void fileWrite(); //�����ϱ� ������ å ����Ʈ�� ���Ͽ� ����	


	//���� ����, �ݳ�
	void borrowBook(string& bookname); //å ����
	void returnBook(string& bookname); //å �ݳ�
	bool canFind(string& bookname);//å�̸��� �����ϴ���
	bool canBorrow(string& bookname);//(å�� ����) ���� �� �ִ� ��

	//����Ʈ ����
	bool isEmpty();
	bool isFull();

	//���� ����
	void removeReserv(string& memberid, string& bookname);
	void insertReserv(string& memberid, string& bookname);
	bool canReserv(string& bookname);
	string reservId(string& bookname);

private:
	BookListNode* head,
		* cursor;
};
