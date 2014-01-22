#ifndef _IMAC3_REP_FORCE_HPP
#define _IMAC3_REP_FORCE_HPP


#include <iostream>

#include "Force.hpp"

namespace imac3 {

class RepulsiveForce : Force {

	public:
		RepulsiveForce(float fK, float fL);
		void apply(ParticleManager &pm);
	
	public: // getter setter à faire
		float m_fK;
		float m_fL;

};

}



#endif // _IMAC3_REP_FORCE_HPP
