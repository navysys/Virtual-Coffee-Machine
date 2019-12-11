#include "CoffeeMachine.h"
#include <list>


CoffeeMachine::CoffeeMachine(): fState(new AcceptingCoins(std::unique_ptr<CoffeeMachine>(this))), fDrink(nullptr),
				fCoinLookup(
			   {{Coins::oneCent, "1c"}, 
				{Coins::twoCent, "2c"}, 
				{Coins::fiveCent, "5c"}, 
				{Coins::tenCent, "10c"}, 
				{Coins::twentyCent, "20c"}, 
				{Coins::fiftyCent, "50c"}, 
				{Coins::oneDollar, "$1"}, 
				{Coins::twoDollar, "$2"} })
{
	this->run();
}


CoffeeMachine::~CoffeeMachine()
{
}


void CoffeeMachine::run()
{
	while(fState.get())
	{
		fState->run();
	}
}

void CoffeeMachine::setState(std::unique_ptr<CoffeeMachineState> newState)
{
	fState = std::move(newState);
}

std::vector<Coins>& CoffeeMachine::getInsertedCoins()
{
	return fInsertedCoins;
}

int CoffeeMachine::getTotalAmount()
{
	return std::accumulate(fInsertedCoins.begin(), fInsertedCoins.end(), 0);
};

std::string CoffeeMachine::printTotalAmount()
{
	return intToDollarString(getTotalAmount());
}

std::string CoffeeMachine::intToDollarString(int aAmount)
{
	std::string dollars = std::to_string(std::abs(aAmount / 100));

	int temp = aAmount % 100;
	temp = std::abs(temp);
	std::string cents = std::to_string(temp);


	if (temp < 10)
		cents = "0" + cents;

	if (aAmount < 0)
	{
		return "-$" + dollars + "." + cents;
	}
	else
	{
		return "$" + dollars + "." + cents;
	}
}

void CoffeeMachine::insertCoin(Coins aCoin)
{
	if (aCoin == 1 || aCoin == 2)
		dispenceCoin(aCoin);
	else
		fInsertedCoins.push_back(aCoin);
}

void CoffeeMachine::dispenceCoin(Coins aCoin)
{
	std::cout << "Dispencing: " << fCoinLookup.at(aCoin) << std::endl;
}

void CoffeeMachine::returnCoins()
{
	std::string print = "[";
	for (auto i : fInsertedCoins) {
		print = print + fCoinLookup.at(i) + ", ";
	}
	print += "]";
	std::cout << print << std::endl;
	fInsertedCoins.clear();
}

void CoffeeMachine::makeDrink(std::shared_ptr<Drink> aDrink)
{
	fDrink = std::make_shared<Cup>(aDrink);
}

void CoffeeMachine::dispenceDrink()
{
	std::cout << fDrink->getName() << std::endl;
	fDrink.reset();
}

void CoffeeMachine::dispenceChange()
{
	std::vector<Coins> changeCoins;
	int change = getTotalAmount() - fDrink->getCost();

	for (auto i = fCoins.rbegin(); i != fCoins.rend(); i++)
	{
		while (change >= *i)
		{
			change = change - *i;
			changeCoins.push_back(*i);
		}
	}
	std::cout << "Change: [ ";
	for (auto c : changeCoins)
	{
		std::cout << fCoinLookup.at(c) << ", ";
	}

	std::cout << " ]" << std::endl;
	fInsertedCoins.clear(); // remove coins
}




