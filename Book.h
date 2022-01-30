//--------------------------------------------------------------------------------
//  2020112377 컴퓨터공학전공 김민수
//  심화프로그래밍-01 프로젝트
//  Book.h
//----------------------------------------------------------------------------------

#pragma once
#include <iostream>
using namespace std;

class BookListNode {
private:
	BookListNode(string& _name, int& _number, string& _reservid, BookListNode* nextPtr); //생성자
	//멤버변수
	string name; //책이름
	int number; //개수
	string reservid; //예약자 이름
	BookListNode* next;//다음 리스트 가리킴

	friend class BookList;
};

class BookList {
public:
	//생성자
	BookList();

	//소멸자
	~BookList();

	//파일 입출력
	void fileRead(); //파일 읽어오기
	void fileWrite(); //종료하기 누르면 책 리스트가 파일에 저장	


	//도서 대출, 반납
	void borrowBook(string& bookname); //책 대출
	void returnBook(string& bookname); //책 반납
	bool canFind(string& bookname);//책이름이 존재하는지
	bool canBorrow(string& bookname);//(책은 있음) 빌릴 수 있는 지

	//리스트 상태
	bool isEmpty();
	bool isFull();

	//도서 예약
	void removeReserv(string& memberid, string& bookname);
	void insertReserv(string& memberid, string& bookname);
	bool canReserv(string& bookname);
	string reservId(string& bookname);

private:
	BookListNode* head,
		* cursor;
};
