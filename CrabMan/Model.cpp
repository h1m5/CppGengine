//
//  Model.c
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 16/01/2017.
//  Copyright © 2017 TriKomand. All rights reserved.
//

#include "Model.h"

void Model::transformToUnitCoordinates(aiNode *rootNode)
{
    double amin = std::numeric_limits<double>::max();
    double amax = std::numeric_limits<double>::min();
    glm::vec3 minDimension(amin, amin, amin);
    glm::vec3 maxDimension(amax, amax, amax);
    
    findObjectDimensions(rootNode, glm::mat4(), minDimension, maxDimension);
    std::cout << "minDimension: " << minDimension.x << ", " << minDimension.y << ", " <<minDimension.z << std::endl;
    std::cout << "maxDimension: " << maxDimension.x << ", " << maxDimension.y << ", " <<maxDimension.z << std::endl;
    
    float dist = max(maxDimension.x - minDimension.x, max(maxDimension.y - minDimension.y, maxDimension.z - minDimension.z));
    float sc = 1.0/dist;
    glm::vec3 center = (maxDimension - minDimension)/2.0f;
    glm::vec3 trans = -(maxDimension - center);
    
    auto transformation = glm::mat4();
    transformation = glm::scale(transformation, glm::vec3(sc,sc,sc));
    transformation = glm::translate(transformation, trans);
    
//    unitTransformation = new glm::mat4(transformation);
    unitScale = new float(sc);
    std::cout << "unitScale: " << *unitScale << std::endl;
//    unitTranslation = new glm::vec3(trans);
//    rootNode->mTransformation = Maths::glmMatrixToAIMatrix(transformation) * rootNode->mTransformation;
}

void Model::findObjectDimensions(aiNode *node, glm::mat4 transformation, glm::vec3 &minDimension, glm::vec3 &maxDimension)
{
    transformation *= Maths::aiMatrixToGLMMatrix(node->mTransformation);
    
    for(int ii=0; ii<node->mNumMeshes; ++ii){
        int start = meshes[ii]->indexOffset;
        int end = start + meshes[ii]->indexCount;
        for(int jj=start; jj<end; ++jj)
        {
            int ind = m_indices[ii] * 3;
            glm::vec4 vec(m_vertices[ind], m_vertices[ind+1], m_vertices[ind+2], 1.0);
            vec = transformation * vec;
            
            if(vec.x < minDimension.x)
                minDimension.x = vec.x;
            if(vec.y < minDimension.y)
                minDimension.y = vec.y;
            if(vec.z < minDimension.z)
                minDimension.z = vec.z;
            if(vec.x > maxDimension.x)
                maxDimension.x = vec.x;
            if(vec.y > maxDimension.y)
                maxDimension.y = vec.y;
            if(vec.z > maxDimension.z)
                maxDimension.z = vec.z;
        }
    }
    
    for(int i=0; i<node->mNumChildren; ++i)
        findObjectDimensions(&(*node->mChildren[i]), transformation, minDimension, maxDimension);
}
