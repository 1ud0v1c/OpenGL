#include "particle.h"

Particle::Particle(GLuint programm,unsigned int maxParticles, glm::vec3 pos, glm::vec3 color, int cycle) {
	this->maxParticles = maxParticles;
	this->pos = pos;
	this->color = color;
	this->programm = programm;
	this->cycle = cycle;
	glUseProgram(programm);
	timeID = (glGetUniformLocation(programm, "time"));

}

Particle::Particle(Particle *p) {
	maxParticles = p->maxParticles;
	pos = p->pos;
	color = p->color;
	programm = p->programm;
	cycle = p->cycle;
}

int Particle::getCycle() {
	return cycle;
}
void Particle::setPosition(glm::vec3 pos){
	glUseProgram(programm);
/*	GLuint positionBuffer;
	GLuint loc =glGetUniformLocation(programm, "moveOffset");
	glUniform3f(loc,pos[0],pos[1],pos[2]);*/
	this->pos = pos;
	float offset [4*maxParticles];
	for(int i=0;i<4*maxParticles;i+=4) {
		offset [i] = pos[0];
		offset [i+1] = pos[1];
		offset [i+2] = pos[2];
		offset [i+3] = 0.1f;
	}
	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(offset), offset, GL_STATIC_DRAW);

	glUseProgram(0);
}

glm::vec3 Particle::sphereDirection(double theta, double phi) {
	float x,y,z;
	x = glm::cos(theta)*glm::cos(phi);
	y = glm::cos(phi)*glm::sin(theta);
	z = glm::sin(phi);
	return glm::vec3(x,y,z);
}

void Particle::makeObject() {
	const GLfloat g_vertex_buffer_data[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
	};
	float offset [4*maxParticles];
	for(int i=0;i<4*maxParticles;i+=4) {
		offset [i] = pos[0];
		offset [i+1] = pos[1];
		offset [i+2] = pos[2];
		offset [i+3] = 0.1f;
	}
	float colors [4*maxParticles];
	int indexColor =1;
	for(int i=0;i<4*maxParticles;i+=4) {
		colors[i] = color[0];
		colors[i+1] = color[1];
		colors[i+2] = color[2];
		colors[i+3] = 1;
		indexColor++;
	}
	float speed [maxParticles];
	for(int i=0;i<maxParticles;i++) speed[i] = (20);
	std::vector<float> directions;
	int nbBins = sqrt(maxParticles);
	for(int indexT = 0; indexT < 10; indexT++) {
		for(int indexP = 0;indexP < 10; indexP++) {
			double phi = -glm::pi<float>()/2 + indexP*glm::pi<float>()/(nbBins-1);
			double theta = 2*indexT*glm::pi<float>()/nbBins;
			glm::vec3 point = sphereDirection(theta,phi);
			directions.push_back(point[0]);
			directions.push_back(point[1]);
			directions.push_back(point[2]);
		}
	}
	GLuint billboard_vertex_buffer;
	glGenBuffers(1, &billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	// The VBO containing the positions and sizes of the particles
	particles_position_buffer;
	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(offset), offset, GL_STATIC_DRAW);
	// The VBO containing the colors of the particles
	GLuint particles_color_buffer;
	glGenBuffers(1, &particles_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(colors), colors, GL_STATIC_DRAW);
	GLuint particles_speed_buffer;
	glGenBuffers(1, &particles_speed_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_speed_buffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(speed), speed, GL_STATIC_DRAW);
	GLuint particles_direction_buffer;
	glGenBuffers(1, &particles_direction_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_direction_buffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*directions.size(), directions.data(), GL_STATIC_DRAW);
	unsigned int index[] = {0,1,2,2,3,0};
	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	GLint vertexIndex = glGetAttribLocation(programm, "position");
	glEnableVertexAttribArray(vertexIndex);
	glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	// 2nd attribute buffer : positions of particles' centers
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0 );
	// 3rd attribute buffer : particles' colors
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glVertexAttribPointer(2,4,GL_FLOAT, GL_FALSE,4*sizeof(float), (void*)0 );
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, particles_direction_buffer);
	glVertexAttribPointer(3,3,GL_FLOAT, GL_FALSE,3*sizeof(float), (void*)0 );
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, particles_speed_buffer);
	glVertexAttribPointer(4,1,GL_FLOAT, GL_FALSE,sizeof(float), (void*)0 );
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glBindVertexArray(0);
}

void Particle::draw() {
	glUseProgram(programm);
	glBindVertexArray(vao);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0,maxParticles);
	glBindVertexArray(0);
}

void Particle::update(float dt) {
	time+=dt;
	glUseProgram(programm);
	glUniform1f(timeID,time);
}
