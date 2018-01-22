#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>
using namespace std;

/*
class food
{
private:
	
	unsigned int id;
	unsigned int max_no;
	time_t cook_duration;
	time_t start;
public:
	food(unsigned int i, unsigned int m, time_t c, time_t s)
		: id(i), max_no(m), cook_duration(c), start(s)
	{}
	int is_finish()
	{
		if ()
	}

};
*/



class food
{
private:
	unsigned int id;
	unsigned int max_no;
	unsigned int price;
	time_t cook_duration;
	time_t start = time(NULL);
	class food *next = NULL;
public:
	food(unsigned int i, unsigned int m, unsigned int p, time_t c)
	{
		id = i;
		max_no = m;
		cook_duration = c*10000;
		price = p;
	}
	class food *set_next(void)
	{
		next = (class food*)malloc(sizeof(class food));

	}
};



class customer
{
	unsigned int id;
	
};

void custom(const char new_food_name[])
{
	cout << "Enter price";
	//cin>>
}

void cook(int food_id)
{

}

void default_foods(void)
{

}


int main(void)
{
	class food *foods_list_headptr[20] = { NULL };  
	class food *foods_list_tailptr[20] = { NULL };
	class food chicken_sample(0, 3, 8, 2);
	class food meat_sample(1, 3, 12, 3);
	class food bread_sample(2, 4, 2, 1);
	class food nooshabe_sample(3, 3, 3, 1);
	class food doogh_sample(4, 3, 2, 1);

}