#include "Mesh.h"

Mesh::Mesh(std::string filename, ShaderProgram* shader) : Shape3d(shader)
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
		currentVertex.position.x = meshPointer->mVertices[i].x;
		currentVertex.position.y = meshPointer->mVertices[i].y;
		currentVertex.position.z = meshPointer->mVertices[i].z;

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

	// Upload the vertices
	// GL_ARRAY_BUFFER = vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID); // tells opengl to create vertex attributes with with the ID
	// uploads data to whatever is bound
	// GL_STATIC_DRAW - 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW); 
	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind the buffer after the data has been added

	// Upload the indices
	// GL_ELEMENT_ARRAY_BUFFER = index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Draw()
{
	// enable attributes in vertex shader
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(3);

	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	// assign the arrtibute data to draw with
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds vertex buffer

	shader->UseShader();

	// bind indices and then draw them
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_SHORT, 0); // draws the mesh on the screen
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}