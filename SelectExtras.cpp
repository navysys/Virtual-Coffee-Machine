#include "CoffeeMachine.h"
#include "CoffeeMachineState.h"
#include <memory>

SelectExtras::SelectExtras(std::shared_ptr<Drink> aDrink,std::shared_ptr<CoffeeMachine> aMachine): CoffeeMachineState(std::move(aMachine)), fDrink(aDrink)
{

}

SelectExtras::~SelectExtras() 
{
}

void SelectExtras::run()
{
	std::cout << "____________________" << std::endl;
	std::cout << "Select Extras" << std::endl;
	std::cout << "1. Sugar. $0.10" << std::endl;
	std::cout << "2. Chocolate. $0.50" << std::endl;
	std::cout << "3. Malt. $0.20" << std::endl;
	std::cout << "4. Extra Cream. $0.50" << std::endl;
	std::cout << "5. Make Coffee" << std::endl;
	std::cout << "6. Undo" << std::endl;
	std::cout << "0. Return" << std::endl;
	std::cout << "____________________" << std::endl;
	std::cout << "You current order is: " << fDrink->getName() << " at " << fMachine->intToDollarString(fDrink->getCost()) << std::endl;
	std::cout << "You have: " << fMachine->printTotalAmount() << " Change: " << fMachine->intToDollarString(fMachine->getTotalAmount() - fDrink->getCost()) << std::endl;
	int input = -1;

	std::cout << "Enter value 0-5:>";
	std::cin >> input;

	if (input < 0 || input > 5)
	{
		std::cout << std::endl << "Invalid Input" << std::endl;
		return;
	}

	if (input == 0)
		fMachine->setState(std::unique_ptr<CoffeeMachineState>(new SelectCoffee(fMachine)));

	if (input == 1)
		fDrink = std::make_shared<Sugar>(fDrink);

	if (input == 2)
		fDrink = std::make_shared<Chocolate>(fDrink);

	if (input == 3)
		fDrink = std::make_shared<Malt>(fDrink);

	if (input == 4)
		fDrink = std::make_shared<Cream>(fDrink);

	if (input == 5)
	{

		if (fMachine->getTotalAmount() - fDrink->getCost() < 0)
		{
			std::cout << std::endl << "Invalid funds" << std::endl;
		}
		else
		{
			fMachine->makeDrink(fDrink);
			//next state
			fMachine->setState(std::unique_ptr<CoffeeMachineState>(new DispenceCoffeeAndChange(fMachine)));
			return;
		}


	}
}