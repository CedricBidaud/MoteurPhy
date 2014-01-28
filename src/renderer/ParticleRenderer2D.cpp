#include "ParticleRenderer2D.hpp"
#include "GLtools.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace imac3 {
/*
const GLchar* ParticleRenderer2D::VERTEX_SHADER =
"#version 330 core\n"
GL_STRINGIFY(
    layout(location = 0) in vec2 aVertexPosition;
	layout(location = 1) in vec2 aTexCoord;
	
    uniform vec2 uParticlePosition;
    uniform float uParticleScale;
	
	out vec2 vTexCoord;
	
    out vec2 vFragPosition;

    void main() {
        vFragPosition = aVertexPosition;
        vTexCoord = aTexCoord;
        
        gl_Position = vec4(uParticlePosition + uParticleScale * aVertexPosition, 0.f, 1.f);
    }
);

const GLchar* ParticleRenderer2D::FRAGMENT_SHADER =
"#version 330 core\n"
GL_STRINGIFY(
    in vec2 vFragPosition;
    in vec2 vTexCoord;
    
    uniform sampler2D texFramebuffer;

    out vec4 fFragColor;

    uniform vec3 uParticleColor;

    float computeAttenuation(float distance) {
        return 3.f * exp(-distance * distance * 9.f);
    }

    void main() {
        float distance = length(vFragPosition);
        float attenuation = computeAttenuation(distance);
        fFragColor = vec4(uParticleColor, attenuation);
        //~ fFragColor = texture(texFramebuffer, vTexCoord);
    }
);

const GLchar* ParticleRenderer2D::POLYGON_VERTEX_SHADER =
"#version 330 core\n"
GL_STRINGIFY(
    layout(location = 0) in vec2 aVertexPosition;

    void main() {
        gl_Position = vec4(aVertexPosition, 0.f, 1.f);
    }
);

const GLchar* ParticleRenderer2D::POLYGON_FRAGMENT_SHADER =
"#version 330 core\n"
GL_STRINGIFY(
    out vec3 fFragColor;

    uniform vec3 uPolygonColor;

    void main() {
        fFragColor = uPolygonColor;
    }
);


const GLchar* ParticleRenderer2D::QUAD_VERTEX_SHADER =
"#version 330 core\n"
GL_STRINGIFY(
    layout(location = 0) in vec2 aVertexPosition;
    layout(location = 1) in vec2 aTexCoord;

	out vec2 vTexCoord;

    void main() {
		vTexCoord = aTexCoord;
        gl_Position = vec4(aVertexPosition, 0.f, 1.f);
    }
);

const GLchar* ParticleRenderer2D::QUAD_FRAGMENT_SHADER =
"#version 330 core\n"
GL_STRINGIFY(
	in vec2 vTexCoord;

    out vec3 fFragColor;
    
    //~ uniform sampler2D texture;

    void main() {
        fFragColor = vec3(1.0, 0.0, 0.0);
        //~ fFragColor = texture(texture, vTexCoord);
    }
);
*/
/*
ParticleRenderer2D::ParticleRenderer2D(float massScale):
    m_ProgramID(buildProgram(VERTEX_SHADER, FRAGMENT_SHADER)),
    m_PolygonProgramID(buildProgram(POLYGON_VERTEX_SHADER, POLYGON_FRAGMENT_SHADER)),
    m_QuadProgramID(buildProgram(QUAD_VERTEX_SHADER, QUAD_FRAGMENT_SHADER)),
    m_fMassScale(massScale) {

    // RÃ©cuperation des uniforms
    m_uParticleColor = glGetUniformLocation(m_ProgramID, "uParticleColor");
    m_uParticlePosition = glGetUniformLocation(m_ProgramID, "uParticlePosition");
    m_uParticleScale = glGetUniformLocation(m_ProgramID, "uParticleScale");

    m_uPolygonColor = glGetUniformLocation(m_PolygonProgramID, "uPolygonColor");

    // CrÃ©ation du VBO
    glGenBuffers(1, &m_VBOID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);

    // Une particule est un carrÃ©
    GLfloat positions[] = {
        -1.f, -1.f,
         1.f, -1.f,
         1.f,  1.f,
        -1.f,  1.f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    // CrÃ©ation du VAO
    glGenVertexArrays(1, &m_VAOID);
    glBindVertexArray(m_VAOID);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenBuffers(1, &m_PolygonVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, m_PolygonVBOID);
    glGenVertexArrays(1, &m_PolygonVAOID);
    glBindVertexArray(m_PolygonVAOID);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
*/

// shaders écrits dans des fichiers externes
ParticleRenderer2D::ParticleRenderer2D(GLuint particleProgram, GLuint polyProgram, GLuint quadProgram, float massScale):
    m_ProgramID(particleProgram),
    m_PolygonProgramID(polyProgram),
    m_QuadProgramID(quadProgram),
    m_fMassScale(massScale) {

    // RÃ©cuperation des uniforms
    m_uParticleColor = glGetUniformLocation(m_ProgramID, "uParticleColor");
    m_uParticlePosition = glGetUniformLocation(m_ProgramID, "uParticlePosition");
    m_uParticleScale = glGetUniformLocation(m_ProgramID, "uParticleScale");

    m_uPolygonColor = glGetUniformLocation(m_PolygonProgramID, "uPolygonColor");
    
    m_uQuadTexture = glGetUniformLocation(m_QuadProgramID, "Texture");

    // CrÃ©ation du VBO
    glGenBuffers(1, &m_VBOID);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);

    // Une particule est un carrÃ©
    GLfloat positions[] = {
        -1.f, -1.f,
         1.f, -1.f,
         1.f,  1.f,
        -1.f,  1.f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    // CrÃ©ation du VAO
    glGenVertexArrays(1, &m_VAOID);
    glBindVertexArray(m_VAOID);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenBuffers(1, &m_PolygonVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, m_PolygonVBOID);
    glGenVertexArrays(1, &m_PolygonVAOID);
    glBindVertexArray(m_PolygonVAOID);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

ParticleRenderer2D::~ParticleRenderer2D() {
    glDeleteBuffers(1, &m_VBOID);
    glDeleteBuffers(1, &m_PolygonVBOID);
    glDeleteVertexArrays(1, &m_VAOID);
    glDeleteVertexArrays(1, &m_PolygonVAOID);
}

void ParticleRenderer2D::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void ParticleRenderer2D::drawParticles(
        uint32_t count,
        const glm::vec2* positionArray,
        const float* massArray,
        const glm::vec3* colorArray) {
    // Active la gestion de la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);

    glUseProgram(m_ProgramID);

    glBindVertexArray(m_VAOID);

    // Dessine chacune des particules
    for(uint32_t i = 0; i < count; ++i) {
        glUniform3fv(m_uParticleColor, 1, glm::value_ptr(colorArray[i]));
        glUniform2fv(m_uParticlePosition, 1, glm::value_ptr(positionArray[i]));
        glUniform1f(m_uParticleScale, m_fMassScale * massArray[i]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    glBindVertexArray(0);

    glDisable(GL_BLEND);
}

void ParticleRenderer2D::drawPolygon(uint32_t count,
                 const glm::vec2* position,
                 const glm::vec3& color,
                 float lineWidth) {
    glBindBuffer(GL_ARRAY_BUFFER, m_PolygonVBOID);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(position[0]), position, GL_DYNAMIC_DRAW);

    glDisable(GL_DEPTH_TEST);

    glLineWidth(lineWidth);

    glUseProgram(m_PolygonProgramID);

    glBindVertexArray(m_PolygonVAOID);

    glUniform3fv(m_uPolygonColor, 1, glm::value_ptr(color));
    glDrawArrays(GL_LINE_LOOP, 0, count);

    glBindVertexArray(0);
}

void ParticleRenderer2D::drawQuad(GLuint vao, GLuint framebuffer, int quadTriangleCount){
	glUseProgram(m_QuadProgramID);
	
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, framebuffer);
    
    glUniform1i(m_uQuadTexture, 0);
	
	glBindVertexArray(vao);
		
			glDrawElements(GL_TRIANGLES, quadTriangleCount*3, GL_UNSIGNED_INT, (void*)0); // seg fault
		
	glBindVertexArray(0);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
	
	//~ seg fault
}

}
