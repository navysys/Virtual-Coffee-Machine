#include "CoffeeMachineState.h"
#include "CoffeeMachine.h"
#include <iostream>

AcceptingCoins::AcceptingCoins(std::shared_ptr<CoffeeMachine> aMachine) : CoffeeMachineState(std::move(aMachine))
{
}

AcceptingCoins::~AcceptingCoins() 
{
}


void AcceptingCoins::run()
{
	std::vector<Coins> coins = { Coins::oneCent, Coins::twoCent, Coins::fiveCent, Coins::tenCent, Coins::twentyCent, Coins::fiftyCent, Coins::oneDollar, Coins::twoDollar };
	std::cout << "______________________" << std::endl;
	std::cout << "Please insert coins :)" << std::endl;

	int i = 1;
	for (auto key_pair : fMachine->fCoinLookup)
	{
		std::cout << std::to_string(i) << ". " << key_pair.second << std::endl;
		i++;
	}

	std::cout << "9. Continue" << std::endl;
	std::cout << "0. Return Coins" << std::endl;
	std::cout << "______________________" << std::endl;
	std::cout << fMachine->printTotalAmount() << std::endl;

	int input = -1;


	std::cout << "Enter value from 0-9 :>";
	std::cin >> input;
		
	if (input < 0 || input > 9) 
	{
		//invalid input
		std::cout << std::endl << "Invalid input" << std::endl;
		input = -1;
		return;
	}

	if (input == 9)
	{
		fMachine->setState(std::unique_ptr<CoffeeMachineState>(new SelectCoffee(fMachine)));
		return;
	}
		
	if (input == 0)
	{
		//return coins, set state new this state to reset
		fMachine->returnCoins();
		fMachine->setState(std::unique_ptr<CoffeeMachineState>(new AcceptingCoins(fMachine)));
		return;
	}

	input--;
	fMachine->insertCoin(coins.at(input));
	std::cout << std::endl << fMachine->printTotalAmount() << std::endl;
	

}

