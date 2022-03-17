//목요드라마 석 & 훈

#include <iostream>
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
	taesu_maum.lock();
	taesu = name;
	Propose("수", taesu);
	this_thread::sleep_for(std::chrono::milliseconds(5000)); //5년
	cout << "수 : " << name << "우리 헤어져";
	taesu_maum.unlock();
}

void main() //PD : 이은석(main)
{
	thread na_seok_hoon(GetLove, "석훈아..");
	thread oh_jeong_seok(GetLove, "정석아..");

	na_seok_hoon.join();
	oh_jeong_seok.join();
}