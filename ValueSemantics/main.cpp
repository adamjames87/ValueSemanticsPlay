#include <ostream>
#include <iostream>
#include <string>
#include <vector>

#include "drawable.h"

using std::string;
using std::ostream;
using std::endl;

class my_class_t {
   int i_;
};

void draw(const my_class_t& m, ostream& out, size_t position)
{
out << "my_class_t" << std::endl;
}


int main()
{
history_t h(1);
current(h).emplace_back(0);
current(h).emplace_back(std::string("This is a string"));
draw(current(h), std::cout, 0);
std::cout  << " ------------------------------- " << endl;
commit(h);

current(h)[0] = 1;
current(h)[1] = std::string("This is a different string");
current(h).emplace_back(current(h));
current(h).emplace_back(my_class_t());

draw(current(h), std::cout, 0);
std::cout  << " ------------------------------- " << endl;
undo(h);
draw(current(h), std::cout, 0);
std::cout  << " ------------------------------- " << endl;



int i;
std::cin >> i;
}