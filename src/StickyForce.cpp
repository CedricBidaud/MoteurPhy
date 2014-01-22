#include <cmath>

#include "StickyForce.hpp"

namespace imac3 {

	StickyForce::StickyForce(float fK, float fLInf, float fLSup){
		m_fK= fK;
		m_fLSup= fLSup;
		m_fLInf= fLInf;
	}

	void StickyForce::apply(ParticleManager &pm) {
		unsigned int count = pm.getSize();

		for(int i = 0; i < count; ++i){

			glm::vec2 p1=pm.getParticlePosition(i);

			for(int j = 0; j < count; ++j){
				if(i != j){
					glm::vec2 p2=pm.getParticlePosition(j);
					
					glm::vec2 vect = p2 - p1;
					
					float norm = sqrt(glm::dot(p2-p1,p2-p1));
					
					glm::vec2 force = glm::vec2(0.0);
					
					if(norm > m_fLInf && norm < m_fLSup)
						force = m_fK*(1-m_fLInf/glm::max(norm,0.0001f))*(p2-p1);
						
					
						
					pm.addForce(i, force);
				}
			}

		}
	}

}
