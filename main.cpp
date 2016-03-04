
#include <iostream>
#include "RegistrarSimulation.h"
#include "Queue.h"
using namespace std;
int main(int argc, char** argv){
	RegistrarSimulation* one = new RegistrarSimulation(argv[1]);
	one->simulation();
	delete one;
	
	return 0;
}