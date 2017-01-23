//
//  maths.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 13/04/16.
//  Copyright © 2016 TriKomand. All rights reserved.
//

#ifndef maths_h
#define maths_h

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/perpendicular.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <list>
#include <assimp/postprocess.h>
#include <random>

static std::default_random_engine randEngine(time(0));

class Maths {
public:
    
    static glm::mat4 createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale)
    {
        glm::mat4 mMatrix = glm::mat4();
        mMatrix = glm::translate(mMatrix, translation);
        mMatrix = glm::rotate(mMatrix, rx, glm::vec3(1, 0, 0));
        mMatrix = glm::rotate(mMatrix, ry, glm::vec3(0, 1, 0));
        mMatrix = glm::rotate(mMatrix, rz, glm::vec3(0, 0, 1));
        mMatrix = glm::scale(mMatrix, glm::vec3(scale, scale, scale));
        
        return mMatrix;
    }
    
    static glm::vec3 interpolate(glm::vec3 x1, glm::vec3 x2, float dt)
    {
        glm::vec3 diff = x2 - x1;
        return x1 + (dt * diff);
    }
    
    static float interpolate(float x1, float x2, float dt)
    {
        float diff = x2 - x1;
        return x1 + (dt * diff);
    }
    
    static glm::vec2 resultant(glm::vec2 v1, glm::vec2 v2)
    {
//        float xs = v1.x + v2.x;
//        float ys = v1.y + v2.y;
//        return sqrt(xs*xs + ys*ys);
        return v1 + v2;
    }
    
    static glm::vec2 resolve(float v, glm::vec2 x1, glm::vec2 x2)
    {
        glm::vec2 resolution;
        float dot = glm::dot(x1, x2);
        float theta = glm::acos(dot);
        resolution.x = v * dot;
        resolution.y = v * glm::sin(theta);
        return resolution;
    }
    
    static void truncate(glm::vec3 &vec, float value)
    {
        vec.x = vec.x > value ? value : vec.x;
//        vec.y = vec.y > value ? value : vec.y;
        vec.z = vec.z > value ? value : vec.z;
    }
    
    static glm::mat4 aiMatrixToGLMMatrix(aiMatrix4x4 &mat4)
    {
        glm::mat4 mat;
        
//        mat[0].x = mat4.a1; mat[0].y = mat4.a2; mat[0].z = mat4.a3; mat[0].w = mat4.a4;
//        mat[1].x = mat4.b1; mat[1].y = mat4.b2; mat[1].z = mat4.b3; mat[1].w = mat4.b4;
//        mat[2].x = mat4.c1; mat[2].y = mat4.c2; mat[2].z = mat4.c3; mat[2].w = mat4.c4;
//        mat[3].x = mat4.d1; mat[3].y = mat4.d2; mat[3].z = mat4.d3; mat[3].w = mat4.d4;
        
        mat[0].x = mat4.a1; mat[0].y = mat4.b1; mat[0].z = mat4.c1; mat[0].w = mat4.d1;
        mat[1].x = mat4.a2; mat[1].y = mat4.b2; mat[1].z = mat4.c2; mat[1].w = mat4.d2;
        mat[2].x = mat4.a3; mat[2].y = mat4.b3; mat[2].z = mat4.c3; mat[2].w = mat4.d3;
        mat[3].x = mat4.a4; mat[3].y = mat4.b4; mat[3].z = mat4.c4; mat[3].w = mat4.d4;
        
        return mat;
    }
    
    static aiMatrix4x4 glmMatrixToAIMatrix(glm::mat4 &mat4)
    {
        aiMatrix4x4 mat;
        mat.a1 = mat4[0].x; mat.a2 = mat4[0].y; mat.a3 = mat4[0].z; mat.a4 = mat4[0].w;
        mat.b1 = mat4[1].x; mat.b2 = mat4[1].y; mat.b3 = mat4[1].z; mat.b4 = mat4[1].w;
        mat.c1 = mat4[2].x; mat.c2 = mat4[2].y; mat.c3 = mat4[2].z; mat.c4 = mat4[2].w;
        mat.d1 = mat4[3].x; mat.d2 = mat4[3].y; mat.d3 = mat4[3].z; mat.d4 = mat4[3].w;
        
        return mat;
    }
    
    static float randomClamped_f(float min = -1.0f, float max = 1)
    {
        std::uniform_real_distribution<float> floatDistribution(min, max);
        auto res = floatDistribution(randEngine);
        return res;
    }
    
    static float randomClamped(int min = 0, int max = 100)
    {
        std::uniform_real_distribution<int> intDistribution(min, max);
        auto res = intDistribution(randEngine);
        return res;
    }
    
    static glm::vec3 pointToWorldSpace(glm::vec3 target, glm::vec3 heading, glm::vec3 side, glm::vec3 position)
    {
        auto transformPoint = target;
        auto transformMatrix = glm::mat3();
        
        transformMatrix[0] = heading;
        transformMatrix[1] = side;
        transformMatrix[2] = position;
        
//        transformMatrix[0] = glm::vec3(heading.x, side.x, position.x);
//        transformMatrix[1] = glm::vec3(heading.y, side.y, position.y);
//        transformMatrix[2] = glm::vec3(heading.z, side.z, position.z);
        
        transformPoint = transformPoint * transformMatrix;
        return transformPoint;
    }
    
    static glm::vec3 pointToLocalSpace(glm::vec3 target, glm::vec3 heading, glm::vec3 side, glm::vec3 position)
    {
        return glm::vec3();
    }
    
    static bool lineIntersectionsCircle(glm::vec3 ahead1, glm::vec3 ahead2, glm::vec3 characterPosition, float radius, glm::vec3 center)
    {
        auto dist1 = glm::distance(center, ahead1);
        auto dist2 = glm::distance(center, ahead2);
        auto dist3 = glm::distance(center, characterPosition);
        return  dist1 <= radius ||  dist2 <= radius || dist3 <= radius;
    }

};

#endif /* maths_h */
