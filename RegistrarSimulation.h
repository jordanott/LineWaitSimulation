#ifndef REGISTRARSIMULATION_H
#define REGISTRARSIMULATION_H
#include <string>
#include <iostream>
#include "Queue.h"

using namespace std;

class RegistrarSimulation
{
public:
	int numStudents;
	int numWindows;
	
	double mean_SWT;
	double meadian_SWT;
	int longest_SWT;
	int num_SOver10;
	double mean_WIT;
	int longest_WIT;
	int num_WOver5;

	int* student_ary;
	int* window_ary;
	int* file_numbers;
	int* window_wait;
	Queue<int>* quee;

	RegistrarSimulation(string);
	~RegistrarSimulation();
	void findNumStudents(string);
	void simulation();
	void calculateStuff();



};
#endif