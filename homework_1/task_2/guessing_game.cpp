#include <iostream>
#include <ctime>
#include <cstdlib>
int main() {
	std::srand(std::time(nullptr));
	int answer = std::rand() % 100;
	int guess;
	while(std::cin>>guess) {
		if(guess < answer) std::cout<<"Your guess is smaller than answer"<<std::endl;
		else if(guess > answer) std::cout<<"Your guess is bigger than answer"<<std::endl;
		else {
			std::cout<<"You won! The answer is: "<<answer<<std::endl;
			break;
		}
	}
	return 0;
}
