#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int trigger;

void seokHoon()
{
	while (trigger == 0)
	{
		cout << "나석훈 : 정석아 사랑해\n";
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void JeongSeok()
{
	while (trigger == 0)
	{
		this_thread::sleep_for(std::chrono::milliseconds(500));
		cout << "오정석 : 석훈아 사랑해\n";
		this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

int main()
{
	trigger = 0;
	cout << "그들의 사랑이 시작된다...\n";

	thread na(seokHoon);
	thread oh(JeongSeok);

	while (trigger == 0)
	{
		cin >> trigger;
	}

	na.join();
	oh.join();

	cout << "그들의 사랑이 끝났다...\n";
}