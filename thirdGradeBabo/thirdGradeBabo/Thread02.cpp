//����� �� & ��
/*#include <iostream>
#include <thread> //���Ĵٵ� ���̺귯���� ������ std��� ���ӽ����̽��� �ʿ��ϴ�
#include <mutex>
#include <string>
#include <chrono>

using namespace std;

string taesu = "�־�...";
mutex taesu_maum;

void Propose(string my_name, string his_name)
{
	cout << my_name << " : " << his_name << ".. ����� �������� ����մϴ�.." << endl;
	cout << my_name << " : " << his_name << ".. �� ������.." << endl;
	this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void GetLove(string name)
{
	taesu_maum.lock(); //lock�� �Ǹ� �����ص� ��ٸ��� ��
	taesu = name;
	Propose("��", taesu);
	this_thread::sleep_for(std::chrono::milliseconds(5000)); //5��
	cout << "�� : " << name << "�츮 �����\n";
	taesu_maum.unlock();
}

void main() //PD : ������(main)
{
	thread na_seok_hoon(GetLove, "���ƾ�.."); //�� ������ �߿� �ؿ� �ִ� �� ���� ����� �� ����
	thread oh_jeong_seok(GetLove, "������..");

	na_seok_hoon.join(); //main ������� ���� �����尡 �������ٴ� ���ӽ��� �Լ�
	oh_jeong_seok.join();
}*/