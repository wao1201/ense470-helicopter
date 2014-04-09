
/**
 * Helicopter_h 
 * @author Trevor Douglas
 *
 * @version
 *
 * @description  A class to represent a helicopter.  It will have basic helicopter functionality.
 */

#include "Helicopter.h"

/* Constructor
 */
Helicopter::Helicopter()
{

    //heliModel = osgDB::readNodeFile("./helicopter/Sikorsky/Sikorsky.osg");

    rotorSpin = 0;
}



osg::ref_ptr<osg::Node> Helicopter::getModel()
{
    return heliModel;
}


void Helicopter::heliSetup(std::string modelName)
{
    heliModel = osgDB::readNodeFile(modelName);

    //InfoVisitor infoVisitor;
    //infoVisitor.setPat(10, (osg::PositionAttitudeTransform *)heliTransform);
    //heliModel->accept( infoVisitor );
}


void Helicopter::FindMainRotorNode(const std::string& nodeName,
				   osg::ref_ptr<osg::PositionAttitudeTransform> transform )
{
	
    // Create a Visitor to find the node of the helicopter
    InfoVisitor infoVisitor(nodeName);
	
    mTransformModelCenter = new osg::MatrixTransform;

    //osg::Matrix m = mTransformModelCenter->getMatrix();
    //m = translation * m;
//	mTransformModelCenter->setMatrix( m );
	
	

    //osg::Matrix m = transform->getMatrix();

    heliModel->accept( infoVisitor );
	
    // Splice a MatrixTransform over the propeller's Group.
    std::pair<bool,osg::ref_ptr<osg::Node> > result = infoVisitor.GetNode();
    bool& found = result.first;
    if ( found )
    {
        std::cout << "Have node" << std::endl;
        // Try to cast it as a Group.
        // Insert our transform
        osg::ref_ptr<osg::Node>& node = result.second;
        if ( node->asGroup() != NULL )
        {
            osg::ref_ptr<osg::Group> group = node->asGroup();
            osg::ref_ptr<osg::Group> parent = group->getParent( 0 );
            parent->removeChild( group.get() );
            parent->addChild( transform.get() );
            transform->addChild( group.get() );
			
        }
    }
}


// Rotate one.
void
Helicopter::RotatePropeller1( osg::ref_ptr<osg::PositionAttitudeTransform> transform )
{
/*	const float radian = osg::DegreesToRadians( 10 );
	const osg::Vec3f v( 1.0f, 0.0f, 0.0f );
	osg::Matrix rotation;
	rotation.makeRotate( radian, v );
	osg::Matrix m = transform->getMatrix();
	m = rotation * m;  // rotate around matrix axis (local space)
	transform->setMatrix( m );*/
    rotorSpin += 10.0;
    transform->setAttitude(osg::Quat(osg::DegreesToRadians(rotorSpin),osg::Vec3f(0,0,1)));

}

void Helicopter::updatePosition()
{
    helicopterPosition.x() += helicopterSpeed.x();
    helicopterPosition.y() += helicopterSpeed.y();
    helicopterPosition.z() += helicopterSpeed.z();
}


/*
 * Update the forward speed of the helicopter (This could be slowing down too)
 */
void Helicopter::updateSpeed()
{
     // FIXME: get rid of magic numbers
     float x_tilt = helicopterOrientation.x_theta - -90;
     float y_tilt = helicopterOrientation.y_theta - 180;

     // clip to some reasonable range (FIXME: should be done in key handler)
     if (x_tilt > 10.0f)
	 x_tilt = 10.0f;
     if (x_tilt < -10.0f)
	 x_tilt = -10.0f;
     if (y_tilt > 10.0f)
	 y_tilt = 10.0f;
     if (y_tilt < -10.0f)
	 y_tilt = -10.0f;

     // x and y tilt are rotations about the  *helicopter's* x and y (primed) axes.
     // x_tilt produces velocity vy_prime, y_tilt produces vx_prime.
     float vx_prime = y_tilt*2.0f;
     float vy_prime = x_tilt*2.0f;

     float z_theta = osg::DegreesToRadians(helicopterOrientation.z_theta);
     helicopterSpeed.x() = vx_prime*cosf(z_theta)
         - vy_prime*sinf(z_theta);

     helicopterSpeed.y() = vx_prime * sinf(z_theta)
         + vy_prime * cosf(z_theta);
     
     // std::cout << "heli speed:"
     //           << vx_prime << ","
     //           << vy_prime << ";"
     //           << helicopterSpeed.x() << ","
     //           << helicopterSpeed.y() << std::endl;
 }

void Helicopter::tilt(float wx, float wy, float wz)
{
    // FIXME: should limit maximum tilt
    helicopterOrientation.x_theta += wx;
    helicopterOrientation.y_theta += wy;
    helicopterOrientation.z_theta += wz;
    // std::cout << "orientation:"
    //           << helicopterOrientation.x_theta << ","
    //           << helicopterOrientation.y_theta << ","
    //           << helicopterOrientation.z_theta << std::endl;
}

	
InfoVisitor::InfoVisitor(const std::string& nodeName)
{
    _level = 0;
    patLevel = 0;
    currentPatLevel = 0;
    setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN); 
    mNodeName = nodeName;
    mFoundNode = NULL;
}

void InfoVisitor::apply( osg::Node& node )
{
    if(node.getName() == mNodeName)
    {
        std::cout << "Got it at ID2" << std::endl;
        mFoundNode = &node;
    }
    else
    {
        // Keep searching.
        traverse( node );
    }
}

void InfoVisitor::apply( osg::Geode& geode )
{
//	std::cout << spaces() << "Found geode level- " << _level << geode.libraryName() << "::"<< geode.className() << std::endl;
    _level++;
	
    for ( unsigned int i=0; i<geode.getNumDrawables(); ++i )
    {
        osg::Drawable* drawable = geode.getDrawable(i);
//		std::cout << "Found Drawable level- "<< _level << spaces() << drawable->libraryName() << "::" << drawable->className() << std::endl;
    }
    traverse( geode );
    _level--;
}


// Return matching node.
std::pair<bool,osg::ref_ptr<osg::Node> > InfoVisitor::GetNode( void )
{
    if ( mFoundNode != NULL )
        return std::make_pair<bool,osg::ref_ptr<osg::Node> >( true, mFoundNode );
    else
        return std::make_pair<bool,osg::ref_ptr<osg::Node> >( false, new osg::Node );
}



/*
  void InfoVisitor::setPat(int patLevel, osg::PositionAttitudeTransform * pat)
  {
  this->patLevel = patLevel;
  this->pat = pat;

  }

*/
