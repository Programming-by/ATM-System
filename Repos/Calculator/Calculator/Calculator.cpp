#include <iostream>
using namespace std;

class clsCalculator {

private:
	
	int _number = 0;

public:

	void Clear() {
		_number = 0;
	}

	void Add(int number) {
		cout << "Result After Adding " << number;
		_number += number;
	}

	void Subtract(int number) {
		cout << "Result After Subtracting " << number;

		_number -= number;
	}

	void Multiply(int number) {
		cout << "Result After Multiplying " << number;

		_number *= number;
	}


	void Divide(int number) {
		if (number == 0) {
			number = 1;
		}
		cout << "Result After Dividing " << number;


		_number /= number;
	}

	void PrintResults() {
		while (_number == 0) {
			cout << "Result After Clear " << _number << " is: " << _number;

			return;
		}
		cout << " is: " << _number << endl;
	}
};

int main()
{
	clsCalculator Calculator1;

	Calculator1.Clear();

	Calculator1.Add(10);
	Calculator1.PrintResults();

	Calculator1.Add(100);
	Calculator1.PrintResults();

	Calculator1.Subtract(20);
	Calculator1.PrintResults();

	Calculator1.Divide(0);
	Calculator1.PrintResults();

	Calculator1.Divide(2);
	Calculator1.PrintResults();


	Calculator1.Multiply(3);
	Calculator1.PrintResults();

	Calculator1.Clear();
	Calculator1.PrintResults();


	system("pause>0");

	return 0;
}