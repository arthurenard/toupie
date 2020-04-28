#include "Systeme.h"

void Systeme::evolue(double dt){
    for(auto toupie : toupies){

       toupie->EulerCromer(dt);
    }
    //cone->EulerCromer(dt);
}
