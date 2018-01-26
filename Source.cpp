#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>
//#include <stdbool.h>
using namespace std;

#define MAX_FOOD 30
#define MAX_CUSTOMER 7
#define BREAD_ID 2

unsigned int foods_no = 5, ingredients_no = 2;
unsigned int cash = 0;

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
	time_t start ;		
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
	char *get_name(void)
	{ 
		if (!is_ingredient && id == BREAD_ID)
			return "No!";
		return name;
	}
	unsigned int get_max_no(void){ return max_no; }
	unsigned int get_number(void){ return number; }
	unsigned int get_price(void)
	{ 
		if (!is_ingredient && id == BREAD_ID)
			return 0;
		return price; 
	}
	bool get_type(void){ return is_ingredient; }
	time_t get_cook_duration(void){ return cook_duration; }
	time_t get_start(void){ return start; }
	class food *get_next(){ return next; }
	void set_next(class food *newfood){ next = newfood; }
};

class food *foods_list_headptr[MAX_FOOD] = { NULL };    //i-th member is a ponter to head of queue of food ID=i
class food *foods_list_tailptr[MAX_FOOD] = { NULL };    //i-th member is a ponter to tail of queue of food ID=i
class food samples[MAX_FOOD];


class customer
{
private:
	unsigned int id;
	unsigned int food_id ;
	unsigned int drink_id;
	bool gfood = false;
	bool gdrink = false;
	time_t tolerance;
	time_t start = NULL;
public:

	customer(void){ return; };		//default constructor

	void enter(unsigned int i)
	{
		id = i;
		unsigned int c1 = 0, c2 = 0;
		unsigned int fd = (rand() % (ingredients_no));
		unsigned int dd = rand() % (foods_no - ingredients_no );
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
		tolerance = ((rand() % 31) + 20);
		if (samples[food_id].get_cook_duration() > tolerance)
			tolerance += 20;
		printf("\n%s\n%s%u\n%s%s%s\n%s%s\n%s%u",
			"New Customer: ", "\tID: ", id, "\tFood: ", samples[food_id].get_name(), " sandwich",
			"\tDrink: ",gdrink? "NO!":samples[drink_id].get_name(),"\tTolerance: ",tolerance);
	}

	unsigned int get_id(){ return id; }
	unsigned int get_food_id(){ return food_id; }
	unsigned int get_drink_id(){return drink_id;}
	bool get_gfood(){ return gfood; }
	bool get_gdrink(){ return gdrink; }
	void set_gfood(bool a){ gfood = a; }
	void set_gdrink(bool a){ gdrink = a; }
	void add_tolerance(time_t at){ tolerance += at; }
	time_t get_tolerance(){ return tolerance; }
	time_t get_start(){ return start; }
};



class customer customers[MAX_CUSTOMER];


//function prototypes:
void custom(char new_food_name[]);
void set_default_foods();
void set_initial_customers();
void cook(int food_id);
void give(unsigned int food_id, unsigned int customer_id);
void put_give(unsigned int food_id, unsigned int customer_id);
bool c_check(unsigned int i);


int main(void)
{
	//srand(time(NULL));
	set_default_foods();
	set_initial_customers();
	cook(1);
	give(4, 0);
	put_give(1, 0);
	cook(0);
	give(4, 1);
	put_give(0, 1);
	return 0;
}


void cook(int food_id)
{
	class food *new_foodptr = (class food*)malloc(sizeof(class food));
	unsigned int t;
	if (foods_list_tailptr[food_id] == NULL)
	{
		t = 1;
	}
	else
	{
		t = foods_list_tailptr[food_id]->get_number() + 1;
	}
	unsigned int w;
	if (foods_list_headptr[food_id] == NULL)
		w = 0;
	else
		w = foods_list_headptr[food_id]->get_number();
	if (t - w+1> samples[food_id].get_max_no())
	{
		cout << "There is not enough space for " << samples[food_id].get_name();
		return;
	}
	new_foodptr->set_spec(samples[food_id].get_id(), samples[food_id].get_name(), samples[food_id].get_max_no(), t,
		samples[food_id].get_price(), samples[food_id].get_type(), samples[food_id].get_cook_duration(), time(NULL));
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

void custom(char new_food_name[])
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
	cout << endl << "Enter cooking duration (in seconds):";
	cin >> c;
	samples[i].set_spec(i, new_food_name, m, 0, p, in, c, time(NULL));
	printf("\n%s\n%s%s\n%s%u\n%s%u\n%s%u\n%s\n%s%u",
		"The new food is: ", "\tName: ", new_food_name, "\tID: ", i, "\tMax number: ", m, "\tPrice: ", p, in ? "ingredien" : "drink or bread", "\tcooking duration: ", c);
	foods_no++;
	if (in)
		ingredients_no++;
}

void set_default_foods()
{
	samples[0].set_spec(0, "chicken", 3, 0, 8, true, 2, 0);
	samples[1].set_spec(1, "meat", 3, 0, 12, true, 3, 0);
	samples[2].set_spec(2, "bread", 4, 0, 2, false, 1, 0);
	samples[3].set_spec(3, "nooshabe", 3, 0, 3, false, 1, 0);
	samples[4].set_spec(4, "doogh", 3, 0, 2, false, 1, 0);
	cook(2);
	cook(3);
	cook(4);
}

void set_initial_customers()
{
	for (size_t i = 0; i < MAX_CUSTOMER; i++)
	{
		customers[i].enter(i);
	}
}

void give(unsigned int drink_id, unsigned int customer_id)
{
	if (samples[drink_id].get_type() || drink_id == BREAD_ID)
	{
		cout << endl << samples[drink_id].get_name() << " is not a drink!" << endl;
		return;
	}
	if (time(NULL) - foods_list_headptr[drink_id]->get_start() < foods_list_headptr[drink_id]->get_cook_duration())
	{
		cout << endl << samples[drink_id].get_name() << " is not ready. Try again in "
			<< ((foods_list_headptr[drink_id]->get_cook_duration()) - (time(NULL) - foods_list_headptr[drink_id]->get_start())) << " seconds.";
		return;
	}

	c_check(customer_id);

	if (customers[customer_id].get_drink_id() != drink_id)
	{
		cout << "Haji eshtebah mizani!";
		return;
	}
	if (customers[customer_id].get_gdrink())
	{
		cout << "Customer nuber " << customer_id << " do not want more drink!";
		return;
	}
	cash += samples[drink_id].get_price();

	//dequeue drink
	class food *tempptr = foods_list_headptr[drink_id];
	foods_list_headptr[drink_id] = foods_list_headptr[drink_id]->get_next();
	if (foods_list_headptr[drink_id] == NULL)		//if queue is emppty
		foods_list_tailptr[drink_id] = NULL;
	free(tempptr);

	customers[customer_id].set_gdrink(true);
	if (customers[customer_id].get_gfood())
	{
		printf("\n%s%u%s%u%s",
			"Customer number ", customer_id, "'s orders completed!\t", samples[drink_id].get_price(), " bitqueens added to cash.");
		customers[customer_id].enter(customer_id);
	}
	cout << endl << samples[drink_id].get_name() << " gave to customer number " << customer_id <<
		" and " << samples[drink_id].get_price() << " bitqueens added to cash.";
	customers[customer_id].add_tolerance(10);
	cook(drink_id);
}

bool c_check(unsigned int i)
{
	bool ans = true;
	for (size_t c_id = 0; c_id < MAX_CUSTOMER; c_id++)
	{


		if (time(NULL) - customers[c_id].get_start() > customers[c_id].get_tolerance())
		{
			cout << endl << "Customer number " << c_id << " went!";
			if (customers[c_id].get_gdrink() && customers[c_id].get_drink_id() != NULL)
			{
				cash -= samples[customers[c_id].get_drink_id()].get_price() + 2;
				cout << endl << "Cash reduced " << samples[customers[c_id].get_drink_id()].get_price() + 2 << " bitqueens. ";
			}
			else if (customers[c_id].get_gfood())
			{
				cash -= samples[customers[c_id].get_food_id()].get_price() + 2 + samples[BREAD_ID].get_price();
				cout << endl << "Cash reduced " << samples[customers[c_id].get_food_id()].get_price() + 2 + samples[BREAD_ID].get_price() << " bitqueens. ";
			}
			customers[c_id].enter(c_id);
			ans = false;
		}

	}
	return ans;
}

void put_give(unsigned int food_id, unsigned int customer_id)
{
	if (!samples[food_id].get_type())
	{
		cout << endl << samples[food_id].get_name() << " is not a food!" << endl;
		return;
	}
	if (time(NULL) - foods_list_headptr[food_id]->get_start() < foods_list_headptr[food_id]->get_cook_duration())
	{
		cout << endl << samples[food_id].get_name() << " is not ready. Try again in "
			<< ((foods_list_headptr[food_id]->get_cook_duration()) - (time(NULL) - foods_list_headptr[food_id]->get_start())) << " seconds.";
		return;
	}
	if (time(NULL) - foods_list_headptr[2]->get_start() < foods_list_headptr[2]->get_cook_duration())
	{
		cout << endl << samples[2].get_name() << " is not ready. Try again in "
			<< ((foods_list_headptr[2]->get_cook_duration()) - (time(NULL) - foods_list_headptr[2]->get_start())) << " seconds.";
		return;
	}

	c_check(customer_id);

	if (customers[customer_id].get_food_id() != food_id)
	{
		cout << endl << "Haji eshtebah mizani!";
		return;
	}
	if (customers[customer_id].get_gfood())
	{
		cout << "Customer number " << customer_id << " don't want more "
			<< samples[food_id].get_name() << " sandwich!";
		return;
	}
	cash += samples[food_id].get_price() + 2;
	
	//dequeue food
	class food *tempptr = foods_list_headptr[food_id];
	foods_list_headptr[food_id] = foods_list_headptr[food_id]->get_next();
	if (foods_list_headptr[food_id] == NULL)		//if queue is emppty
		foods_list_tailptr[food_id] = NULL;

	//dequeue bread
	foods_list_headptr[2] = foods_list_headptr[2]->get_next();
	if (foods_list_headptr[2] == NULL)		//if queue is emppty
		foods_list_tailptr[2] = NULL;

	free(tempptr);
	cook(BREAD_ID);

	customers[customer_id].set_gfood(true);
	if (customers[customer_id].get_gdrink())
	{
		printf("\n%s%u%s%u%s",
			"Customer number ", customer_id, "'s orders completed!\t", samples[food_id].get_price() + 2, " bitqueens added to cash.");
		customers[customer_id].enter(customer_id);
		return;
	}
	cout << endl << samples[food_id].get_name() << " gave to customer number " << customer_id <<
		" and " << samples[food_id].get_price() + 2 << "bitqueens added to cash.";
	customers[customer_id].add_tolerance(10);
}



