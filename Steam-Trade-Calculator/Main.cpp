#include <iostream>
#include <windows.h>

using std::cout;
using std::cin;

class CheckProfit
{
public:

	CheckProfit()
	{
		_marketPrice = 0;
		_steamPrice = 0;
		_steamPriceWithoutCommission = 0;
		_steam_prc = 15;
		_pricePrcDiff = 0;
		_currency = "UAH";
	}

public:

	void SetMarketPrice(float marketPrice)
	{
		_marketPrice = marketPrice;
	}
	void SetSteamPrice(float steamPrice)
	{
		_steamPrice = steamPrice;
	}
	void PriceTrim(float& num)
	{
		int a = num;
		float b = int((num - a) * 100) / (float)100;
		num = a + b;
	}
	void PriceMinusCommissionSteam()
	{
		_steamPriceWithoutCommission = _steamPrice - (_steamPrice * _steam_prc / 100);
		PriceTrim(_steamPriceWithoutCommission);
	}
	void PricePercentagesDifference()
	{
		float a = _marketPrice;
		float b = _steamPriceWithoutCommission;

		// Difference in percentages: a < b = ((b - a) / a) * 100 || a > b = ((a - b) / a) * 100 

		if (a < b) _pricePrcDiff = ((b - a) / a) * 100;
		else _pricePrcDiff = 0;

		PriceTrim(_pricePrcDiff);
	}

public:

	float _marketPrice;
	float _steamPrice;
	float _steamPriceWithoutCommission;
	float _steam_prc;
	float _pricePrcDiff;
	const char* _currency;
};

void ShowResult(CheckProfit& price)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	float profit = price._steamPriceWithoutCommission - price._marketPrice;

	cout << "\n " << "Market Price\t\t\t" << price._marketPrice;
	cout << "\n " << "Steam Price\t\t\t" << price._steamPrice;
	cout << "\n " << "Without Steam Commission\t" << price._steamPriceWithoutCommission;
	cout << "\n\n Profit: ";

	if (profit > 0 || profit == 0)
	{
		SetConsoleTextAttribute(hConsole, 10);
		cout << "+";
	}
	else SetConsoleTextAttribute(hConsole, 12);

	cout << profit << " (" << price._pricePrcDiff << "%)" << "\n";
	SetConsoleTextAttribute(hConsole, 15);
}

int main()
{
	float marketPrice = 0;
	float steamPrice = 0;

	CheckProfit price = CheckProfit();

	do
	{
		system("cls");
		ShowResult(price);

		cout << "\n MARKET PRICE\t> ";
		cin >> marketPrice;
		cout << " STEAM PRICE\t> ";
		cin >> steamPrice;

		price.SetMarketPrice(marketPrice);
		price.SetSteamPrice(steamPrice);

		price.PriceMinusCommissionSteam();
		price.PricePercentagesDifference();

	} while (true);
}
