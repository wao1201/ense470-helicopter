#ifndef HELICOPTER_H
#define HELICOPTER_H

#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <iostream>
#include <utility>
#include "util.h"

class Helicopter
{
private:
    osg::ref_ptr<osg::Node> heliModel;
    osg::PositionAttitudeTransform * helicopterMainRotorPat;
    float rotorSpin;
    osg::ref_ptr<osg::MatrixTransform> mTransformModelCenter;  // to adjust center of 3D model if necessary
    osg::ref_ptr<osg::MatrixTransform> mTransform;
    osg::ref_ptr<osg::Group> mModelGroup;

public:
    Helicopter();
    void FindMainRotorNode( const std::string& nodeName, osg::ref_ptr<osg::PositionAttitudeTransform> transform );
    void RotatePropeller1( osg::ref_ptr<osg::PositionAttitudeTransform> transform );
    osg::ref_ptr<osg::Node> getModel();
    void heliSetup(std::string modelName);
    void updatePosition();
    void updateSpeed();
    void tilt(float wx, float wy, float wz);

    osg::Vec3 helicopterPosition;
    osg::Vec3 helicopterSpeed;
//    struct AngularSpeed	helicopterAngularSpeed;
    struct Orientation  helicopterOrientation;
};



class InfoVisitor : public osg::NodeVisitor
{
public:
    InfoVisitor(const std::string& nodeName);
	
    std::string spaces(){ return std::string(_level*2, ' '); }
	
    virtual void apply( osg::Node& node );
    virtual void apply( osg::Geode& geode );
    void setHelicopterPat(int patLevel, osg::PositionAttitudeTransform * pat);
    osg::PositionAttitudeTransform * getHelicopterPat();
    std::pair<bool,osg::ref_ptr<osg::Node> > GetNode( void );

protected:
    unsigned int _level;

private:
    int patLevel;
    int currentPatLevel;
    std::string	mNodeName;
    osg::Node*	mFoundNode;
};

#endif
