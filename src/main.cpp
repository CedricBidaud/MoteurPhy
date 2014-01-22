#include <iostream>
#include <cstdlib>

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

#include "renderer/WindowManager.hpp"
#include "renderer/ParticleRenderer2D.hpp"

#include <vector>

#include "ParticleManager.hpp"
#include "ConstantForce.hpp"
#include "Leapfrog.hpp"
#include "Polygon.hpp"
#include "PolygonForce.hpp"
#include "HookForce.hpp"
#include "RepulsiveForce.hpp"
#include "StickyForce.hpp"
#include "BrakeForce.hpp"

//~ #include "utils.hpp"

static const Uint32 WINDOW_WIDTH = 1024;
static const Uint32 WINDOW_HEIGHT = 1024;

using namespace imac3;


int main() {
    WindowManager wm(WINDOW_WIDTH, WINDOW_HEIGHT, "Newton was a Geek");
    wm.setFramerate(30);

    ParticleRenderer2D renderer;

    // Création des particules
    ParticleManager particleManager;
    //particleManager.addParticle(glm::vec2(0, 0), 1, glm::vec3(1, 1, 1), glm::vec2(0.f));
	//particleManager.addCircleParticles(0.5f, 18);
	particleManager.addRandomParticles(1);
/*
    particleManager.addParticle(glm::vec2(-0.3f, 0.0f), 1, glm::vec3(1, 0, 1), glm::vec2(0.f));
    particleManager.addParticle(glm::vec2(0.3f, 0.0f), 1, glm::vec3(0, 1, 1), glm::vec2(0.f));
    particleManager.addParticle(glm::vec2(0.2f, 0.4f), 1, glm::vec3(1, 1, 0), glm::vec2(0.f));
*/
	ConstantForce constForce(glm::vec2(0.000f,-0.03f));

    // hookForce(K,L)
    float L = 0.05f;
    HookForce hookForce(0.2f, 0.15f);
    //~ RepulsiveForce repulsiveForce(1.0f, L);
    RepulsiveForce repulsiveForce(0.1f, L);
    
    //~ StickyForce(float fK, float fLInf, float fLSup);
    StickyForce stickyForce(0.4, L - 0.02, L+0.02);

    // brakeForce(dt,V,L)
    BrakeForce brakeForce(0.0f, 0.05f, L);
	
	//particleManager.printForces();

    Leapfrog leapfrog;
    
    // Polygon Polygon::buildBox(glm::vec3 color, glm::vec2 position, float width, float height, bool isInner)
    Polygon box = Polygon::buildBox(glm::vec3(0.5,0.3,0.3), glm::vec2(0.f,0.f), 1.8f, 1.8f, true);
    Polygon box2 = Polygon::buildBox(glm::vec3(0.5,0.3,0.3), glm::vec2(-0.2f,-0.5f), 0.5f, 0.3f, false);
    
    Polygon boxL = Polygon::buildBox(glm::vec3(1.0), glm::vec2(-1.0,0.0),0.1,2.0,false);
    Polygon boxR = Polygon::buildBox(glm::vec3(1.0), glm::vec2(1.0,0.0),0.1,2.0,false);
    Polygon boxT = Polygon::buildBox(glm::vec3(1.0), glm::vec2(0.0,1.0),2.0,0.1,false);
    Polygon boxB = Polygon::buildBox(glm::vec3(1.0), glm::vec2(0.0,-1.0),2.0,0.1,false);
    
    //Polygon circle = Polygon::buildCircle(glm::vec3(0.2,0.7,0.2), glm::vec2(0.4f,0.1f), 0.2f, 32, false);
    //Polygon circle2 = Polygon::buildCircle(glm::vec3(0.2,0.5,0.9), glm::vec2(-0.2f,0.35f), 0.15f, 32, false);

	PolygonForce boxPolyForce(box, 1.1, leapfrog);
	PolygonForce box2PolyForce(box2, 1.1f, leapfrog);
	
	PolygonForce boxLPolyForce(boxL, 1.1f, leapfrog);
	PolygonForce boxRPolyForce(boxR, 1.1f, leapfrog);
	PolygonForce boxTPolyForce(boxT, 1.1f, leapfrog);
	PolygonForce boxBPolyForce(boxB, 1.1f, leapfrog);
	
	//PolygonForce circlePolyForce(circle, 2.f, leapfrog);
	//PolygonForce circle2PolyForce(circle2, 2.0f, leapfrog);
	
	
    // Temps s'écoulant entre chaque frame
    float dt = 0.f;

	int i = 0;
	
	float pas = 0.001;
	
	bool open = false;

	bool done = false;
    while(!done) {
        wm.startMainLoop();

        // Rendu
        renderer.clear();
        
        // ---- test ----
        if(open){
			//~ particleManager.addRandomParticles(100);
			particleManager.addRandomParticles(1);
			//~ particleManager.addParticle(glm::vec2(0, 0.5), 1, glm::vec3(100/(i+1), i, i), glm::vec2(glm::linearRand(-0.1,0.1),glm::linearRand(-0.1,0.1)));
			
			//~ std::cout << "i : " << i << std::endl;
			i = 0;
		}
		
		//~ ++i;
        
        particleManager.drawParticles(renderer);
		//~ box.draw(renderer, 2.f);
		box2.draw(renderer, 2.f);
		
		boxL.draw(renderer, 2.f);
		boxR.draw(renderer, 2.f);
		boxT.draw(renderer, 2.f);
		boxB.draw(renderer, 2.f);
        //circle.draw(renderer, 2.f);
        //circle2.draw(renderer, 2.f);

        // Simulation
        constForce.apply(particleManager);

        repulsiveForce.apply(particleManager);
        stickyForce.apply(particleManager);
        //~ hookForce.apply(particleManager);

        brakeForce.setDt(dt);
        brakeForce.apply(particleManager);

        //~ boxPolyForce.setDt(dt);
        //~ boxPolyForce.apply(particleManager);
        
        box2PolyForce.setDt(dt);
        box2PolyForce.apply(particleManager);
        
        boxLPolyForce.setDt(dt);
        boxLPolyForce.apply(particleManager);
        
        boxRPolyForce.setDt(dt);
        boxRPolyForce.apply(particleManager);
        
        boxTPolyForce.setDt(dt);
        boxTPolyForce.apply(particleManager);
        
        boxBPolyForce.setDt(dt);
        boxBPolyForce.apply(particleManager);
        
        //circlePolyForce.setDt(dt);
        //circlePolyForce.apply(particleManager);
        
        //circle2PolyForce.setDt(dt);
        //circle2PolyForce.apply(particleManager);
        
        leapfrog.solve(particleManager, dt);

        // Gestion des evenements
		SDL_Event e;
        while(wm.pollEvent(e)) {
			switch(e.type) {
				default:
					break;
					
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym){
						case SDLK_ESCAPE:
							done = true;
							break;
							
						case SDLK_SPACE:
							//~ particleManager.addRandomParticles(100);
							open = !open;
							break;
							
						case SDLK_r:
							repulsiveForce.m_fK += pas;
							std::cout << "rep K : " << repulsiveForce.m_fK << " - rep L : " << repulsiveForce.m_fL << std::endl;
							break;
							
						case SDLK_t:
							repulsiveForce.m_fL += pas;
							stickyForce.m_fLSup += pas;
							stickyForce.m_fLInf += pas;
							std::cout << "rep K : " << repulsiveForce.m_fK << " - rep L : " << repulsiveForce.m_fL << std::endl;
							break;
							
						case SDLK_b:
							brakeForce.m_fV += pas;
							std::cout << "brake K : " << brakeForce.m_fV << " - brake L : " << brakeForce.m_fL << std::endl;
							break;
							
						case SDLK_n:
							brakeForce.m_fL += pas;
							std::cout << "brake K : " << brakeForce.m_fV << " - brake L : " << brakeForce.m_fL << std::endl;
							break;
							
						case SDLK_p:
							pas *= 2.0;
							break;
							
						case SDLK_i:
							pas *= -1.0;
							break;
					}
					break;
					
				
				case SDL_QUIT:
					done = true;
					break;
			}
		}

        // Mise à jour de la fenêtre
        dt = wm.update();
	}

	return EXIT_SUCCESS;
}
