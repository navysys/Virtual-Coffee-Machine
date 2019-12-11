#include "CoffeeMachineState.h"
#include "CoffeeMachine.h"
#include <iostream>

SelectCoffee::SelectCoffee(std::shared_ptr<CoffeeMachine> aMachine): CoffeeMachineState(std::move(aMachine))
{
}

SelectCoffee::~SelectCoffee()
{
}

void SelectCoffee::run()
{
	std::cout << "____________________" << std::endl;
	std::cout << "Please Select a coffee" << std::endl;
	std::cout << "1. Cappuccino. $3.50" << std::endl;
	std::cout << "2. Latte. $3.00" << std::endl;
	std::cout << "3. Decaf. $4.00" << std::endl;
	std::cout << "4. Continue" << std::endl;
	std::cout << "0. Return" << std::endl;
	std::cout << "____________________" << std::endl;
	std::cout << fMachine->printTotalAmount() << std::endl;
	int input = -1;
	std::shared_ptr<Drink> coffee;

	while (true)
	{
		std::cout << "Enter value 0-4:>";
		std::cin >> input;

		if (input < 0 || input > 4)
		{
			std::cout << std::endl << "Invalid Input" << std::endl;
			input = -1;
			continue;
		}

		if (input == 0)
		{
			fMachine->setState(std::unique_ptr<CoffeeMachineState>(new AcceptingCoins(fMachine)));
			break;
		}

		switch (input)
		{
		case 1: 
			coffee = std::make_shared<Cappuccino>();
			break;
		case 2:
			coffee = std::make_shared<Latte>();
			break;
		case 3:
			coffee = std::make_shared<Decaf>();
			break;
		default:
			break;
		}

		if (input == 4)
		{
			if (!coffee)
			{
				std::cout << std::endl << "Select a Coffee before continuing" << std::endl;
				continue;
			}
			else
			{
				if (fMachine->getTotalAmount() - coffee->getCost() < 0)
				{
					std::cout << std::endl << "Invalid funds" << std::endl;
				}
				else
				{
					fMachine->setState(std::unique_ptr<CoffeeMachineState>(new SelectExtras(coffee, fMachine)));
					return;
				}
				
			}

		}

		std::cout << "You selected: " << coffee->getName() << " for " << fMachine->intToDollarString(coffee->getCost()) << " Change: " << fMachine->intToDollarString(fMachine->getTotalAmount() - coffee->getCost()) << std::endl;
	}

}
