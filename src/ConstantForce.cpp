#include "ConstantForce.hpp"

namespace imac3 {

	ConstantForce::ConstantForce(glm::vec2 force){
		m_force = force;
	}

	void ConstantForce::apply(ParticleManager &pm) {
		unsigned int count = pm.getSize();
		for(int i = 0; i < count; ++i){
			pm.addForce(i, m_force);
		}
	}

}
