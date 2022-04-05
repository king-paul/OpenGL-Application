#pragma once
#include <glm.hpp>

using namespace glm;

struct Light
{
	vec3 m_direction;
	vec3 m_colour;
	vec3 m_ambientColour;
	float m_intensity;

	Light(vec3 direction = { 1, 0, 1 }, float intensity = 1) : m_direction(direction), m_intensity(intensity)
	{
		m_colour = { 1, 1, 1 };
		m_ambientColour = vec3();
	}

	Light(vec3 direction, vec3 colour = {1, 1, 1}, float intensity = 1) :
		m_direction(direction), m_colour(colour), m_intensity(intensity)
	{
		m_ambientColour = vec3();
	}

	Light(vec3 direction, vec3 colour, vec3 ambientColour = { 0, 0, 0 }, float intensity = 1) :
		m_direction(direction), m_colour(colour), m_ambientColour(ambientColour), m_intensity(intensity)
	{ }

};