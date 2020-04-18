#ifndef H_SYSTEME
#define H_SYSTEME

#include <iostream>
#include <vector>
#include <cmath> 

#include "Toupie.h"



class Systeme : public Dessinable {
	public: 
		virtual void dessine() override
		{ support->dessine(*this); }
		
	protected:
		std::vector<Toupie> toupies;

};

#endif
