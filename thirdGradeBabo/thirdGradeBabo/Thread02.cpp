//목요드라마 석 & 훈
/*#include <iostream>
#include <thread> //스탠다드 라이브러리기 때문에 std라는 네임스페이스가 필요하다
#include <mutex>
#include <string>
#include <chrono>

using namespace std;

string taesu = "솔아...";
mutex taesu_maum;

void Propose(string my_name, string his_name)
{
	cout << my_name << " : " << his_name << ".. 당신을 진심으로 사랑합니다.." << endl;
	cout << my_name << " : " << his_name << ".. 날 가져줘.." << endl;
	this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void GetLove(string name)
{
	taesu_maum.lock(); //lock이 되면 접근해도 기다리게 됨
	taesu = name;
	Propose("수", taesu);
	this_thread::sleep_for(std::chrono::milliseconds(5000)); //5년
	cout << "수 : " << name << "우리 헤어져\n";
	taesu_maum.unlock();
}

void main() //PD : 이은석(main)
{
	thread na_seok_hoon(GetLove, "석훈아.."); //두 스레드 중에 밑에 있는 게 먼저 실행될 수 있음
	thread oh_jeong_seok(GetLove, "정석아..");

	na_seok_hoon.join(); //main 스레드와 위의 스레드가 합쳐진다는 뉘앙스의 함수
	oh_jeong_seok.join();
}*/