#include <cmath>
#include "Polygon.hpp"

namespace imac3{

	Polygon Polygon::buildBox(glm::vec3 color, glm::vec2 position, float width, float height, bool isInner){
		Polygon poly;
		poly.m_color=color;
		poly.m_pointsArray.push_back(glm::vec2(position.x-width/2.f, position.y-height/2.f));
		poly.m_pointsArray.push_back(glm::vec2(position.x+width/2.f, position.y-height/2.f));
		poly.m_pointsArray.push_back(glm::vec2(position.x+width/2.f, position.y+height/2.f));
		poly.m_pointsArray.push_back(glm::vec2(position.x-width/2.f, position.y+height/2.f));

		poly.m_isInner = isInner;

		return poly;
	}

	Polygon Polygon::buildCircle(glm::vec3 color, glm::vec2 center, float radius, size_t discFactor, bool isInner){
		Polygon circle;
		circle.m_color = color;

		for(int i = 0; i < discFactor; ++i) {
			float theta = 6.28f / discFactor * i;
			float x = center.x + radius*cos(theta);
			float y = center.y + radius*sin(theta);
			circle.m_pointsArray.push_back(glm::vec2(x,y));
		}

		circle.m_isInner = isInner;

		return circle;
	}

	void Polygon::draw(ParticleRenderer2D& renderer, float lineWidth) const{
		renderer.drawPolygon(m_pointsArray.size(), &m_pointsArray[0], m_color, lineWidth);
	}
	
	unsigned int Polygon::getSize() const{
		return m_pointsArray.size();
	}
	
	glm::vec2 Polygon::getPosition(int idx) const{
		return m_pointsArray[idx];
	}
	
	bool Polygon::isInner() const{
		return m_isInner;
	}

}
