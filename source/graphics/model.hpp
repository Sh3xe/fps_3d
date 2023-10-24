#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "vvtypes.hpp"
#include "mesh.hpp"
#include "texture2d.hpp"

#include <string>
#include <map>

class Model
{
public:
	friend class Renderer;

	Model();
	Model( const std::string &path );
	~Model();

	bool load_from_file(const std::string &path);

	inline operator bool() const { return m_valid; }

private:
	void process_node( aiNode *node, const aiScene *scene );
	void process_mesh( aiMesh *mesh, const aiScene *scene );
	std::vector< NamedTexture* > load_material_textures( aiMaterial *material, const aiScene *, aiTextureType type );

	const std::string get_type_as_string(aiTextureType type);

	std::string m_directory;
	std::vector<Mesh> m_meshes;
	std::map<std::string, NamedTexture> m_loaded_textures;
	bool m_valid = false;
};