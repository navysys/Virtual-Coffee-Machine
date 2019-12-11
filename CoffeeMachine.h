#pragma once
#include "Drink.h"
#include "CoffeeMachineState.h"
#include <stack>
#include <numeric>
#include <iostream>
#include <map>
#include <vector>

enum Coins
{
	oneCent = 1, twoCent = 2, fiveCent = 5, tenCent = 10, twentyCent = 20, fiftyCent = 50, oneDollar = 100, twoDollar = 200
};


class CoffeeMachine
{
private:
	std::unique_ptr<CoffeeMachineState> fState;
	std::vector<Coins> fInsertedCoins;
	std::shared_ptr<Drink> fDrink;
	void run();
public:
	const std::map<Coins, std::string> fCoinLookup;
	const std::vector<Coins> fCoins = { Coins::oneCent, Coins::twoCent, Coins::fiveCent, Coins::tenCent, Coins::twentyCent, Coins::fiftyCent, Coins::oneDollar, Coins::twoDollar };

	CoffeeMachine();
	~CoffeeMachine();

	void setState(std::unique_ptr<CoffeeMachineState> newState);

	std::vector<Coins>& getInsertedCoins();
	int getTotalAmount();
	std::string printTotalAmount();
	std::string intToDollarString(int aAmount);
	void insertCoin(Coins aCoin);
	void dispenceCoin(Coins aCoin);
	void returnCoins();

	void makeDrink(std::shared_ptr<Drink> aDrink);
	void dispenceDrink();
	void dispenceChange();
};


