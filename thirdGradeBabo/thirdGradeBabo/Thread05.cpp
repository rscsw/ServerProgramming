#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <windows.h>
#include <conio.h>

using namespace std;

mutex m;
bool trigger = true;

void gotoxy(int x, int y) {
    COORD pos = { x,y }; //x, y ��ǥ ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //Ŀ�� ����
}


void print()
{
    int i = 0;
    while (trigger)
    {

        this_thread::sleep_for(std::chrono::milliseconds(1000));
        m.lock();
        gotoxy(0, i);
        std::cout << "�� & �� " << i << endl;
        i++;
        if (i > 5)
        {
            system("cls");
            i = 0;
        }
        m.unlock();
    }
}



int main()
{
    thread t;
    t = thread(print);

    std::string str;

    while (true)
    {
        if (_kbhit())
        {        //Ű���� �Է� Ȯ�� (true / false)
            char c = _getch();
            if (c == '/')
            {
                m.lock();
                gotoxy(0, 10);
                cin >> str;
                cin.ignore();
                gotoxy(0, 8);
                cout << str;
                m.unlock();
                if (str == "/q")
                {
                    trigger = false;
                    break;
                }
            }
        }
    }
    t.join();
}

