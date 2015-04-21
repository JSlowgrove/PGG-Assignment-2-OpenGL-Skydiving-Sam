#include "ParticleEffect.h"

/**************************************************************************************************************/

/*Constructs a ParticleEffect Object.*/
ParticleEffect::ParticleEffect(std::string objectName, std::unordered_map<std::string, Object*> &objects,
	std::unordered_map<std::string, Shader*> &shaders, std::string vertexShaderName, 
	std::string fragmentShaderName, glm::vec3 emitter, bool emit)
{
	/*initialize random seed: */
	srand((unsigned int)time(NULL));

	/*store the variables*/
	this->objectName = objectName;
	this->vertexShaderName = vertexShaderName;
	this->fragmentShaderName = fragmentShaderName;
	this->emitter = emitter;

	/*initialise the move speed*/
	moveSpeed = 1.0f;

	/*set the value of emit*/
	this->emit = emit;

	/*generate the new particles*/
	makeNewParticles(objects, shaders);
}

/**************************************************************************************************************/

/*Destructs a ParticleEffect Object.*/
ParticleEffect::~ParticleEffect()
{
}

/**************************************************************************************************************/

/*update the ParticleEffect*/
void ParticleEffect::update(float dt)
{
	/*update the particles*/
	for (auto particle : particles)
	{
		particle->update(dt);
	}

	/*if the particle should emit*/
	if (emit)
	{
		/*while the number of particles is greater than the max number of particles.*/
		while (particles.size() > MAX_NUMBER_OF_PARTICLES)
		{
			/*erase the oldest particle*/
			particles.erase(particles.begin());
		}
	}
	else
	{
		/*make sure there is at least 1 particle left*/
		if (particles.size() > 0)
		{
			/*erase the oldest particle*/
			particles.erase(particles.begin());
		}
	}
}

/**************************************************************************************************************/

/*draw the particle effects*/
void ParticleEffect::draw(glm::mat4 &viewMatrix, glm::mat4 &projMatrix)
{
	/*loop through all of the particles*/
	for (auto particle : particles)
	{
		/*draw the particle*/
		particle->draw(viewMatrix, projMatrix);
	}
}

/**************************************************************************************************************/

/*creates the new particles*/
void ParticleEffect::makeNewParticles(std::unordered_map<std::string, Object*> &objects,
	std::unordered_map<std::string, Shader*> &shaders)
{
	/*if the particle should emit*/
	if (emit)
	{
		/*get the number of particles to initialise between 0 and 4*/
		int numberOfParticles = (rand() % 5);

		/*loop for all of the particles to create*/
		for (int i = 0; i < numberOfParticles; i++)
		{
			/*get the scale of the particle, between 0.01f and 0.05f*/
			float scaleValue = (float)((rand() % 5) + 1) * 0.01f;

			/*get the direction of the particle between -1.5f and 1.5f*/
			glm::vec3 direction;
			direction.x = (float)((rand() % 300) + 1) * 0.01f;
			direction.y = (float)((rand() % 300) + 1) * 0.01f;
			direction.z = (float)((rand() % 300) + 1) * 0.01f;
			direction -= 1.5f;

			/*push a new particle to the vector*/
			particles.push_back(new Particle
				(new Model(vertexShaderName, fragmentShaderName, objectName, objects, shaders),
				scaleValue, direction, moveSpeed)
				);

			/*set the initial position to the emitter*/
			particles.back()->setPosition(emitter);
		}
	}
}

/**************************************************************************************************************/

/*Sets the emitter position.*/
void ParticleEffect::setEmitter(glm::vec3 emitter)
{
	/*set the emitter*/
	this->emitter = emitter;
}

/**************************************************************************************************************/

/*Sets the emit boolean.*/
void ParticleEffect::setEmitting(bool emit)
{
	/*set the value of emit*/
	this->emit = emit;
}