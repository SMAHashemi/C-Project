#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>
using namespace std;

#define MAX_FOOD 30


class food
{
private:
	unsigned int id;
	char name[20];
	unsigned int max_no;
	unsigned int price;
	time_t cook_duration;
	time_t start = time(NULL);
	class food *next = NULL;
public:
	

	food(){ return; }		//default constructor

	void set_spec(unsigned int i, char *n, unsigned int m, unsigned int p, time_t c, time_t s)
	{
		id = i;
		strcpy(name, n);
		max_no = m;
		cook_duration = c * 10000;
		price = p;
		start = s;
	}

	int get_id(){ return id; }
	char *get_name(){ return name; }
	unsigned int get_max_no(){ return max_no; }
	unsigned int get_price(){ return price; }
	time_t get_cook_duration(){ return cook_duration; }
	
	void set_next(class food *newfood)
	{
		next = newfood;
	}
};

class food *foods_list_headptr[MAX_FOOD] = { NULL };    //i-th member is a ponter to head of queue of food ID=i
class food *foods_list_tailptr[MAX_FOOD] = { NULL };    //i-th member is a ponter to tail of queue of food ID=i
class food samples[MAX_FOOD];

class customer
{
	unsigned int id;
	
};

void custom(const char new_food_name[])
{
	cout << "Enter price";
}

void set_default_foods()
{
	samples[0].set_spec(0, "chicken", 3, 8, 2, 0);
	samples[1].set_spec(1, "meat", 3, 12, 3, 0);
	samples[2].set_spec(2, "bread", 4, 2, 1, 0);
	samples[3].set_spec(3, "nooshabe", 3, 3, 1, 0);
	samples[4].set_spec(4, "doogh", 3, 2, 1, 0);

}
void cook(int food_id)
{
	class food *new_foodptr = (class food*)malloc(sizeof(class food));
	new_foodptr->set_spec(samples[food_id].get_id(), samples[food_id].get_name(), samples[food_id].get_max_no(), samples[food_id].get_price(), samples[food_id].get_cook_duration(), time(NULL));
	new_foodptr->set_next(NULL);
	//if empty, insert a node at head
	if (foods_list_headptr[food_id] == NULL)
	{
		foods_list_headptr[food_id] = new_foodptr;
	}
	else
	{
		foods_list_tailptr[food_id]->set_next(new_foodptr);
	}
	foods_list_tailptr[food_id] = new_foodptr;
}


int main(void)
{
	set_default_foods();

	return 0;
}