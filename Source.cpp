#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <stdbool.h>
using namespace std;

#define MAX_FOOD 30


class food
{
private:
	unsigned int id;
	char name[20];					
	unsigned int max_no;			
	unsigned int number;			
	unsigned int price;				
	bool is_ingredient = false;		
	time_t cook_duration;			
	time_t start = time(NULL);		
	class food *next = NULL;		
public:
	

	food(){ return; }		//default constructor

	void set_spec(unsigned int i, char *n, unsigned int m, unsigned int no, unsigned int p, bool in, time_t c, time_t s)
	{
		id = i;
		strcpy(name, n);
		max_no = m;
		number = no;
		cook_duration = c;
		price = p;
		is_ingredient = in;
		start = s;
	}

	int get_id(void){ return id; }
	char *get_name(void){ return name; }
	unsigned int get_max_no(void){ return max_no; }
	unsigned int get_number(void){ return number; }
	unsigned int get_price(void){ return price; }
	bool get_type(void){ return is_ingredient; }
	time_t get_cook_duration(void){ return cook_duration; }
	
	void set_next(class food *newfood)
	{
		next = newfood;
	}
};

class food *foods_list_headptr[MAX_FOOD] = { NULL };    //i-th member is a ponter to head of queue of food ID=i
class food *foods_list_tailptr[MAX_FOOD] = { NULL };    //i-th member is a ponter to tail of queue of food ID=i
class food samples[MAX_FOOD];
unsigned int foods_no = 5, ingredients_no = 2;

class customer
{
private:
	unsigned int id;
	unsigned int food_id ;
	unsigned int drink_id;
	time_t tolerance;
	time_t start = NULL;
public:

	customer(void){ return; };		//default constructor

	void enter(unsigned int i)
	{
		id = i;
		unsigned int c1 = 0, c2 = 0;
		unsigned int fd = rand() % (ingredients_no);
		unsigned int dd = rand() % (foods_no - ingredients_no);
		while (c1 <= fd)
		{
			if (samples[c2].get_type())
				c1++;
			c2++;
		}
		food_id = samples[c2-1].get_id();
		c1 = 0;
		c2 = 0;
		while (c1 <= dd)
		{
			if (!samples[c2].get_type())
				c1++;
			c2++;
		}
		drink_id = samples[c2 - 1].get_id();
		start = time(NULL);
		tolerance = ((rand() % 31) + 20) * 10000;
		if (samples[food_id].get_cook_duration() > tolerance)
			tolerance += 20;
	}
};

class customer customers[7];

void custom( char new_food_name[])
{
	
	unsigned int m;
	unsigned int i;
	unsigned int p;
	bool in;
	time_t c;
	time_t start = time(NULL);
	cout << endl << "custom food: " << new_food_name;
	cout << endl << "(" << foods_no << "foods exict)  " << "Enter ID:";
	cin >> i;
	cout << endl << "Enter max number:";
	cin >> m;
	cout << endl << "Enter price:";
	cin >> p;
	cout << "Is this ingredient?  (If it will be put in bread enter TRUE else(drink or bread) enter FALSE)";
	cin >> in;
	cout << endl << "Enter cooking duration (in miliseconds):";
	cin >> c;
	samples[i].set_spec(i, new_food_name, m, 0, p, in, c, time(NULL));
	printf("\n%s\n%s%s\n%s%u\n%s%u\n%s%u\n%s\n%s%u",
		"The new food is: ", "\tName: ", new_food_name, "\tID: ", i, "\tMax number: ", m, "\tPrice: ", p, in? "ingredien":"drink or bread", "\tcooking duration: ", c);
	foods_no++;
	if (in)
		ingredients_no++;
}

void set_default_foods()
{
	samples[0].set_spec(0, "chicken", 3, 0, 8, true, 20000, 0);
	samples[1].set_spec(1, "meat", 3, 0, 12, true, 30000, 0);
	samples[2].set_spec(2, "bread", 4, 0, 2, false, 10000, 0);
	samples[3].set_spec(3, "nooshabe", 3, 0, 3, false, 10000, 0);
	samples[4].set_spec(4, "doogh", 3, 0, 2, false, 10000, 0);

}

void set_initial_customers()
{
	for (size_t i = 0; i < 7; i++)
	{
		customers[i].enter(i);
	}
}

void cook(int food_id)
{
	class food *new_foodptr = (class food*)malloc(sizeof(class food));
	int t;
	if (foods_list_tailptr[food_id] == NULL)
	{
		t = 1;
	}
	else
	{
		t = foods_list_tailptr[food_id]->get_number() + 1;
	}
	if (t > samples[food_id].get_max_no())
	{
		cout << "There is not enough space for " << samples[food_id].get_name();
		return;
	}
	new_foodptr->set_spec(samples[food_id].get_id(), samples[food_id].get_name(), samples[food_id].get_max_no(), t , samples[food_id].get_price(), samples[food_id].get_type(), samples[food_id].get_cook_duration(), time(NULL));
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
	srand(time(NULL));
	set_default_foods();
	set_initial_customers();

	return 0;
}



