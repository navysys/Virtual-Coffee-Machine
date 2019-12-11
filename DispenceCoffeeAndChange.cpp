#include "CoffeeMachineState.h"
#include "CoffeeMachine.h"

DispenceCoffeeAndChange::DispenceCoffeeAndChange(std::shared_ptr<CoffeeMachine> aMachine): CoffeeMachineState(std::move(aMachine))
{}

DispenceCoffeeAndChange::~DispenceCoffeeAndChange()
{}

void DispenceCoffeeAndChange::run()
{
	fMachine->dispenceChange();
	fMachine->dispenceDrink();
	fMachine->setState(std::unique_ptr<CoffeeMachineState>(new AcceptingCoins(fMachine)));
}