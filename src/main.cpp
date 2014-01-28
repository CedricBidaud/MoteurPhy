#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream> 

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

#include "imgui.h"
#include "imguiRenderGL.h"

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

	Leapfrog leapfrog;

	ConstantForce constForce(glm::vec2(0.000f,-0.03f));

    // hookForce(K,L)
    float L = 0.05f;
    HookForce hookForce(0.2f, 0.15f);
    //~ RepulsiveForce(float fKRep, float fKSticky, float fLInf, float fLSup);
    RepulsiveForce repulsiveForce(0.191f, 0.282f, 0.145, 0.159);
    
    //~ StickyForce(float fK, float fLInf, float fLSup);
    //~ StickyForce stickyForce(0.4, L - 0.02, L+0.02);

    //~ BrakeForce(float dt, float v, float l, const Leapfrog& solver);
    BrakeForce brakeForce(0.0f, 0.011, 0.159, leapfrog);
	
	//particleManager.printForces();
    
    // Polygon Polygon::buildBox(glm::vec3 color, glm::vec2 position, float width, float height, bool isInner)
    Polygon box = Polygon::buildBox(glm::vec3(0.5,0.3,0.3), glm::vec2(0.f,0.f), 1.8f, 1.8f, true);
    Polygon box2 = Polygon::buildBox(glm::vec3(0.5,0.3,0.3), glm::vec2(-0.2f,-0.5f), 0.5f, 0.3f, false);
    
    Polygon boxL = Polygon::buildBox(glm::vec3(1.0), glm::vec2(-1.0,0.0),0.1,2.0,false);
    Polygon boxR = Polygon::buildBox(glm::vec3(1.0), glm::vec2(1.0,0.0),0.1,2.0,false);
    Polygon boxT = Polygon::buildBox(glm::vec3(1.0), glm::vec2(0.0,1.0),2.0,0.1,false);
    Polygon boxB = Polygon::buildBox(glm::vec3(1.0), glm::vec2(0.0,-1.0),2.0,0.1,false);
    
    //Polygon circle = Polygon::buildCircle(glm::vec3(0.2,0.7,0.2), glm::vec2(0.4f,0.1f), 0.2f, 32, false);
    //Polygon circle2 = Polygon::buildCircle(glm::vec3(0.2,0.5,0.9), glm::vec2(-0.2f,0.35f), 0.15f, 32, false);
	
	float polyStickyCoef = 1.005f;
	
	PolygonForce boxPolyForce(box, polyStickyCoef, leapfrog);
	PolygonForce box2PolyForce(box2, polyStickyCoef, leapfrog);
	
	PolygonForce boxLPolyForce(boxL, polyStickyCoef, leapfrog);
	PolygonForce boxRPolyForce(boxR, polyStickyCoef, leapfrog);
	PolygonForce boxTPolyForce(boxT, polyStickyCoef, leapfrog);
	PolygonForce boxBPolyForce(boxB, polyStickyCoef, leapfrog);
	
	//PolygonForce circlePolyForce(circle, 2.f, leapfrog);
	//PolygonForce circle2PolyForce(circle2, 2.0f, leapfrog);
	
	
    // Temps s'écoulant entre chaque frame
    float dt = 0.f;

	int i = 0;
	
	float pas = 0.001;
	
	bool open = false;

	bool done = false;
	
	/*
	 * 
	 * IHM
	 * 
	 */
	 
	 
	
	GLenum error;
	if(GLEW_OK != (error = glewInit())) {
			std::cerr << "Impossible d'initialiser GLEW: " << glewGetErrorString(error) << std::endl;
			return EXIT_FAILURE;
	}
	
	bool ihm = true;
	bool ihmForTom = true;
    
    bool is_lClicPressed = false;
    
    int uiWidth = 300;
	int uiHeight = 500;
	int detailsUIHeight = 170;
	int camUIHeight = 200;
	int viewUIHeight = 250;
	
	int mousex = 0;
	int mousey = 0;
	int uiScrollTest = 0;
	int detailsUIscrollArea = 0;
	int camUIscrollArea = 0;
	int viewUIscrollArea = 0;
	int closeScrollArea = 0;
	
	int toggle = 0;
	
	bool repulsiveIHM = true;
	//~ bool stickyIHM = true;
	bool brakeIHM = true;
	bool link = false;
	
	
	if (!imguiRenderGLInit("DroidSans.ttf")){
		fprintf(stderr, "Could not init GUI renderer.\n");
		exit(EXIT_FAILURE);
	}
	
	
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
        //~ stickyForce.apply(particleManager);
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
        
        
        // --- IMGUI ---
        
        if (ihmForTom==true){
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_DEPTH_TEST);
			
			SDL_GetMouseState(&mousex, &mousey);
			
			mousey = WINDOW_HEIGHT - mousey;
			imguiBeginFrame(mousex, mousey, is_lClicPressed, 0);        
			
			imguiBeginScrollArea("Forces", WINDOW_WIDTH - uiWidth, WINDOW_HEIGHT - (uiHeight+10), uiWidth, uiHeight, &uiScrollTest);
			imguiSeparatorLine();
			imguiSeparator();
			
			if(imguiButton("Afficher Interface")){
				ihm = !ihm;
			}
			
			if(ihm == true) {
				char lineBuffer[512];
				sprintf(lineBuffer, "Nb Particules %d", particleManager.getSize());
				imguiLabel(lineBuffer);
				imguiSeparator();
				
				if(imguiItem("Repulsive Force", repulsiveIHM)){
					repulsiveIHM = false;
					//~ stickyIHM = true;
					brakeIHM = true;
				}
				
				if(imguiItem("Brake Force", brakeIHM)){
					brakeIHM = false;
					repulsiveIHM = true;
					//~ stickyIHM = true;
					//~ std::cout << "test brake item" << std::endl;
				}
				
				//~ imguiLabel("Test Scroller");
				
				imguiSeparatorLine();
				
				
			
				if(repulsiveIHM == false){
					imguiLabel("Repulsive Force");
					
					
					if(imguiCheck("Lier les bornes", link, true)){
						link = !link;
					}
					
					float actualInf = repulsiveForce.m_fLInf;
					float actualSup = repulsiveForce.m_fLSup;
					
					imguiSlider("Repulsive KRep", &repulsiveForce.m_fKRep, 0.f, 2.f, 0.001f);
					imguiSlider("Repulsive KSticky", &repulsiveForce.m_fKSticky, 0.f, 2.f, 0.001f);
					imguiSlider("Repulsive LInf", &repulsiveForce.m_fLInf, 0.f, 0.5f, 0.001f);
					imguiSlider("Repulsive LSup", &repulsiveForce.m_fLSup, 0.f, 0.5f, 0.001f);
					
					float dInf = repulsiveForce.m_fLInf - actualInf;
					float dSup = repulsiveForce.m_fLSup - actualSup;
					
					if(link == true){
						repulsiveForce.m_fLInf += dSup;
						repulsiveForce.m_fLSup += dInf;
					}
					
					
				}
				
				if(brakeIHM == false){
					imguiLabel("Brake Force");
					
					imguiSlider("Brake V", &brakeForce.m_fV, 0.f, 1.f, 0.001f);
					imguiSlider("Brake L", &brakeForce.m_fL, 0.f, 0.8f, 0.001f);
					imguiSlider("Brake Amort", &brakeForce.m_fAmort, 0.0f, 0.01f, 0.0001f);
				}
				
				imguiSeparator();
				if(imguiButton("Ouvrir / Fermer la vanne (Spacebar)")){
					open = !open;
				}
				
				imguiSeparator();
				if(imguiButton("Reset ('c')")){
					particleManager.clean();
				}
				
			}
			
			imguiEndScrollArea();
			imguiEndFrame();
			
			imguiRenderGLDraw(WINDOW_WIDTH, WINDOW_HEIGHT);
			
			// Mise à jour de l'affichage
			SDL_GL_SwapBuffers();
							
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);

		}
		
		// Sauvegarde de la config
		std::fstream config;
		
        // Gestion des evenements
		SDL_Event e;
        while(wm.pollEvent(e)) {
			switch(e.type) {
				default:
					break;
					
				case SDL_MOUSEBUTTONDOWN:
					switch(e.button.button){
						case SDL_BUTTON_LEFT:
							is_lClicPressed = true;
							//~ std::cout << "pushed : " << is_lClicPressed << std::endl;
							break;
							
						default:
							break;
					}
					break;
												
				case SDL_MOUSEBUTTONUP:
					switch(e.button.button){
						case SDL_BUTTON_LEFT:
							is_lClicPressed = false;
							//~ std::cout << "released : " << is_lClicPressed << std::endl;
							break;
						
						default:
							break;
					}
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
							
						case SDLK_c:
							particleManager.clean();
							break;
							
						case SDLK_s:
							if (!config.is_open())
							{
								config.open ("config.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
								if (config.is_open())
								{
									config << constForce.m_force.y << "\n";
									config << repulsiveForce.m_fKRep << "\n";
									config << repulsiveForce.m_fKSticky << "\n";
									config << repulsiveForce.m_fLInf << "\n";
									config << repulsiveForce.m_fLSup << "\n";
									config << brakeForce.m_fV << "\n";
									config << brakeForce.m_fL << "\n";
									config << brakeForce.m_fAmort << "\n";
									//config.flush();
									std::cout << "Config written \n";
								} else {
									std::cout << "Unable to open config \n";
								}
								config.close();
							}
							break;
							
						case SDLK_l:
							std::string value;
							float f;
							config.open ("config.txt");
							if (config.is_open())
							{
								std::cout << "Config is open \n";
								getline (config,value);		
								std::istringstream(value) >> f; 
								constForce.m_force.y = f;
								getline (config,value);		
								std::istringstream(value) >> f; 
								repulsiveForce.m_fKRep = f;
								getline (config,value);
								std::istringstream(value) >> f; 
								repulsiveForce.m_fKSticky = f;
								getline (config,value);
								std::istringstream(value) >> f; 
								repulsiveForce.m_fLInf = f;
								getline (config,value);
								std::istringstream(value) >> f; 
								repulsiveForce.m_fLSup = f;
								getline (config,value);
								std::istringstream(value) >> f; 
								brakeForce.m_fV = f;
								getline (config,value);
								std::istringstream(value) >> f; 
								brakeForce.m_fL = f;
								getline (config,value);
								std::istringstream(value) >> f; 
								brakeForce.m_fAmort = f;
								std::cout << "Config loaded \n";
								config.close();
							}
							else std::cout << "Unable to open config \n";
							break;
							
						//~ case SDLK_r:
							//~ repulsiveForce.m_fK += pas;
							//~ std::cout << "rep K : " << repulsiveForce.m_fK << " - rep L : " << repulsiveForce.m_fL << std::endl;
							//~ break;
							//~ 
						//~ case SDLK_t:
							//~ repulsiveForce.m_fL += pas;
							//~ stickyForce.m_fLSup += pas;
							//~ stickyForce.m_fLInf += pas;
							//~ std::cout << "rep K : " << repulsiveForce.m_fK << " - rep L : " << repulsiveForce.m_fL << std::endl;
							//~ break;
							//~ 
						//~ case SDLK_b:
							//~ brakeForce.m_fV += pas;
							//~ std::cout << "brake K : " << brakeForce.m_fV << " - brake L : " << brakeForce.m_fL << std::endl;
							//~ break;
							//~ 
						//~ case SDLK_n:
							//~ brakeForce.m_fL += pas;
							//~ std::cout << "brake K : " << brakeForce.m_fV << " - brake L : " << brakeForce.m_fL << std::endl;
							//~ break;
							
						//~ case SDLK_p:
							//~ pas *= 2.0;
							//~ break;
							//~ 
						//~ case SDLK_i:
							//~ pas *= -1.0;
							//~ break;
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
	
	// imgui
    imguiRenderGLDestroy();

	return EXIT_SUCCESS;
}
