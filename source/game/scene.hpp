#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "defines.hpp"
#include "graphics/model.hpp"
#include "graphics/api/cubemap_texture.hpp"

struct SceneModel
{
	Ref<Model> model;
	glm::mat4 transform;
};

struct Scene
{
	// Geometry
	// std::vector<GrassVolume> grass_volumes;
	// std::vector<WaterVolume> water_volumes;
	std::vector<SceneModel> models;

	// Sunlight information
	glm::vec3 sky_color;
	glm::vec3 sun_dir;
	float sky_color_intensity;

	CubemapTexture skybox_texture;


	static Ref<Scene> load_from_file( const std::string &path );
};