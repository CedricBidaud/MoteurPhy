#ifndef _IMAC3_POLYGON_HPP
#define _IMAC3_POLYGON_HPP

#include <vector>
#include <glm/glm.hpp>

#include "renderer/ParticleRenderer2D.hpp"

namespace imac3{

	class Polygon{
		public:
			static Polygon buildBox(glm::vec3 color, glm::vec2 position, float width, float height, bool isInner = false);
			static Polygon buildCircle(glm::vec3 color, glm::vec2 center, float radius, size_t discFactor, bool isInner = false);
			void draw(ParticleRenderer2D& renderer, float lineWidth = 1.f) const;
			unsigned int getSize() const;
			glm::vec2 getPosition(int idx) const;
			bool isInner() const;
	
		private:
			std::vector<glm::vec2> m_pointsArray;
			glm::vec3 m_color;
			bool m_isInner;
	};

}

#endif // _IMAC3_POLYGON_HPP
