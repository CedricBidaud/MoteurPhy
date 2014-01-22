#include "PolygonForce.hpp"
#include "Leapfrog.hpp"
#include "utils.hpp"

namespace imac3 {

	PolygonForce::PolygonForce(const Polygon& polygon, float elasticity, const Leapfrog& solver) {
		m_Polygon = &polygon;
		m_fElasticity = elasticity;
		m_Solver = &solver;
		m_fDt = 0.f;
	}
	
	void PolygonForce::setDt(float dt){
		m_fDt = dt;
	}
	
	glm::vec2 PolygonForce::computeForce(float elasticity, glm::vec2 velocity, glm::vec2 normale, float mass, float dt){
		//~ std::cout << "Elasticity :" << elasticity << std::endl;
		//~ std::cout << "Velocity :" << velocity.x << ", " << velocity.y << std::endl;
		//~ std::cout << "Normale (poly) :" << normale.x << ", " << normale.y << std::endl;
		//~ std::cout << "Masse :" << mass << std::endl;
		//~ std::cout << "Dt :" << dt << std::endl;
		return glm::vec2(elasticity*glm::dot(velocity,-normale)*(mass/dt)*normale);
	}
	
	void PolygonForce::apply(ParticleManager &pm){
		//~ std::cout << "Dt : " << m_fDt << std::endl;
		for(int i = 0; i < pm.getSize(); ++i){ // loop sur les particules du ParticleManager
			Leapfrog::ParticleState actualState;
			actualState.position = pm.getParticlePosition(i);
			actualState.velocity = pm.getParticleVelocity(i);
			
			Leapfrog::ParticleState nextState = Leapfrog::getNextState(i, pm, m_fDt);
			
			//~ std::cout << "actual pos : " << actualState.position.x << ", " << actualState.position.y << std::endl;
			//~ std::cout << "next pos : " << nextState.position.x << ", " << nextState.position.y << std::endl;
			// OK
			if(m_Polygon->isInner()){
				for(int j = 0; j < m_Polygon->getSize(); ++j){ // loop sur les arretes du poly
					int k = (j+1)%m_Polygon->getSize();
					
					glm::vec2 intersection;
					glm::vec2 normale;
					
					bool isIntersected = intersect(actualState.position, nextState.position, m_Polygon->getPosition(j), m_Polygon->getPosition(k), &intersection, &normale);
					if(isIntersected) {
						//std::cout << "COLLISION INNER" << std::endl;
						
						//~ std::cout << "Normale (after intersect) : " << normale.x << ", " << normale.y << std::endl;
						
						glm::vec2 force = PolygonForce::computeForce(m_fElasticity, nextState.velocity, normale, pm.getParticleMass(i), m_fDt); 
						//std::cout << "force : " << force.x << ", " << force.y << std::endl;
						pm.addForce(i, force);
					}
				} // end for arretes poly
			}else{
				for(int j = m_Polygon->getSize()-1; j >= 0; --j){ // VERIFIER
					int k = j-1;
					if(k == -1)
						k = m_Polygon->getSize()-1;
					
					glm::vec2 intersection;
					glm::vec2 normale;
					
					bool isIntersected = intersect(actualState.position, nextState.position, m_Polygon->getPosition(j), m_Polygon->getPosition(k), &intersection, &normale);
					if(isIntersected) {
						//std::cout << "COLLISION OUTTER" << std::endl;
						glm::vec2 force = PolygonForce::computeForce(m_fElasticity, nextState.velocity, normale, pm.getParticleMass(i), m_fDt); 
						//std::cout << "force : " << force.x << ", " << force.y << std::endl;
						pm.addForce(i, force);
					}
				} // end for
			}
		} // end for PM
	}

}

