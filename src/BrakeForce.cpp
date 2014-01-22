#include <cmath>

#include "BrakeForce.hpp"

namespace imac3 {

	BrakeForce::BrakeForce(float dt, float v, float l){
		m_fDt= dt;
		m_fV= v;
		m_fL = l;
	}

	void BrakeForce::setDt(float dt){
		m_fDt = dt;
	}

	void BrakeForce::apply(ParticleManager &pm) {
		unsigned int count = pm.getSize();

		for(int i = 0; i < count; ++i){

			glm::vec2 v1=pm.getParticleVelocity(i);

			for(int j = 0; j < count; ++j){
				if(i != j){
					glm::vec2 v2=pm.getParticleVelocity(j);
					glm::vec2 p1 = pm.getParticlePosition(i);
					glm::vec2 p2 = pm.getParticlePosition(j);

					if(m_fDt > 0){
						//std::cout << "TEST" << std::endl;
						glm::vec2 force = glm::vec2(0.0, 0.0);
						
						float norm = glm::length(p2-p1);
						
						if(norm < m_fL)
							force = m_fV*((v2-v1)/m_fDt);
							
						//~ force *= 1.0/pow(norm, 0.2);
							
						//~ std::cout << "test norm : " << norm << std::endl;
						
						//~ if(norm < 0.10 && norm > 0.0)
							//~ force *= 100.0;
						
/*
						std::cout << "V : " << m_fV << std::endl;

						std::cout << "v1 : " << v1.x << ", " << v1.y << std::endl;
						std::cout << "v2 : " << v2.x << ", " << v2.y << std::endl;
						std::cout << "Force : " << force.x << ", " << force.y << std::endl;
*/						
						pm.addForce(i, force);

					}
				}
			}

		}
	}

}
