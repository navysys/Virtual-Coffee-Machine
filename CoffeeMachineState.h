#pragma once
#include <vector>
#include <memory>
#include <stack>
#include "Drink.h"

class CoffeeMachine;

class CoffeeMachineState
{
public:
	CoffeeMachineState(std::shared_ptr<CoffeeMachine> aMachine) : fMachine(std::move(aMachine)) {};
	virtual ~CoffeeMachineState() {}

	virtual void run() {};
protected:
	std::shared_ptr<CoffeeMachine> fMachine;
};

class AcceptingCoins : public CoffeeMachineState
{
public:
	AcceptingCoins(std::shared_ptr<CoffeeMachine> aMachine);
	virtual ~AcceptingCoins();
	
	void run() override;

};

class SelectCoffee : public CoffeeMachineState
{
public:
	SelectCoffee(std::shared_ptr<CoffeeMachine> aMachine);
	virtual ~SelectCoffee();
	void run() override;
};

class SelectExtras : public CoffeeMachineState
{
private:
	std::shared_ptr<Drink> fDrink;
public:
	SelectExtras(std::shared_ptr<Drink> aDrink, std::shared_ptr<CoffeeMachine> aMachine);
	virtual ~SelectExtras();

	void run() override;

};

class DispenceCoffeeAndChange : public CoffeeMachineState
{
public:
	DispenceCoffeeAndChange(std::shared_ptr<CoffeeMachine> aMachine);
	virtual ~DispenceCoffeeAndChange();

	void run() override;
};


