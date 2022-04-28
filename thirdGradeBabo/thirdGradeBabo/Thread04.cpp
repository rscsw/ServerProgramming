//����� �� & ��
#include <iostream> //iostream ��� ���� (������� ���� ��� ����)
#include <thread>   //������ ��� ����
#include <mutex>    //���ؽ� ��� ����
#include <string>   //��Ʈ�� ��� ����
#include <chrono>   //ũ�γ� ��� ����

using namespace std; //std��� �̸��� namespace ��� ����

class Actor //Actor��� �̸��� Ŭ���� ���� (��󸶿� �⿬�� ���)
{
public:
	string name; //����� �̸�
	thread th;   //����� �� ����� ������
	mutex heart; //����� ���� (���ؽ��̱� ������ ��װ� Ǯ �� �ִ�)

	Actor() {} //������
	virtual void Start(Actor* actor) {} //����� �Լ��̱� ������ ��ӹ��� Ŭ������ ����� ����� �� �ִ�
	virtual void Run(Actor* actor) {}   //�����ͷ� �޸� �ּҸ� �����Ѵ�
};


class Hoon : public Actor //Actor Ŭ������ ��ӹ��� Hoon Ŭ���� ����
{
public:
	void(Hoon::* RunPointer)(Actor* actor); //�Լ� ������ ����, �Ű������� actor ����

	Hoon() //������
	{
		name = "����"; //����� �̸��� "����"�� �����Ѵ�
	}

	void Start(Actor* actor) //Start �Լ� �������̵�, ��� ����� ������ �޾ƿ´�
	{
		RunPointer = &Hoon::Run;			  //�����ͷ� ������ RunPointer�� class Hoon�� �ִ� Run�̶�� �Լ��� �ּҰ��� �޾ƿ´�
		th = thread(RunPointer, this, actor); //�Լ��� ������ ������(RunPointer), RunPounter�� ����Ű�� �ִ� �Լ�(this = Hoon::Run), �Ű����� actor
	}

	void Run(Actor* actor) { //Run �Լ� �������̵�, �Ʒ��� �Լ����� ������� ����ǵ��� ��
		FallinLove(actor);   //�� �Լ��� ���� ������ �Ʒ� ����
		Flirting(actor);
		Fuckyou(actor);
	}

	void FallinLove(Actor* actor) //����� ������ �Լ�
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));						   //1�� �����ٰ� ����ǵ��� ����
		cout << "�� : (�� ���ڱ�..." << actor->name << "��(��) ���� �ʹ� ������....)\n\n"; //��� ��츦 ���� ������ ����
		heart.lock();																	   //����(���ؽ�)�� ����� �ɾ� �ٸ� ����� �����ӿ� �Ժη� ħ������ ���ϰ� ��
		this_thread::sleep_for(std::chrono::milliseconds(1000));						   //1�� �����ٰ� ����ǵ��� ����
	}

	void Flirting(Actor* actor) //�����ϴ� ��븦 ��Ȥ�ϴ� �Լ�
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));				//1�� �����ٰ� ����ǵ��� ����
		cout << "�� : " << actor->name << "... ���濡��... ���԰���??\n\n"; //��� ��츦 ��Ȥ��
		actor->heart.lock();													//��� ����� ����(���ؽ�)�� ����� �ɾ� �ٸ� ����� ������ �� ���� �����
	}																			//FallinLove �Լ����� �̹� ������ lock�� �ɾ��� ������ ��� ����� ������ lock�� �ɷ��� ������ �ɸ��� �ʴ´�, ����� �߻�

	void Fuckyou(Actor* actor) //������� ���� ��ť�� ������ �Լ�
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));	  //1�� �����ٰ� ����ǵ��� ����
		cout << "�� : (��..." << actor->name << "...��������...\n\n"; //��� ��쿡�� ���� ������
		this_thread::sleep_for(std::chrono::milliseconds(1000));	  //1�� �����ٰ� ����ǵ��� ����
	}
};

class Seok : public Actor //���� ����^^
{
public:
	void(Seok::* RunPointer)(Actor* actor);

	Seok()
	{
		name = "����";
	}

	void Start(Actor* actor)
	{
		RunPointer = &Seok::Run;
		th = thread(RunPointer, this, actor);
	}

	void Run(Actor* actor) {
		FallinLove(actor);
		Flirting(actor);
		Fuckyou(actor);
	}

	void FallinLove(Actor* actor)
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "�� : (�� ���ڱ�..." << actor->name << "��(��) ���� �ʹ� ������....)\n\n";
		heart.lock();
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	void Flirting(Actor* actor)
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "�� : " << actor->name << "... ���濡��... ���԰���??\n\n";
		actor->heart.lock();
	}

	void Fuckyou(Actor* actor)
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "�� : (��..." << actor->name << "...��������...\n\n";
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
};

class Su : public Actor
{
public:
	void(Su::* RunPointer)(Actor* actor);

	Su()
	{
		name = "��";
	}

	void Start(Actor* actor)
	{
		RunPointer = &Su::Run;
		th = thread(RunPointer, this, actor);
	}

	void Run(Actor* actor) {
		FallinLove(actor);
		Flirting(actor);
		Fuckyou(actor);
	}

	void FallinLove(Actor* actor)
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "�� : (�� ���ڱ�..." << actor->name << "��(��) ���� �ʹ� ������....)\n\n";
		heart.lock();
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	void Flirting(Actor* actor)
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "�� : " << actor->name << "... ���濡��... ���԰���??\n\n";
		actor->heart.lock();
	}

	void Fuckyou(Actor* actor)
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "�� : (��..." << actor->name << "...��������...\n\n";
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
};

int main() //Thread0 PD : ������ (main)
{
	Actor* h = new Hoon(); //�� ��� ����
	Actor* s = new Seok(); //�� ��� ����
	Actor* su = new Su();  //�� ��� ����

	h->Start(s);  //�� ��찡 �� ����� ������ �޾ƿ� �� �ֵ��� ����
	s->Start(su); //�� ��찡 �� ����� ������ �޾ƿ� �� �ֵ��� ����
	su->Start(h); //�� ��찡 �� ����� ������ �޾ƿ� �� �ֵ��� ����

	h->th.join();  //�� ����� th�� ����� Run �Լ��� ����� ������ ���
	s->th.join();  //�� ����� th�� ����� Run �Լ��� ����� ������ ���
	su->th.join(); //�� ����� th�� ����� Run �Լ��� ����� ������ ���

	this_thread::sleep_for(std::chrono::milliseconds(1000)); //1�� �����ٰ� ����ǵ��� ����
	delete(h);  //�� ��� ����
	delete(s);  //�� ��� ����
	delete(su); //�� ��� ����

	return 0; //���α׷� ����
}