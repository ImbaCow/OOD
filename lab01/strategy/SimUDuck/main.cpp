#include "pch.h"

using namespace std;

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		cout << "I'm flying with wings!!" << endl;
	}
};

class FlyWithCount : public IFlyBehavior
{
public:
	void Fly() override
	{
		++counter;
		cout << "I'm flying with wings " << counter << " time" << endl;
	}

private:
	size_t counter;
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
};

struct IQuackBehavior
{
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};

class QuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Quack Quack!!!" << endl;
	}
};
class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Squeek!!!" << endl;
	}
};

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override {}
};

struct IDanceBehavior
{
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};

class WaltzDanceBehavior : public IDanceBehavior
{
	void Dance() override
	{
		cout << "I'm dancing waltz!" << endl;
	}
};

class MenuetDanceBehavior : public IDanceBehavior
{
	void Dance() override
	{
		cout << "I'm dancing menuet!" << endl;
	}
};

class NoDanceBehavior : public IDanceBehavior
{
	void Dance() override {}
};

class Duck
{
public:
	Duck(unique_ptr<IFlyBehavior>&& flyBehavior,
		unique_ptr<IQuackBehavior>&& quackBehavior,
		unique_ptr<IDanceBehavior>&& danceBehavior)
		: m_quackStrategy(move(quackBehavior))
		, m_danceStrategy(move(danceBehavior))
	{
		SetFlyBehavior(move(flyBehavior));
	}

	void Quack() const
	{
		m_quackStrategy->Quack();
	}

	void Swim()
	{
		cout << "I'm swimming" << endl;
	}

	void Fly()
	{
		m_flyStrategy->Fly();
	}

	void Dance()
	{
		m_danceStrategy->Dance();
	}

	void SetFlyBehavior(unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		m_flyStrategy = move(flyBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	unique_ptr<IFlyBehavior> m_flyStrategy;
	unique_ptr<IQuackBehavior> m_quackStrategy;
	unique_ptr<IDanceBehavior> m_danceStrategy;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(make_unique<FlyWithCount>(), make_unique<QuackBehavior>(), make_unique<WaltzDanceBehavior>())
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(make_unique<FlyWithCount>(), make_unique<QuackBehavior>(), make_unique<MenuetDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<MuteQuackBehavior>(), make_unique<NoDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<SqueakBehavior>(), make_unique<NoDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<QuackBehavior>(), make_unique<NoDanceBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyBehavior(make_unique<FlyNoWay>());
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyBehavior(make_unique<FlyWithCount>());
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(make_unique<FlyWithWings>());
	PlayWithDuck(modelDuck);
}
