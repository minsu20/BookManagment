//--------------------------------------------------------------------------------
//  2020112377 컴퓨터공학전공 김민수
//  심화프로그래밍-01 프로젝트
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

//소멸자
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

//파일 입출력
void BookList::fileRead() {
	ifstream readFile;
	readFile.open("도서정보.txt");
	if (readFile.is_open()) {
		while (!readFile.eof()) {
			if (isEmpty()) { //첫번째 줄
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
		cout << "   파일을 읽을 수 없습니다." << endl;
		return;
	}
	readFile.close();
}//파일 읽어오기

void BookList::fileWrite() {
	ofstream writeFile;
	writeFile.open("도서정보.txt");
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
		cout << "   파일을 출력할 수 없습니다. " << endl;
	}
	writeFile.close();
	cout << "   도서정보 파일이 정상적으로 업데이트되었습니다." << endl;
}//종료하기 누르면 책 리스트가 파일에 저장	
//-----------------------------------------------------------------------------파일 입출력

bool BookList::canFind(string& bookname) { //책이름이 리스트에 존재하는지->책이 존재하는지
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

bool BookList::canBorrow(string& bookname) {//빌릴 수 있는 지
	if (canFind(bookname) == true) {
		if (cursor->number > 0)
			return true;
		else
			return false; //책이 있지만 이미 다 대출중
	}
}

void BookList::borrowBook(string& bookname){ //책 대출
	cursor = head;
	while (cursor != NULL) {
		if (cursor->name == bookname)
			break;
		cursor = cursor->next;
	}
		int temp = cursor->number;
		cursor->number = temp - 1; //책 개수 1 감소
		cout << "   책을 빌렸습니다." << endl;
}

void BookList::returnBook(string& bookname) { //책 반납
	cursor = head;
	while (cursor != NULL) {
		if (cursor->name == bookname)
			break;
		cursor = cursor->next;
	}
	int temp = cursor->number;
	cursor->number = temp + 1;
	cout << "   책을 반납했습니다." << endl; //책 반납하기

}
//---------------------------------------------------------------------------------도서 대출, 반납

bool BookList::isEmpty() {
	return head == nullptr;
}

bool BookList::isFull() {
	string str1 = "";
	int num2 = NULL;
	string str3 = "";
	BookListNode* tempPtr = new BookListNode(str1, num2, str3, NULL);
	if (tempPtr == nullptr)
		return true; //새 노드가 생성이 안되면 true
	else {
		delete tempPtr;
		return false;
	}
}
//---------------------------------------------------------------------------------리스트 상태(full&empty)

bool BookList::canReserv(string& bookname) { //예약자 id가 N인지
	if (canFind(bookname) == true) {//책 빌릴 수 있음
		if (cursor->reservid=="N")
			return true;
		else
			return false;
	}
}

void BookList::insertReserv(string& memberid, string& bookname) {//예약등록
	cursor = head;
	while (cursor != NULL) {
		if (cursor->name == bookname)
			break;
		cursor = cursor->next;
	}
	cout << "   책이 예약되었습니다." << endl;
	string temp = cursor->reservid;
	cursor->reservid = memberid;//N->memberid
}

void BookList::removeReserv(string& memberid, string& bookname) { //예약자 삭제
	cursor = head;
	while (cursor != NULL) {
		if (cursor->name == bookname)
			break;
		cursor = cursor->next;
	}
	string temp = cursor->reservid;
	cursor->reservid = "N"; //memberid->N
}

string BookList::reservId(string& bookname) {//reservId 반환
	if (canFind(bookname) == true) {//책을 찾고
		return cursor->reservid;
	}
}
//---------------------------------------------------------------------------------도서 예약
