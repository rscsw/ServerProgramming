//����� �� & ��
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>

using namespace std;

class Actor
{
public:
	string name;
	thread th;
	mutex heart;

	Actor() {}
	virtual void Start(Actor* actor) {}
	virtual void Run(Actor* actor) {}
};


class Hoon : public Actor
{
public:
	void(Hoon::* RunPointer)(Actor* actor);

	Hoon()
	{
		name = "����";
	}

	void Start(Actor* actor)
	{
		RunPointer = &Hoon::Run;
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

class Seok : public Actor
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
	Actor* h = new Hoon();
	Actor* s = new Seok();
	Actor* su = new Su();

	h->Start(s);
	s->Start(su);
	su->Start(h);

	h->th.join();
	s->th.join();
	su->th.join();

	this_thread::sleep_for(std::chrono::milliseconds(1000));
	delete(h);
	delete(s);
	delete(su);

	return 0;
}