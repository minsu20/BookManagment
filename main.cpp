//--------------------------------------------------------------------------------
//  2020112377 컴퓨터공학전공 김민수
//  심화프로그래밍-01 프로젝트
//  main.cpp
//----------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "Person.h"
#include "Book.h"

void print_help()   //Print Commands
{
    cout << endl << "   [도서 관리 프로그램]" << endl;
    cout << "   1-회원가입" << endl;
    cout << "   2-회원탈퇴" << endl;
    cout << "   3-도서 대출" << endl;
    cout << "   4-도서 반납" << endl;
    cout << "   5-책 대출가능 여부 보기" << endl;
    cout << "   6-종료하기" << endl;
    cout << "   **프로그램을 다 실행하고 마칠 때 반드시 종료하기를 해주십시오. \n     종료하기를 안하면 정보가 업데이트가 안됩니다**" << endl;
    cout << endl;
}

int main() {
    PersonList myperson;
    BookList mybook;
    char cmd;
    myperson.fileRead();
    mybook.fileRead();
    do
    {
        print_help();// Read command
        cout << "   ";
        cin >> cmd;

        switch (cmd)
        {
        case '1'://회원 추가
            cin.ignore();
            myperson.insert();
            break;

        case '2'://회원 삭제
            cin.ignore();
            myperson.remove();
            break;

        case '3': { //책 대출
            cin.ignore();
            cout << "   회원 id를 입력하세요. :";
            string memberid;
            getline(cin, memberid);
            if (myperson.isMember(memberid) == true) {
                cout << "   빌릴 책의 이름을 입력하세요. : ";
                string bookname;
                getline(cin, bookname);
                if (mybook.canFind(bookname) == true) { //책이 존재
                    if (mybook.canBorrow(bookname) == true) {//여분도 존재
                        cout << "   해당 책의 여분이 존재합니다. " << endl;
                            myperson.borrowBook(bookname); //책을 빌림
                            mybook.borrowBook(bookname); //책리스트에서 대여가능 개수 1감소
                    }
                    else { //책은 존재 여분은 존재x
                        if (mybook.canReserv(bookname) == true)//예약자가 없으면
                            mybook.insertReserv(memberid, bookname); //예약
                        else //예약자 있음
                            cout << "   예약자도 이미 존재합니다." << endl;
                    }
                }
                else { //책이 존재x
                    cout << "   존재하지 않는 책입니다." << endl;
                }
            }
            else {
                cout << "   등록된 회원이 아닙니다. " << endl;
            }
            break;
        }

        case '4': { //책 반납
            cin.ignore();
            cout << "   회원 id를 입력하세요. :";
            string memberid;
            getline(cin, memberid);
            if (myperson.isMember(memberid) == true) {//멤버인 경우
                cout << "   빌렸던 책의 이름을 입력하세요. : ";
                string bookname;
                getline(cin, bookname);
                if (myperson.returnBook(bookname) == true) {//빌린 책인 경우
                    cout << "   빌린 책이 맞습니다." << endl;
                      if (mybook.canReserv(bookname) == true) { //예약자가 없으면
                        mybook.returnBook(bookname);
                    }//책리스트에서 대여가능 개수 1 증가

                    else { //예약자가 있으면
                        string reservid = mybook.reservId(bookname);
                        mybook.removeReserv(memberid, bookname);//예약자명단에는 지워지고
                        if (myperson.isMember(reservid) == true) {//회원명단에서 cursor를 예약자로 이동
                            myperson.borrowBook(bookname); //예약자 책 자동으로 빌려짐
                            cout << "   예약자가 책을 빌렸습니다" << endl;
                        }
                    }
                  }

                else {
                    cout << "   이 책을 빌리지 않았습니다. " << endl;
                }
            }
            else {
                cout << "   등록된 회원이 아닙니다. " << endl;
            }
            break;
        }

        case '5': {   //책 대출 가능 여부
            cin.ignore();
            cout << "   책의 이름을 입력하세요.: ";
            string bookname;
            getline(cin, bookname);
            if (mybook.canFind(bookname) == true) { //책 존재
                if (mybook.canBorrow(bookname) == true) //책 남은 권수>0
                    cout << "   책을 빌릴 수 있습니다." << endl;
                else { //책 남은 개수==0
                    if (mybook.canReserv(bookname) == true)//예약 가능
                        cout << "   책은 다 대출중이지만 예약은 가능합니다." << endl;
                    else
                        cout << "   책이 다 대출중이고 예약도 다 찼습니다." << endl;
                }
            }
            else
                cout << "   책이 존재하지 않습니다." << endl;
            break;
         }

         case '6': 
             break;

          default:                               // Invalid command
              cout << "   Inactive or invalid command" << endl;
        }
    } while (cmd != '6');
    myperson.fileWrite();
    mybook.fileWrite();
}