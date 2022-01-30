//--------------------------------------------------------------------------------
//  2020112377 ��ǻ�Ͱ������� ��μ�
//  ��ȭ���α׷���-01 ������Ʈ
//  Person.cpp
//----------------------------------------------------------------------------------

#include "Person.h"
#include <fstream>
#include <string>
#include <iomanip>


PersonListNode::PersonListNode(string& _name, string& _id, string& _pw, string& _phonenum, PersonListNode* nextPtr)
	:name(_name), id(_id), pw(_pw), phonenum(_phonenum), next(nextPtr)
{
	//PersonListNode ������
}

PersonList::PersonList()
	: head(NULL), cursor(NULL)
{
	//PersonList ������
}

PersonList::~PersonList() {
	PersonListNode* tempPtr;

	cursor = head; //cursor�� head�� ����
	while (cursor != NULL) { //Ŀ���� NULL�� �ɶ�����
		tempPtr = cursor;
		cursor = tempPtr->next;
		delete tempPtr; 
	}
	cursor = NULL;
	head = NULL;
}//PersonList �Ҹ���
//-----------------------------------------------------------------------------������, �Ҹ���

void PersonList::fileRead() { //�����о�� ����Ʈ�� ����
	ifstream readFile; //���� ������ ���� ����
	readFile.open("ȸ������.txt"); //���� ����
	if (readFile.is_open()) { //������ ���ȴ��� Ȯ��
		while (!readFile.eof()) { //���� ������ �б�
			if (isEmpty()) { //ù��° ��
				string name, id, pw, phonenum, phead;
				getline(readFile, phead); //���
				getline(readFile, phead); //�ٹٲ�
				readFile >> id >> pw >> name >> phonenum;//���̵�, ��й�ȣ, �̸�, ��ȭ��ȣ �о����
				PersonListNode* location = new PersonListNode(name, id, pw, phonenum, NULL); //ȸ������Ʈ��� ���� �� ����
				head = location;
				cursor = location; //ù��° ���̹Ƿ� �ش� ��尡  head���� cursor�� ��
				string b1, b2, b3, b4, b5;
				readFile >> b1 >> b2 >> b3 >> b4 >> b5;
				cursor->bookList[0] = b1;
				cursor->bookList[1] = b2;
				cursor->bookList[2] = b3;
				cursor->bookList[3] = b4;
				cursor->bookList[4] = b5;
			}
			else { //������ ��
				string name, id, pw, phonenum, phead;
				readFile >> id >> pw >> name >> phonenum;
				PersonListNode* location = new PersonListNode(name, id, pw, phonenum, NULL);
				cursor->next = location; //cursor ������ �ش� ȸ������Ʈ��带 ����Ű�� ��
				cursor = location; //cursor �̵�
				string b1, b2, b3, b4, b5;
				readFile >> b1 >> b2 >> b3 >> b4 >> b5;
				cursor->bookList[0] = b1;
				cursor->bookList[1] = b2;
				cursor->bookList[2] = b3;
				cursor->bookList[3] = b4;
				cursor->bookList[4] = b5;
			}
		}
	}
	else {
		cout << "   ������ ���� �� �����ϴ�." << endl;
		return;
	}
	readFile.close(); //���� �ݱ�
}

void PersonList::fileWrite() {//�����ϱ� ������ ȸ�� ����Ʈ�� ���Ͽ� ����	
	ofstream writeFile; //�� ������ ���� ����
	writeFile.open("ȸ������.txt");
	if (writeFile.is_open()) { //���� ����
		writeFile << "----id------     -pw-   --name---   --phonenumber-- ---borrowingbooks-----";
		cursor = head; 
		while (cursor != NULL) { //Ŀ���� NULL�� �ɶ�����
			writeFile << endl << endl;
			writeFile << setw(17) <<left<< cursor->id;
			writeFile << cursor->pw << "    ";
			writeFile<<setw(12)<<left<<cursor->name;
			writeFile<< cursor->phonenum << "    "; //���Ͽ� Ŀ���� ȸ������ ���
			for (int i = 0; i < 5; i++) {
				if(i<4)
					writeFile << cursor->bookList[i] << "  ";
				if (i == 4)
					writeFile << cursor->bookList[i];
			}
			cursor = cursor->next; //Ŀ�� �������� �̵�
		}
	}
	else {
		cout << "   ������ ����� �� �����ϴ�. " << endl;
	}
	writeFile.close(); //���� �ݱ�

	cout << "   ȸ������ ������ ���������� ������Ʈ�Ǿ����ϴ�." << endl;
}
//-----------------------------------------------------------------------------���� �����

//�߰�, ����, �˻�
void PersonList::insert() { //ȸ�� �߰�
	if (isFull()) { //�̹� ����Ʈ�� �� �� ���
		cout << "   ȸ���� �� �̻� �߰��� �� �����ϴ�." << endl;
		return;
	}
	else {
		cout << "   id�� �Է��ϼ���. (����/����/Ư����ȣ 15���ڱ���) : ";
		string newid;
		getline(cin, newid);
		if (isMember(newid) == true) { //id�� �̹� �����ϴ� ���
			cout << "   �ߺ��� id�Դϴ�. �ٸ� id�� �Է��ϼ���. !" << endl << endl;
			insert();
		}
		else {
			string newpw, newname, newphonenum;
			cout << "   ��ȿ�� id�Դϴ�." << endl;
			cout << "   ��й�ȣ�� �Է��ϼ���. (���� 4����): ";
			getline(cin, newpw);
			cout << "   �̸��� �Է��ϼ���. (���� 10���ڱ���): ";
			getline(cin, newname);
			cout << "   ��ȭ��ȣ�� �Է��ϼ���. (xxx-xxxx-xxxx��������): ";
			getline(cin, newphonenum);
			if (isEmpty()) { //����Ʈ�� ���������
				PersonListNode* location = new PersonListNode(newname, newid, newpw, newphonenum, NULL);
				head = location;
				cursor = location;
				for (int i = 0; i < 5; i++) {
					location->bookList[i] = "N";
				}
				return;
			}
			else {
				cursor = head;
				while (cursor->next != NULL)
					cursor = cursor->next; //Ŀ���� �� �ڷ� �̵�
				PersonListNode* location = new PersonListNode(newname, newid, newpw, newphonenum, NULL);
				cursor->next = location; //�� �ڿ� ���� �߰�
				for (int i = 0; i < 5; i++) {
					location->bookList[i] = "N";
				}
			}
			cout << "   ȸ�������� �Ϸ��߽��ϴ�! " << endl;
		}
	}
}

void PersonList::remove() {//ȸ�� ����
	if (isEmpty()) {//����ִ� ���
		cout << "  ����Ʈ�� ����ֽ��ϴ�." << endl;
		return;
	}
	else {
		cout << "   ȸ���� id�� �Է��ϼ���. : ";
		string idsearch;
		getline(cin, idsearch);

		if (isMember(idsearch) == false) { //id�� �������� �ʴ� ���
			cout << "   �ش��ϴ� id�� �������� �ʽ��ϴ�!"<<endl;
			return;
		}

		else {
			if (canRemove() == true) { //��� å�� �ݳ��ϸ� Ż�� ����
				cout << "   ȸ���� ��й�ȣ�� �Է��ϼ���. : ";
				string pwsearch;
				getline(cin, pwsearch);
				if (cursor->pw == pwsearch) { //��й�ȣ�� ��ġ�ϴ� ���
					if (cursor == head) {//Ŀ���� ��忡 �ִ� ���
						PersonListNode* tempPtr = head;
						head = head->next; //head�� �������� �̵�
						cursor = cursor->next; //cursor�� �������� �̵�
						delete tempPtr; //temPtr ����
						return;
					}
					else {
						PersonListNode* tempPtr2 = cursor; //������ �ϴ� ȸ������Ʈ��带 Ŀ���� ����Ŵ
						PersonListNode* tempPtr = head;
						while (tempPtr->next != cursor) { //tempPtr������ cursor�� ����ų ������ tempPtr�� �ڷ� �ű� 
							tempPtr = tempPtr->next;
						}
						cursor = tempPtr; //Ŀ���� ��ĭ ������
						cursor->next = tempPtr2->next; //Ŀ�� ��ĭ ���� ������ Ŀ���� ������带 ����Ŵ
						delete tempPtr2; //tempPtr2 ����
					}
					cout << "   ȸ���� �����߽��ϴ�."<<endl;
				}
				else { //��й�ȣ�� Ʋ����
					cout << "   ��й�ȣ�� �ùٸ��� �ʽ��ϴ�.!" << endl;
				}
			}
			else {
				cout << "   ���� ���� �ݳ����� ���� å�� �ֽ��ϴ�. ��� å�� �ݳ��ؾ� Ż�� �����մϴ�. " << endl;
			}
		}
	}
}

bool PersonList::isMember(string& findId) { //�ش� id�� �����ִ� ȸ���� �ִ��� �˻�
	cursor = head;
	while (cursor != NULL) {
		if (cursor->id == findId) //ã���� 
			break; //����
		cursor = cursor->next; //�ƴϸ� ��� �ڷ� �̵�
	}
	if (cursor != NULL) //Ŀ���� NULL�� �ƴϸ�->ã����
		return true;
	else
		return false;
}
//---------------------------------------------------------------------------------�߰�, ����, �˻�

bool PersonList::isEmpty() { //����ִ���
	return head == NULL;
}

bool PersonList::isFull() { //�� ä�����ִ���
	string str1 = "";
	string str2 = "";
	string str3 = "";
	string str4 = "";
	PersonListNode* tempPtr = new PersonListNode(str1, str2, str3, str4, NULL);
	if (tempPtr == NULL)
		return true; //�� ��尡 ������ �ȵǸ� true
	else {
		delete tempPtr;
		return false;
	}
}
//-----------------------------------------------------------------------------full, empty

void PersonList::borrowBook(string& bookname) {// å ����->�������� å ����Ʈ�� ���� �߰�
	if (isFullBook() == false) {//5���� �� ������ �ʾҴٸ�
		for (int i = 0; i < 5; i++) {
			if (cursor->bookList[i] == "N") {//ó������ "N"�� ���� �ε����� ���� �߰�
				cursor->bookList[i] = bookname;
				return;
			}
		}
	}
	else { //5���� �� ���ȴٸ�
		cout << "   ȸ���� ������ å�� ������ �̹� 5���Դϴ�." << endl;
	}
}

bool PersonList::returnBook(string& bookname) { //å �ݳ�->�������� å ����Ʈ�� ���� ����, ���� å�� ���� ��� false ��ȯ

	int i;
	for (i = 0; i < 5; i++) {
		if (cursor->bookList[i] == bookname) //������ break
			break;
	}
	if (i == 5)
		return false;
	else { //i�� 5�� �ƴϸ� �׻� true
		cursor->bookList[i] = "N";
		return true;
	}
}
bool PersonList::canRemove() {
	int i, count = 0;
	for ( i = 0; i < 5; i++) {
		if (cursor->bookList[i] == "N") {
			count++;
		}
	}
	if (count == 5) //��� N�̸�->N�� ������ 5���
		return true;
	else
		return false;
}

bool PersonList::isFullBook() {

	int i;
	for (i = 0; i < 5; i++) {
		if (cursor->bookList[i] == "N")
			break;
	}
	if (i == 5) //N�� �Ѱ��� ����->full
		return true;
	else
		return false;
}

//-----------------------------------------------------------------------------���� ����, �ݳ�
