//
//  path.h
//  CrabMan
//
//  Created by Imhoisili Otokhagua on 22/01/2017.
//  Copyright © 2017 TriKomand. All rights reserved.
//

#ifndef path_h
#define path_h

#include "maths.h"

class Path
{
    std::list<glm::vec3> _points;
    
    std::list<glm::vec3>::iterator _curPoint;
    
    bool _looped;
public:
    
    Path():_looped(false) {}
    
    Path(int numPoints, float minX, float maxX, float minZ, float maxZ)
    {
        createRandomPath(numPoints, minX, minZ, maxX, maxZ);
        
        _curPoint = _points.begin();
    }
    
    glm::vec3 getCurrentPoint()const{return *_curPoint;}
    
    bool finished() { return !(_curPoint != _points.end());}
    
    void setStartPoint(){
        _curPoint = _points.begin();
    }
    
    void setNextPoint()
    {
        assert(_points.size() > 0);
        
        if(++_curPoint == _points.end())
        {
            if(_looped)
            {
                _curPoint = _points.begin();
            }
        }
    }
    
    std::list<glm::vec3> createRandomPath(int numPoints, float minX, float minZ, float maxX, float maxZ)
    {
        _points.clear();
        
        float midX = (minX + maxX) / 2.0f;
        float midZ = (minZ + maxZ) / 2.0f;
        
        float smaller = min(midX, midZ);
        
        float spacing = (M_PI * 2) / (float)numPoints;
        
        for(int i=0; i<numPoints; i++)
        {
            float radialDist1 = Maths::randomClamped_f(smaller, smaller*2.0f);
            float radialDist2 = Maths::randomClamped_f(smaller, smaller*2.0f);
            glm::vec3 temp(radialDist1, 0.0f, radialDist2);
            temp.x += midX; temp.z += midZ;
            
            _points.push_back(temp);
        }
        
        _curPoint = _points.begin();
        return _points;
    }
    
    void loopOn(){_looped = true;}
    void loopOff(){_looped = false;}
    
    void addPoint(float x, float y, float z){
        _points.push_back(glm::vec3(x,y,z));
    }
    
    void clear(){_points.clear();}
    
    std::list<glm::vec3> getPath()const{return _points;}
    
};

#endif /* path_h */
