#include <iostream>
using namespace std;

#include "../../model/ricettario.h"


int main() 
{
  Ricettario* r = new Ricettario();
  
  r.load();
  
  return 0;
}