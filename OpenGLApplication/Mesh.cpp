#include "Mesh.h"

Mesh::Mesh(std::string filename, ShaderProgram* shader, vec3 position, vec3 colour) : Object3d(shader, position)
{
	// allocates new space and creates ids
	glGenBuffers(1, &vertexBufferID);
	glGenBuffers(1, &indexBufferID);

	std::vector<Vertex> vertices;

	Assimp::Importer importer;
	// filename, flags for process that are happening
	const aiScene* scene = importer.ReadFile("Meshes/" + filename, 
		aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);

	//assume there's only one mesh and create a pointer to it
	aiMesh* meshPointer = *scene->mMeshes;

	// iterate through all of the vertices in the imported mesh
	for (unsigned int i = 0; i < meshPointer->mNumVertices; i++)
	{
		// pass position vertices from pointer into local vertex data strcutrue
		Vertex currentVertex;
		currentVertex.position.x = position.x + meshPointer->mVertices[i].x;
		currentVertex.position.y = position.y + meshPointer->mVertices[i].y;
		currentVertex.position.z = position.z + meshPointer->mVertices[i].z;
		
		currentVertex.colour = { 1, 0, 0 }; // colour vertex red		

		// get the normals of the vertices to use for lighting
		currentVertex.normal.x = meshPointer->mNormals[i].x;
		currentVertex.normal.y = meshPointer->mNormals[i].y;
		currentVertex.normal.z = meshPointer->mNormals[i].z;

		vertices.push_back(currentVertex); // add to vertex vector
	}

	// iterate through indicies is loaded mesh
	for (unsigned int i = 0; i < meshPointer->mNumFaces; i++)
	{
		// add indices in mesh to local indicies structure
		indices.push_back((unsigned short)meshPointer->mFaces[i].mIndices[0]);
		indices.push_back((unsigned short)meshPointer->mFaces[i].mIndices[1]);
		indices.push_back((unsigned short)meshPointer->mFaces[i].mIndices[2]);
	}

	SetData(sizeof(Vertex) * vertices.size(), vertices.data());
}

Mesh::Mesh(std::string filename, ShaderProgram* shader, vec3 position, Texture* texture) : Object3d(shader, position, texture)
{	
	// allocates new space and creates ids
	glGenBuffers(1, &vertexBufferID);
	glGenBuffers(1, &indexBufferID);

	std::vector<Vertex> vertices;	
	
	Assimp::Importer importer;
	// filename, flags for process that are happening
	const aiScene* scene = importer.ReadFile("Meshes/"+filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	
	//assume there's only one mesh and create a pointer to it
	aiMesh* meshPointer = *scene->mMeshes;

	// iterate through all of the vertices in the imported mesh
	for (unsigned int i = 0; i < meshPointer->mNumVertices; i++)
	{
		// pass position vertices from pointer into local vertex data strcutrue
		Vertex currentVertex;
		currentVertex.position.x = position.x + meshPointer->mVertices[i].x;
		currentVertex.position.y = position.y + meshPointer->mVertices[i].y;
		currentVertex.position.z = position.z + meshPointer->mVertices[i].z;

		if (meshPointer->HasTextureCoords(0))
		{
			currentVertex.uv.x = meshPointer->mTextureCoords[0][i].x;
			currentVertex.uv.y = 1 - meshPointer->mTextureCoords[0][i].y;
		}

		// get the normals of the vertices to use for lighting
		currentVertex.normal.x = meshPointer->mNormals[i].x;
		currentVertex.normal.y = meshPointer->mNormals[i].y;
		currentVertex.normal.z = meshPointer->mNormals[i].z;

		vertices.push_back(currentVertex); // add to vertex vector
	}

	// iterate through indicies is loaded mesh
	for (unsigned int i = 0; i < meshPointer->mNumFaces; i++)
	{
		// add indices in mesh to local indicies structure
		indices.push_back((unsigned short)meshPointer->mFaces[i].mIndices[0]);
		indices.push_back((unsigned short)meshPointer->mFaces[i].mIndices[1]);
		indices.push_back((unsigned short)meshPointer->mFaces[i].mIndices[2]);
	}

	SetData(sizeof(Vertex) * vertices.size(), vertices.data());
}

Mesh::Mesh(std::string filename, ShaderProgram* shader, vec3 position, Texture* diffuse, Texture* normal, Texture* specular) :
	Object3d(shader, position, diffuse, normal, specular)
{
	// allocates new space and creates ids
	glGenBuffers(1, &vertexBufferID);
	glGenBuffers(1, &indexBufferID);

	std::vector<Vertex> vertices;

	Assimp::Importer importer;
	// filename, flags for process that are happening
	const aiScene* scene = importer.ReadFile("Meshes/" + filename, 
		aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);

	//assume there's only one mesh and create a pointer to it
	aiMesh* meshPointer = *scene->mMeshes;

	// iterate through all of the vertices in the imported mesh
	for (unsigned int i = 0; i < meshPointer->mNumVertices; i++)
	{
		// pass position vertices from pointer into local vertex data strcutrue
		Vertex currentVertex;
		currentVertex.position.x = position.x + meshPointer->mVertices[i].x;
		currentVertex.position.y = position.y + meshPointer->mVertices[i].y;
		currentVertex.position.z = position.z + meshPointer->mVertices[i].z;

		if (meshPointer->HasTextureCoords(0))
		{
			currentVertex.uv.x = meshPointer->mTextureCoords[0][i].x;
			currentVertex.uv.y = 1 - meshPointer->mTextureCoords[0][i].y;
		}

		// get the normals tangeants and bitangeants for the TBN matrix
		currentVertex.normal.x = meshPointer->mNormals[i].x;
		currentVertex.normal.y = meshPointer->mNormals[i].y;
		currentVertex.normal.z = meshPointer->mNormals[i].z;

		currentVertex.tangeant.x = meshPointer->mTangents[i].x;
		currentVertex.tangeant.y = meshPointer->mTangents[i].y;
		currentVertex.tangeant.z = meshPointer->mTangents[i].z;

		currentVertex.bitangeant.x = meshPointer->mBitangents[i].x;
		currentVertex.bitangeant.y = meshPointer->mBitangents[i].y;
		currentVertex.bitangeant.z = meshPointer->mBitangents[i].z;

		vertices.push_back(currentVertex); // add to vertex vector
	}

	// iterate through indicies is loaded mesh
	for (unsigned int i = 0; i < meshPointer->mNumFaces; i++)
	{
		// add indices in mesh to local indicies structure
		indices.push_back((unsigned short)meshPointer->mFaces[i].mIndices[0]);
		indices.push_back((unsigned short)meshPointer->mFaces[i].mIndices[1]);
		indices.push_back((unsigned short)meshPointer->mFaces[i].mIndices[2]);
	}

	SetData(sizeof(Vertex) * vertices.size(), vertices.data());
}

void Mesh::SetData(unsigned int bufferSize, const void* data)
{
	// Upload the vertices
	// GL_ARRAY_BUFFER = vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID); // tells opengl to create vertex attributes with with the ID
	// uploads data to whatever is bound
	// GL_STATIC_DRAW - 
	glBufferData(GL_ARRAY_BUFFER, bufferSize, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind the buffer after the data has been added

	// Upload the indices
	// GL_ELEMENT_ARRAY_BUFFER = index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// enable attributes in vertex shader
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);

	if (texDiffuse)
	{		
		texDiffuse->Bind(0);

		if (texNormal)
		{
			texDiffuse->Bind(1);

			if (texSpecular)
				texSpecular->Bind(2);
		}
	}

}

void Mesh::Draw()
{	
	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	// assign the arrtibute data to draw with
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangeant));
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangeant));

	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds vertex buffer

	shader->UseShader();

	// bind indices and then draw them
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_SHORT, 0); // draws the mesh on the screen
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}