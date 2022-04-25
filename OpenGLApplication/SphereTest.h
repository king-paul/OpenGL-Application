#pragma once
#include "Object3d.h"

class SphereTest : public Object3d
{
public:
    SphereTest(float radius = 1.0f, int sectorCount = 36, int stackCount = 18, bool smooth = true);
	void Draw() override;

    void BuildVerticesSmooth();
    void BuildVerticesFlat();    

private:
    float m_radius;
    int m_sectorCount;  // longitude, # of slices
    int m_stackCount;   // latitude, # of stacks
    bool m_smooth;

    void BuildInterleavedVertices();
};

