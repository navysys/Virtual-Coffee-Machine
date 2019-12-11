#pragma once

#pragma once
#include <string>


class Drink
{
public:
	Drink() = default;
	Drink(std::string name, int cost) : fName(name), fCost(cost) {}
	virtual ~Drink() {  };

	virtual std::string getName() { return fName; }
	virtual int getCost() { return fCost; }
protected:
	std::string fName;
	int fCost;

};

class Cappuccino : public Drink
{
public:
	Cappuccino() : Drink("Cappuccino", 350) {};
	~Cappuccino() = default;
};

class Latte : public Drink
{
public:
	Latte() : Drink("Latte", 300) {};
	~Latte() = default;
};

class Decaf : public Drink
{
public:
	Decaf() : Drink("Decaf", 400) {};
	~Decaf() = default;

};

class DrinkExtrasDecorator : public Drink
{
public:
	explicit DrinkExtrasDecorator(std::shared_ptr<Drink> drink) : fDrink(drink) {}
	virtual ~DrinkExtrasDecorator() { };
	virtual std::string getName() = 0;
	virtual int getCost() = 0;
protected:
	std::shared_ptr<Drink> fDrink;
};

class Sugar : public DrinkExtrasDecorator
{
public:
	explicit Sugar(std::shared_ptr<Drink> drink) : DrinkExtrasDecorator(drink) {};
	~Sugar() = default;

	std::string getName() override
	{
		return fDrink->getName() + ", Sugar";
	}

	int getCost() override
	{
		return fDrink->getCost() + 10;
	}

};

class Chocolate : public DrinkExtrasDecorator
{
public:
	explicit Chocolate(std::shared_ptr<Drink> drink) : DrinkExtrasDecorator(drink) {};
	~Chocolate() = default;

	std::string getName() override
	{
		return fDrink->getName() + ", Chocolate";
	}

	int getCost() override
	{
		return fDrink->getCost() + 50;
	}
};

class Malt : public DrinkExtrasDecorator
{
public:
	explicit Malt(std::shared_ptr<Drink> drink) : DrinkExtrasDecorator(drink) {};
	~Malt() = default;

	std::string getName() override
	{
		return fDrink->getName() + ", Malt";
	}

	int getCost() override
	{
		return fDrink->getCost() + 20;
	}
};


class Cream : public DrinkExtrasDecorator
{
public:
	explicit Cream(std::shared_ptr<Drink> drink) : DrinkExtrasDecorator(drink) {};
	~Cream() = default;

	std::string getName() override
	{
		return fDrink->getName() + ", Extra Cream";
	}

	int getCost() override
	{
		return fDrink->getCost() + 50;
	}
};

class Cup : public DrinkExtrasDecorator
{
public:
	explicit Cup(std::shared_ptr<Drink> drink) : DrinkExtrasDecorator(drink) {};
	~Cup() = default;

	std::string getName() override
	{
		return "Enjoy your " + fDrink->getName();
	}

	int getCost() override
	{
		return fDrink->getCost();
	}
};