#include "ParticleManager.hpp"
#include "renderer/GLtools.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace imac3{

ParticleManager::ParticleManager(){
}

ParticleManager::~ParticleManager(){
	
}

unsigned int ParticleManager::addParticle(glm::vec2 position, float mass, glm::vec3 color, glm::vec2 velocity) {
	m_positionArray.push_back(position);
	m_massArray.push_back(mass);
	m_colorArray.push_back(color);
	m_velocityArray.push_back(velocity);
	m_forceArray.push_back(glm::vec2(0.f));
	return m_positionArray.size() - 1;
}

void ParticleManager::addRandomParticles(unsigned int count){
	for (int i=0;i<count;++i){
		glm::vec2 pos = glm::vec2(glm::linearRand(0.5f,0.5f),glm::linearRand(0.75f,0.75f));
		addParticle(pos, glm::linearRand(1.0f,1.0f), glm::vec3(glm::linearRand(0.0,1.0),glm::linearRand(0.0,1.0),glm::linearRand(0.0,1.0)), glm::vec2(glm::linearRand(-0.03,-0.06),glm::linearRand(0.07,0.13)));
	}
}

void ParticleManager::drawParticles(ParticleRenderer2D& renderer) {
	renderer.drawParticles(
		m_positionArray.size(),
		&m_positionArray[0],
		&m_massArray[0],
		&m_colorArray[0]
	);
}

unsigned int ParticleManager::getSize() {
	return m_positionArray.size();
}

void ParticleManager::addForce(int i, glm::vec2 force){
	m_forceArray[i] += force;
	//~ std::cout << "force : " << m_forceArray[i].x << ", " << m_forceArray[i].y << std::endl;
}

void ParticleManager::printForces(){
	for (int i=0;i<m_forceArray.size();++i){
		//~ std::cout << "force : " << m_forceArray[i].x << ", " << m_forceArray[i].y << std::endl;
	}
}

float ParticleManager::getParticleMass(unsigned int i){
	return m_massArray[i];
}

glm::vec2 ParticleManager::getParticlePosition(unsigned int i){
	return m_positionArray[i];
}

glm::vec2 ParticleManager::getParticleVelocity(unsigned int i){
	return m_velocityArray[i];
}

glm::vec2 ParticleManager::getParticleForce(unsigned int i){
	return m_forceArray[i];
}

void ParticleManager::setParticlePosition(unsigned int i, glm::vec2 position){
	m_positionArray[i] = position;
}

void ParticleManager::setParticleVelocity(unsigned int i, glm::vec2 velocity){
	m_velocityArray[i] = velocity;
}

void ParticleManager::setParticleForce(unsigned int i, glm::vec2 force){
	m_forceArray[i] = force;
}

void ParticleManager::resetParticleForce(unsigned int i){
	//~ std::cout << "Before : " << m_forceArray[i].x << ", " << m_forceArray[i].y << std::endl;
	setParticleForce(i, glm::vec2(0.f));
	//~ std::cout << "After : " << m_forceArray[i].x << ", " << m_forceArray[i].y << std::endl;
}

void ParticleManager::clean(){
	m_positionArray.clear();
	m_massArray.clear();
	m_colorArray.clear();
	m_velocityArray.clear();
	m_forceArray.clear();
}

} // end namespace imac3
