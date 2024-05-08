#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "defines.hpp"
#include "mesh.hpp"
#include "api/texture2d.hpp"

#include <string>
#include <map>
#include <memory>

class Model
{
public:
	friend class Renderer3D;

	Model();
	Model( const std::string &path );
	~Model();

	bool load_from_file(const std::string &path);

	inline bool is_valid() const { return m_valid; }

private:
	void process_node( aiNode *node, const aiScene *scene );
	void process_mesh( aiMesh *mesh, const aiScene *scene );
	std::vector<Ref<NamedTexture>> load_material_textures( aiMaterial *material, const aiScene *, aiTextureType type );

	const std::string get_type_as_string(aiTextureType type);

	std::string m_directory;
	std::vector<Unq<Mesh>> m_meshes;
	std::map<std::string, Ref<NamedTexture>> m_loaded_textures;
	bool m_valid = false;
};