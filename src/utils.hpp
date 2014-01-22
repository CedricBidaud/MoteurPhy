#ifndef _IMAC3_UTILS_HPP
#define _IMAC3_UTILS_HPP

#include <glm/glm.hpp>

namespace imac3{
	
		glm::vec2 normale(const glm::vec2& A, const glm::vec2& B){
			return glm::normalize(glm::vec2(-(B.y - A.y), (B.x - A.x))); // pas facile à lire sur le tableau...
			//~ return glm::vec2(-(B.y - B.x), (A.y - A.x)); // test => donne la meme chose o_O
		}
		
		float squareNorm(glm::vec2 vect){
			return (vect.x*vect.x + vect.y*vect.y);
		}

		float norm(glm::vec2 vect){
			return sqrt(glm::dot(vect,vect));
		}
		
		bool intersect(const glm::vec2& p1, const glm::vec2& p2, 
						const glm::vec2& A, const glm::vec2& B,
						glm::vec2* intersection, glm::vec2* normal){
			glm::vec2 n = normale(A,B);
			
			float k = -glm::dot(p1-A,n)/glm::dot(p2-p1,n);
			//~ float k2 = glm::dot(-(p1-A),n)/glm::dot(p2-p1,n); // test => meme chose
			//~ std::cout << "k : " << k << ", k2 : " << k2 << std::endl;
			
			if(k >= 0 && k <= 1){
				//~ std::cout << "TEST 0-1" << std::endl;
				// OK
				
				//~ std::cout << "Normale (utils) : " << n.x << ", " << n.y << std::endl;
				
				glm::vec2 M = p1+k*(p2-p1);
				
				float scal = glm::dot(M-A, B-A);
				//~ float squareN = squareNorm(B-A);
				//~ float squareN = glm::dot(B-A, B-A); // norme au carré : produit scalaire du vecteur avec lui même
				
				//~ std::cout << "---TEST---" << std::endl;
				//~ std::cout << "scal : " << scal << ", square norm : " << glm::dot(B-A, B-A) << std::endl;
				
				
				float offset = 0.000;
				
				if(scal >= 0.0f -offset && scal <= glm::dot(B-A, B-A) +offset){
					*intersection = M;
					*normal = n;
					return true;
				}				
			}
			
			return false;
		}
		
		/*
		// cross 
		// ----- 
		// http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
		// -----
		bool intersect(const glm::vec2& p1, const glm::vec2& p2, 
						const glm::vec2& A, const glm::vec2& B,
						glm::vec2* interPoint, glm::vec2* normal){
			glm::vec2 n = normale(A,B);
			
			glm::vec2 traj = p2 - p1;
			glm::vec2 segment = B - A;
			
			glm::vec3 intersection = glm::cross(glm::vec3(traj.x, traj.y, 0.0), glm::vec3(segment.x, segment.y ,0.0));
			
			std::cout << "test : " << intersection.x << ", " << intersection.y << ", " << intersection.z << std::endl;
			
			if(intersection.x > glm::min(A.x, B.x) && intersection.y < glm::max(A.x, B.x)){
				if(intersection.y > glm::min(A.y, B.y) && intersection.y < glm::max(A.y, B.y)){
					std::cout << "test" << std::endl;
					
					*interPoint = glm::vec2(intersection.x,intersection.y);
					*normal = n;
					return true;
				}
			}
			
			return false;
		}
		*/
		/*
		// third try !
		bool intersect(const glm::vec2& p1, const glm::vec2& p2, 
						const glm::vec2& A, const glm::vec2& B,
						glm::vec2* intersectPoint, glm::vec2* normal){
			glm::vec2 n = normale(A,B);

			// trajectoire
			float A_traj = p2.y-p1.y;
			float B_traj = p1.x-p2.x;
			float C_traj = A_traj*p1.x+B_traj*p1.y;
			
			float A_seg = B.y-A.y;
			float B_seg = A.x-B.x;
			float C_seg = A_seg*A.x+B_seg*A.y;
		
			float det = A_traj*B_seg - A_seg*B_traj;

			if(det == 0){
				//Lines are parallel
			}else{
				
				//~ std::cout << "test" << std::endl;
				double x = (B_seg*C_traj - B_traj*C_seg)/det;
				double y = (A_traj*C_seg - A_seg*C_traj)/det;
				
				glm::vec2 intersection = glm::vec2(x,y);
				
				std::cout << "inter : " << intersection.x << ", " << intersection.y << std::endl;
				
				if(intersection.x > glm::min(A.x, B.x) && intersection.x < glm::max(A.x, B.x)){
					//~ std::cout << "test" << std::endl;
					if(intersection.y < glm::min(A.y, B.y) && intersection.y > glm::max(A.y, B.y)){
						std::cout << "test" << std::endl;
						
						*intersectPoint = intersection;
						*normal = n;
						return true;
					}
				}
			}
		
			return false;
		}
		*/
		/*
		bool intersect(const glm::vec2& p1, const glm::vec2& p2, 
						const glm::vec2& A, const glm::vec2& B,
						glm::vec2* intersection, glm::vec2* normal){
		//~ bool intersect(float p0_x, float p0_y, float p1_x, float p1_y, 
			//~ float p2_x, float p2_y, float p3_x, float p3_y){
				//~ 
			double p0_x = p1.x;
			double p0_y = p1.y;
			double p1_x = p2.x;
			double p1_y = p2.y;
			
			double p2_x = A.x;
			double p2_y = A.y;
			double p3_x = B.x;
			double p3_y = B.y;
				
			
			double s1_x, s1_y, s2_x, s2_y;
			s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
			s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

			double s, t;
			s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
			t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

			if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
			{
				std::cout << "test" << std::endl;
				// Collision detected
				//~ if (i_x != NULL)
					//~ *i_x = p0_x + (t * s1_x);
				//~ if (i_y != NULL)
					//~ *i_y = p0_y + (t * s1_y);
					//~ 
				*intersection = glm::vec2(p0_x + (t * s1_x),p0_y + (t * s1_y));
				*normal = normale(A,B);
					
				return true;
			}

			return false; // No collision
		}
		*/
		
}

#endif
