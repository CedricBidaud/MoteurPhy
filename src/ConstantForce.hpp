#ifndef _IMAC3_CONST_FORCE_HPP
#define _IMAC3_CONST_FORCE_HPP


#include <iostream>

#include "Force.hpp"

namespace imac3 {

class ConstantForce : Force {

	public:
		ConstantForce(glm::vec2 force);
		void apply(ParticleManager &pm);
	
	private:
		glm::vec2 m_force;

};

}



#endif // _IMAC3_CONST_FORCE_HPP
