//--------------------------------------------------------------------------------
//  2020112377 컴퓨터공학전공 김민수
//  심화프로그래밍-01 프로젝트
//  Person.h
//----------------------------------------------------------------------------------

#pragma once
#include <iostream>
using namespace std;

class PersonListNode {
private:
	PersonListNode(string& _name, string& _id, string& _pw, string& _phonenum, PersonListNode* nextPtr); //생성자
	//멤버변수
	string name;// 이름
	string id;// 아이디 -> 중복할 수 없다.
	string pw; //비밀번호
	string phonenum; //전화번호

	PersonListNode* next;//다음 리스트노드 가리킴
	string bookList[5];//대출중인 책 리스트-최대 5개까지 빌릴 수 있다.
	friend class PersonList;
};

class PersonList {
public:
	//생성자
	PersonList();

	//소멸자
	~PersonList();

	//파일 입출력
	void fileRead(); //파일 읽어오기->원한다면 
	void fileWrite(); //종료하기 누르면 회원 리스트가 파일에 저장	

	//추가, 제거, 검색
	void insert(); //회원 추가
	void remove(); //회원 삭제
	bool isMember(string& findId); //해당하는 id를 갖고 있는 회원이 있는지 검사

	//리스트 상태
	bool isEmpty(); //회원 리스트가 비어있음->더이상 삭제 못함
	bool isFull(); //회원 리스트가 꽉 차있음->더이상 추가 못함

	//도서 대출, 반납
	void borrowBook(string& bookname); //해당하는 id 회원의 대출중인 책 리스트에서 bookname 원소 추가
	bool returnBook(string& bookname); //해당하는 id 회원의 대출중인 책 리스트에서 bookname 원소 삭제
	bool canRemove(); //탈퇴할 수 있는지 check 하는 함수 (도서를 하나라도 반납하지 않은 경우->false)
	bool isFullBook();//빌린 책이 이미 5권인지 check하는 함수


private:
	PersonListNode* head,
		* cursor;
}; 
