//목요드라마 석 & 훈
#include <iostream> //iostream 사용 선언 (입출력을 위한 헤더 파일)
#include <thread>   //쓰레드 사용 선언
#include <mutex>    //뮤텍스 사용 선언
#include <string>   //스트링 사용 선언
#include <chrono>   //크로노 사용 선언

using namespace std; //std라는 이름의 namespace 사용 선언

class Actor //Actor라는 이름의 클래스 생성 (드라마에 출연할 배우)
{
public:
	string name; //배우의 이름
	thread th;   //출력할 때 사용할 쓰레드
	mutex heart; //배우의 마음 (뮤텍스이기 때문에 잠그고 풀 수 있다)

	Actor() {} //생성자
	virtual void Start(Actor* actor) {} //버츄얼 함수이기 때문에 상속받은 클래스가 덮어씌워 사용할 수 있다
	virtual void Run(Actor* actor) {}   //포인터로 메모리 주소를 저장한다
};


class Hoon : public Actor //Actor 클래스를 상속받은 Hoon 클래스 생성
{
public:
	void(Hoon::* RunPointer)(Actor* actor); //함수 포인터 선언, 매개변수로 actor 선언

	Hoon() //생성자
	{
		name = "훈이"; //배우의 이름을 "훈이"로 설정한다
	}

	void Start(Actor* actor) //Start 함수 오버라이드, 상대 배우의 변수를 받아온다
	{
		RunPointer = &Hoon::Run;			  //포인터로 선언한 RunPointer는 class Hoon에 있는 Run이라는 함수의 주소값을 받아온다
		th = thread(RunPointer, this, actor); //함수를 지목할 포인터(RunPointer), RunPounter가 가리키고 있는 함수(this = Hoon::Run), 매개변수 actor
	}

	void Run(Actor* actor) { //Run 함수 오버라이드, 아래의 함수들이 순서대로 실행되도록 함
		FallinLove(actor);   //각 함수에 대한 설명은 아래 참고
		Flirting(actor);
		Fuckyou(actor);
	}

	void FallinLove(Actor* actor) //사랑에 빠지는 함수
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));						   //1초 쉬었다가 실행되도록 해줌
		cout << "훈 : (나 갑자기..." << actor->name << "을(를) 보니 너무 설렌다....)\n\n"; //상대 배우를 보고 설레기 시작
		heart.lock();																	   //마음(뮤텍스)에 잠금을 걸어 다른 사람이 마음속에 함부로 침입하지 못하게 함
		this_thread::sleep_for(std::chrono::milliseconds(1000));						   //1초 쉬었다가 실행되도록 해줌
	}

	void Flirting(Actor* actor) //좋아하는 상대를 유혹하는 함수
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));				//1초 쉬었다가 실행되도록 해줌
		cout << "훈 : " << actor->name << "... 내방에서... 라면먹고갈래??\n\n"; //상대 배우를 유혹함
		actor->heart.lock();													//상대 배우의 마음(뮤텍스)에 잠금을 걸어 다른 사람을 좋아할 수 없게 만든다
	}																			//FallinLove 함수에서 이미 마음에 lock을 걸었기 때문에 상대 배우의 마음에 lock을 걸려고 하지만 걸리지 않는다, 데드락 발생

	void Fuckyou(Actor* actor) //헤어지기 위해 뻐큐를 날리는 함수
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));	  //1초 쉬었다가 실행되도록 해줌
		cout << "훈 : (아..." << actor->name << "...정떨어져...\n\n"; //상대 배우에게 정이 떨어짐
		this_thread::sleep_for(std::chrono::milliseconds(1000));	  //1초 쉬었다가 실행되도록 해줌
	}
};

class Seok : public Actor //이하 동문^^
{
public:
	void(Seok::* RunPointer)(Actor* actor);

	Seok()
	{
		name = "석이";
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
		cout << "석 : (나 갑자기..." << actor->name << "을(를) 보니 너무 설렌다....)\n\n";
		heart.lock();
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	void Flirting(Actor* actor)
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "석 : " << actor->name << "... 내방에서... 라면먹고갈래??\n\n";
		actor->heart.lock();
	}

	void Fuckyou(Actor* actor)
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "석 : (아..." << actor->name << "...정떨어져...\n\n";
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
};

class Su : public Actor
{
public:
	void(Su::* RunPointer)(Actor* actor);

	Su()
	{
		name = "수";
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
		cout << "수 : (나 갑자기..." << actor->name << "을(를) 보니 너무 설렌다....)\n\n";
		heart.lock();
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	void Flirting(Actor* actor)
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "수 : " << actor->name << "... 내방에서... 라면먹고갈래??\n\n";
		actor->heart.lock();
	}

	void Fuckyou(Actor* actor)
	{
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout << "수 : (아..." << actor->name << "...정떨어져...\n\n";
		this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
};

int main() //Thread0 PD : 이은석 (main)
{
	Actor* h = new Hoon(); //훈 배우 생성
	Actor* s = new Seok(); //석 배우 생성
	Actor* su = new Su();  //수 배우 생성

	h->Start(s);  //훈 배우가 석 배우의 변수를 받아올 수 있도록 해줌
	s->Start(su); //석 배우가 수 배우의 변수를 받아올 수 있도록 해줌
	su->Start(h); //수 배우가 석 배우의 변수를 받아올 수 있도록 해줌

	h->th.join();  //훈 배우의 th에 저장된 Run 함수가 종료될 때까지 대기
	s->th.join();  //석 배우의 th에 저장된 Run 함수가 종료될 때까지 대기
	su->th.join(); //수 배우의 th에 저장된 Run 함수가 종료될 때까지 대기

	this_thread::sleep_for(std::chrono::milliseconds(1000)); //1초 쉬었다가 실행되도록 해줌
	delete(h);  //훈 배우 삭제
	delete(s);  //석 배우 삭제
	delete(su); //수 배우 삭제

	return 0; //프로그램 종료
}