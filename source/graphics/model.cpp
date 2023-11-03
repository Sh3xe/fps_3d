#include "model.hpp"
#include "core/logger.hpp"

//TODO: add exception ihandling in load_from_file so that I can just throw in process_...()

Model::Model()
{
	m_valid = false;
}

Model::Model( const std::string &path )
{
	m_valid = load_from_file(path);
}

Model::~Model()
{
	VV_TRACE("~Mesh");
}

bool Model::load_from_file(const std::string &path)
{
	Assimp::Importer importer {};

	importer.ReadFile( std::string{"../"} + path,
		aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs );

	const aiScene *scene = importer.GetScene();

	if( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
	{
		VV_ERROR("Cannot load model: ", std::string{"../"} + path);
		m_valid = false;
		return false;
	}

	m_directory = path.substr(0, path.find_last_of('/'));
	VV_DEBUG("Loading model: ", path, " in directory: ", m_directory);
	process_node( scene->mRootNode, scene );
	m_valid = true;
	return true;
}

void Model::process_node( aiNode *node, const aiScene *scene )
{
	for( size_t i = 0; i < node->mNumMeshes; ++i )
		process_mesh( scene->mMeshes[node->mMeshes[i]], scene);

	for( size_t i = 0; i < node->mNumChildren; ++i )
		process_node(node->mChildren[i], scene);
}

void Model::process_mesh( aiMesh *mesh, const aiScene *scene )
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<Ref<NamedTexture>> textures;

	if( !mesh->HasPositions() || !mesh->HasNormals() )
	{
		VV_WARN("Mesh do not have the required data, skipping ", mesh->mName.C_Str());
		m_valid = false;
		return;
	}

	// loading vertex data
	for( size_t i = 0; i < mesh->mNumVertices; ++i )
	{
		Vertex vertex;

		// positions
		vertex.px = mesh->mVertices[i].x;
		vertex.py = mesh->mVertices[i].y;
		vertex.pz = mesh->mVertices[i].z;

		// normals
		if( mesh->HasNormals() )
		{
			vertex.nx = mesh->mNormals[i].x;
			vertex.ny = mesh->mNormals[i].y;
			vertex.nz = mesh->mNormals[i].z;
		}

		// tangent && bitangent
		if( mesh->HasTangentsAndBitangents() )
		{
			vertex.tx = mesh->mTangents[i].x;
			vertex.ty = mesh->mTangents[i].y;
			vertex.tz = mesh->mTangents[i].z;
			vertex.btx = mesh->mBitangents[i].x;
			vertex.bty = mesh->mBitangents[i].y;
			vertex.btz = mesh->mBitangents[i].z;
		}

		// texture coordinates
		if( mesh->HasTextureCoords(0) )
		{
			vertex.tex = mesh->mTextureCoords[0][i].x;
			vertex.tey = mesh->mTextureCoords[0][i].y;
		}
		else 
		{
			VV_WARN("no texture coordinates, using (0,0)");
			vertex.tex = 0.0f;
			vertex.tey = 0.0f;
		}

		vertices.push_back(vertex);
	}

	// indices
	for( size_t i = 0; i < mesh->mNumFaces; ++i )
	{
		aiFace face = mesh->mFaces[i];
		for( size_t j = 0; j < face.mNumIndices; ++j )
			indices.push_back(face.mIndices[j]);
	}

	// materials
	aiMaterial *mat = scene->mMaterials[ mesh->mMaterialIndex ];
	auto diffuse_textures = load_material_textures(mat, scene, aiTextureType_DIFFUSE);
	auto specular_textures = load_material_textures(mat, scene, aiTextureType_SPECULAR);

	textures.insert( textures.end(), diffuse_textures.begin(), diffuse_textures.end());
	textures.insert( textures.end(), specular_textures.begin(), specular_textures.end());

	m_meshes.push_back( std::make_unique<Mesh>(vertices, indices, textures) );
}

std::vector<Ref<NamedTexture>> Model::load_material_textures( aiMaterial *material, const aiScene *scene, aiTextureType type )
{
	std::vector<Ref<NamedTexture>> textures;
	size_t tex_count = material->GetTextureCount(type);

	for(size_t i = 0; i < tex_count; ++i)
	{
		// get texture info
		aiString path;
		material->GetTexture(type, i, &path);
		std::string full_path = m_directory + "/" + path.C_Str();
		// VV_TRACE(full_path);
		
		// find the texture in memory
		auto it = m_loaded_textures.find(full_path);
		if( it != m_loaded_textures.end() )
		{
			// if the texture is already loaded, just use the loaded one
			textures.push_back( it->second );
		}
		else 
		{
			// else, load it into memory
			m_loaded_textures.insert( {full_path, std::make_shared<NamedTexture>()} );
			auto &tex = m_loaded_textures[full_path];
			tex->type = get_type_as_string(type);
			tex->texture.load_from_file(full_path);
			textures.push_back(tex);
		}
	}

	return textures;
}

const std::string Model::get_type_as_string(aiTextureType type)
{
	switch(type)
	{
	case aiTextureType_DIFFUSE:
		return "diffuse";
	case aiTextureType_SPECULAR:
		return "specular";
	default: return "unknown";
	}

	VV_DEBUG("WTF??");
	return "";
}