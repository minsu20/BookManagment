//--------------------------------------------------------------------------------
//  2020112377 ��ǻ�Ͱ������� ��μ�
//  ��ȭ���α׷���-01 ������Ʈ
//  main.cpp
//----------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "Person.h"
#include "Book.h"

void print_help()   //Print Commands
{
    cout << endl << "   [���� ���� ���α׷�]" << endl;
    cout << "   1-ȸ������" << endl;
    cout << "   2-ȸ��Ż��" << endl;
    cout << "   3-���� ����" << endl;
    cout << "   4-���� �ݳ�" << endl;
    cout << "   5-å ���Ⱑ�� ���� ����" << endl;
    cout << "   6-�����ϱ�" << endl;
    cout << "   **���α׷��� �� �����ϰ� ��ĥ �� �ݵ�� �����ϱ⸦ ���ֽʽÿ�. \n     �����ϱ⸦ ���ϸ� ������ ������Ʈ�� �ȵ˴ϴ�**" << endl;
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
        case '1'://ȸ�� �߰�
            cin.ignore();
            myperson.insert();
            break;

        case '2'://ȸ�� ����
            cin.ignore();
            myperson.remove();
            break;

        case '3': { //å ����
            cin.ignore();
            cout << "   ȸ�� id�� �Է��ϼ���. :";
            string memberid;
            getline(cin, memberid);
            if (myperson.isMember(memberid) == true) {
                cout << "   ���� å�� �̸��� �Է��ϼ���. : ";
                string bookname;
                getline(cin, bookname);
                if (mybook.canFind(bookname) == true) { //å�� ����
                    if (mybook.canBorrow(bookname) == true) {//���е� ����
                        cout << "   �ش� å�� ������ �����մϴ�. " << endl;
                            myperson.borrowBook(bookname); //å�� ����
                            mybook.borrowBook(bookname); //å����Ʈ���� �뿩���� ���� 1����
                    }
                    else { //å�� ���� ������ ����x
                        if (mybook.canReserv(bookname) == true)//�����ڰ� ������
                            mybook.insertReserv(memberid, bookname); //����
                        else //������ ����
                            cout << "   �����ڵ� �̹� �����մϴ�." << endl;
                    }
                }
                else { //å�� ����x
                    cout << "   �������� �ʴ� å�Դϴ�." << endl;
                }
            }
            else {
                cout << "   ��ϵ� ȸ���� �ƴմϴ�. " << endl;
            }
            break;
        }

        case '4': { //å �ݳ�
            cin.ignore();
            cout << "   ȸ�� id�� �Է��ϼ���. :";
            string memberid;
            getline(cin, memberid);
            if (myperson.isMember(memberid) == true) {//����� ���
                cout << "   ���ȴ� å�� �̸��� �Է��ϼ���. : ";
                string bookname;
                getline(cin, bookname);
                if (myperson.returnBook(bookname) == true) {//���� å�� ���
                    cout << "   ���� å�� �½��ϴ�." << endl;
                      if (mybook.canReserv(bookname) == true) { //�����ڰ� ������
                        mybook.returnBook(bookname);
                    }//å����Ʈ���� �뿩���� ���� 1 ����

                    else { //�����ڰ� ������
                        string reservid = mybook.reservId(bookname);
                        mybook.removeReserv(memberid, bookname);//�����ڸ�ܿ��� ��������
                        if (myperson.isMember(reservid) == true) {//ȸ����ܿ��� cursor�� �����ڷ� �̵�
                            myperson.borrowBook(bookname); //������ å �ڵ����� ������
                            cout << "   �����ڰ� å�� ���Ƚ��ϴ�" << endl;
                        }
                    }
                  }

                else {
                    cout << "   �� å�� ������ �ʾҽ��ϴ�. " << endl;
                }
            }
            else {
                cout << "   ��ϵ� ȸ���� �ƴմϴ�. " << endl;
            }
            break;
        }

        case '5': {   //å ���� ���� ����
            cin.ignore();
            cout << "   å�� �̸��� �Է��ϼ���.: ";
            string bookname;
            getline(cin, bookname);
            if (mybook.canFind(bookname) == true) { //å ����
                if (mybook.canBorrow(bookname) == true) //å ���� �Ǽ�>0
                    cout << "   å�� ���� �� �ֽ��ϴ�." << endl;
                else { //å ���� ����==0
                    if (mybook.canReserv(bookname) == true)//���� ����
                        cout << "   å�� �� ������������ ������ �����մϴ�." << endl;
                    else
                        cout << "   å�� �� �������̰� ���൵ �� á���ϴ�." << endl;
                }
            }
            else
                cout << "   å�� �������� �ʽ��ϴ�." << endl;
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