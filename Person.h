//--------------------------------------------------------------------------------
//  2020112377 ��ǻ�Ͱ������� ��μ�
//  ��ȭ���α׷���-01 ������Ʈ
//  Person.h
//----------------------------------------------------------------------------------

#pragma once
#include <iostream>
using namespace std;

class PersonListNode {
private:
	PersonListNode(string& _name, string& _id, string& _pw, string& _phonenum, PersonListNode* nextPtr); //������
	//�������
	string name;// �̸�
	string id;// ���̵� -> �ߺ��� �� ����.
	string pw; //��й�ȣ
	string phonenum; //��ȭ��ȣ

	PersonListNode* next;//���� ����Ʈ��� ����Ŵ
	string bookList[5];//�������� å ����Ʈ-�ִ� 5������ ���� �� �ִ�.
	friend class PersonList;
};

class PersonList {
public:
	//������
	PersonList();

	//�Ҹ���
	~PersonList();

	//���� �����
	void fileRead(); //���� �о����->���Ѵٸ� 
	void fileWrite(); //�����ϱ� ������ ȸ�� ����Ʈ�� ���Ͽ� ����	

	//�߰�, ����, �˻�
	void insert(); //ȸ�� �߰�
	void remove(); //ȸ�� ����
	bool isMember(string& findId); //�ش��ϴ� id�� ���� �ִ� ȸ���� �ִ��� �˻�

	//����Ʈ ����
	bool isEmpty(); //ȸ�� ����Ʈ�� �������->���̻� ���� ����
	bool isFull(); //ȸ�� ����Ʈ�� �� ������->���̻� �߰� ����

	//���� ����, �ݳ�
	void borrowBook(string& bookname); //�ش��ϴ� id ȸ���� �������� å ����Ʈ���� bookname ���� �߰�
	bool returnBook(string& bookname); //�ش��ϴ� id ȸ���� �������� å ����Ʈ���� bookname ���� ����
	bool canRemove(); //Ż���� �� �ִ��� check �ϴ� �Լ� (������ �ϳ��� �ݳ����� ���� ���->false)
	bool isFullBook();//���� å�� �̹� 5������ check�ϴ� �Լ�


private:
	PersonListNode* head,
		* cursor;
}; 
