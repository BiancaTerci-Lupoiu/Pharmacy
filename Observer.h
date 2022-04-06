#pragma once
#include<vector>
using std::vector;

// definesc obiecte de tip observator care au o singura actiune: update
class Observer {
public:
	virtual void update() = 0;
};

// definesc obiecte de tip observabile (ce observa observatorii din vectorul observatori)
class Observable {
private:
	vector<Observer*> observatori;
public:
	void addObserver(Observer* obs) {
		observatori.push_back(obs);
	}
	void removeObserver(Observer* obs)
	{
		observatori.erase(std::remove(observatori.begin(),observatori.end(), obs), observatori.end());
	}
	void notify() {
		for (auto obs : observatori) {
			obs->update();
		}
	}
};