#include "pch.h"

using namespace std;

using Func = function<void()>;

void FlyWithWingsBehavior()
{
	cout << "I'm flying with wings!!" << endl;
};

Func FlyWithCounterBehavior = [counter = 0]() mutable {
	++counter;
	cout << "I'm flying with wings " << counter << " time" << endl;
};

void QuackBehavior()
{
	cout << "Quack Quack!!!" << endl;
};

void SqueakBehavior()
{
	cout << "Squeek!!!" << endl;
};

void WaltzDanceBehavior()
{
	cout << "I'm dance waltz!" << endl;
};

void MenuetDanceBehavior()
{
	cout << "I'm dance menuet!" << endl;
};

class Duck
{
public:
	Duck(const Func& drawStrategy)
	{
		m_drawStrategy = drawStrategy;
	}

	void Fly() const
	{
		if (m_flyStrategy)
		{
			m_flyStrategy();
		}
	}

	void Quack() const
	{
		if (m_quackStrategy)
		{
			m_quackStrategy();
		}
	}

	void Dance() const
	{
		if (m_danceStrategy)
		{
			m_danceStrategy();
		}
	}

	void Draw() const
	{
		if (m_drawStrategy)
		{
			m_drawStrategy();
		}
	}

	void SetFlyStrategy(const Func& flyStrategy)
	{
		m_flyStrategy = flyStrategy;
	}

	void SetQuackStrategy(const Func& quackStrategy)
	{
		m_quackStrategy = quackStrategy;
	}

	void SetDanceStrategy(const Func& danceStrategy)
	{
		m_danceStrategy = danceStrategy;
	}

private:
	Func m_flyStrategy;
	Func m_quackStrategy;
	Func m_danceStrategy;
	Func m_drawStrategy;
};

Duck GetMallardDuck()
{
	Duck duck([]() {
		cout << "I'm mallard duck" << endl;
	});
	duck.SetFlyStrategy(FlyWithCounterBehavior);
	duck.SetQuackStrategy(QuackBehavior);
	duck.SetDanceStrategy(WaltzDanceBehavior);

	return duck;
}

Duck GetRedheadDuck()
{
	Duck duck([]() {
		cout << "I'm redhead duck" << endl;
	});
	duck.SetFlyStrategy(FlyWithCounterBehavior);
	duck.SetQuackStrategy(QuackBehavior);
	duck.SetDanceStrategy(MenuetDanceBehavior);

	return duck;
}

Duck GetRubberDuck()
{
	Duck duck([]() {
		cout << "I'm rubber duck" << endl;
	});
	duck.SetFlyStrategy(NULL);
	duck.SetQuackStrategy(SqueakBehavior);
	duck.SetDanceStrategy(NULL);

	return duck;
}

Duck GetDecoyDuck()
{
	Duck duck([]() {
		cout << "I'm decoy duck" << endl;
	});
	duck.SetFlyStrategy(NULL);
	duck.SetQuackStrategy(NULL);
	duck.SetDanceStrategy(NULL);

	return duck;
}

Duck GetModelDuck()
{
	Duck duck([]() {
		cout << "I'm model duck" << endl;
	});
	duck.SetFlyStrategy(NULL);
	duck.SetQuackStrategy(QuackBehavior);
	duck.SetDanceStrategy(NULL);

	return duck;
}

void DrawDuck(const Duck& duck)
{
	duck.Draw();
}

void PlayWithDuck(const Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	Duck mallardDuck = GetMallardDuck();
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyStrategy(NULL);
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyStrategy(FlyWithCounterBehavior);
	PlayWithDuck(mallardDuck);

	Duck redheadDuck = GetRedheadDuck();
	PlayWithDuck(redheadDuck);
	PlayWithDuck(redheadDuck);
	PlayWithDuck(mallardDuck);

	Duck rubberDuck = GetRubberDuck();
	PlayWithDuck(rubberDuck);

	Duck decoyDuck = GetDecoyDuck();
	PlayWithDuck(decoyDuck);

	Duck modelDuck = GetModelDuck();
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyStrategy(FlyWithWingsBehavior);
	PlayWithDuck(modelDuck);
}
