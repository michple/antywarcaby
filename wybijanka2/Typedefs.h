#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <vector>
#include <array>
#include <memory>
#include <iostream>
using namespace std;
class Ruch;
typedef vector <std::shared_ptr <Ruch> > t_ruchy_tab;
typedef shared_ptr <Ruch> t_ruch;
typedef array <int, 2> t_kordy;

#endif
