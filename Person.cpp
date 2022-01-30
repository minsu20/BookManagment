//--------------------------------------------------------------------------------
//  2020112377 컴퓨터공학전공 김민수
//  심화프로그래밍-01 프로젝트
//  Person.cpp
//----------------------------------------------------------------------------------

#include "Person.h"
#include <fstream>
#include <string>
#include <iomanip>


PersonListNode::PersonListNode(string& _name, string& _id, string& _pw, string& _phonenum, PersonListNode* nextPtr)
	:name(_name), id(_id), pw(_pw), phonenum(_phonenum), next(nextPtr)
{
	//PersonListNode 생성자
}

PersonList::PersonList()
	: head(NULL), cursor(NULL)
{
	//PersonList 생성자
}

PersonList::~PersonList() {
	PersonListNode* tempPtr;

	cursor = head; //cursor에 head를 대입
	while (cursor != NULL) { //커서가 NULL이 될때까지
		tempPtr = cursor;
		cursor = tempPtr->next;
		delete tempPtr; 
	}
	cursor = NULL;
	head = NULL;
}//PersonList 소멸자
//-----------------------------------------------------------------------------생성자, 소멸자

void PersonList::fileRead() { //파일읽어와 리스트에 저장
	ifstream readFile; //읽을 목적의 파일 선언
	readFile.open("회원정보.txt"); //파일 열기
	if (readFile.is_open()) { //파일이 열렸는지 확인
		while (!readFile.eof()) { //파일 끝까지 읽기
			if (isEmpty()) { //첫번째 줄
				string name, id, pw, phonenum, phead;
				getline(readFile, phead); //헤드
				getline(readFile, phead); //줄바꿈
				readFile >> id >> pw >> name >> phonenum;//아이디, 비밀번호, 이름, 전화번호 읽어오기
				PersonListNode* location = new PersonListNode(name, id, pw, phonenum, NULL); //회원리스트노드 생성 및 대입
				head = location;
				cursor = location; //첫번째 줄이므로 해당 노드가  head이자 cursor가 됨
				string b1, b2, b3, b4, b5;
				readFile >> b1 >> b2 >> b3 >> b4 >> b5;
				cursor->bookList[0] = b1;
				cursor->bookList[1] = b2;
				cursor->bookList[2] = b3;
				cursor->bookList[3] = b4;
				cursor->bookList[4] = b5;
			}
			else { //나머지 줄
				string name, id, pw, phonenum, phead;
				readFile >> id >> pw >> name >> phonenum;
				PersonListNode* location = new PersonListNode(name, id, pw, phonenum, NULL);
				cursor->next = location; //cursor 다음을 해당 회원리스트노드를 가리키게 함
				cursor = location; //cursor 이동
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
		cout << "   파일을 읽을 수 없습니다." << endl;
		return;
	}
	readFile.close(); //파일 닫기
}

void PersonList::fileWrite() {//종료하기 누르면 회원 리스트가 파일에 저장	
	ofstream writeFile; //쓸 목적의 파일 선언
	writeFile.open("회원정보.txt");
	if (writeFile.is_open()) { //파일 열기
		writeFile << "----id------     -pw-   --name---   --phonenumber-- ---borrowingbooks-----";
		cursor = head; 
		while (cursor != NULL) { //커서가 NULL이 될때까지
			writeFile << endl << endl;
			writeFile << setw(17) <<left<< cursor->id;
			writeFile << cursor->pw << "    ";
			writeFile<<setw(12)<<left<<cursor->name;
			writeFile<< cursor->phonenum << "    "; //파일에 커서의 회원정보 출력
			for (int i = 0; i < 5; i++) {
				if(i<4)
					writeFile << cursor->bookList[i] << "  ";
				if (i == 4)
					writeFile << cursor->bookList[i];
			}
			cursor = cursor->next; //커서 다음으로 이동
		}
	}
	else {
		cout << "   파일을 출력할 수 없습니다. " << endl;
	}
	writeFile.close(); //파일 닫기

	cout << "   회원정보 파일이 정상적으로 업데이트되었습니다." << endl;
}
//-----------------------------------------------------------------------------파일 입출력

//추가, 제거, 검색
void PersonList::insert() { //회원 추가
	if (isFull()) { //이미 리스트가 다 찬 경우
		cout << "   회원을 더 이상 추가할 수 없습니다." << endl;
		return;
	}
	else {
		cout << "   id를 입력하세요. (영문/숫자/특수기호 15글자까지) : ";
		string newid;
		getline(cin, newid);
		if (isMember(newid) == true) { //id가 이미 존재하는 경우
			cout << "   중복된 id입니다. 다른 id를 입력하세요. !" << endl << endl;
			insert();
		}
		else {
			string newpw, newname, newphonenum;
			cout << "   유효한 id입니다." << endl;
			cout << "   비밀번호를 입력하세요. (숫자 4글자): ";
			getline(cin, newpw);
			cout << "   이름을 입력하세요. (영문 10글자까지): ";
			getline(cin, newname);
			cout << "   전화번호를 입력하세요. (xxx-xxxx-xxxx형식으로): ";
			getline(cin, newphonenum);
			if (isEmpty()) { //리스트가 비어있으면
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
					cursor = cursor->next; //커서를 맨 뒤로 이동
				PersonListNode* location = new PersonListNode(newname, newid, newpw, newphonenum, NULL);
				cursor->next = location; //맨 뒤에 원소 추가
				for (int i = 0; i < 5; i++) {
					location->bookList[i] = "N";
				}
			}
			cout << "   회원가입을 완료했습니다! " << endl;
		}
	}
}

void PersonList::remove() {//회원 삭제
	if (isEmpty()) {//비어있는 경우
		cout << "  리스트가 비어있습니다." << endl;
		return;
	}
	else {
		cout << "   회원의 id를 입력하세요. : ";
		string idsearch;
		getline(cin, idsearch);

		if (isMember(idsearch) == false) { //id가 존재하지 않는 경우
			cout << "   해당하는 id는 존재하지 않습니다!"<<endl;
			return;
		}

		else {
			if (canRemove() == true) { //모든 책을 반납하면 탈퇴 가능
				cout << "   회원의 비밀번호를 입력하세요. : ";
				string pwsearch;
				getline(cin, pwsearch);
				if (cursor->pw == pwsearch) { //비밀번호가 일치하는 경우
					if (cursor == head) {//커서가 헤드에 있는 경우
						PersonListNode* tempPtr = head;
						head = head->next; //head를 다음으로 이동
						cursor = cursor->next; //cursor를 다음으로 이동
						delete tempPtr; //temPtr 삭제
						return;
					}
					else {
						PersonListNode* tempPtr2 = cursor; //지워야 하는 회원리스트노드를 커서가 가리킴
						PersonListNode* tempPtr = head;
						while (tempPtr->next != cursor) { //tempPtr다음이 cursor를 가리킬 때까지 tempPtr를 뒤로 옮김 
							tempPtr = tempPtr->next;
						}
						cursor = tempPtr; //커서를 한칸 앞으로
						cursor->next = tempPtr2->next; //커서 한칸 앞의 다음이 커서의 다음노드를 가리킴
						delete tempPtr2; //tempPtr2 삭제
					}
					cout << "   회원을 삭제했습니다."<<endl;
				}
				else { //비밀번호가 틀리면
					cout << "   비밀번호가 올바르지 않습니다.!" << endl;
				}
			}
			else {
				cout << "   아직 도서 반납하지 않은 책이 있습니다. 모든 책을 반납해야 탈퇴가 가능합니다. " << endl;
			}
		}
	}
}

bool PersonList::isMember(string& findId) { //해당 id를 갖고있는 회원이 있는지 검사
	cursor = head;
	while (cursor != NULL) {
		if (cursor->id == findId) //찾으면 
			break; //멈춤
		cursor = cursor->next; //아니면 계속 뒤로 이동
	}
	if (cursor != NULL) //커서가 NULL이 아니면->찾았음
		return true;
	else
		return false;
}
//---------------------------------------------------------------------------------추가, 제거, 검색

bool PersonList::isEmpty() { //비어있는지
	return head == NULL;
}

bool PersonList::isFull() { //꽉 채워져있는지
	string str1 = "";
	string str2 = "";
	string str3 = "";
	string str4 = "";
	PersonListNode* tempPtr = new PersonListNode(str1, str2, str3, str4, NULL);
	if (tempPtr == NULL)
		return true; //새 노드가 생성이 안되면 true
	else {
		delete tempPtr;
		return false;
	}
}
//-----------------------------------------------------------------------------full, empty

void PersonList::borrowBook(string& bookname) {// 책 대출->대출중인 책 리스트에 원소 추가
	if (isFullBook() == false) {//5권을 다 빌리지 않았다면
		for (int i = 0; i < 5; i++) {
			if (cursor->bookList[i] == "N") {//처음으로 "N"이 나온 인덱스에 원소 추가
				cursor->bookList[i] = bookname;
				return;
			}
		}
	}
	else { //5권을 다 빌렸다면
		cout << "   회원의 대출한 책의 개수가 이미 5권입니다." << endl;
	}
}

bool PersonList::returnBook(string& bookname) { //책 반납->대출중인 책 리스트에 원소 삭제, 빌린 책이 없는 경우 false 반환

	int i;
	for (i = 0; i < 5; i++) {
		if (cursor->bookList[i] == bookname) //같으면 break
			break;
	}
	if (i == 5)
		return false;
	else { //i가 5가 아니며 항상 true
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
	if (count == 5) //모두 N이면->N의 개수가 5라면
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
	if (i == 5) //N이 한개도 없음->full
		return true;
	else
		return false;
}

//-----------------------------------------------------------------------------도서 대출, 반납
